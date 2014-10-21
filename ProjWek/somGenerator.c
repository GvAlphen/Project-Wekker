#ifndef SOMGENERATOR_H_
#define SOMGENERATOR_H_

#include "somGenerator.h"

/*int main(){
	char *str;
	int i;
	initSomGenerator();

	for (i = 0; i < 100; i++){
		str = generateSom();
		printf("%s\n", str);
	}
	free(str);
}*/

//Returns a pointer to a string or something
char* generateSom(){
	char op = randomOperator();
	char buff[11];
	char num1buff[3];
	char num2buff[3];
	char* som = malloc(sizeof(char) * 11);

	int firstNum = randomNum(0, 99);
	int secondNum;
	int answer;

	if (op != '-'){
		secondNum = randomNum(0, 99);
	} else {
		secondNum = randomNum(0, (firstNum - 1));
	}

	switch (op){
	case '+':
		answer = firstNum + secondNum;
		break;
	case '-':
		answer = firstNum - secondNum;
		break;
	case '*':
		answer = firstNum * secondNum;
		break;
	case '/':
		//Speciale methode, dank aan Arjan!
		answer = randomNum(1, 99);
		secondNum = randomNum(1, ((int) 100 / answer));
		firstNum = answer * secondNum;
		break;
	}

	if(firstNum < 10){
		sprintf(num1buff, "0%d", firstNum);
	} else {
		sprintf(num1buff, "%d", firstNum);
	}

	if(secondNum < 10){
		sprintf(num2buff, "0%d", secondNum);
	} else {
		sprintf(num2buff, "%d", secondNum);
	}

	sprintf(buff, "%s%c%s=%d", num1buff, op, num2buff, answer);
	strncpy(som, buff, 11);
	return som;
}

char randomOperator(){
	char operators[4] = { '+', '-', '*', '/' };
	return operators[randomNum(0, 3)];
}

//Gives the RNG a seed to work with
void initSomGenerator(){
	srand((unsigned int)time(NULL));
}

//Returns an int between the min and max values
//So if max/min = 10, 10 can also be returned!!!
int randomNum(int min, int max){
	int r;

	r = rand() % ((max - min) + 1) + min;
	return r;
}

#endif /* SOMGENERATOR_H_ */
