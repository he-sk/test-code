find_package(OpenCL REQUIRED)
find_package(BoostCompute CONFIG REQUIRED)

add_definitions("-DBOOST_COMPUTE_DEBUG_KERNEL_COMPILATION=1")

include_directories(
        ${BoostCompute_INCLUDE_DIRS})

add_subdirectory(buffer-allocation)
add_subdirectory(buffer-reclamation)
add_subdirectory(preferred-work-group-size)
#add_subdirectory(vector-index)
