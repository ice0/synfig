add_executable(bline-test bline.cpp)
target_include_directories(bline-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_link_libraries(bline-test PRIVATE synfig)
