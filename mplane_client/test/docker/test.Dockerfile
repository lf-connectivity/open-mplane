FROM o-ran-sc/nts-ng-o-ran-ru-fh:1.3.0

ENV DEBIAN_FRONTEND=noninteractive

# Do in one step to avoid committing apt lists to a layer
RUN apt-get clean && \
    apt-get update && \
    apt-get install -y --no-install-recommends \
        libssl-dev \
        libpcre3-dev \
        zlib1g-dev \
        pkg-config \
        wget \
        cmake \
        make \
        g++ \
        git \
        patch \
        ca-certificates \
        net-tools && \
    rm -rf /var/lib/apt/lists/*

RUN update-ca-certificates

# Remove system-wide SSH keys
RUN rm -rf /etc/ssh

# Download, build, and install dependencies
COPY utils /mplane_client/utils
WORKDIR /mplane_client/utils
RUN ./get_deps.sh --no-fwdproxy --dir /mplane_client && \
    ./build_deps.sh --no-netopeer2 --dir /mplane_client && \
    cd ../deps && \
    ls | grep "install" --invert | xargs rm -rf

COPY CMakeLists.txt /mplane_client/CMakeLists.txt
WORKDIR /mplane_client/utils

CMD ["/opt/dev/ntsim-ng/ntsim-ng", "-w/opt/dev/ntsim-ng", "--supervisor"]
