/*! linker script for memory layout */

/* Its parsed as C before used in linking! */

ENTRY(arch_startup)

SECTIONS {
	.code 0x0 :
 	{
 		kernel_code_addr = .;

 		/* instructions */
 		*?/boot/startup.asm.o ( .text* )

		*?/boot/premjesti.o ( .text* )
	}
	.instrukcije 0x200000 : AT(0x100000)
	{
 		*( .text* )
 	}
	size_i = SIZEOF(.instrukcije);
	xxxx = 0x100000;

	.data 0x400000: AT(0x300000)
 	{
 		kernel_data_addr = .;

 		/* read only data (constants), initialized global variables */
 		* ( .rodata* .data* )
 	}
	size_data = SIZEOF(.data);

	.bss 0x500000: AT(0x450000)
 	{
 		*( .bss* COMMON* )

 		. = ALIGN (4096);
 	}

	.stog_u_slici 0x600000:
	{
		*( .stog )
		. = ALIGN (4096);
	}
}
