
CC = gcc
CFLAGS  = -w -O2 -std=c99

SYSHW3 = sysHW3/
HIO = Hash-it-Out/
HIO2 = hash_it_out/c_code/

all: syshw3 HIO HIO2 clean_obj

mytest.o: #test.c create_cache_wrapper.c
	$(CC) $(CFLAGS) -c test.c

clean_obj:
	rm *.o


syshw3: sysHW3.o mytest.o syshw3_wrapper.o
	$(CC) -o exe7 hash_cache.o helper.o lru_replacement.o test.o syshw3_wrapper.o

sysHW3.o: $(SYSHW3)hash_cache.c $(SYSHW3)helper.c $(SYSHW3)lru_replacement.c
	$(CC) $(CFLAGS) -c $(SYSHW3)hash_cache.c $(SYSHW3)helper.c $(SYSHW3)lru_replacement.c

syshw3_wrapper.o: create_cache_wrapper.c
	$(CC) $(CFLAGS) -o syshw3_wrapper.o -D=SYSHW3 -c create_cache_wrapper.c



HIO: HIO.o mytest.o HIO_wrapper.o
	$(CC) -o exe6 cache.o lru.o test.o HIO_wrapper.o

HIO.o: $(HIO)cache.c $(HIO)lru.c
	$(CC) $(CFLAGS) -c $(HIO)cache.c $(HIO)lru.c

HIO_wrapper.o: create_cache_wrapper.c
	$(CC) $(CFLAGS) -o HIO_wrapper.o -D=HIO -c create_cache_wrapper.c



HIO2: HIO2.o mytest.o HIO2_wrapper.o
	$(CC) -o exe5 cache.o dbLL.o evict.o node.o test.o HIO2_wrapper.o

HIO2.o: $(HIO2)cache.c $(HIO2)dbLL.c $(HIO2)evict.c  $(HIO2)node.c
	$(CC) $(CFLAGS) -c $(HIO2)cache.c $(HIO2)dbLL.c $(HIO2)evict.c  $(HIO2)node.c

HIO2_wrapper.o: create_cache_wrapper.c
	$(CC) $(CFLAGS) -o HIO2_wrapper.o -D=HIO2 -c create_cache_wrapper.c
