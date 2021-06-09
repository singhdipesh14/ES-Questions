#include <LPC17xx.h>

unsigned int dig[] = {4, 3, 2, 1};
unsigned int dig_sel[] = {0, 1, 2, 3};
unsigned int array[] = {0x66, 0x4F, 0x5B, 0x06};
unsigned int i = 0;
int main()
{
	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC_PINCON->PINSEL3 &= 0xFFC03FFF;

	LPC_GPIO0->FIODIR |= 0X00000FF0;
	LPC_GPIO1->FIODIR |= 0x07800000;

	while (1)
	{
		LPC_GPIO1->FIOPIN = i << 23;
		LPC_GPIO0->FIOPIN = array[dig_sel[i]]<<4;
		i = (i + 1) % 4;
	}
}
