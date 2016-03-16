
#include <stdio.h>
#include "cachewrapper.h"


cache_t create_cache_wrapper(uint64_t maxmem, hash_func hash){
#ifdef AKOSIK
    printf("AKOSIK\n");
    return create_cache(maxmem,hash,NULL,NULL);
#elif defined ALEDGER
    printf("ALEDGER\n");
    return create_cache(maxmem);
#elif defined APAN
    printf("APAN\n");
    return create_cache(maxmem,hash);
#elif defined BBLACK
    printf("BBLACK\n");
    return create_cache(maxmem,hash);
#elif defined JCOSEL
    printf("JCOSEL\n");
    return create_cache(maxmem,hash);
#elif defined JHEPWORTH
    printf("JHEPWORTH\n");
    return create_cache(maxmem);
#elif defined ZZHONG
    printf("ZZHONG\n");
    return create_cache(maxmem,hash,NULL);
#endif
}
