SUMMARY = "Base Utils for Open M-Plane images"

inherit packagegroup

debug_pkgs = "\
    devmem2 \
    evtest \
    gdb \
    python3-debugger \
    strace \
    stress-ng \
    stressapptest \
    vim \
    "

fs_pkgs = "\
    e2fsprogs \
    lsof \
    mtd-utils \
    procps \
    sysfsutils \
    util-linux \
    "

misc_pkgs = "\
    bash \
    bc \
    ckermit \
    coreutils \
    cronie \
    file \
    findutils \
    grep \
    i2c-tools \
    ldd \
    less \
    lrzsz \
    memtester \
    netcat-openbsd \
    openssh-sftp-server \
    pciutils \
    rsync \
    rsyslog \
    screen \
    sysstat \
    tzdata \
    usbutils \
    "

net_pkgs = "\
    chrony \
    chronyc \
    dhcp-client \
    dhcp-server \
    ethtool \
    iftop \
    iperf3 \
    iproute2 \
    iproute2-genl \
    iproute2-ifstat \
    iproute2-lnstat \
    iproute2-nstat \
    iproute2-ss \
    iproute2-tc \
    iptables \
    iputils \
    iw \
    mtr \
    net-snmp-server-snmpd \
    net-tools \
    resolvconf \
    rng-tools \
    sntp \
    tcpdump \
    traceroute \
    "

RRECOMMENDS_${PN} = "\
    ${debug_pkgs} \
    ${fs_pkgs} \
    ${misc_pkgs} \
    ${net_pkgs} \
    "
