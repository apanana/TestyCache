#include <stdio.h>
#include "cachewrapper.h"


cache_t create_cache_wrapper(uint64_t maxmem, hash_func hash){
#ifdef AKOSIK
    return create_cache(maxmem,hash,NULL,NULL);
#elif defined ALEDGER
    return create_cache(maxmem);
#elif defined APAN
    return create_cache(maxmem,hash);
#elif defined BBLACK
    return create_cache(maxmem,hash);
#elif defined JCOSEL
    return create_cache(maxmem,hash);
#elif defined JHEPWORTH
    return create_cache(maxmem);
#elif defined ZZHONG
    return create_cache(maxmem,hash,NULL);
#endif
}

void *cache_get_wrapper(cache_t cache, uint8_t *key, uint32_t *val_size){
#ifdef APAN
    return cache_get(cache,key);
#else
    return cache_get(cache,key,val_size);
#endif
}
