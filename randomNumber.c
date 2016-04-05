#include <time.h>
// srand(time(NULL)) no void setup()

void random_number (short *x, short *y) { 
	
	*x = rand() % 4;
	*y = rand() % 20;

	while(1) {
		if(( *x >= 0 && *x <= 3 ) && ( *y >= 0 && *y <= 19 ))
			break;

		*x = rand() % 4;
		*y = rand() % 20;
	}
}
