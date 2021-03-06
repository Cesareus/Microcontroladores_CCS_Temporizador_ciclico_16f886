#include <main.h>
#include <lcd.c>
#define SW1 PIN_A1 //PORTA RA1
#define SW2 PIN_A2 //PORTA RA2
#define SW3 PIN_A3 //PORTA RA3
#define SW4 PIN_A4 //PORTA RA4
#define SW5 PIN_A5 //PORTA RA5
#define bomba PIN_C4 //PORTA RC4
#define BLLCD PIN_C3 //luz backlight
#use fast_io(A)   // Configuración rápida del puerto A
#use fast_io(B)  // Configuración rápida del puerto B
#use fast_io(C) // Configuración rápida del puerto C

//******* Variables *******//
signed int tempo=10, onoff=10,suma=0;
int min=0, seg=0, cont=0;

#int_TIMER1
void temp1s(void)
{
  cont++;
  if (cont==2)  
  {
  seg++;
  cont=0;
  }
  set_timer1 (3036);
  if (seg==59)
  {
  seg=0;
  min++;
  }
}

// ************** Programa Principal ************** //
void main()
{

   set_tris_a(0x3E);
   set_tris_b(0x00);
   set_tris_c(0x00);
   
   setup_timer_1 (T1_INTERNAL | T1_DIV_BY_8);
   set_timer1 (3036);
   enable_interrupts(global);
   lcd_init (); // Inicializa la libreria para manejar el LCD.
   output_high(BLLCD);
   printf ( LCD_PUTC, "\f" ); // Limpia la LCD.
    lcd_gotoxy(1,1);
   printf(lcd_putc,"Config Inicial");
   delay_ms(500);
             
   while(true){
  
  if(tempo<10){
  lcd_gotoxy(1,2);
  printf(lcd_putc,"Time:%d ",tempo);}
  else{
  lcd_gotoxy(1,2);
  printf(lcd_putc,"Time:%d",tempo);}
  if(onoff<10){
  lcd_gotoxy(9,2);
  printf(lcd_putc,"onoff:%d ",onoff);}
  else{
  lcd_gotoxy(9,2);
  printf(lcd_putc,"onoff:%d",onoff);}
 
   if(!input(SW1)){
   while(!input(SW1)){}
   tempo--;
   output_high(BLLCD);
   }
   if(!input(SW2)){
   while(!input(SW2)){}                           
   tempo++;
   output_high(BLLCD);
   }
   if(!input(SW3))
   {
   while(!input(SW3)){}                              
   onoff--;
   output_high(BLLCD);
   }
   if(!input(SW4))
   {
   while(!input(SW4)){}                               
   onoff++;
   output_high(BLLCD);
   }
   if(!input(SW5)){
   while(!input(SW5)){} 
   enable_interrupts(INT_TIMER1);
   break;
   }
   }
   printf(lcd_putc,"\f");   
   while(true)
   { 
   lcd_gotoxy(1,2);
   printf(lcd_putc,"Time:%d",tempo);
   lcd_gotoxy(9,2);
   printf(lcd_putc,"onoff:%d",onoff);
   lcd_gotoxy(1,1);
   printf(lcd_putc,"min:%d ",min);
   suma= tempo+onoff;
    if(min==1){
   output_low(BLLCD);
   }
   
 if (min==tempo && min<=suma && onoff>0 && tempo>=0)
   {
   if(min==1){
   output_low(BLLCD);
   }
   output_high(bomba);
   lcd_gotoxy(8,1);
   printf(lcd_putc,"Bomba on ");
   lcd_gotoxy(1,1);
   printf(lcd_putc,"min:%d ",min);
   }   
   if (min==suma && onoff>0 && tempo>=0)
   {
   output_low(bomba);
   lcd_gotoxy(8,1);
   printf(lcd_putc,"Bomba off");
   lcd_gotoxy(1,1);
   printf(lcd_putc,"min:%d ",min);
   min=0;
   }    
   if (tempo<0 || onoff<=0)
   {
   output_low(bomba);
   lcd_gotoxy(1,1);
   printf(lcd_putc,"ERROR onoff o ");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"onoff-temp <= 0 ");
   delay_ms(1500);
   Break;
   }    
   }
   disable_interrupts(INT_TIMER1);
   delay_ms(1000);
   printf ( LCD_PUTC, "\f" );
   lcd_gotoxy(1,1);
   printf(lcd_putc,"Final");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"Temporizado");
}


