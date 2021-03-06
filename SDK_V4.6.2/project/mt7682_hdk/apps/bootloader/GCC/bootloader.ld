
/*
 *        MT7686 CM4 Loader Memory Map
 *
 */

/* TODO stack size fine tune */

/* Entry Point */
ENTRY(Reset_Handler)

/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0;      /* required amount of heap  */
_Min_Stack_Size = 0x400; /* required amount of stack */

/* Specify the memory areas */
MEMORY
{
  TCM (rwx)    : ORIGIN = 0x04008000, LENGTH = 64K
  SYSRAM (rwx) : ORIGIN = 0x04200000, LENGTH = 384K
  ROM_BL(rx)   : ORIGIN = 0x08002000, LENGTH = 64K
}

/* Highest address of the user mode stack */
_estack = ORIGIN(TCM) + LENGTH(TCM);
__StackTop = _estack;

/* Define output sections */
SECTIONS
{
  . = ORIGIN(ROM_BL);
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.reset_handler))
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } > TCM AT > ROM_BL

  /* The program code and other data goes into FLASH */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    *(.ram_rodata)
    *(.sysram_rodata)
    *(.tcm_rodata)
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
	  *(.eh_frame)
    *(.ram_code)
    *(.sysram_code)
	  *(.tcm_code)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
    _exit = .;
  } >TCM AT > ROM_BL


  /* used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    *(.tcm_rwdata)
    *(.*ram_rwdata)
    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >TCM AT > ROM_BL

  /* Uninitialized data section */
  . = ALIGN(4);
  .tcm_bss (NOLOAD) :
  {
      _tcm_zi_start = .;
      *(.tcm_zidata)
      . = ALIGN(4);
      _tcm_zi_end = .;
  }> TCM AT> ROM_BL

  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __end__ = .;
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >SYSRAM AT > ROM_BL

  /* User_heap_stack section, used to check that there is enough RAM left */
  ._user_heap_stack :
  {
    . = ALIGN(4);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    __HeapBase = .;
    . = . + _Min_Heap_Size;
    __HeapLimit = .;
    __StackLimit = .;
    . = . + _Min_Stack_Size;
    . = ALIGN(4);
  } >TCM AT > ROM_BL

  /* BL ROM DATA */
  .bl_rom_region :
  {
    . = ALIGN(4);
    *(.rom_data)         /* .rom_data sections (constants, strings, etc.) */
    *(.rom_data*)        /* .rom_data* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } > ROM_BL
}
