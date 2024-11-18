BITS 32

section .text
    ALIGN 4
    DD 0x1BADB002
    DD 0x00000000
    DD -(0x1BADB002 + 0x00000000)

global start
extern kernel_main

start:
	CLI
	MOV esp, stack_space
	PUSH ebx
	PUSH eax
	call kernel_main

section .bss
RESB 8192
stack_space: