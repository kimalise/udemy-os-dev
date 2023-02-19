section .asm

extern int21h_handler
extern no_interrupt_handler

global int21h
global load_idt
global enable_interrupt
global disable_interrupt
global no_interrupt

enable_interrupt:
    sti
    ret
disable_interrupt:
    cli
    ret

load_idt:
    push ebp
    mov ebp, esp

    mov ebx, [ebp + 8]

    lidt [ebx]

    pop ebp
    ret

int21h:
    cli
    pushad ; 把所有通用寄存器压栈

    call int21h_handler

    popad
    sti
    iret

no_interrupt:
    cli
    pushad ; 把所有通用寄存器压栈

    call no_interrupt_handler

    popad
    sti
    iret

