#include <wiringPi.h>
#include <stdio.h>

unsigned int uiTestCount = 0;

int main(void)
{
	wiringPiSetup();
	pinMode(10, OUTPUT);

	for (;;)
	{
		uiTestCount = uiTestCount + 1;
		printf("Test Count : %d\n", uiTestCount);

		digitalWrite(10, HIGH);
		delay(500);
		digitalWrite(10, LOW);
		delay(500);
	}

	return 0;
}
