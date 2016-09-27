CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99 
CFLAGS_orig = -O0
CFLAGS_opt  = -O0
CFLAGS_hash = -O0
CFLAGS_memory = -O0
CFLAGS_thread = -O0

EXEC = phonebook_orig phonebook_opt phonebook_hash phonebook_memory phonebook_thread
all: $(EXEC)

SRCS_common = main.c

phonebook_orig: $(SRCS_common) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

phonebook_opt: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DIMPL="\"$@.h\"" -o $@ \
		-DOPT="1" \
		$(SRCS_common) $@.c

phonebook_hash: $(SRCS_common) phonebook_hash.c phonebook_hash.h
	$(CC) $(CFLAGS_common) $(CFLAGS_hash) \
		-DIMPL="\"$@.h\"" -o $@ \
		-DHASH="1"\
		$(SRCS_common) $@.c

phonebook_memory: $(SRCS_common) phonebook_memory.c phonebook_memory.h
	$(CC) $(CFLAGS_common) $(CFLAGS_memory) \
		-DIMPL="\"$@.h\"" -o $@ \
		-DPOOL="1"\
		$(SRCS_common) $@.c

phonebook_thread: $(SRCS_common) phonebook_thread.c phonebook_thread.h
	$(CC) $(CFLAGS_common) $(CFLAGS_thread) \
		-DIMPL="\"$@.h\"" -o $@ \
		-DTHREAD="1"\
		-pthread\
		$(SRCS_common) $@.c

run: $(EXEC)
	echo 3 | sudo tee /proc/sys/vm/drop_caches
	watch -d -t "./phonebook_hash && echo 3 | sudo tee /proc/sys/vm/drop_caches"

cache-test: $(EXEC)
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_orig
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_opt
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_hash
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_memory
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_thread


output.txt: cache-test calculate
	./calculate

plot: output.txt
	gnuplot scripts/runtime.gp

plot_slot: 
	gnuplot scripts/slot.gp

calculate: calculate.c
	$(CC) $(CFLAGS_common) $^ -o $@

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.* \
	      	calculate orig.txt opt.txt hash.txt output.txt runtime.png slot.txt thread.txt 

