ORG 0x7c00
BITS 16

start:
    mov bx, 0
    mov ah, 0eh
    mov al, 'A'
    int 0x10

times 510 - ($ - $$) db 0 ; $means current line's address, while $$ means the first line 
dw 0xAA55 ; intel little endian 55AA
