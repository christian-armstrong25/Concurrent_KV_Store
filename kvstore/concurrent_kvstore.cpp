#include "concurrent_kvstore.hpp"

#include <iterator>
#include <optional>
#include <set>

bool ConcurrentKvStore::Get(const GetRequest* req, GetResponse* res) {
    std::shared_lock guard(store.bucket_mutexes[store.bucket(req->key)]);
    // TODO (Part A, Steps 4 and 5): IMPLEMENT
    if (store.getIfExists(store.bucket(req->key), req->key) == std::nullopt) {
        return false;
    }
    res->value = store.getIfExists(store.bucket(req->key), req->key)->value;
    return true;
}

bool ConcurrentKvStore::Put(const PutRequest* req, PutResponse*) {
    std::unique_lock guard(store.bucket_mutexes[store.bucket(req->key)]);
    // TODO (Part A, Steps 4 and 5): IMPLEMENT
    store.insertItem(store.bucket(req->key), req->key, req->value);
    return true;
}

bool ConcurrentKvStore::Append(const AppendRequest* req, AppendResponse*) {
    std::unique_lock guard(store.bucket_mutexes[store.bucket(req->key)]);
    // TODO (Part A, Steps 4 and 5): IMPLEMENT
    if (store.getIfExists(store.bucket(req->key), req->key) == std::nullopt) {
        store.insertItem(store.bucket(req->key), req->key, req->value);
    } else {
        std::string temp = store.getIfExists(store.bucket(req->key), req->key)->value;
        store.removeItem(store.bucket(req->key), req->key);
        store.insertItem(store.bucket(req->key), req->key, temp + req->value);
    }
    return true;
}

bool ConcurrentKvStore::Delete(const DeleteRequest* req, DeleteResponse* res) {
    std::unique_lock guard(store.bucket_mutexes[store.bucket(req->key)]);
    // TODO (Part A, Steps 4 and 5): IMPLEMENT
    if (store.getIfExists(store.bucket(req->key), req->key) == std::nullopt) {
        return false;
    }
    res->value = store.getIfExists(store.bucket(req->key), req->key)->value;
    store.removeItem(store.bucket(req->key), req->key);
    return true;
}

bool ConcurrentKvStore::MultiGet(const MultiGetRequest* req, MultiGetResponse* res) {
    std::set<int> buckets;
    for (const auto& key : req->keys) {
        buckets.insert(store.bucket(key));
    }

    for (const auto& bucket : buckets) {
        store.bucket_mutexes[bucket].lock();
    }

    // TODO (Part A, Steps 4 and 5): IMPLEMENT
    for (const auto& key : req->keys) {
        if (store.getIfExists(store.bucket(key), key) == std::nullopt) {
            return false;
        }
        res->values.push_back(store.getIfExists(store.bucket(key), key)->value);
    }

    for (const auto& bucket : buckets) {
        store.bucket_mutexes[bucket].unlock();
    }

    return true;
}

bool ConcurrentKvStore::MultiPut(const MultiPutRequest* req, MultiPutResponse*) {
    if (req->keys.size() != req->values.size()) {
        return false;
    }

    std::set<int> buckets;
    for (const auto& key : req->keys) {
        buckets.insert(store.bucket(key));
    }

    for (const auto& bucket : buckets) {
        store.bucket_mutexes[bucket].lock();
    }

    for (int i = 0; i < req->keys.size(); i++) {
        store.insertItem(store.bucket(req->keys[i]), req->keys[i], req->values[i]);
    }

    for (const auto& bucket : buckets) {
        store.bucket_mutexes[bucket].unlock();
    }

    return true;
}

std::vector<std::string> ConcurrentKvStore::AllKeys() {
    // TODO (Part A, Steps 4 and 5): IMPLEMENT
    std::vector<std::string> keys;
    for (const auto& bucket : store.buckets) {
        std::shared_lock guard(store.bucket_mutexes[&bucket - &store.buckets[0]]);
        for (const auto& item : bucket) {
            keys.push_back(item.key);
        }
    }
    return keys;
}
