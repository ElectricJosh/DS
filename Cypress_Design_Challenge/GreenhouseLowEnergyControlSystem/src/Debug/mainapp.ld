OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
SEARCH_DIR(.)
/* pram_patch_begin=0x270400 pram_patch_end=0x273BFC pram_end=0x274000 */
/* ram_patch_begin=0x20F79C ram_patch_end=0x20FAC0 ram_end=0x270000 */
/* aon_patch_begin=0x000000 aon_patch_end=0x2031F4 aon_end=0x204574 */
/* app_patch_ram=0x000000 aon_patch_end=0x2031F4 aon_end=0x204574 */
/* FLASH0_BEGIN_ADDR=0x500000 FLASH0_LENGTH=0x040000 */
/* FLASH0_SS=0x500000 */
/* FLASH0_VS=0x500400 */
/* FLASH0_DS=0x501400 */
/* FLASH0_DS2=0x520A00 */
MEMORY
{
	ram (rwx) : ORIGIN = 0x20FAC0, LENGTH = 0x60140
	aon (rwx) : ORIGIN = 0x2031F4, LENGTH = 0x1380
	static_section (r) : ORIGIN = 0x500C00, LENGTH = 0x400
	xip_section (rx) : ORIGIN = 0x511500, LENGTH = 0x2FF00
	log_section (r) : ORIGIN = 0x81000004, LENGTH = 0x100000
}
EXTERN(spar_irom_begin spar_irom_end spar_irom_length);
EXTERN(spar_iram_begin spar_iram_end spar_iram_length);
EXTERN(spar_iram_data_begin spar_iram_data_end spar_iram_data_length);
EXTERN(spar_iram_bss_begin spar_iram_bss_end spar_iram_bss_length);
EXTERN(spar_irom_data_begin);
EXTERN(aon_iram_end);
EXTERN(xip_area_begin);
EXTERN(xip_area_end);
PROVIDE(spar_irom_length = spar_irom_end - spar_irom_begin);
PROVIDE(spar_iram_length = spar_iram_end - spar_iram_begin);
PROVIDE(spar_iram_data_length = spar_iram_data_end - spar_iram_data_begin);
PROVIDE(spar_iram_bss_length = spar_iram_bss_end - spar_iram_bss_begin);
SECTIONS
{
	spar_irom_begin = 0x20FAC0;
	.app_xip_area : ALIGN (4)
	{
		CREATE_OBJECT_SYMBOLS
		xip_area_begin = .;
		*/empty_wiced_bt.o (.text.* .gnu.linkonce.t.* .rodata .constdata* .rodata.* .gnu.linkonce.r.*)
		*/app_bt_cfg.o (.text.* .gnu.linkonce.t.* .rodata .constdata* .rodata.* .gnu.linkonce.r.*)
		*/GeneratedSource/cycfg_gatt_db.o (.text.* .gnu.linkonce.t.* .rodata .constdata* .rodata.* .gnu.linkonce.r.*)
		*/spar_setup.o (.text.* .gnu.linkonce.t.* .rodata .constdata* .rodata.* .gnu.linkonce.r.*)
		*/wiced_platform.o (.text.* .gnu.linkonce.t.* .rodata .constdata* .rodata.* .gnu.linkonce.r.*)
		*/wiced_platform_pin_config.o (.text.* .gnu.linkonce.t.* .rodata .constdata* .rodata.* .gnu.linkonce.r.*)
		*/lib_installer.o (.text.* .gnu.linkonce.t.* .rodata .constdata* .rodata.* .gnu.linkonce.r.*)
		*(.pisec_*)
		KEEP(*(.data_in_xip_area))
		KEEP(*(.dsp_pram_section))
		*(.app_init_code)
		*(.emb_text)
		*(.text)
		*(EmHeAacDec)
		*(.text.*)
		*(.gnu.linkonce.t.*)
		*(i.*)
		*(.glue_7t)
		*(.glue_7)
		*(.vfp11_veneer)
		*(.v4_bx)
		*(.init_code)
		*(.init_text)
		*(.spar_setup)
		*(.ARM.extab*)
		*(.gnu.linkonce.armextab.*)
		*(.ARM.exidx*)
		*(.gnu.linkonce.armexidx.*)
		*(const_drom_var)
		*(.rodata)
		*(.constdata*)
		*(.rodata.*)
		*(.gnu.linkonce.r.*)
		*(.data.rom)
		spar_irom_end = .;
		xip_area_end = .;
	} >xip_section
	.text : 
	{
		CREATE_OBJECT_SYMBOLS
		*(.app_init_code)
		*(.emb_text)
		*(.text)
		*(.text.*)
		*(EmHeAacDec)
		*(.gnu.linkonce.t.*)
		*(.glue_7t)
		*(.glue_7)
		*(.vfp11_veneer)
		*(.v4_bx)
		*(.ARM.extab*)
		*(.gnu.linkonce.armextab.*)
		*(.ARM.exidx*)
		*(.gnu.linkonce.armexidx.*)
	} >ram
	.rodata : ALIGN (4)
	{
		CREATE_OBJECT_SYMBOLS
		*(const_drom_var)
		*(.rodata)
		*(.constdata*)
		*(.rodata.*)
		*(.gnu.linkonce.r.*)
		*(.data.rom)
		spar_irom_end = .;
	} >ram
	.data : ALIGN (4)
	{
		CREATE_OBJECT_SYMBOLS
		spar_iram_begin = .;
		spar_iram_data_begin = .;
		*(.data)
		*(.data.*)
		*(.gnu.linkonce.d.*)
		*(.init_patch_table)
		spar_iram_data_end = .;
	} >ram
	spar_irom_data_begin = spar_iram_data_begin;
	.bss : ALIGN (4)
	{
		CREATE_OBJECT_SYMBOLS
		spar_iram_bss_begin = .;
		*(.bss)
		*(.bss.*)
		*(.gnu.linkonce.b.*)
		*(COMMON)
		spar_iram_bss_end = .;
		spar_iram_end = .;
	} >ram
	.setup : ALIGN (4)
	{
		CREATE_OBJECT_SYMBOLS
		*(.init_code)
		*(.init_text)
		*(.spar_setup)
	} >ram
	.aon : ALIGN (4)
	{
		CREATE_OBJECT_SYMBOLS
		aon_iram_begin = .;
		*(always_on_ram_var)
		*(.aon_code)
		*(.data_in_retention_ram)
		*(.code_in_retention_ram)
		aon_iram_end = .;
	} >aon
	.static_area : ALIGN (4)
	{
		CREATE_OBJECT_SYMBOLS
		static_area_begin = .;
		KEEP(*(.data_in_static_area))
		static_area_end = .;
	} >static_section
	.log_section : ALIGN (4)
	{
		CREATE_OBJECT_SYMBOLS
		KEEP(*(log_data))
	} >log_section
}
