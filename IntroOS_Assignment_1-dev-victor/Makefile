CC=gcc
CFLAGS=-g -Wall

SRCDIR=src
INCDIR=include
LIBDIR=lib

OBJS = utils.o hash.o sha256.o print_tree.o compute_hashes.o hash_delivery.o
LOBJS = $(addprefix $(LIBDIR)/, $(OBJS))

all: merkle child_process

inter: CFLAGS += -D TEST_INTERMEDIATE
inter: merkle

merkle: $(SRCDIR)/merkle.c $(LIBDIR)/utils.o $(LIBDIR)/print_tree.o
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^

child_process: $(SRCDIR)/child_process.c $(LOBJS)
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^

$(LIBDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/%.h
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

t1:
	./merkle input/T1.txt 8

t2:
	./merkle input/T2.txt 16

t3:
	./merkle input/T3.txt 32

.PHONY: clean all t1 t2 t3

clean:
	rm -f merkle child_process compute_hashes hash_delivery utils $(LIBDIR)/child_process.o $(LIBDIR)/merkle.o $(LIBDIR)/compute_hashes.o  $(LIBDIR)/hash_delivery.o $(LIBDIR)/utils.o
	rm -rf output/ *.dSYM/
