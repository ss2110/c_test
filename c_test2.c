#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

//pigpio header
#include <pigpio.h>

int toggleValue = 1;
unsigned int uiTimerCount = 0;

static void tmrSendHandler(int sig)
{
	uiTimerCount = uiTimerCount + 1;
	printf("Timer Value : %d\n", uiTimerCount);

	toggleValue = toggleValue * -1;
	if (toggleValue == 1)
	{
		gpioWrite(8, 1);
	}
	else
	{
		gpioWrite(8, 0);
	}
}

int main(int argc, char **argv)
{
	int retv;

	struct itimerval itv;
	struct sigaction sa;

	// setup pinmode
	if (gpioInitialise() < 0)
	{
		printf("pigpio initialization failed\n");
		return 0;
	}
	gpioSetMode(8, PI_OUTPUT);
	// setup pigpio end

	sigemptyset(&sa.sa_mask);

	sa.sa_flags = 0;
	sa.sa_handler = tmrSendHandler;
	retv = sigaction(SIGALRM, &sa, NULL);
	if (retv == -1)
	{
		printf("Failed to register signal handler : sigaction \n");
		return retv;
	}

	itv.it_value.tv_sec = 1;
	itv.it_value.tv_usec = 0;
	itv.it_interval.tv_sec = 1;
	itv.it_interval.tv_usec = 0;

	retv = setitimer(ITIMER_REAL, &itv, NULL);
	if (retv == -1)
	{
		printf("Timer setting error : setitimer \n");
		return retv;
	}

	while (1)
	{
		usleep(1);
	}

	// pigpio terminate
	gpioTerminate();

	return 0;
}
