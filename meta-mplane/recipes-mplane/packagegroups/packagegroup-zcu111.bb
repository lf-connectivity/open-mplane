SUMMARY="Package group for ZCU111 fb-oru"

inherit packagegroup

RDEPENDS_${PN} = " \
  app-startup-scripts \
  applications-common-rootfs \
  dot1agd-utils \
  mplane-oranrrh-process \
  netopeer2 \
  packagegroup-yang-files \
  yang-manager-server-scripts \
"
