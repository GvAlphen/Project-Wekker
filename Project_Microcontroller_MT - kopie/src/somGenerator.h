#ifndef SOMGENERATOR_H_
#define SOMGENERATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char * test();
char randomOperator();
char * generateSom();
void generatePlusSom(char address[]);
void generateMinSom(char address[]);
void initSomGenerator();
int randomNum(int min, int max);

#endif /* SOMGENERATOR_H_ */
