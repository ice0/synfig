vcpkg_check_linkage(ONLY_DYNAMIC_LIBRARY)

vcpkg_download_distfile(ARCHIVE
    URLS "https://github.com/libxmlplusplus/libxmlplusplus/releases/download/2.42.2/libxml++-2.42.2.tar.xz"
    FILENAME "libxml++-2.42.2.tar.xz"
    SHA512 214da4c8120fedc96adf6ad965b65be9f4deb53d86f41667c236c52e1e3aace819fc61b096815879cc38aaf12ac77fbccb050088ce6bc3ff03030dcc81e4a8c9
)

vcpkg_extract_source_archive_ex(
    OUT_SOURCE_PATH SOURCE_PATH
    ARCHIVE ${ARCHIVE}
)

vcpkg_configure_meson(
    SOURCE_PATH ${SOURCE_PATH}
    OPTIONS
        -Dmsvc14x-parallel-installable=false
        -Dbuild-documentation=false
        -Dbuild-tests=false
        -Dbuild-examples=false
)

vcpkg_install_meson()
vcpkg_fixup_pkgconfig()
vcpkg_copy_pdbs()

file(INSTALL "${SOURCE_PATH}/COPYING" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}" RENAME copyright)
