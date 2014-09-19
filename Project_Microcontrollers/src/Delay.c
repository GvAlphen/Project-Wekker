#include <time.h>

void delay(unsigned int secs) {
    int retTime = time(0) + secs;
    while (time(0) < retTime){}
}
