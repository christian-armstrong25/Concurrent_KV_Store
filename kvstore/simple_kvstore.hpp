#ifndef SIMPLE_KVSTORE_HPP
#define SIMPLE_KVSTORE_HPP

#include <map>
#include <mutex>

#include "kvstore.hpp"
#include "net/server_commands.hpp"

class SimpleKvStore : public KvStore {
 public:
    SimpleKvStore() = default;
    ~SimpleKvStore() = default;

    std::mutex mutex_;

    bool Get(const GetRequest* req, GetResponse* res) override;
    bool Put(const PutRequest* req, PutResponse*) override;
    bool Append(const AppendRequest* req, AppendResponse*) override;
    bool Delete(const DeleteRequest* req, DeleteResponse* res) override;
    bool MultiGet(const MultiGetRequest* req, MultiGetResponse* res) override;
    bool MultiPut(const MultiPutRequest* req, MultiPutResponse*) override;

    std::vector<std::string> AllKeys() override;

 private:
    // TODO (Part A, Steps 1 and 2): Implement your internal key-value store here!
    std::map<std::string, std::string> kv;
};

#endif /* end of include guard */