// Base provided by Bruce Segee
// Walter Rasmussen - Boom Johnson - Spring 2018
// Prints a picture over serial communication. 
#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F_CPU 1000000UL
#include <util/delay.h>

int serial_putchar(char, FILE *);
int serial_getchar(FILE *);
static FILE serial_stream = FDEV_SETUP_STREAM (serial_putchar, serial_getchar, _FDEV_SETUP_RW);

void init_serial(void);
void printArt(void);

/* this is the high_low server running on serial on an avr */
/* it sets up the serial communication for 1200 baud */
/* note that the random number generator will always generate the same sequence */
int main(void)
{ 
  init_serial();
  _delay_ms(2000);
  while(1) 
  { 
    printArt();
  }   
  return 0;
}

//U2Xn = 0 , 20.00MHz Clock ,BAUD 9600
// UBBR = 129, 0.2% error, according to Table 24-7 of ATmega88 datasheet
void init_serial(void)
{
   UBRRn=129; // 9600 BAUD FOR 20MHZ SYSTEM CLOCK
   UCSR0A= 1<<U2X0;
   UCSR0C= (1<<USBS0)|(3<<UCSZ00) ;  // 8 BIT NO PARITY 2 STOP
   UCSR0B=(1<<RXEN0)|(1<<TXEN0)  ; //ENABLE TX AND RX ALSO 8 BIT
   stdin=&serial_stream;
   stdout=&serial_stream;

}   

