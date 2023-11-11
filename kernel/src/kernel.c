#include "../include/kernel.h"

void test_idt()
{
	__asm__("int $0x04");
}

void kernel_main(uint32_t mbaddr, uint32_t mbmagic,
		 kernel_mem_limits_t kmlimits, uint32_t boot_page_directory)
{
	multiboot_info_t *mbinfo = remap_multiboot_info(mbaddr);
	terminal_init();
	gdt_init();
	idt_init();

	// TODO: TSS init need to be fixed
	/*
	tss_init(5, 0x10, 0);
	uint32_t esp;
	asm volatile("mov %%esp, %0" : "=r"(esp));
	tss_set_stack(0x10, esp);
	*/

	timer_init(100);
	keyboard_init();
	check_mboot_bootloader_magic(mbmagic);
	display_memory_info(mbinfo, &kmlimits);
	paging_init(boot_page_directory);

#if TEST_IDT
	test_idt();
#endif

#if GUI_MODE
	set_mode(320, 200, 8);
	clear_screen_withcolor(0x04);
#endif
}
