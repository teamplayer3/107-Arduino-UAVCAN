

#include "ArduinoTLSFHeap.hpp"

std::vector<AllocInfo> ArduinoTLSFHeap::alloc_statistics;

void free_intern(void *const pointer)
{
    if (pointer != nullptr)
    {
        tlsf_free(ArduinoTLSFHeap::TLSF, pointer);
#if MONITOR_HEAP == true
        ArduinoTLSFHeap::alloc_statistics.push_back({false,
                                                     0,
                                                     pointer});
#endif
    }
}

void *allocate_intern(size_t const amount)
{

    void *ptr = tlsf_malloc(ArduinoTLSFHeap::TLSF, amount);
#if MONITOR_HEAP == true
    ArduinoTLSFHeap::alloc_statistics.push_back({true,
                                                 amount,
                                                 ptr});
#endif
    return ptr;
}