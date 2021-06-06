#include <LPC17xx.h>

int main()
{
	signed int i = 0, j, k;
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC_GPIO0->FIODIR |= 0x00000FF0;
	LPC_PINCON->PINSEL4 |= 3 << 26; //2.12
	LPC_PINCON->PINSEL4 ^= 3 << 26; //2.12
	LPC_GPIO2->FIODIR |= 1 << 12;
	LPC_GPIO2->FIODIR ^= 1 << 12;
	while (1)
	{
		k = LPC_GPIO2->FIOPIN;
		k >>= 12;
		k &= 1;
		if (k == 1)
		{
			if (i > 255)
			{
				i = 0;
			}
			for (; i < 256 && k == 1; i++)
			{
				LPC_GPIO0->FIOPIN = i << 4;
				for (j = 1; j < 10000; j++)
					;
				k = LPC_GPIO2->FIOPIN;
				k >>= 12;
				k &= 1;
				if (i > 255)
				{
					i = 0;
				}
			}
		}
		else
		{
			if (i <= 0)
			{
				i = 255;
			}
			for (; i >= 0 && k == 0; i--)
			{
				LPC_GPIO0->FIOPIN = i << 4;
				for (j = 1; j < 10000; j++)
					;
				k = LPC_GPIO2->FIOPIN;
				k >>= 12;
				k &= 1;
				if (i <= 0)
				{
					i = 255;
				}
			}
		}
	}
}
