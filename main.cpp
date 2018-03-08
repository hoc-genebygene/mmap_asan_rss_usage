#include <sys/resource.h>
#include <sys/mman.h>

#include <iostream>
#include <random>

size_t get_max_mem() {
    struct rusage r_usage;
    getrusage(RUSAGE_SELF,&r_usage);
    
    auto max_mem = r_usage.ru_maxrss;
    
#ifdef __linux__
    // on linux, the max ram consumption is in KB. On Mac, it is in bytes.
    max_mem *= 1024;
#endif
    
    return max_mem;
}

int main() {
    size_t mmap_size = 1024 * 1024 * 1024; // 1GB mmap
    
    char * mmap_data_ptr = reinterpret_cast<char *>(mmap(nullptr, mmap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
    
    
    std::random_device r;
    std::default_random_engine random_engine(r());
    std::uniform_int_distribution<int> uniform_dist(0, 255);
    
    for (int k = 0; k < mmap_size; ++k) {
        mmap_data_ptr[k] = uniform_dist(random_engine);
    }
    
    std::cout << get_max_mem() / (1024.0 * 1024.0) << " MB" << std::endl;
    std::cout << "Amplification factor: " << ((double)get_max_mem()) / mmap_size << std::endl;
}
