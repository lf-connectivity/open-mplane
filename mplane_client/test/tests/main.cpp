// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#include <TestClient.h>

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <gtest/gtest.h>

// Default values match default values of mpclient-server
DEFINE_string(serverHost, "localhost", "Host to which this client connects");
DEFINE_int32(serverPort, 50051, "Port to which this client connects");
DEFINE_bool(insecure, false, "Use this flag to disable gRPC TLS encryption");
DEFINE_string(
    certPath, "server.crt",
    "Certificate chain path for gRPC TLS encryption (a.k.a. public key)");

// Default values are chosen to match the Dockerized testing environment
DEFINE_string(netconfHost, "0.0.0.0", "Host at which the NETCONF server is");
DEFINE_int32(netconfPort, 830, "Port at which the NETCONF server is");
DEFINE_string(netconfUser, "netconf", "Username for the NETCONF server");
DEFINE_string(netconfPassword, "netconf!", "Password for the NETCONF user");
DEFINE_int32(netconfCallhomePort, 6666,
             "Port at which the NETCONF server will call home");
DEFINE_string(netconfPublicKeyPath, "/home/netconf/.ssh/melacon.server.key.pub",
              "Path to the NETCONF auth public key");
DEFINE_string(netconfPrivateKeyPath, "/home/netconf/.ssh/melacon.server.key",
              "Path to the NETCONF auth private key");

int main(int argc, char **argv) {
  FLAGS_alsologtostderr = 1;
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
