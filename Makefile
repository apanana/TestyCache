
CC = gcc
CFLAGS  = -w -O2 -std=c99

SYSHW3 = sysHW3/

all: syshw3 clean_obj

mytest.o: #test.c create_cache_wrapper.c
	$(CC) $(CFLAGS) -c test.c

clean_obj:
	rm *.o

syshw3: sysHW3.o mytest.o syshw3_wrapper.o
	$(CC) -o exe7 hash_cache.o helper.o lru_replacement.o test.o create_cache_wrapper.o

sysHW3.o: $(SYSHW3)hash_cache.c $(SYSHW3)helper.c $(SYSHW3)lru_replacement.c
	$(CC) $(CFLAGS) -c $(SYSHW3)hash_cache.c $(SYSHW3)helper.c $(SYSHW3)lru_replacement.c

syshw3_wrapper.o: create_cache_wrapper.c
	$(CC) $(CFLAGS) -D=sysHW3 -c create_cache_wrapper.c
