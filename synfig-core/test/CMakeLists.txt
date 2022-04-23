add_executable(bline-test2 bline2.cpp uniqueid.cpp)
target_include_directories(bline-test2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

set_target_properties(bline-test2 PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
target_compile_options(bline-test2 PRIVATE -O2)
#target_compile_options(bline-test2 PRIVATE -O2 -mno-fp-ret-in-387)

add_executable(bline-test bline.cpp)
target_include_directories(bline-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_link_libraries(bline-test PRIVATE synfig)
set_target_properties(bline-test PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
target_compile_options(bline-test PRIVATE -O2)
