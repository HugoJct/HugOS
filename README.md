# Hachujeo_kernel

## Requirements

`sudo apt install qemu-system-x86 build-essential nasm genisoimage`

## Done

- [x] Bootloader
- [x] OS Compilation
- [x] Stack 
- [x] Calling C from assembly
- [x] C compilation
- [x] Segmentation
- [x] Interruptions
- [x] Framebuffer
  - [x] Writing text


## TODO

**Context switch**
- Paging
- Page frame allocator
- User mode

## Worklog

### 17/01/24

Validation du sujet et discussions des objectifs à atteindre

### 24/01/24

- documentation du code en l'état actuel
- listing des points techniques déjà implémentés et de ceux à faire en priorité
- documentation sur les fonctionnalités à commencer à implémenter pour la semaine suivante (paging, page frame allocator, user mode)

## Brainstorm

### Paging

Segmentation translates a logical address into a linear address. Paging translates these linear addresses onto the physical address space, and determines access rights and how the memory should be cached.

Paging is a technique we will use to enable virtual memory. That means that each process will get the impression that the available memory range is ``0x00000000 - 0xFFFFFFFF`` even though the actual size of the memory might be much less.

![Paging](res/images/paging.png)


#### Paging for X86

A page directory that can contain references to 1024 **page tables**, each of which can point to 1024 sections of physical memory called page frames. Each page frame is 4096 byte large.

All page directories, **page tables** and page frames need to be aligned on 4096 byte addresses. This makes it possible to address a **page directory**, **page tables** or **page frames** with just the highest 20 bits of a 32 bit address, since the lowest 12 need to be zero.

*The translation of linear addresses to physical addresses is described in the figure below*

## Terminologies

- **Logical Address or Virtual Address:** This is a deal that is generated through the CPU and used by a technique to get the right of entry to reminiscence. It is known as a logical or digital deal because it isn’t always a physical vicinity in memory but an opportunity for a connection with a place inside the device’s logical address location.
- **Logical Address Space or Virtual Address Space:** This is the set of all logical addresses generated via a software program. It is normally represented in phrases or bytes and is split into regular-duration pages in a paging scheme.
- **Physical Address:** This is a cope that corresponds to a bodily place in reminiscence. It is the actual cope with this that is available on the memory unit and is used by the memory controller to get admission to the reminiscence.
- **Physical Address Space:** This is the set of all bodily addresses that correspond to the logical addresses inside the way’s logical deal with place. It is usually represented in words or bytes and is cut up into fixed-size frames in a paging scheme.

## Ressources

- Modern Operating Systems - Andrew S. Tanenbaum
- The Little book About OS Developpement - Erik Helin & Adam Renberg : https://littleosbook.github.io
