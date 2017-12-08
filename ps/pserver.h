#pragma once
#include <memory>
#include <vector>
#include <thread>
#include "brpc/server.h"
#include "kv.h"

namespace ps {
template<typename KEY, typename VAL>
class Pserver {
public:
  explicit Pserver(int id, int shard_count): _server_id(id) {
    for(size_t i=0; i < shard_count; ++i) {
      _shards.push_back(new KVstore<KEY, VAL>());
    }
    // start server thread
    for(size_t i=0; i < _shards.size(); ++i) {
      auto th = std::thread(PserverService);
      th.detach();
      _threads.push_back(std::move(th));
    }
  }

  ~Pserver() {
    for(size_t i=0; i < _shards.size(); ++i) {
      _threads[i].join()
    }
  }

private:
  bool PserverService() {}

private:
  int _server_id;
  std::vector<std::unique_ptr<KVstore<KEY, VAL>> > _shards;
  std::vector<std::thread> _threads;
};

}

