ORG 0x7c00
BITS 16

CODE_SEG equ gdt_code - gdt_start ;0x8
DATA_SEG equ gdt_data - gdt_start ;0x10

_start:
    jmp short start
    nop

times 33 db 0

start:
    jmp 0:step2

step2:
    cli
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov ax, 0x00
    mov ss, ax
    mov sp, 0x7c00
    sti

.load_protected:
    cli
    lgdt[gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:load32
    ; jmp $

gdt_start:
gdt_null:
    dd 0x0
    dd 0x0

; offset 0x8
gdt_code:
    dw 0xffff 
    dw 0x0
    db 0x
    db 0x9a
    db 11001111b
    db 0
gdt_data:
    dw 0xffff
    dw 0
    db 0
    db 0x92
    db 11001111b
    db 0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

[BITS 32]
load32:
    mov eax, 1 ; starting sector, 0 is boot sector
    mov ecx, 100 ; total number of sector to load
    mov edi, 0x0100000 ; load 100 sector to memory address 0x0100000: 1M
    call ata_lba_read
    jmp CODE_SEG:0x0100000

ata_lba_read: ; driver
    mov ebx, eax ; backup the LBA
    ; send the highest 8 bits of the lba to hard disk controller
    shr eax, 24
    or eax, 0xE0 ; select the master drive
    mov dx, 0x1F6
    out dx, al
    ; finished sending the highest 8 bits of the lba

    ; send the total sectors to read
    mov eax, ecx
    mov dx, 0x1F2
    out dx, al
    ; finished sending the total sectors to read

    ; send more bits of the LBA
    mov eax, ebx ; restore the backup LBA
    mov dx, 0x1F3
    out dx, al
    ; finished sending more bits of the LBA

    mov dx, 0x1F4
    mov eax, ebx ; restore the backup LBA
    shr eax, 8
    out dx, al
    ; finished sending more bits of the LBA

    ; send upper 16 bits of the LBA
    mov dx, 0x1F5
    mov eax, ebx ; Restore the backup LBA
    shr eax, 16
    out dx, al
    ; finished sending upper 16 bits of the LBA

    mov dx, 0x1f7
    mov al, 0x20
    out dx, al

    ; read all sectors into memory
.next_sector:
    push ecx

    ; checking if we need to read
.try_again:
    mov dx, 0x1f7
    in al, dx
    test al, 8
    jz .try_again

    ; we need to read 256 words at a time
    mov ecx, 256
    mov dx, 0x1F0
    rep insw ; read a word from port 0x1F0 and store in [es:di]
    pop ecx
    loop .next_sector
    ; end of reading sectors into memory
    ret

times 510 - ($ - $$) db 0 ; $means current line's address, while $$ means the first line 
dw 0xAA55 ; intel little endian 55AA