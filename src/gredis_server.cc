#include <iostream>
#include <grpc++/grpc++.h>
#include "Redis.hpp"
#include "gredis.grpc.pb.h"

using namespace std;


class GredisImpl final : public gredis::Gredis::Service {
public:
	GredisImpl(Redis *redis) {
		this->redis = redis;
	}
  grpc::Status GetValue(grpc::ServerContext* context,
                        const gredis::GetValueRequest* request,
                        gredis::GetValueReply* reply) override {

		reply->set_value(this->redis->get(request->key()));
    return grpc::Status::OK;
  }

  grpc::Status SetValue(grpc::ServerContext* context,
                        const gredis::SetValueRequest* request,
                        gredis::SetValueReply* reply) override {

    this->redis->set(request->key(), request->value());
    return grpc::Status::OK;
  }

private:
	Redis *redis;
};

void RunServer() {
  std::string server_address("0.0.0.0:3000");
	Redis *redis = new Redis();
	redis->connect();
	GredisImpl *service = new GredisImpl(redis);

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();
  return 0;
}
