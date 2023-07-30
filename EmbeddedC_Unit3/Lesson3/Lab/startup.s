/* startup_cortexM3.s
Eng.Hossam Adel
*/


/* SRAM 0x20000000 */
.section .vectors 

.word 0x20001000 /*stack pointer */
.word _reset /*reset*/
.word Vector_handler /*1*/
.word Vector_handler /*2*/
.word Vector_handler /*3*/
.word Vector_handler /*4*/
.word Vector_handler /*5*/
.word Vector_handler /*6*/
.word Vector_handler /*7*/
.word Vector_handler /*8*/
.word Vector_handler /*9*/
.word Vector_handler /*10*/
.word Vector_handler /*11*/
.word Vector_handler /*12*/
.word Vector_handler /*13*/
.word Vector_handler /*14*/
.word Vector_handler /*15*/
.word Vector_handler /*16*/
.word Vector_handler /*17*/
.word Vector_handler /*18*/

.section .text

_reset:
	bl main
	b .

.thumb_func

Vector_handler:
	b _reset
	