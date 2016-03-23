CC = gcc#x86_64-w64-mingw32-gcc
CFLAGS  = -D NDEBUG -g -w -std=c99

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

test_all: test_akosik test_aledger test_apan test_bblack test_jcosel test_jhepworth test_zzhong run_all

run_all:
	python run_test.py

clean_all:
	rm -rf tests/*

tests/create_akosik: source/test.c source/cachewrapper.c
	$(CC) -D AKOSIK source/main.c $(AKOSIK)cache.c $(AKOSIK)lru.c $(CFLAGS) -o tests/create_akosik

test_akosik: tests/create_akosik
	python run_test.py ./tests/create_akosik

clean_akosik:
	rm tests/create_akosik

tests/create_aledger: source/test.c
	$(CC) -D ALEDGER source/main.c $(ALEDGER)cache.c $(ALEDGER)dbLL.c $(ALEDGER)evict.c $(ALEDGER)node.c $(CFLAGS) -o tests/create_aledger

test_aledger: tests/create_aledger
	python run_test.py  ./tests/create_aledger

clean_aledger:
	rm tests/create_aledger

tests/create_apan: source/test.c
	$(CC) -D APAN source/main.c $(APAN)cache.c $(APAN)lru.c $(CFLAGS) -o tests/create_apan

test_apan: tests/create_apan
	python run_test.py ./tests/create_apan

clean_apan:
	rm tests/create_apan

tests/create_bblack: source/test.c
	$(CC) -D BBLACK source/main.c $(BBLACK)hash_cache.c $(BBLACK)helper.c $(BBLACK)lru_replacement.c $(CFLAGS) -o tests/create_bblack

test_bblack: tests/create_bblack
	python run_test.py ./tests/create_bblack

clean_bblack:
	rm tests/create_bblack

tests/create_jcosel: source/test.c
	$(CC) -D JCOSEL source/main.c $(JCOSEL)cache.c $(CFLAGS) -o tests/create_jcosel -lm

test_jcosel: tests/create_jcosel
	python run_test.py ./tests/create_jcosel

clean_jcosel:
	rm tests/create_jcosel

tests/create_jhepworth: source/test.c
	$(CC) -D JHEPWORTH source/main.c $(JHEPWORTH)cache.c $(JHEPWORTH)list.c $(JHEPWORTH)slabs.c $(JHEPWORTH)tools.c $(CFLAGS) -o tests/create_jhepworth

test_jhepworth: tests/create_jhepworth
	python run_test.py ./tests/create_jhepworth

clean_jhepworth:
	rm tests/create_jhepworth

tests/create_zzhong: source/test.c
	$(CC) -D ZZHONG source/main.c $(ZZHONG)cache.c $(ZZHONG)hash_table.c $(ZZHONG)LRU.c $(CFLAGS) -o tests/create_zzhong

test_zzhong: tests/create_zzhong
	python run_test.py ./tests/create_zzhong

clean_zzhong:
	rm tests/create_zzhong