// Waits for input then prints                                                  */
void printArt(void)
{
   FILE *fp, *fpr;
   char end = 'q', input;
   int i = 0; 
 
   fp=stdout;
   fpr=stdin;
 
  fprintf(fp,"Welcome to the single image Art Exhibit. \r\n");
  fprintf(fp,"Enter any key to display the picture. Enter 'q' to exit. \r\n");

  while(fscanf(fpr,"%c",&guess)!=1) fscanf(fpr,"%*s");

  while(input!=end) // Exits when 'q' is pressed
  {   	
    i = input; 
    
    // \x1b[%dm , allows the color to be changed by the value at the end
    // (30+i++%7) , ensures %d is 30-36 which are the color code values
    fprintf(fp,"\x1b[%dm//////////////////////////oso+-........................./oss///////////////////////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////////////+so/................................-+so////////////////////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm//////////////////////y+....................................../y+//////////////////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm////////////////////+y-.........................................sdmmdh+////////////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////////+y-...........................................Nmmmmmo///////////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////////h:............----...........................sNmmmmmmo//////////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////////d-........------------------.............dmdmmmmmmmmmm+/////////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////////h-......---....-----...................-/Nmmmmmmmmmmmmm/////////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////////y/://:/+++/:-.......-+ooo:.............+mmmmmmmmmmmmmmNo////////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm/////////////////+sdmmmdddmmmmmmds....-dmmmmmddhysoo+:.....:mmmmmmmmmmmmmmm////////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm////////////////ommmmmmmmmmmmmmmmd....ymmmmmmmmmmmmmmmd:-://ydNNNNNNNmmmmmmy///////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm////////////////ymmdddyhddhhydmmho-o+/+yhhhyooossssyyyddhsoosNNmmmmmmmmmmmmNo//////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm////////////////osyssss++++ooooohsNy+:::/+shhyso++oosoh:----:Nmmmmmmmmmmmmmmd//////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm////////////////dh//++d/syyyyo..hsNss.../yNhMMdd+---hho-....ommmmmNdhdmmmmmmh//////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm////////////////dm///+mohMhNd-./hh+dyo...-hhmy::...-dm:.....dmmmmmNy:-ommmmmmy+////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm////////////////oNy//so.-sys:.-dh:-ohys:..-::--....sds-..../Nmmmmmmmm+./Nmmmmmmo///////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm/////////////////sNy+h-.....-+hh:...+ysso/-.....-/shy-.....-Nmmmmmmmmy-.ymmmmmmy///////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm//////////////////+ydmo+/+osydy-.....-/oyhhhysyyyyy+-.......dmmmmmmmmm:.oNmmmmmy///////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm////////////////////h++osso+:m-.........///ys///::-........./mmmmmmmmy-.smmmmmmy///////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////////so........d...:yyys:...-+s-.............../mmmmmmmd--mmmmmmmy///////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm/////////////////sdmho-....../o+oosdhyhhs++/-.....--.........:dNmmmmNo.hmmmmmmmy///////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm////////////////ymmmmNh.......-:+ydmmmmmmhs/-....sdddhyo/-..:yNmmmmmd--Nmmmmmmmmso/////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////sNmmmmmN/./shhdddmmmmmmmmmmmmdh/-smmmmmmmmdhhdmmmmmmd:.smmmmmmmmmmm/////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////dmmmmmmmmhmmmmmmmmmmmmmmmmmmmmmmdmmmmmmmmmmmmmmmmmmN+./mmmmmmmmmmmh/////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmdymmmmmmmmmmmmy/////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmdh+//////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmy//////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm//////////////+NmmmmmmmmmmmmmmddddddddddmmmNmmmmmmmmmmmmmmmmmmmmmmmmNmmmmmmmmmmmmmmh///////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm//////////////ommmmmmmmmmmMN+--....--:::::+MddMmmmmmmmmmmmmmmmmmmmmNNmmmmmmmmmmmmdo////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm//////////////ommmmmmmmmmmmhy/+oyyhhdddddhhsommmmmmmmmmmmmmmmmmmmmmNmddddddhhhhyo//////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////ohmmmmmmmmmmmdohmmmddddmmmy/ommmmmmmmmmmmmmmmmmmmmmNNd++++//////////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm////////////////+Nmmmmmmmmmmmmo+yddmmmds/:ymmmmmmmmmmmmmmmmmmmmmmNNsd//////////////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm/////////////////Nmmmmmmmmmmmmmh/:+oo/--+dmmmmmmmmmmmmmmmmmmmmmmmNd-h//////////////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm/////////////////Nmmmmmmmmmmmmmmmhs+osshmmmmmmmmmmmmmmmmmmmmmmmmmM+.y+/////////////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm/////////////////NmmmmmmmmmmmmmmmmmmmmmmmmNNmmmmmmmmmmmmmmmmmmmmmN/.os////+++//////////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm/////////////////mmmmmmmmmmmmmmmmmNmmmmmmmmNNmmmmmmmmmmmmmmmmmmmNN:.:dhhhhhhhhyo+//////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm/////////////////+hmmmmmmmmmmmmmmNmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmN:..Ndhhhhhhhhddy/////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////////ohmmmmmmmmmmmmNmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmh-..dmhhhhhhhhhhdh////////////\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm/////////////////////sdmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmdds:...oMNdhhhhhhhhhmsyhhhso++///\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////////////shmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmd+--....-MMmhhhhhhhhhmNNNNNNNNmdy+\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////////////////odmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmN+:.......NMdhhhhhhhhhhmNNNNNNNNNNm\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm/////////////////////////////ymmmmmmmmmmmmmmmmmmmmmmmmmmmmmmy:-......:NdhhhhhhhhhhhhhmNNNNNNNNN\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////////////////+ossdNmmmmmmmmmmmmmmmmmmmmmmmmmy/-......./ddhhhhhhhhhhhhhhhhmNNNNNNN\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm////////////////////////+hddddhhhddshmmmmmmmmmmmmmmmmmmmy+:-.......smhhhhhhhhhhhhhhhhhhhdNNNNNN\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////////////ymhhhhhhhhhm--/syyhdmmmmmmmmdddy+:-.......+ddhhhhhhhhhhhhhhhhhhhhhmNNNNN\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm//////////////////////ydhhhhhhhhhhm...-::-::/oyysoo+/::-.......:hdhhhhhhhhhhhhhhhhhhhhhhhNNNNNN\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm/////////////////////+mhhhhhhhhhhhm.........-..-------......./hdhhhhhhhhhhhhhhhhhhhhhhhdmNNNNNN\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm/////////////////////ydhhhhhhhhhhhmys+/-...................-hdhhhhhhhhhhhhhhhhhhhddmmmNNNNNNNNN\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm/////////////////////dhhhhhhhhhhhhhhhhdddy/...............+mhhhhhhhhhhhhhhhhhhdmNNNNNNNNNNNNNNN\r\n", (30+i++%7));
    fprintf(fp,"\x1b[%dm///////////////////ohdhhhhhhhhhhhhhhhhhhhhmy.............smhhhhhhhhhhhhhhhhhhmNNNNNNNNNNNNNNNNN\r\n", (30+i++%7));

    while(fscanf(fpr,"%d",&guess)!=1) fscanf(fpr,"%*s");
    
    fprintf(fp,"Congratualtions you got it right\r\n");

  }

}

//simplest possible putchar, waits until UDR is empty and puts character
int serial_putchar(char val, FILE * fp)
{
  while((UCSR0A&(1<<UDRE0)) == 0); //wait until empty 
   UDR0 = val;
   return 0;
}

//simplest possible getchar, waits until a char is available and reads it
//note:1) it is a blocking read (will wait forever for a char)
//note:2) if multiple characters come in and are not read, they will be lost
int serial_getchar(FILE * fp)
{
   while((UCSR0A&(1<<RXC0)) == 0);  //WAIT FOR CHAR
   return UDR0;
}     

