SOURCES = $(wildcard kernel/*.cpp drivers/*.cpp util/*.cpp)
HEADERS = $(wildcard kernel/*.hpp drivers/*.hpp util/*.hpp)

# Nice syntax for file extension replacement
OBJ = ${SOURCES:.cpp=.o}

# Change this if your cross-compiler is somewhere else
CC = clang++ -target i386-pc-none-elf
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb
LD = ld.lld
# -g: Use debugging symbols in gcc
CFLAGS = -g -std=c++2a

# First rule is run by default
os-image.bin: boot/bootsect.bin kernel.bin
	cat $^ > os-image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^

run: os-image.bin
	qemu-system-i386 -fda os-image.bin

# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .cpp
%.o: %.cpp ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o

