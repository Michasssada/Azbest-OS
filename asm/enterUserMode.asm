[BITS 32]               ; Ensure we are in 32-bit mode
[GLOBAL enterUserMode]  ; Export function for C to call

enterUserMode:
    ; C passes parameters in registers:
    ; - userStackTop -> in `eax`
    ; - userEntryPoint -> in `ebx`

    mov ax, 0x23       ; Load User Data Segment (DPL=3)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov esp, eax       ; Set ESP to user stack pointer

    ; Prepare IRET stack frame
    push 0x23          ; User Data Segment (SS)
    push esp           ; User Stack Pointer (ESP)
    pushf              ; Push EFLAGS (interrupts enabled)
    push 0x1B          ; User Code Segment (CS)
    push ebx           ; User-space Entry Point (EIP)

    iret               ; Switch to Ring 3

