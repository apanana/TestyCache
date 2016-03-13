#include "cachewrapper.h"
#ifdef SYSHW3
#include "sysHW3/cache.h"
#elif defined  HIO
#include "Hash-it-Out/cache.h"
#elif defined  HIO2
#include "hash_it_out/c_code/cache.h"
#endif
#include <stdio.h>
cache_t create_cache_wrapper(uint64_t maxmem, hash_func hash){
#ifdef SYSHW3
    printf("syshw3\n");
    return create_cache(maxmem,hash);
#elif defined  HIO
    printf("HIO\n");
    return create_cache(maxmem,hash);
#elif defined  HIO2
    printf("HIO2\n");
    return create_cache(maxmem);
#endif
}
