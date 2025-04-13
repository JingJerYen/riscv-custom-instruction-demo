CC	:= clang
CFLAGS	:= --target=riscv32 -march=rv32imac_xstar -O0
RVCC	:= /usr/bin/riscv64-elf-gcc
SPIKE	:= 
PK32	:=

# === Files ===
SRC     := $(wildcard *.c)
OBJS    := $(SRC:.c=.o)
ASMS	:= $(SRC:.c=.s)
LLVMIRS	:= $(SRC:.c=.ll)
EXES	:= $(SRC:.c=.exe)

# === Rules ===

all:	$(ASMS) $(OBJS)	$(LLVMIRS) $(EXES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.s: %.c
	$(CC) $(CFLAGS) -S $< -o $@

%.ll: %.c
	$(CC) $(CFLAGS) -S -emit-llvm $< -o $@

%.exe: %.o
	$(RVCC) -march=rv32imac -mabi=ilp32 $< -o $@		

#run_%: %.exe
#	$(SPIKE) --isa=rv32imac_xstar $(PK32) $<

clean:
	rm -f *.o *.s *.ll *.exe
