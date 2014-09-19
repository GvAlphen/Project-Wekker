int q = 0;
void delay()
{
	for (q = 0; q<100000; q++)
	{
		asm("nop");
	}
}
