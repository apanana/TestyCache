CC = gcc
CFLAGS  =  -g -Wall -w -O2 -std=c99

AKOSIK = source/akosik/
ALEDGER = source/aledger/
APAN = source/apan/
BBLACK = source/bblack/
JCOSEL = source/jcosel/
JHEPWORTH = source/jhepworth/
ZZHONG = source/zzhong/
# makeall:
# 	make create_akosik
# 	make create_aledger
# 	make create_apan
# 	make create_bblack
# 	make create_jcosel
# 	make create_jhepworth
# 	make create_zzhong

# test_all:
# 	test_akosik test_aledger test_apan test_bblack test_jcosel test_jhepworth test_zzhong

clean_all:
	$(RM) *.o

# create_akosik:

# test_akosik:

# clean_akosik:

# create_aledger:

# test_aledger:

# clean_aledger:

create_apan: source/test.c
	$(CC) source/test.c $(APAN)cache.c $(APAN)lru.c $(CFLAGS) -o create_apan

test_apan: create_apan
	./create_apan

clean_apan:
	rm create_apan

# HIO: HIO.o mytest.o HIO_wrapper.o
# 	$(CC) -o exe4 cache.o lru.o test.o HIO_wrapper.o $(LINK_FLAGS)

# HIO.o: $(HIO)cache.c $(HIO)lru.c
# 	$(CC) $(CFLAGS) -c $(HIO)cache.c $(HIO)lru.c

# mytest.o: #test.c create_cache_wrapper.c
# 	$(CC) $(CFLAGS) -c test.c

# HIO_wrapper.o: create_cache_wrapper.c
# 	$(CC) $(CFLAGS) -o HIO_wrapper.o -D=HIO -c create_cache_wrapper.c


# create_bblack:

# test_bblack:

# clean_bblack:

# create_jcosel:

# test_jcosel:

# clean_jcosel:

# create_jhepworth:

# test_jhepworth:

# clean_jhepworth:

# create_zzhong:

# test_zzhong:

# clean_zzhong:
