FROM  mplane/mplane-client-integrated-tester:latest

RUN apt update; \
    apt install --yes \
        python3 \
        python3-pip

RUN python3 -m pip install \
        flask \
        flask-socketio \
        protobuf \
        grpcio \
	grpcio-tools

COPY demo /mplane_demo

RUN python3 -m grpc_tools.protoc --experimental_allow_proto3_optional -I/mplane_client/src/if --python_out=/mplane_demo --grpc_python_out=/mplane_demo mpclient.proto
