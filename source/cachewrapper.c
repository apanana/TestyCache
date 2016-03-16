#include "cachewrapper.h"

#ifdef AKOSIK
#include "akosik/cache.h"
#elif defined  ALEDGER
#include "aledger/cache.h"
#elif defined  APAN
#include "apan/cache.h"
#elif defined  BBLACK
#include "bblack/hash_cache.h"
#elif defined  JCOSEL
#include "jcosel/cache.h"
#elif defined  JHEPWORTH
#include "jhepworth/cache.h"
#elif defined  ZZHONG
#include "zzhong/cache.h"
#endif

#include <stdio.h>
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
