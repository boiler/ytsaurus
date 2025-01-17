
# This file was generated by the build system used internally in the Yandex and called "ya"
# (https://github.com/yandex/yatool).
#
# Configuration files of ya build system usually named as ya.make. If ya.make file is presented
# at the  root of the repository, then this repository supports ya build. 
# 
# If the repository supports both CMake and ya build configuration, please modify both of them.
#
# If only CMake build configuration is supported then modify only CMake files and note that only
# simple modifications are allowed like adding source-files to targets or adding simple properties
# like target_include_directories. These modifications will be ported to original ya.make files
# by maintainers. Any complex modifications which can't be easily ported back to the ya build 
# system may be rejected.

find_package(linux-headers-generic REQUIRED)
add_library(server-lib-zookeeper_master)


target_compile_options(server-lib-zookeeper_master PRIVATE
  -Wdeprecated-this-capture
)

target_include_directories(server-lib-zookeeper_master PUBLIC
  ${PROJECT_BINARY_DIR}/yt
)

target_link_libraries(server-lib-zookeeper_master PUBLIC
  linux-headers-generic::linux-headers-generic
  contrib-libs-cxxsupp
  yutil
  yt-yt-core
  server-lib-hydra
)

target_sources(server-lib-zookeeper_master PRIVATE
  ${PROJECT_SOURCE_DIR}/yt/yt/server/lib/zookeeper_master/bootstrap.cpp
  ${PROJECT_SOURCE_DIR}/yt/yt/server/lib/zookeeper_master/zookeeper_manager.cpp
  ${PROJECT_SOURCE_DIR}/yt/yt/server/lib/zookeeper_master/zookeeper_shard.cpp
)






