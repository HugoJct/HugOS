# loader.s

## Constants

The `MAGIC_NUMBER` constant is required as stated by the [GNU GRUB multiboot specification](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html) for the following code to be bootable. It must be equal to 0X1BADB002 ("bad boot" which is counter intuitive).

## Sections 

The bss section is a portion of the data section which here holds only the stack.

The text section is the code section (which holds the code).

The `loader` label specifies where to enter the program (the execution jumps there from the linker script). There we initialize the stack pointer with the correct size, then we call the C code ufunction kmain. 
