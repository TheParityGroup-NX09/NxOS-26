bits 32
; grub needs to find 0x1BADB002 to start boot loading.
MBOOT_MAGIC    equ 0x1BADB002
MBOOT_FLAGS    equ 0x00000003
MBOOT_CHECKSUM equ -(MBOOT_MAGIC + MBOOT_FLAGS)

section .multiboot
align 4
    dd MBOOT_MAGIC
    dd MBOOT_FLAGS
    dd MBOOT_CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16384 ; 16 KiB of stack space (might change later)
stack_top:

section .text
global _start
extern kmain

_start:
    mov esp, stack_top

    push ebx
    push eax
    ; after video driver is done, add<call drVideoInit> (this will help with glitchess)
    call kmain

.hang:
    cli
    hlt
    jmp .hang