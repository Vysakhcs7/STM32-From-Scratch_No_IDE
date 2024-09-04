MEMORY
{
  FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 1024K
  SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
  .text :
  {
    *(.isr_vector)
    *(.text)
    *(.rodata)
    _etext = .;
  } > FLASH

  .data :
  {
    _sdata = .;
    *(.data)
    _edata = .;
  } > SRAM AT > FLASH

  .bss :
  {
    _sbss = .;
    *(.bss)
    _ebss = .;
  } > SRAM

  /* Optional: Section for heap and stack */
  _end = .;
  _estack = ORIGIN(SRAM) + LENGTH(SRAM);
}

/* Define the entry point */
ENTRY(Reset_Handler)
