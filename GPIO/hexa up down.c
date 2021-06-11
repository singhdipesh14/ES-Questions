#include <LPC17xx.h>

unsigned int seg[] = {0 << 23, 1 << 23, 2 << 23, 3 << 23};
signed int dig1 = -1, dig2 = -1, dig3 = -1, dig4 = -1;
unsigned int seg_cnt = 0, temp1 = 0;
unsigned int array[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
unsigned long int i = 0, k;

void delay(void);
void display(void);

int main()
{
	SystemInit();
	SystemCoreClockUpdate();

	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC_PINCON->PINSEL3 &= 0XFFC03FFF;
	LPC_PINCON->PINSEL4 |= 3 << 26; //2.12
	LPC_PINCON->PINSEL4 ^= 3 << 26; //2.12
	LPC_GPIO2->FIODIR |= 1 << 12;
	LPC_GPIO2->FIODIR ^= 1 << 12;
	LPC_GPIO0->FIODIR |= 0x00000FF0;
	LPC_GPIO1->FIODIR |= 0x07800000;

	while (1)
	{
		k = LPC_GPIO2->FIOPIN;
		k >>= 12;
		k &= 1;
		if (k == 1)
		{
			if (dig1 == -1)
			{
				dig1 = 0;
			}
			if (dig2 == -1)
			{
				dig2 = 0;
			}
			if (dig3 == -1)
			{
				dig3 = 0;
			}
			if (dig4 == -1)
			{
				dig4 = 0;
			}
		}
		else
		{

			if (dig1 == -1)
			{
				dig1 = 0xF;
			}
			if (dig2 == -1)
			{
				dig2 = 0xF;
			}
			if (dig3 == -1)
			{
				dig3 = 0xF;
			}
			if (dig4 == -1)
			{
				dig4 = 0xF;
			}
		}
		delay();
		display();
		seg_cnt++;

		if (seg_cnt == 4)
		{
			seg_cnt = 0;
			if (k == 1)
			{
				dig1++;
				if (dig1 == 0x10)
				{
					dig1 = 0;
					dig2++;
					if (dig2 == 0x10)
					{
						dig2 = 0;
						dig3++;
						if (dig3 == 0x10)
						{
							dig3 = 0;
							dig4++;
							if (dig4 == 0x10)
							{
								dig4 = 0;
							}
						}
					}
				}
			}
			else
			{
				dig1--;
				if (dig1 == -1)
				{
					dig1 = 0xF;
					dig2--;
					if (dig2 == -1)
					{
						dig2 = 0xF;
						dig3--;
						if (dig3 == -1)
						{
							dig3 = 0xF;
							dig4--;
							if (dig4 == -1)
							{
								dig4 = 0xF;
							}
						}
					}
				}
			}
		}
	}
}

void display()
{
	LPC_GPIO1->FIOPIN = seg[seg_cnt];
	if (seg_cnt == 0)
	{
		temp1 = dig1;
	}
	else if (seg_cnt == 1)
	{
		temp1 = dig2;
	}
	else if (seg_cnt == 2)
	{
		temp1 = dig3;
	}
	else if (seg_cnt == 3)
	{
		temp1 = dig4;
	}
	LPC_GPIO0->FIOPIN = array[temp1] << 4;
	for (i = 0; i < 500; i++)
		;
}

void delay()
{
	unsigned int i;
	for (i = 0; i < 10000; i++)
		;
}
