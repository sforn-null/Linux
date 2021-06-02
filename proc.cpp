#include"proc.h"

void proc()
{
	   char bar[NUM];
	   memset(bar, '\0', sizeof(bar));
	   int i = 0;
	   const char* lable = "|/-\\";
	   while (i < 100)
		   {
		     fflush(stdout);
		     bar[i++] = '#';
		     usleep(100000);
		     printf("[%-100s][%3d%%][%c]\r", bar, i, lable[i % 4]);
		   }
	   printf("\n");
	 }

