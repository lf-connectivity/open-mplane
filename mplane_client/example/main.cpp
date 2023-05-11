// (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

#include "CommandProcessor.h"

#include <fstream>

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <google/protobuf/util/json_util.h>
#include <grpcpp/grpcpp.h>
#include <openssl/crypto.h>

// Default values match default values of mpclient-server
DEFINE_string(serverHost, "localhost", "Host to which this client connects");
DEFINE_int32(serverPort, 50051, "Port to which this client connects");
DEFINE_bool(insecure, false, "Use this flag to disable gRPC TLS encryption");
DEFINE_string(
    certPath, "server.crt",
    "Certificate chain path for gRPC TLS encryption (a.k.a. public key)");

// Default values are chosen to match the Dockerized testing environment
DEFINE_string(netconfHost, "",
              "Host at which the NETCONF server is; this setting overrides the "
              "command input");
DEFINE_int32(netconfPort, 830,
             "Port at which the NETCONF server is; this setting overrides the "
             "command input");
DEFINE_string(netconfUser, "",
              "Username for the NETCONF server; this setting overrides the "
              "command input");
DEFINE_string(
    netconfPassword, "",
    "Password for the NETCONF user; this setting overrides the command input");
DEFINE_string(netconfCallhomeHost, "",
              "Host at which the NETCONF server will call home; this setting "
              "overrides the command input");
DEFINE_int32(netconfCallhomePort, 4334,
             "Port at which the NETCONF server will call home; this setting "
             "overrides the command input");
DEFINE_string(netconfPublicKeyPath, "",
              "Path to the NETCONF auth public key; this setting overrides the "
              "command input");
DEFINE_string(netconfPrivateKeyPath, "",
              "Path to the NETCONF auth private key; this setting overrides "
              "the command input");

// Accept a JSON file (following the CommandSequence protobuf schema) as input
DEFINE_string(
    commands, "",
    "JSON file containing commands following CommandSequence protobuf schema");

namespace {
std::string hostAndPortToTarget(const std::string &host, const uint32_t port) {
  std::stringstream ss;
  ss << host << ":" << port;
  return ss.str();
}

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

int main(int argc, char **argv) {
  FLAGS_alsologtostderr = 1;
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  // Open JSON file
  if (FLAGS_commands == "") {
    throw std::runtime_error("Must pass a file to --commands");
  }
  std::ifstream inputStream(FLAGS_commands);
  std::string commandsStr;
  if (inputStream) {
    std::stringstream buffer;
    buffer << inputStream.rdbuf();
    commandsStr = buffer.str();
  } else {
    throw std::runtime_error("File '" + FLAGS_commands + "' does not exist");
  }

  // Parse commands
  mpclient::CommandSequence commands;
  google::protobuf::util::JsonParseOptions parseOptions;
  google::protobuf::util::JsonStringToMessage(commandsStr, &commands,
                                              parseOptions);
  const uint32_t numCommands = commands.commands().size();
  LOG(INFO) << "Parsed input, found " << numCommands << " commands";
  if (numCommands == 0) {
    LOG(WARNING) << "Is there a syntax or schema error in your commands file?";
  }

  CommandProcessor processor(grpc::CreateChannel(
      hostAndPortToTarget(FLAGS_serverHost, FLAGS_serverPort),
      getCredentials()));
  for (const auto &command : commands.commands()) {
    processor.processCommand(command);
  }
  processor.waitForNotifications();

  return 0;
}
