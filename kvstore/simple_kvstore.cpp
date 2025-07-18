#include "simple_kvstore.hpp"

bool SimpleKvStore::Get(const GetRequest* req, GetResponse* res) {
    std::unique_lock guard(this->mutex_);
    // TODO (Part A, Steps 1 and 2): IMPLEMENT
    if (kv.find(req->key) == kv.end()) {
        return false;
    }
    res->value = kv[req->key];
    return true;
}

bool SimpleKvStore::Put(const PutRequest* req, PutResponse*) {
    std::unique_lock guard(this->mutex_);
    // TODO (Part A, Steps 1 and 2): IMPLEMENT
    kv[req->key] = req->value;
    return true;
}

bool SimpleKvStore::Append(const AppendRequest* req, AppendResponse*) {
    std::unique_lock guard(this->mutex_);
    // TODO (Part A, Steps 1 and 2): IMPLEMENT
    if (kv.find(req->key) == kv.end()) {
        kv[req->key] = req->value;
    } else {
        kv[req->key] += req->value;
    }
    return true;
}

bool SimpleKvStore::Delete(const DeleteRequest* req, DeleteResponse* res) {
    std::unique_lock guard(this->mutex_);
    // TODO (Part A, Steps 1 and 2): IMPLEMENT
    if (kv.find(req->key) == kv.end()) {
        return false;
    }
    res->value = kv[req->key];
    kv.erase(req->key);
    return true;
}

bool SimpleKvStore::MultiGet(const MultiGetRequest* req, MultiGetResponse* res) {
    std::unique_lock guard(this->mutex_);
    // TODO (Part A, Steps 1 and 2): IMPLEMENT
    for (const auto& key : req->keys) {
        if (kv.find(key) == kv.end()) {
            return false;
        }
        res->values.push_back(kv[key]);
    }
    return true;
}

bool SimpleKvStore::MultiPut(const MultiPutRequest* req, MultiPutResponse*) {
    std::unique_lock guard(this->mutex_);
    // TODO (Part A, Steps 1 and 2): IMPLEMENT
    if (req->keys.size() != req->values.size()) {
        return false;
    }

    for (int i = 0; i < req->keys.size(); i++) {
        kv[req->keys[i]] = req->values[i];
    }
    return true;
}

std::vector<std::string> SimpleKvStore::AllKeys() {
    std::unique_lock guard(this->mutex_);
    // TODO (Part A, Steps 1 and 2): IMPLEMENT
    std::vector<std::string> keys;
    for (const auto& key : kv) {
        keys.push_back(key.first);
    }
    return keys;
}