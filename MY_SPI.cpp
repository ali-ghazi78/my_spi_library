/*
 * MY_SPI.cpp
 *
 * Created: 5/14/2018 7:20:20 PM
 * Author : ali
 */ 

#include <avr/io.h>


#define SPI_P SPID
#define SPI_PORT PORTD
#define SPI_SCK  (1<<7)
#define SPI_MOSI (1<<5)
#define SPI_MISO (1<<6)
#define SPI_SS (1<<4)
#define SPI_SS_R (1<<4)//d4
#define SPI_SS_T (1<<4)//a4

#define SS_LOW (SPI_PORT.OUTCLR=SPI_SS)
#define SS_HIGH (SPI_PORT.OUTSET=SPI_SS)

#define SS_R_LOW (SPI_PORT.OUTCLR=SPI_SS_R)
#define SS_R_HIGH (SPI_PORT.OUTSET=SPI_SS_R)

#define SS_T_LOW (PORTA.OUTCLR=SPI_SS_T)
#define SS_T_HIGH (PORTA.OUTSET=SPI_SS_T)

#define R (ss=1)
#define T (ss=0)

#define CE_R_LOW (PORTC.OUTCLR=1<<0)//C0
#define CE_R_HIGH (PORTC.OUTSET=1<<0)//C0

#define CE_T_LOW (PORTC.OUTCLR=1<<1)//C1
#define CE_T_HIGH (PORTC.OUTSET=1<<1)//C1




/* Replace with your library code */
int myfunc(void)
{
	return 0;

}









void spi_init(PORT_t *SPI_PORT,SPI_t *SPI,unsigned char SPI_MOSI_PIN_NUMBER,unsigned char SPI_MISO_PIN_NUMBER,unsigned char SPI_SCK_PIN_NUMBER,PORT_t *SPI_SS_PORT,unsigned char SPI_SS_PIN_NUMBER,unsigned char SPI_PRESCALER,unsigned char SPI_MODE)
{
	
	
															
	SPI_PORT->DIRSET=(1<<SPI_SCK_PIN_NUMBER)|(1<<SPI_MOSI_PIN_NUMBER);		//set mosi and sck and ss as output just set as output don't give any thing to out don't use port.out=1<<X
	SPI_SS_PORT->DIRSET=SPI_SS_PIN_NUMBER;									// the reason that i use another port typedef for ss is that you can use several spi slave 
	
	SPI_PORT->DIRCLR=(1<<SPI_MISO_PIN_NUMBER);
	SPI.CTRL=(SPI_ENABLE_bm)|(SPI_MASTER_bm)|(SPI_PRESCALER)|(SPI_MODE);//mode 1 is chosen	don't forget to set the correct mode for spi otherwise you will interfere with some data shifting and problems hajiii mode kheili moheme yaani nokte asasi entekhabe mode doroste ke sck ro kodom labe bayad puls befreste
	
	
}
void spi_write(unsigned char my_data,unsigned char data_order)
{
	//vase khoondane hatmn ye shero veri bayad befresti .aval command midi baad ye cherti mifresti va mikhooni .vase har bar khoondan bas befresti
	//data oreder==0---->msb first   | NOT SURE DATA OREDER 0 IS PREFERED
	//data oreder==1---->lsb first   | NOT SURE DATA OREDER 0 IS PREFERED
	//handy data order
	//datasheet nrf dar morede databit command va data zer zade .har do tahsoon ye joor fersetade mishn lazm nis avaz koni data order ro
	
	if(data_order)// i dont wanna use data order when using nrf
	{
		unsigned char temp=0;
		temp|=(((my_data&1)&&(1))<<7);
		temp|=(((my_data&2)&&(1))<<6);
		temp|=(((my_data&4)&&(1))<<5);
		temp|=(((my_data&8)&&(1))<<4);
		temp|=(((my_data&16)&&(1))<<3);
		temp|=(((my_data&32)&&(1))<<2);
		temp|=(((my_data&64)&&(1))<<1);
		temp|=(((my_data&128)&&(1))<<0);
		my_data=temp;
	}
	
	SPI_P.DATA=my_data;
	
	while(!(SPI_P.STATUS&(1<<7)));	//wait until sending is complete

}
unsigned char spi(unsigned char my_data,unsigned char data_order)
{
	spi_write(my_data,data_order);
	return SPI_P.DATA;
}
unsigned char spi_read()
{
	return SPI_P.DATA;
}





