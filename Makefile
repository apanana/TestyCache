CC = x86_64-w64-mingw32-gcc
CFLAGS  = -g -Wall -w -O2 -std=c99

AKOSIK = source/akosik/
ALEDGER = source/aledger/
APAN = source/apan/
BBLACK = source/bblack/
JCOSEL = source/jcosel/
JHEPWORTH = source/jhepworth/
ZZHONG = source/zzhong/

makeall:
	make tests/create_akosik
	make tests/create_aledger
	make tests/create_apan
	make tests/create_bblack
	make tests/create_jcosel
	make tests/create_jhepworth
	make tests/create_zzhong

test_all: test_akosik test_aledger test_apan test_bblack test_jcosel test_jhepworth test_zzhong
	# test_akosik test_aledger test_apan test_bblack test_jcosel test_jhepworth test_zzhong
	# test_akosik test_aledger test_apan test_jcosel test_jhepworth test_zzhong


clean_all:
	rm -rf tests/*

tests/create_akosik: source/test.c source/cachewrapper.c
	$(CC) -D AKOSIK -D key_t=key_type source/test.c source/cachewrapper.c $(AKOSIK)cache.c $(AKOSIK)lru.c $(CFLAGS) -o tests/create_akosik

test_akosik: tests/create_akosik
	./tests/create_akosik

clean_akosik:
	rm tests/create_akosik

tests/create_aledger: source/test.c
	$(CC) -D ALEDGER source/test.c source/cachewrapper.c $(ALEDGER)cache.c $(ALEDGER)dbLL.c $(ALEDGER)evict.c $(ALEDGER)node.c $(CFLAGS) -o tests/create_aledger

test_aledger: tests/create_aledger
	./tests/create_aledger

clean_aledger:
	rm tests/create_aledger

tests/create_apan: source/test.c
	$(CC) -D APAN source/test.c source/cachewrapper.c $(APAN)cache.c $(APAN)lru.c $(CFLAGS) -o tests/create_apan

test_apan: tests/create_apan
	./tests/create_apan

clean_apan:
	rm tests/create_apan

tests/create_bblack: source/test.c
	$(CC) -D BBLACK source/test.c source/cachewrapper.c $(BBLACK)hash_cache.c $(BBLACK)helper.c $(BBLACK)lru_replacement.c $(CFLAGS) -o tests/create_bblack

test_bblack: tests/create_bblack
	./tests/create_bblack

clean_bblack:
	rm tests/create_bblack

tests/create_jcosel: source/test.c
	$(CC) -D JCOSEL source/test.c source/cachewrapper.c $(JCOSEL)cache.c $(CFLAGS) -o tests/create_jcosel

test_jcosel: tests/create_jcosel
	./tests/create_jcosel

clean_jcosel:
	rm tests/create_jcosel

tests/create_jhepworth: source/test.c
	$(CC) -D JHEPWORTH source/test.c source/cachewrapper.c $(JHEPWORTH)cache.c $(JHEPWORTH)list.c $(JHEPWORTH)slabs.c $(JHEPWORTH)tools.c $(CFLAGS) -o tests/create_jhepworth

test_jhepworth: tests/create_jhepworth
	./tests/create_jhepworth

clean_jhepworth:
	rm tests/create_jhepworth

tests/create_zzhong: source/test.c
	$(CC) -D ZZHONG source/test.c source/cachewrapper.c $(ZZHONG)cache.c $(ZZHONG)hash_table.c $(ZZHONG)LRU.c $(CFLAGS) -o tests/create_zzhong

test_zzhong: tests/create_zzhong
	./tests/create_zzhong

clean_zzhong:
	rm tests/create_zzhong
