SUMMARY="Package group for fb-oru yang files"

inherit packagegroup

RDEPENDS_${PN} = " \
  yang-ietf \
  yang-oran \
  yang-startup \
  yang-config \
"
