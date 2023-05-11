// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#include "MpclientImpl.h"

#include <fstream>
#include <sstream>
#include <string>

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <nc_client.h>

DEFINE_string(host, "localhost",
              "Host on which this process listens for instructions");
DEFINE_int32(port, 50051,
             "Port on which this process listens for instructions");
DEFINE_bool(insecure, false, "Use this flag to disable gRPC TLS encryption");
DEFINE_string(
    certPath, "server.crt",
    "Certificate chain path for gRPC TLS encryption (a.k.a. public key)");
DEFINE_string(privateKeyPath, "server.key",
              "Private key path for gRPC TLS encryption");

namespace {
std::string loadFile(const std::string &path) {
  std::ifstream inputStream(path);
  if (inputStream) {
    return std::string((std::istreambuf_iterator<char>(inputStream)),
                       (std::istreambuf_iterator<char>()));
  } else {
    throw std::runtime_error("File '" + path + "' does not exist");
  }
}

/**
 * Use this to securely cleanse a string (e.g. one that holds a TLS key)
 */
void cleanseString(std::string &str) {
  OPENSSL_cleanse(const_cast<char *>(str.data()), str.size());
}
} // namespace

int main(int argc, char **argv) {
  FLAGS_alsologtostderr = 1;
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  nc_client_init();

  std::stringstream serverAddr;
  serverAddr << FLAGS_host << ":" << FLAGS_port;
  LOG(INFO) << "Server listening on " << FLAGS_host << ":" << FLAGS_port;

  MpclientImpl mpclientService;

  grpc::ServerBuilder builder;
  grpc::SslServerCredentialsOptions tlsOptions;
  if (FLAGS_insecure) {
    builder.AddListeningPort(serverAddr.str(),
                             grpc::InsecureServerCredentials());
  } else {
    // Everything is constructed by references or pointers, so there is only
    // one copy the public and private keys
    tlsOptions.pem_key_cert_pairs.push_back(
        {loadFile(FLAGS_privateKeyPath), loadFile(FLAGS_certPath)});
    builder.AddListeningPort(serverAddr.str(),
                             grpc::SslServerCredentials(tlsOptions));

    // Cleanse strings used to handle keys
    cleanseString(tlsOptions.pem_key_cert_pairs.begin()->private_key);
    cleanseString(tlsOptions.pem_key_cert_pairs.begin()->cert_chain);
  }
  builder.RegisterService(&mpclientService);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();

  nc_client_destroy();
  return 0;
}
