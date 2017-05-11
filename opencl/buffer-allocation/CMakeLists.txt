add_executable(test-buffer-allocation test_buffer_allocation.cpp)
target_link_libraries(test-buffer-allocation ${Boost_LIBRARIES} ${OpenCL_LIBRARIES})
