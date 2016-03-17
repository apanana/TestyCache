#ifdef AKOSIK
#include "akosik/cache.h
#elif defined  ALEDGER
#include "aledger/cache.h"
#elif defined  APAN
#include "apan/cache.h"
#elif defined  BBLACK
#include "bblack/cache.h"
#elif defined  JCOSEL
#include "jcosel/cache.h"
#elif defined  JHEPWORTH
#include "jhepworth/cache.h"
#elif defined  ZZHONG
#include "zzhong/cache.h"
#endif

cache_t create_cache_wrapper(uint64_t maxmem, hash_func hash);

void *cache_get_wrapper(cache_t cache,uint8_t *key, uint32_t *val_size);
