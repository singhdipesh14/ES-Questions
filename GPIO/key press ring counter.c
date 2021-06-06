#include <LPC17xx.h>

int main()
{
	unsigned int k, LED, i;
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC_GPIO0->FIODIR |= 0x00000FF0;
	LPC_PINCON->PINSEL4 |= 3 << 26; //2.12
	LPC_PINCON->PINSEL4 ^= 3 << 26; //2.12
	LPC_GPIO2->FIODIR |= 1 << 12;
	LPC_GPIO2->FIODIR ^= 1 << 12;
	LED= 0x00000010;
	while (1)
	{
		k = LPC_GPIO2->FIOPIN;
		k >>= 12;
		k &= 1;
		if (k == 1)
		{
			LPC_GPIO0->FIOPIN = LED;
			LED <<= 1;
			if (LED == 0x00001000)
			{
				LED = 0x00000010;
			}
			for(i =0; i<100000; i++);
		}
	}
}
