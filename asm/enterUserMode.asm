; Set up the new segment registers
global enter
enter:
    mov ax, 0x1B        ; User Data Segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ax, 0x1A        ; User Code Segment
    mov cs, ax          ; Far jump to user space code

    ; Jump to user space code
    jmp 0x1A:0x100000   ; (Code segment and address of user code)
