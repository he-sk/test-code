#include <boost/compute/core.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>

namespace bc = boost::compute;

int main(int ac, char** av) {

  if (ac != 3) {
    std::cerr << "Usage: " << av[0] << " [SIZE_IN_BYTES] [BUFFERS]" << std::endl;
    return EXIT_FAILURE;
  }

  auto size = std::stol(av[1]);
  std::cout << "Size: " << size << std::endl;
  auto buffers = std::stoi(av[2]);
  bc::device device = bc::system::default_device();
  bc::context context(device);
  bc::command_queue queue(context, device);
  std::cout << "Device: " << device.name() << std::endl;
  std::vector<bc::buffer> deviceBuffers(buffers);
  std::vector<bc::buffer> pinnedHostBuffers(buffers);
  std::vector<void*> pinnedHostPointers(buffers);

  std::cout << "Creating device buffers: " << std::flush;
  for (auto i = 0; i < buffers; ++i) {
    deviceBuffers[i] = bc::buffer(context, size, CL_MEM_READ_ONLY);
    std::cout << "." << std::flush;
  }
  std::cout << "OK" << std::endl;

  std::cout << "Creating pinned buffers: " << std::flush;
  for (auto i = 0; i < buffers; ++i) {
    pinnedHostBuffers[i] = bc::buffer(context, size, CL_MEM_READ_ONLY | CL_MEM_ALLOC_HOST_PTR);
    std::cout << "." << std::flush;
  }
  std::cout << "OK" << std::endl;

  std::cout << "Mapping host pointers  : " << std::flush;
  for (auto i = 0; i < buffers; ++i) {
    pinnedHostPointers[i] = queue.enqueue_map_buffer(pinnedHostBuffers[i], CL_MAP_WRITE_INVALIDATE_REGION, 0, size);
    queue.finish();
    std::cout << "." << std::flush;
  }
  std::cout << "OK" << std::endl;

  std::cout << "Writing data           : " << std::flush;
  auto data = std::unique_ptr<char[]>(new char[size]);
  for (auto i = 0; i < buffers; ++i) {
    queue.enqueue_write_buffer(deviceBuffers[i], 0, size, pinnedHostPointers[i]);
    queue.finish();
    std::cout << "." << std::flush;
  }
  std::cout << "OK" << std::endl;

  std::cout << "Unmapping host pointers: " << std::flush;
  for (auto i = 0; i < buffers; ++i) {
    queue.enqueue_unmap_buffer(pinnedHostBuffers[i], pinnedHostPointers[i]);
    queue.finish();
    std::cout << "." << std::flush;
  }
  std::cout << "OK" << std::endl;
  
  return EXIT_SUCCESS;
}
