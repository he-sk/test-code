find_package(Boost)

add_executable(test-vector-alignment test_vector_alignment.cpp)
target_link_libraries(test-vector-alignment ${Boost_LIBRARIES})
