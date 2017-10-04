add_executable(test-buffer-reclamation test_buffer_reclamation.cpp)
target_link_libraries(test-buffer-reclamation ${Boost_LIBRARIES} ${OpenCL_LIBRARIES})
