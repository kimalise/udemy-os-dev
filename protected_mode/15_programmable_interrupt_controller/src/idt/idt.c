#include "idt.h"
#include "config.h"
#include "memory/memory.h"
#include "kernel.h"

struct idt_descriptor_t idt_desc_table[KimOS_MAX_IDT_SIZE];

struct idtr_t idtr;

extern void load_idt(struct idtr_t* idtr);

void zero_handler()
{
    print("divided by zero interrupt!\n");
}

void initialize_idt()
{
    memset(idt_desc_table, 0, sizeof(idt_desc_table));

    idtr.limit= sizeof(idt_desc_table) - 1;
    idtr.offset = (uint32_t) idt_desc_table;

    set_idt_entry(0, zero_handler);

    load_idt(&idtr);
}

void set_idt_entry(int entry_number, void* handler_addr)
{
    struct idt_descriptor_t* p = &idt_desc_table[entry_number];
    // uint32_t addr = (uint32_t) handler_addr;
    p->offset_1 = (uint32_t) handler_addr & 0x0000ffff; // lower 16bits
    p->selector = KimOS_CODE_SEGMENT;
    p->zero = 0x00;
    p->type_attributes = 0xEE;
    p->offset_2 = (uint32_t) handler_addr >> 16; // higher 16bits

    return;
}