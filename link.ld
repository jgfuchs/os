ENTRY(start)

SECTIONS
{
	. = 0x100000;
	
	.text ALIGN(4096) :
	{
		*(.text)
	}
	
	.data ALIGN(4096) :
	{
		*(.data)
		*(.rodata)
	}
	
	.bss ALIGN(4096) :
	{
		*(.bss)
	}
	
	/DISCARD/ :
	{
		*(.comment)
	}
}
