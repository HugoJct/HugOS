CC=gcc
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -Isrc/include -std=gnu17 -g
LDFLAGS=-T link.ld -melf_i386

AS=nasm
ASFLAGS=-f elf -g

BUILD_DIR=build
SRC_DIR=src

S_SRC=$(wildcard $(SRC_DIR)/*.s)
S_OBJECTS=$(S_SRC:$(SRC_DIR)/%.s=$(BUILD_DIR)/%.o) 

C_SRC=$(wildcard $(SRC_DIR)/*.c)
C_OBJECTS=$(C_SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) 

all: iso/boot/kernel.elf os.iso

iso/boot/kernel.elf: $(S_OBJECTS) $(C_OBJECTS)
	ld $(LDFLAGS) $^ -o iso/boot/kernel.elf

os.iso: iso/boot/kernel.elf
	genisoimage -R                              \
		-b boot/grub/stage2_eltorito    \
		-no-emul-boot                   \
		-boot-load-size 4               \
		-A os                           \
		-input-charset utf8             \
		-quiet                          \
		-boot-info-table                \
		-o os.iso                       \
		iso

run: os.iso
	qemu-system-i386 -monitor stdio -cdrom os.iso -m 1G

debug: os.iso
	gdb --command=gdbcmd.txt

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s | $(BUILD_DIR)
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR):
	@mkdir -p build

clean:
	rm -rf *.o kernel.elf os.iso build/ iso/boot/kernel.elf
