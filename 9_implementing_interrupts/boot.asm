ORG 0
BITS 16

_start:
    jmp short start
    nop

times 33 db 0

start:
    jmp 0x7c0:step2

handle_zero:
    mov ah, 0eh
    mov al, '0'
    mov bx, 0x00
    int 0x10
    iret

handle_one:
    mov ah, 0eh
    mov al, '1'
    int 0x10
    iret

step2:
    cli
    mov ax, 0x7c0
    mov ds, ax
    mov es, ax
    mov ax, 0x00
    mov ss, ax
    mov sp, 0x7c00
    sti

    ; int 0
    mov word[ss:0x00], handle_zero
    mov word[ss:0x02], 0x7c0
    mov word[ss:0x04], handle_one
    mov word[ss:0x06], 0x7c0

    ; int 0
    ; mov ax, 0x00
    ; div ax
    ; int 1

    mov si, message
    call print
    jmp $

print:
    mov bx, 0
.loop
    lodsb
    cmp al, 0
    je .done
    call print_char
    jmp .loop
.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10
    ret

message:
    db 'Hello World!', 0

times 510 - ($ - $$) db 0 ; $means current line's address, while $$ means the first line 
dw 0xAA55 ; intel little endian 55AA