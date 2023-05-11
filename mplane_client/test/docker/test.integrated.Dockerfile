FROM mplane/mplane-client-tester

# Generate keys for testing
WORKDIR /mplane_client
RUN mkdir -p build && \
    openssl genrsa -out build/server.key 2048 && \
    openssl req -new -x509 -sha256 -key build/server.key -out build/server.crt -days 3650 \
        -subj "/C=US/ST=NC/O=Facebook/CN=localhost"

# Patch the configuration file to make M-Plane client a background process
# (this is not done in mplane/mpclient-tester because the binary for
# mpc_client is not available when the container enters, unlike here)
COPY ./test/docker/patches/0001-Add-mplane-client-background-process.patch \
     /opt/dev/ntsim-ng/config/config.patch
RUN patch --directory /opt/dev/ntsim-ng/config/ --strip 4 config.json config.patch

# Copy M-Plane Client and M-Plane Tester code
COPY src /mplane_client/src
COPY test/rpc-client /mplane_client/test/rpc-client
COPY test/tests /mplane_client/test/tests

WORKDIR /mplane_client/utils
RUN ./build_mpclient.sh --parallel 2

# Run background processes; actual program will be run with `docker exec`
WORKDIR /mplane_client/build
CMD ["/opt/dev/ntsim-ng/ntsim-ng", "-w/opt/dev/ntsim-ng", "--supervisor"]
