do_install() {
  test "${TARGET_DIR}" = "" && bberror "Please define TARGET_DIR in recipe" && exit 1
  test "${SOURCE_DIR}" = "" && bberror "Please define SOURCE_DIR in recipe" && exit 1

  targetdir="${TARGET_DIR}"
  sourcedir="${SOURCE_DIR}"
  install -m 0755 -d ${targetdir}
  find $sourcedir -print0 | while IFS= read -r -d '' f
  do
      test -f "${f}" || continue
      filename="$(basename "$f")"
      dir="$(dirname "$f")"
      dir="${dir#"$sourcedir"}"
      test -d "${targetdir}/${dir}" || install -m 0755 -d "${targetdir}/${dir}"
      install -m 0755 "${f}" "${targetdir}/${dir}/${filename}"
  done
}
