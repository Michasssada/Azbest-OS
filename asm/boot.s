.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' for Multiboot */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum for validation */

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
.global isr_handler
isr_handler:
    pusha
    // Your ISR code here (e.g., log the interrupt)
    popa
    iret
_start:
	mov $stack_top, %esp
    
	call kernel_main
	cli
1:	hlt
	jmp 1b

.size _start, . - _start