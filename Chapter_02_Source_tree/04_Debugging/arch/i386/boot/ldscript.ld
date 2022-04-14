ENTRY(arch_startup)

SECTIONS {
	.text :
	{


		*( .text* )

	}
	.rodata :
	{
		kernel_data_addr = .;

		/*read only data (constants)*/
		* ( .rodata*)
	}
	.data :
	{
		kernel_data_addr = .;

		/* initialized global variables */
		* (.data* )
	}
	.bss :
	{
		*( .bss* COMMON* )

		. = ALIGN (4096);
	}

	/*
	 * what with other sections generated with gcc (various versions)?
	 * if optimizing for size discard them with: /DISCARD/ : { *(*) }
	 * if debugging with qemu/gdb they must be included
	 * - they can be included implicitly, without declaring them here
	 * - but they will be put behind "kernel_end_addr" so its best to use
	 *   multiboot loader (QEMU is that)
	 */

#ifndef DEBUG
	/DISCARD/ : { *(*) }
#endif
	kernel_end_addr = .;
}
