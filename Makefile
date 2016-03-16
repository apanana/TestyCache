CC = gcc
CFLAGS  =  -g -Wall -w -O2 -std=c99

AKOSIK = source/akosik/
ALEDGER = source/aledger/
APAN = source/apan/
BBLACK = source/bblack/
JCOSEL = source/jcosel/
JHEPWORTH = source/jhepworth/
ZZHONG = source/zzhong/

makeall:
	make create_akosik
	make create_aledger
	make create_apan
	# make create_bblack
	make create_jcosel
	make create_jhepworth
	make create_zzhong

test_all: test_akosik test_aledger test_apan test_jcosel test_jhepworth test_zzhong
	# test_akosik test_aledger test_apan test_bblack test_jcosel test_jhepworth test_zzhong



clean_all:
	$(RM) *.o

create_akosik: source/test.c
	$(CC) source/test.c $(AKOSIK)cache.c $(AKOSIK)lru.c $(CFLAGS) -o create_akosik

test_akosik: create_akosik
	./create_akosik

clean_akosik:
	rm create_akosik

create_aledger: source/test.c
	$(CC) source/test.c $(ALEDGER)cache.c $(ALEDGER)dbLL.c $(ALEDGER)evict.c $(ALEDGER)node.c $(CFLAGS) -o create_aledger

test_aledger: create_aledger
	./create_aledger

clean_aledger:
	rm create_aledger

create_apan: source/test.c
	$(CC) source/test.c $(APAN)cache.c $(APAN)lru.c $(CFLAGS) -o create_apan

test_apan: create_apan
	./create_apan

clean_apan:
	rm create_apan

create_bblack: source/test.c
	$(CC) source/test.c $(BBLACK)hash_cache.c $(BBLACK)helper.c $(BBLACK)lru_replacement.c $(CFLAGS) -o create_bblack

test_bblack: create_bblack
	./create_bblack

clean_bblack:
	rm create_bblack

create_jcosel: source/test.c
	$(CC) source/test.c $(JCOSEL)cache.c $(CFLAGS) -o create_jcosel

test_jcosel: create_jcosel
	./create_jcosel

clean_jcosel:
	rm create_jcosel

create_jhepworth: source/test.c
	$(CC) source/test.c $(JHEPWORTH)cache.c $(JHEPWORTH)list.c $(JHEPWORTH)slabs.c $(JHEPWORTH)tools.c $(CFLAGS) -o create_jhepworth

test_jhepworth: create_jhepworth
	./create_jhepworth

clean_jhepworth:
	rm create_jhepworth

create_zzhong: source/test.c
	$(CC) source/test.c $(ZZHONG)cache.c $(ZZHONG)hash_table.c $(ZZHONG)LRU.c $(CFLAGS) -o create_zzhong

test_zzhong: create_zzhong
	./create_zzhong

clean_zzhong:
	rm create_zzhong
