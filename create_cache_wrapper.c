#include "cachewrapper.h"
#ifdef sysHW3
#include "sysHW3/cache.h"
#endif
#include <stdio.h>
cache_t create_cache_wrapper(uint64_t maxmem, hash_func hash){
#ifdef sysHW3
    return create_cache(maxmem,hash);
#endif
}
