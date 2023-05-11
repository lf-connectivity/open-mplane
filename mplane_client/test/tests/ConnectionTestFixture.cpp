// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#include "ConnectionTestFixture.h"

#include "Common.h"

#include <sstream>

#include <gflags/gflags.h>
#include <grpcpp/grpcpp.h>
#include <openssl/crypto.h>

DECLARE_string(serverHost);
DECLARE_int32(serverPort);
DECLARE_bool(insecure);
DECLARE_string(certPath);

namespace {
std::string hostAndPortToTarget(const std::string &host, const uint32_t port) {
  std::stringstream ss;
  ss << host << ":" << port;
  return ss.str();
}

/**
 * Use this to securely cleanse a string (e.g. one that holds a TLS key)
 */
void cleanseString(std::string &str) {
  OPENSSL_cleanse(const_cast<char *>(str.data()), str.size());
}

std::shared_ptr<grpc::ChannelCredentials> getCredentials() {
  if (FLAGS_insecure) {
    return grpc::InsecureChannelCredentials();
  } else {
    grpc::SslCredentialsOptions tlsOptions;
    tlsOptions.pem_root_certs = loadFile(FLAGS_certPath);
    auto output = grpc::SslCredentials(tlsOptions);
    cleanseString(tlsOptions.pem_root_certs);
    return output;
  }
}
} // namespace

int32_t ConnectionTest::maxSessionId_ = -1;

ConnectionTest::ConnectionTest()
    : client_(grpc::CreateChannel(
          hostAndPortToTarget(FLAGS_serverHost, FLAGS_serverPort),
          getCredentials())) {}

void ConnectionTest::checkSessionId(const uint32_t sessionId) {
  ASSERT_GT((int32_t)sessionId, maxSessionId_); // Force signed comparison
  maxSessionId_ = sessionId;
}
