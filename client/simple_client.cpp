#include "simple_client.hpp"

#include <stdio.h>
#include <string.h>

std::optional<std::string> SimpleClient::Get(const std::string& key) {
    std::shared_ptr<ServerConn> conn = connect_to_server(this->server_addr);
    if (!conn) {
        cerr_color(RED, "Failed to connect to KvServer at ", this->server_addr, '.');
        return std::nullopt;
    }

    GetRequest req{key};
    if (!conn->send_request(req)) return std::nullopt;

    std::optional<Response> res = conn->recv_response();
    if (!res) return std::nullopt;
    if (auto* get_res = std::get_if<GetResponse>(&*res)) {
        return get_res->value;
    } else if (auto* error_res = std::get_if<ErrorResponse>(&*res)) {
        cerr_color(RED, "could not find key: ", key);
        // cerr_color(RED, "Failed to Get value from server: ", error_res->msg);
    }

    return std::nullopt;
}

bool SimpleClient::Put(const std::string& key, const std::string& value) {
    std::shared_ptr<ServerConn> conn = connect_to_server(this->server_addr);
    if (!conn) {
        cerr_color(RED, "Failed to connect to KvServer at ", this->server_addr, '.');
        return false;
    }

    PutRequest req{key, value};
    if (!conn->send_request(req)) return false;

    std::optional<Response> res = conn->recv_response();
    if (!res) return false;
    if (auto* put_res = std::get_if<PutResponse>(&*res)) {
        return true;
    } else if (auto* error_res = std::get_if<ErrorResponse>(&*res)) {
        cerr_color(RED, "Failed to Put value to server: ", error_res->msg);
    }

    return false;
}

bool SimpleClient::Append(const std::string& key, const std::string& value) {
    std::shared_ptr<ServerConn> conn = connect_to_server(this->server_addr);
    if (!conn) {
        cerr_color(RED, "Failed to connect to KvServer at ", this->server_addr, '.');
        return false;
    }

    AppendRequest req{key, value};
    if (!conn->send_request(req)) return false;

    std::optional<Response> res = conn->recv_response();
    if (!res) return false;
    if (auto* append_res = std::get_if<AppendResponse>(&*res)) {
        return true;
    } else if (auto* error_res = std::get_if<ErrorResponse>(&*res)) {
        cerr_color(RED, "Failed to Append value to server: ", error_res->msg);
    }

    return false;
}

std::optional<std::string> SimpleClient::Delete(const std::string& key) {
    std::shared_ptr<ServerConn> conn = connect_to_server(this->server_addr);
    if (!conn) {
        cerr_color(RED, "Failed to connect to KvServer at ", this->server_addr, '.');
        return std::nullopt;
    }

    DeleteRequest req{key};
    if (!conn->send_request(req)) return std::nullopt;

    std::optional<Response> res = conn->recv_response();
    if (!res) return std::nullopt;
    if (auto* delete_res = std::get_if<DeleteResponse>(&*res)) {
        return delete_res->value;
    } else if (auto* error_res = std::get_if<ErrorResponse>(&*res)) {
        cerr_color(RED, "Failed to Delete value on server: ", error_res->msg);
    }

    return std::nullopt;
}

std::optional<std::vector<std::string>> SimpleClient::MultiGet(
    const std::vector<std::string>& keys) {
    std::shared_ptr<ServerConn> conn = connect_to_server(this->server_addr);
    if (!conn) {
        cerr_color(RED, "Failed to connect to KvServer at ", this->server_addr, '.');
        return std::nullopt;
    }

    MultiGetRequest req{keys};
    if (!conn->send_request(req)) return std::nullopt;

    std::optional<Response> res = conn->recv_response();
    if (!res) return std::nullopt;
    if (auto* multiget_res = std::get_if<MultiGetResponse>(&*res)) {
        return multiget_res->values;
    } else if (auto* error_res = std::get_if<ErrorResponse>(&*res)) {
        cerr_color(RED, "Failed to MultiGet values on server: ", error_res->msg);
    }

    return std::nullopt;
}

bool SimpleClient::MultiPut(const std::vector<std::string>& keys,
                            const std::vector<std::string>& values) {
    std::shared_ptr<ServerConn> conn = connect_to_server(this->server_addr);
    if (!conn) {
        cerr_color(RED, "Failed to connect to KvServer at ", this->server_addr, '.');
        return false;
    }

    MultiPutRequest req{keys, values};
    if (!conn->send_request(req)) return false;

    std::optional<Response> res = conn->recv_response();
    if (!res) return false;
    if (auto* multiput_res = std::get_if<MultiPutResponse>(&*res)) {
        return true;
    } else if (auto* error_res = std::get_if<ErrorResponse>(&*res)) {
        cerr_color(RED, "Failed to MultiPut values on server: ", error_res->msg);
    }

    return false;
}

// delete all posts of a user, but not the user itself
bool SimpleClient::GDPRDelete(const std::string& user) {
    std::string key = user + "_posts";
    auto userPostsOpt = Get(key);
    if (!userPostsOpt) {
        cerr_color(RED, user + " does not exist.");
        return false;
    }

    std::istringstream userPostsStream(userPostsOpt.value());
    std::string post;
    while (std::getline(userPostsStream, post, ',')) {
        post.erase(std::remove_if(post.begin(), post.end(), ::isspace),
                   post.end());  // remove whitespaces
        Delete(post);            // delete post
    }
    Put(key, "");                // dissociate user from posts
    return true;
}
