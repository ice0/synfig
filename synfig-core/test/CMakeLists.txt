add_executable(bline-test bline2.cpp uniqueid.cpp)
target_include_directories(bline-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

set_target_properties(bline-test PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
