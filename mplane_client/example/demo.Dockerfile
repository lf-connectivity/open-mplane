FROM  mplane/mplane-client-integrated-tester:latest

RUN apt update; \
    apt install --yes \
        python3 \
        python3-pip

RUN python3 -m pip install \
        flask \
        flask-socketio \
        protobuf \
        grpcio

COPY mplane_demo /mplane_demo
