#include <16F886.h>
#device adc=8
#fuses INTRC_IO,NOWDT,PUT,MCLR,NOPROTECT,NOCPD,NOBROWNOUT
#fuses NOIESO,NOFCMEN,NOWRT,NODEBUG,NOLVP  
#use delay(clock=4M)
#define use_portb_lcd TRUE

