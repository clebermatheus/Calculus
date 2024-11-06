#include <stdio.h>
#include <string.h>
#include "conio.h"
#include <math.h>

int maxPot = 10, cont, item, dados = 0, maiorPot = 0;
char func[300], integral[400];
float consFunc[10], consInt[10], valXa, valXb;
double epsilon = 1e-6, intFunc;

void menu(void);
void dadosin(void);
void calcint(void);

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
					calcint();
					printf("\n\nIntegral definida da função\n\nf(x) = %s\n\n entre os pontos de dados (a = %4.2f e b = %4.2f), considerando a constante de integração igual a zero, é:\n\nInt[f(%s)] = %4.2e\n", func, valXa, valXb, func, intFunc);
					printf("\n\nA integral da função\n\nf(x) = %s\n\nconsiderando a constante de integração igual a zero, é: \n\nInt[f(x)] = %s\n\n", func, integral);
					printf("Pressione uma tecla!");
					while(!kbhit());
				}
				break;
			case 0:
				break;
		}
	} while (item != 0);

	return 0;
}

void menu(void) {
	do {
		clrscr();
		printf("\n(0) - Sair");
		printf("\n(1) - Entrada de dados");
		printf("\n(2) - Calcular integral da função\n\n->");
		scanf("%d", &item);
		if (item > 2 || item < 0) {
			printf("Inválido! Pressione uma tecla!");
			while(!kbhit());
		}
	} while(item < 0 || item > 2);
}

void dadosin(void) {
	char functemp[20] = "";

	clrscr();
	printf("\nEntrando com a função: ");
	printf("\nEntre com o valor da maior potência da função: ");
	do {
		scanf("%d", &maiorPot);
	} while(maiorPot > maxPot);
	for (cont = 0; cont < maiorPot + 1; cont++) {
		printf("\nEntre com o valor da constante da potência %d de x da função: ", maiorPot - cont);
		scanf("%f", &consFunc[cont]);
	}
	for (cont = 0; cont < maiorPot + 1; cont++) {
		if (cont == 0) {
			if ((maiorPot - cont) > 1) {
				sprintf(functemp, "%4.2fx^%d", consFunc[cont], maiorPot - cont);
				strcat(func, functemp);
			} else if ((maiorPot - cont) == 1) {
				sprintf(functemp, "%4.2fx", consFunc[cont]);
				strcat(func, functemp);
			} else if ((maiorPot - cont) == 0) {
				sprintf(functemp, "%4.2f", consFunc[cont]);
				strcat(func, functemp);
			}
		} else if ((maiorPot - cont) == 1) {
			if (consFunc[cont] > 0) {
				sprintf(functemp, "+ %4.2fx", consFunc[cont]);
				strcat(func, functemp);
			} else if (consFunc[cont] < 0) {
				sprintf(functemp, "%4.2fx", consFunc[cont]);
				strcat(func, functemp);
			}
		} else if (((maiorPot - cont) > 1) && (cont != 0)) {
			if (consFunc[cont] > 0) {
				sprintf(functemp, "+ %4.2fx^%d", consFunc[cont], maiorPot - cont);
				strcat(func, functemp);
			} else if (consFunc[cont] < 0) {
				sprintf(functemp, "%4.2fx^%d", consFunc[cont], maiorPot - cont);
				strcat(func, functemp);
			}
		} else if ((maiorPot - cont) == 0) {
			if (consFunc[cont] > 0) {
				sprintf(functemp, "+ %4.2f", consFunc[cont]);
				strcat(func, functemp);
			} else if (consFunc[cont] < 0) {
				sprintf(functemp, "%4.2f", consFunc[cont]);
				strcat(func, functemp);
			}
		}
	}
	printf("\nEntre com o valor do ponto inicial 'a' a ser calculada a integral: ");
	scanf("%f", &valXa);
	printf("\nEntre com o valor do ponto final 'b' a ser calculada a integral: ");
	scanf("%f", &valXb);

	clrscr();
	printf("\n\nA função é:\nf(x) = %s", func);
	printf("\n\nOs pontos a ser calculados a integral são:\na = %4.2f, b = %4.2f", valXa, valXb);
	printf("\n\nO valor de epsilon considerado é:\nepsilon = %4.2e", epsilon);
	printf("\n\nDados completos: Pressione uma tecla...");
	while(!kbhit());
	dados = 1;
}

void calcint(void) {
	char functemp[20] = "";
	int cont1, cont2;
	double intFunc1;

	intFunc = 0;
	cont2 = (int) ((valXb - valXa)/epsilon);

	for (cont1 = 0; cont1 < cont2; cont1++) {
		intFunc1 = 0;
		for (cont = 0; cont < maiorPot + 1; cont++) {
			if ((maiorPot - cont) > 0) {
				intFunc1 = intFunc1 + consFunc[cont] * pow(valXa + cont1 * epsilon, (double) (maiorPot - cont));
			} else {
				intFunc1 = intFunc1 + consFunc[cont];
			}
			intFunc = intFunc + intFunc1;
		}
		intFunc = intFunc * epsilon;
		for (cont = 0; cont < maiorPot + 1; cont++) {
			consInt[cont] = consFunc[cont] / (maiorPot - cont + 1);
		}
		strcpy(integral, "");
		for(cont = 0; cont < maiorPot + 1; cont++) {
			if (cont == 0) {
				if ((maiorPot - cont + 1) > 1) {
					sprintf(functemp, "%4.2fx^%d", consInt[cont], maiorPot - cont + 1);
					strcat(integral, functemp);
				} else if ((maiorPot - cont + 1) == 1) {
					sprintf(functemp, "%4.2fx", consInt[cont]);
					strcat(integral, functemp);
				} else if ((maiorPot - cont + 1) == 0) {
					sprintf(functemp, "%4.2f", consInt[cont]);
					strcat(integral, functemp);
				}
			} else if ((maiorPot - cont + 1) == 1) {
				if (consInt[cont] > 0) {
					sprintf(functemp, "+ %4.2fx", consInt[cont]);
					strcat(integral, functemp);
				} else if (consInt[cont] < 0) {
					sprintf(functemp, "%4.2fx", consInt[cont]);
					strcat(integral, functemp);
				}
			} else if (((maiorPot - cont + 1) > 1) && (cont != 0)) {
				if (consInt[cont] > 0) {
					sprintf(functemp, "+ %4.2fx^%d", consInt[cont], maiorPot - cont + 1);
					strcat(integral, functemp);
				} else if (consInt[cont] < 0) {
					sprintf(functemp, "%4.2fx^%d", consInt[cont], maiorPot - cont + 1);
					strcat(integral, functemp);
				}
			} else if ((maiorPot - cont + 1) == 0) {
				if (consInt[cont] > 0) {
					sprintf(functemp, "+ %4.2f", consInt[cont]);
					strcat(integral, functemp);
				} else if (consInt[cont] < 0) {
					sprintf(functemp, "%4.2f", consInt[cont]);
					strcat(integral, functemp);
				}
			}
		}
	}
}
