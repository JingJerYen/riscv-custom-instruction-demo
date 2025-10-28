CC	:= /path/to/llvm-project/build/bin/clang-17
CFLAGS	:= --target=riscv32 -march=rv32imac_xstar_zve32x -O0
SPIKE	:= /path/to/riscv-isa-sim/build/spike
PK32	:= /path/to/riscv-pk/build32/pk

# === Files ===
SRC     := $(wildcard *.c)
OBJS    := $(SRC:.c=.o)
ASMS	:= $(SRC:.c=.s)
LLVMIRS	:= $(SRC:.c=.ll)
EXES	:= $(SRC:.c=)

# === Rules ===

all:	$(ASMS) $(OBJS)	$(LLVMIRS) $(EXES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.s: %.c
	$(CC) $(CFLAGS) -S $< -o $@

%.ll: %.c
	$(CC) $(CFLAGS) -S -emit-llvm $< -o $@

%: %.o
	$(CC) -march=rv32imac_zicsr_zve32x -mabi=ilp32 $< -o $@

run-%: %
	$(SPIKE) --isa=rv32imacv_xstar $(PK32) $<

clean:
	rm -f *.o *.s *.ll $(EXES)
