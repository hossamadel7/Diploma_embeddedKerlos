/* Linker_script cortexM3
by Eng.Hossam Adel
*/
MEMORY
{
	flash(RX) : ORIGIN = 0X08000000 , LENGTH =128K
	sram(RWX) : ORIGIN = 0X20000000 , LENGTH =20K
}

SECTIONS
{
	.text : {
		*(.vectors*)
		*(.text*)
		*(.rodata)
		_E_text = . ;
	} > flash

	.data :
	{
		_S_DATA = . ;
		*(.data)
		_E_DATA = . ;
	}

	.bss : { 
		_S_bss = . ;
		*(.bss*)
		_E_bss = . ;
		_stack_top = .;
	} >sram

}