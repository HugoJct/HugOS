# gdt.s

The `GDT_init` function initializes 3 global descriptor table entries:
- An empty one 
- One for the data 
- One for the code

All of 3 spanning the whole address space available.

