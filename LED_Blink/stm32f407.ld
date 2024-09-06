/* 	Entry Point */
ENTRY(Reset_Handler)

/* Memory Map */
MEMORY
{
	FLASH(rx)   : ORIGIN = 0x08000000, LENGTH = 1024K 
	SRAM(rwx)   : ORIGIN = 0x20000000, LENGTH = 128K
}

/* Sections */
SECTIONS
{
	.isr_vector :
	{
	   *(.isr_vector) 
	}>FLASH

	.text :
	{
	  *(.text)
	  *(.rodata)
	  _etext = .;
	}>FLASH
	
	.data :
	{
	  _sdata = .;
	  *(.data)
	  _edata = .;
	}>SRAM AT >FLASH
	
	.bss :
	{
	 _sbss = .;
	 *(.bss)
	 _ebss = .;
	}>SRAM
}


