#include "../include/kernel.h"

void kernel_main()
{
	terminal_init();
	get_cpu_info();

	//  idt_activate();
	//  outb(0x60, 0x10);

	//set_mode(320, 200, 8);
	//clear_screen_withcolor(0x01);
	//color_demo();
}
