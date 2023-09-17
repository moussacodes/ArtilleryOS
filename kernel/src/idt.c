#include "../include/idt.h"

idt_t idt[ARTILLERYOS_MAX_INTERRUPT_SIZE];
idt_ptr_t idt_ptr;

extern void idt_load(idt_ptr_t *ptr);

void idt_zero()
{
	terminal_print("Divide by zero error\n");
}

void idt_set(int interrupt_no, void *address)
{
	idt_t *desc = &idt[interrupt_no];
	uint32_t addr = (uint32_t)address;

	desc->offset_1 = addr & 0xFFFF;
	desc->selector = KERNEL_CODE_SELECTOR;
	desc->zero = 0x00;
	desc->type_attr = 0xEE;
	desc->offset_2 = (addr >> 16) & 0xFFFF;
}

void idt_init()
{
	memset(idt, 0, sizeof(idt));
	idt_ptr.limit = sizeof(idt) - 1;
	idt_ptr.base = (uint32_t)idt;

	idt_set(0, &idt_zero);

	idt_load(&idt_ptr);
}