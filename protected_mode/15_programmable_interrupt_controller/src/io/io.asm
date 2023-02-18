section .asm

global insb
global insw
global outb
global outw

insb:
    push ebp
    mov ebp, esp

    xor eax, eax
    mov edx, [ebp + 8] ; edx中写入端口号
    in al, dx ;从dx端口读取一个字节到al

    pop ebp
    ret

insw:
    push ebp
    mov ebp, esp

    xor eax, eax
    mov edx, [ebp + 8]
    in ax, dx

    pop ebp
    ret

outb:
    push ebp
    mov ebp, esp

    ; void outb(unsigned short port, unsigned char val);
    mov eax, [ebp + 12] ; val
    mov edx, [ebp + 8] ; port
    out dx, al

    pop ebp
    ret

outw:
    push ebp
    mov ebp, esp

    ; void outw(unsigned short port, unsigned short val);
    mov eax, [ebp + 12] ; val
    mov edx, [ebp + 8] ; port
    out dx, ax

    pop ebp
    ret



