find_package(OpenCL REQUIRED)
find_package(BoostCompute CONFIG REQUIRED)

include_directories(
        ${BoostCompute_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/include)

add_executable(test-buffer-allocation test_buffer_allocation.cpp)
target_link_libraries(test-buffer-allocation ${Boost_LIBRARIES} ${OpenCL_LIBRARIES})
