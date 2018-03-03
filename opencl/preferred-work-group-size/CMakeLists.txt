add_executable(preferred-work-group-size preferred-work-group-size.cpp)
target_link_libraries(preferred-work-group-size ${Boost_LIBRARIES} ${OpenCL_LIBRARIES})
