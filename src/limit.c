#include <stdio.h>
#include <string.h>
#include "conio.h"
#include <math.h>

int maxPotNum = 10;
int maxPotDen = 10;
int cont, item, dados = 0;
int maiorPotNum = 0;
int maiorPotDen = 0;
int tipodafunc = 0;
char tipoFunc[2][20] = {"definida no ponto", "idefinidada no ponto"};
char func[300];
float consNum[10], consDen[10], valX;
double epsilon = 1e-2, limFunc, valDen = 0, valNum = 0;

void menu(void);
void dadosin(void);
void calclim(void);

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
					calclim();
					printf("\n\nLimite para x -> %4.2f da função\n\nf(x) = %s\n\né: \n\nlim f(x) = %4.2lf\nx -> %4.2f", valX, func, limFunc, valX);
					printf("\n\nA função é %s no ponto x = %f\n\n", tipoFunc[tipodafunc], valX);
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
		printf("\n(0) - Sai");
		printf("\n(1) - Entrada de dados");
		printf("\n(2) - Calcular limite da função\n\n->");
		scanf("%d", &item);
		if (item > 2 || item < 0) {
			printf("Inválido! Pressione uma tecla!");
			while(!kbhit());
		}
	} while(item < 0 || item > 2);
}

void dadosin(void) {
	char functemp[20] = "";
	int cden = 0;
	clrscr();
	printf("\nEntrando com a função: ");
	printf("\nEntre com o valor da maior potência do numerador: ");
	do {
		scanf("%d", &maiorPotNum);
	} while(maiorPotNum > maxPotNum);
	printf("\nEntre com o valor da maior potência do denominador: ");
	do {
		scanf("%d", &maiorPotDen);
	} while(maiorPotDen > maxPotDen);
	for (int cont = 0; cont < maiorPotNum + 1; cont++) {
		printf("\nEntre com o valor da constante da potência %d de x do numerador: ", maiorPotNum - cont);
		scanf("%f", &consNum[cont]);
	}
	if (maiorPotDen > 0) {
		for (int cont = 0; cont < maiorPotDen + 1; cont++) {
			printf("\nEntre com o valor da cosntante da potência %d de x do denominador: ", maiorPotDen - cont);
			scanf("%f", &consDen[cont]);
		}
	} else if (maiorPotDen == 0) {
		printf("\nHá alguma cosntante no denominador? (para nõa digite 0)\n");
		scanf("%d", &cden);
		if (cden != 0) {
			printf("Entre com o valor dessa constante: ");
			scanf("%f", &consDen[maiorPotDen]);
		}
	}
	strcpy(func, "(");
	for (int cont = 0; cont < maiorPotNum + 1; cont++) {
		if (cont == 0) {
			if ((maiorPotNum - cont) > 1) {
				sprintf(functemp, "%4.2fx^%d", consNum[cont], maiorPotNum - cont);
			} else if ((maiorPotNum - cont) == 1) {
				sprintf(functemp, "%4.2fx", consNum[cont]);
			} else if ((maiorPotNum - cont) == 0) {
				sprintf(functemp, "%4.2f", consNum[cont]);
			}
		} else if ((maiorPotNum - cont) == 1) {
			if (consNum[cont] > 0) {
				sprintf(functemp, "+ %4.2fx", consNum[cont]);
			} else if (consNum[cont] < 0) {
				sprintf(functemp, "%4.2fx", consNum[cont]);
			}
		} else if (((maiorPotNum - cont) > 1) && (cont != 0)) {
			if (consNum[cont] > 0) {
				sprintf(functemp, "+ %4.2fx^%d", consNum[cont], maiorPotNum - cont);
			} else if (consNum[cont] < 0) {
				sprintf(functemp, "%4.2fx^%d", consNum[cont], maiorPotNum - cont);
			}
		} else if ((maiorPotNum - cont) == 0) {
			if (consNum[cont] > 0) {
				sprintf(functemp, "+ %4.2f", consNum[cont]);
			} else if (consNum[cont] < 0) {
				sprintf(functemp, "%4.2f", consNum[cont]);
			}
		}
		strcat(func, functemp);
	}
	strcat(func, ")");
	if (maiorPotDen > 0) {
		strcat(func, "/");
		strcat(func, "(");
		for (int cont = 0; cont < maiorPotDen + 1; cont++) {
			if (cont == 0) {
				if ((maiorPotDen - cont) > 1) {
					sprintf(functemp, "%4.2fx^%d", consDen[cont], maiorPotDen - cont);
					strcat(func, functemp);
				} else if ((maiorPotDen - cont) == 1) {
					sprintf(functemp, "%4.2fx", consDen[cont]);
					strcat(func, functemp);
				} else if ((maiorPotDen - cont) == 0) {
					sprintf(functemp, "%4.2f", consDen[cont]);
					strcat(func, functemp);
				}
			} else if ((maiorPotDen - cont) == 1) {
				if (consDen[cont] > 0) {
					sprintf(functemp, "+ %4.2fx", consDen[cont]);
					strcat(func, functemp);
				} else if (consDen[cont] < 0) {
					sprintf(functemp, "%4.2fx", consDen[cont]);
					strcat(func, functemp);
				}
			} else if (((maiorPotDen - cont) > 1) && (cont != 0)) {
				if (consDen[cont] > 0) {
					sprintf(functemp, "+ %4.2fx^%d", consDen[cont], maiorPotDen - cont);
					strcat(func, functemp);
				} else if (consDen[cont] < 0) {
					sprintf(functemp, "%4.2fx^%d", consDen[cont], maiorPotDen - cont);
					strcat(func, functemp);
				}
			} else if ((maiorPotDen - cont) == 0) {
				if (consDen[cont] > 0) {
					sprintf(functemp, "+ %4.2f", consDen[cont]);
					strcat(func, functemp);
				} else if (consDen[cont] < 0) {
					sprintf(functemp, "%4.2f", consDen[cont]);
					strcat(func, functemp);
				}
			}
		}
		strcat(func, ")");
	}
	printf("\nEntre com o valor do ponto a ser calculado o limite: ");
	scanf("%f", &valX);
	printf("\nO valor de epsilon é definido como %lf. Digite seu novo valor: ", epsilon);
	scanf("%lf", &epsilon);

	clrscr();
	printf("\n\nA função é:\nf(x) = %s", func);
	printf("\n\nO ponto a ser calculado o limite é:\nx = %4.2f", valX);
	printf("\n\nO valor de epsilon considerado é:\nepsilon = %lf", epsilon);

	printf("\n\nDados completos: Pressione uma tecla...");
	while(!kbhit());
	dados = 1;
}

void calclim(void) {
	valDen = 0;
	valNum = 0;

	for (cont = 0; cont < maiorPotDen + 1; cont++)
		valDen = valDen  + consDen[cont] * pow(valX, maiorPotDen - cont);

	if (valDen <= 1e-6) {
		tipodafunc = 1;
		for (cont = 0; cont < maiorPotDen + 1; cont++)
			valDen = valDen + consDen[cont] * pow(valX - epsilon, (double) (maiorPotDen - cont));
	} else tipodafunc = 0;

	for (cont = 0; cont < maiorPotNum + 1; cont++)
		valNum = valNum + consNum[cont] * pow(valX - epsilon, (double) (maiorPotNum - cont));

	if (valDen != 0.0)
		limFunc = valNum/valDen + 10*epsilon;
	else
		limFunc = valNum + 10*epsilon;
}
