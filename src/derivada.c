#include <stdio.h>
#include <string.h>
#include <math.h>
#include "conio.h"

int maxPotNum = 10;
int maxPotDen = 10;
int cont, item, dados = 0;
int maiorPotNum = 0;
int maiorPotDen = 0;
char func[300];
char funcNum[300];
char funcDen[300];
char derNum[300];
char derDen[300];
char derivada[1000];
float consNum[10], consDen[10], consDerNum[10], consDerDen[10], consDerFunc[10], valX;
double epsilon = 1e-10, derFunc, valden = 0, valnum = 0;

void menu(void);
void dadosin(void);
void calcder(void);

int main() {
	clrscr();
	do {
		menu();
		switch (item) {
			case 1:
				dadosin();
				break;
			case 2:
				if (!dados) {
					printf("\nNão houve entrada de dados!\n");
					printf("Pressione uma tecla!");
					while (!kbhit());
				} else {
					calcder();
					printf("\n\nDerivada da função\n\nf(x) = %s\n\n no ponto dado é: \n\nf'(%4.2f) = %4.2lf\n", func, valX, derFunc);
					printf("\n\nA derivada da função\n\nf(x) = %s\n\né: \n\nf'(x) = %s\n\n", func, derivada);
					printf("Pressione uma tecla!");
					while(!kbhit());
				}
				break;
			case 0: break;
		}
	} while (item != 0);

	return 0;
}

void menu(void) {
	do {
		clrscr();
		printf("\n(0) - Sai");
		printf("\n(1) - Entrada de dados");
		printf("\n(2) - Calcular derivada da função\n\n->");
		scanf("%d", &item);
		if ((item > 2) || (item < 0)) {
			printf("Inválido! Pressione uma tecla!");
			while(!kbhit());
		}
	} while((item < 0) || (item > 2));
}

void dadosin(void) {
	char functemp[20] = "";

	clrscr();
	printf("\nEntrando com a função: ");
	printf("\nEntre com o valor da maior potência do numerador: ");
	do {
		scanf("%d", &maiorPotNum);
	} while(maiorPotDen > maxPotDen);
	for (cont = 0; cont < maiorPotNum + 1; cont++) {
		printf("\nEntre com o valor da constante da potência %d de x do numerador: ", maiorPotNum - cont);
		scanf("%f", &consNum[cont]);
	}
	if (maiorPotDen > 0) for (cont = 0; cont < maiorPotDen + 1; cont++) {
		printf("\nEntre com o vlaor da constante da potência %d de x do denominador: ", maiorPotDen - cont);
		scanf("%f", &consDen[cont]);
	}
	strcpy(funcNum, "(");
}
