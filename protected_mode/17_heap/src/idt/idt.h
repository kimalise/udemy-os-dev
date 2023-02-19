#ifndef IDT_H
#define IDT_H

// #include <stddef.h>
#include <stdint.h>

struct idt_descriptor_t
{
    uint16_t offset_1;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attributes;
    uint16_t offset_2;
}__attribute__((packed));

struct idtr_t
{
    uint16_t limit;
    uint32_t offset;
}__attribute__((packed));

void initialize_idt();
void set_idt_entry(int entry_number, void* handler_addr);
void int21h_handler();
void enable_interrupt();
void disable_interrupt();

#endif