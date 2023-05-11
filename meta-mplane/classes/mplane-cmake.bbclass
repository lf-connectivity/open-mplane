do_cmake() {
  cp ${WORKDIR}/CMakeLists.txt ${S}
}

addtask do_cmake after do_patch before do_configure

CXXFLAGS += "-DBUILD_IF_ORAN"
