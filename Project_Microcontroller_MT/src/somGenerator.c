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

	sprintf(buff, "%d%c%d=%d", firstNum, op, secondNum, answer);
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
