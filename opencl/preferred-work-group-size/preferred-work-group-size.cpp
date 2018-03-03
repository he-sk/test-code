#include <boost/compute/core.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>

namespace bc = boost::compute;

int main(int ac, char** av) {

  if (ac != 4) {
    std::cerr << "Usage: " << av[0] << " [DEVICE] [SOURCE FILE] [KERNEL NAME]" << std::endl;
    return EXIT_FAILURE;
  }

  auto device_id = std::stoi(av[1]);
  if (device_id >= bc::system::device_count()) {
    std::cerr << "There are only " << bc::system::device_count() << " devices." << std::endl;
    return EXIT_FAILURE;
  }
  bc::device device = bc::system::devices()[device_id];
  std::cout << "Device: " << device.name() << std::endl;

  auto filename = av[2];
  bc::context context(device);
  auto program = bc::program::create_with_source_file(filename, context);
  try {
    program.build();
  } catch (...) {
    std::cerr << program.build_log() << std::endl;
    return EXIT_FAILURE;
  }

  auto kernelname = av[3];
  std::cout << "Kernel: " << kernelname << std::endl;
  auto kernel = program.create_kernel(kernelname);
  std::cout << "Kernel work group size: " << kernel.get_work_group_info<size_t>(device, CL_KERNEL_WORK_GROUP_SIZE) << std::endl;
  std::cout << "Preferred work group size multiple: " << kernel.get_work_group_info<size_t>(device, CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE) << std::endl;
  
  return EXIT_SUCCESS;
}
