#include <boost/compute/core.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>

namespace bc = boost::compute;

int main(int ac, char** av) {

  if (ac != 3) {
    std::cerr << "Usage: " << av[0] << " [SIZE_IN_BYTES] [LOOP]" << std::endl;
    return EXIT_FAILURE;
  }

  auto size = std::stol(av[1]);
  std::cout << "Size: " << size << std::endl;
  auto loop = std::stoi(av[2]);
  bc::device device = bc::system::default_device();
  bc::context context(device);
  bc::command_queue queue(context, device);
  std::cout << "Device: " << device.name() << std::endl;
  bc::buffer deviceBuffer;
  bc::buffer pinnedHostBuffer;
  void* pinnedHostPointer = nullptr;

  std::cout << "Repeatedly creating and releasing buffers: " << std::flush;
  for (auto i = 0; i < loop; ++i) {
    deviceBuffer = bc::buffer(context, size, CL_MEM_READ_ONLY);
    std::cout << "D" << std::flush;
    pinnedHostBuffer = bc::buffer(context, size, CL_MEM_READ_ONLY | CL_MEM_ALLOC_HOST_PTR);
    std::cout << "P" << std::flush;
    pinnedHostPointer = queue.enqueue_map_buffer(pinnedHostBuffer, CL_MAP_WRITE_INVALIDATE_REGION, 0, size);
    queue.finish();
    std::cout << "M" << std::flush;
    queue.enqueue_write_buffer(deviceBuffer, 0, size, pinnedHostPointer);
    std::cout << "W" << std::flush;
    queue.enqueue_unmap_buffer(pinnedHostBuffer, pinnedHostPointer);
    queue.finish();
    std::cout << "U " << std::flush;
  }
  std::cout << "OK" << std::endl;

  return EXIT_SUCCESS;
}
