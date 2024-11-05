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
	for (cont = 0; cont < maiorPotNum + 1; cont++) {
		if (cont == 0) {
			if ((maiorPotNum - cont) > 1) {
				sprintf(functemp, "%4.2fx^%d", consNum[cont], maiorPotNum - cont);
				strcat(funcNum, functemp);
			} else if ((maiorPotNum - cont) == 1) {
				sprintf(functemp, "%4.2fx", consNum[cont]);
				strcat(funcNum, functemp);
			} else if ((maiorPotNum - cont) == 0) {
				sprintf(functemp, "%4.2f", consNum[cont]);
				strcat(funcNum, functemp);
			}
		} else if ((maiorPotNum - cont) == 1) {
			if (consNum[cont] > 0) {
				sprintf(functemp, "+ %4.2fx", consNum[cont]);
				strcat(funcNum, functemp);
			} else if (consNum[cont] < 0) {
				sprintf(functemp, "%4.2fx", consNum[cont]);
				strcat(funcNum, functemp);
			}
		} else if (((maiorPotNum - cont) > 1) && (cont != 0)) {
			if (consNum[cont] > 0) {
				sprintf(functemp, "+ %4.2fx^%d", consNum[cont], maiorPotNum - cont);
				strcat(funcNum, functemp);
			} else if (consNum[cont] < 0) {
				sprintf(functemp, "%4.2fx^%d", consNum[cont], maiorPotNum - cont);
				strcat(funcNum, functemp);
			}
		} else if ((maiorPotNum - cont) == 0) {
			if (consNum[cont] > 0) {
				sprintf(functemp, "+ %4.2f", consNum[cont]);
				strcat(funcNum, functemp);
			} else if (consNum[cont] < 0) {
				sprintf(functemp, "%4.2f", consNum[cont]);
				strcat(funcNum, functemp);
			}
		}
	}
	strcat(funcNum, ")");
	strcat(func, funcNum);
	if (maiorPotDen > 0) {
		strcat(func, "/");
		strcat(funcDen, "(");
		for (cont = 0; cont < maiorPotDen + 1; cont++) {
			if (cont == 0) {
				if ((maiorPotDen - cont) > 1) {
					sprintf(functemp, "%4.2fx^%d", consDen[cont], maiorPotDen - cont);
					strcat(funcDen, functemp);
				} else if ((maiorPotDen - cont) == 1) {
					sprintf(functemp, "%4.2fx", consDen[cont]);
					strcat(funcDen, functemp);
				} else if ((maiorPotDen - cont) == 0) {
					sprintf(functemp, "%4.2f", consDen[cont]);
					strcat(funcDen, functemp);
				}
			} else if ((maiorPotDen - cont) == 1) {
				if (consDen[cont] > 0) {
					sprintf(functemp, "+ %4.2fx", consDen[cont]);
					strcat(funcDen, functemp);
				} else if (consDen[cont] < 0) {
					sprintf(functemp, "%4.2fx", consDen[cont]);
					strcat(funcDen, functemp);
				}
			} else if (((maiorPotDen - cont) > 1) && (cont != 0)) {
				if (consDen[cont] > 0) {
					sprintf(functemp, "+ %4.2fx^%d", consDen[cont], maiorPotDen - cont);
					strcat(funcDen, functemp);
				} else if (consDen[cont] < 0) {
					sprintf(functemp, "%4.2fx^%d", consDen[cont], maiorPotDen - cont);
					strcat(funcDen, functemp);
				}
			} else if ((maiorPotDen - cont) == 0) {
				if (consDen[cont] > 0) {
					sprintf(functemp, "+ %4.2f", consDen[cont]);
					strcat(funcDen, functemp);
				} else if (consDen[cont] < 0) {
					sprintf(functemp, "%4.2f", consDen[cont]);
					strcat(funcDen, functemp);
				}
			}
		}
		strcat(funcDen, ")");
		strcat(func, funcDen);
	}
	printf("\nEntre com o valor do ponto a ser calculado a derivada: ");
	scanf("%f", &valX);
	clrscr();
	printf("\n\nA função é:\nf(x) = %s", func);
	printf("\n\nO ponto a ser calculado a derivada é:\nx = %4.2f", valX);
	printf("\n\nO valor de epsilon considerado é:\nepsilon = %4.2e", epsilon);
	printf("\n\nDados completos! Pressione uma tecla...");
	while(!kbhit());
	dados = 1;
}

void calcder(void) {
	char functemp[20] = "";
	double valden1 = 0, valnum1 = 0, derFunc1 = 0;

	valden = 0;
	valnum = 0;
	for (cont = 0; cont < maiorPotDen + 1; cont++) {
		valden = valden + consDen[cont] * pow(valX + epsilon, (double) maiorPotDen - cont);
		valden1 = valden1 + consDen[cont] * pow(valX, (double) maiorPotDen - cont);
	}
	for (cont = 0; cont < maiorPotNum + 1; cont++) {
		valnum = valnum + consNum[cont] * pow(valX + epsilon, (double) (maiorPotNum - cont));
		valnum1 = valnum1 + consNum[cont] * pow(valX, (double) (maiorPotNum - cont));
	}
	if (valden != 0.0) derFunc = valnum/valden;
	else derFunc = valnum;

	if (valden1 != 0.0) derFunc1 = valnum1/valden1;
	else derFunc1 = valnum1;

	derFunc = (derFunc - derFunc1)/epsilon;

	for (cont = 0; cont < maiorPotNum + 1; cont++) {
		consDerNum[cont] = consNum[cont] * (maiorPotNum - cont);
	}
	for (cont = 0; cont < maiorPotDen + 1; cont++) {
		consDerDen[cont] = consDen[cont] * (maiorPotDen - cont);
	}
	strcpy(derNum, "(");
	for (cont = 0; cont < maiorPotNum; cont++) {
		if (cont == 0) {
			if ((maiorPotNum - cont) > 1) {
				sprintf(functemp, "%4.2fx^%d", consDerNum[cont], maiorPotNum - cont - 1);
				strcat(derNum, functemp);
			} else if ((maiorPotNum - cont - 1) == 1) {
				sprintf(functemp, "+ %4.2fx", consDerNum[cont]);
				strcat(derNum, functemp);
			} else if ((maiorPotNum - cont - 1) == 0) {
				sprintf(functemp, "+ %4.2f", consDerNum[cont]);
				strcat(derNum, functemp);
			}
		} else if ((maiorPotNum - cont - 1) == 1) {
			if (consDerNum[cont] > 0) {
				sprintf(functemp, "+ %4.2fx", consDerNum[cont]);
				strcat(derNum, functemp);
			} else if (consDerNum[cont] < 0) {
				sprintf(functemp, "%4.2fx", consDerNum[cont]);
				strcat(derNum, functemp);
			}
		} else if (((maiorPotNum - cont - 1) > 1) && (cont != 0)) {
			if (consDerNum[cont] > 0) {
				sprintf(functemp, "+ %4.2fx^%d", consDerNum[cont], maiorPotNum - cont - 1);
				strcat(derNum, functemp);
			} else if (consDerNum[cont] < 0) {
				sprintf(functemp, "%4.2fx^%d", consDerNum[cont], maiorPotNum - cont - 1);
				strcat(derNum, functemp);
			}
		} else if ((maiorPotNum - cont - 1) == 0) {
			if (consDerNum[cont] > 0) {
				sprintf(functemp, "+ %4.2f", consDerNum[cont]);
				strcat(derNum, functemp);
			} else if (consDerNum[cont] < 0) {
				sprintf(functemp, "%4.2f", consDerNum[cont]);
				strcat(derNum, functemp);
			}
		}
	}
	strcat(derNum, ") ");
	if (maiorPotDen > 0) {
		strcpy(derDen, " (");
		for (cont = 0; cont < maiorPotDen; cont++) {
			if (cont == 0) {
				if ((maiorPotDen - cont - 1) > 1) {
					sprintf(functemp, "%4.2fx^%d", consDerDen[cont], maiorPotDen - cont - 1);
					strcat(derDen, functemp);
				} else if ((maiorPotDen - cont - 1) == 1) {
					sprintf(functemp, "%4.2fx", consDerDen[cont]);
					strcat(derDen, functemp);
				} else if ((maiorPotDen - cont - 1) == 0) {
					sprintf(functemp, "%4.2f", consDerDen[cont]);
					strcat(derDen, functemp);
				}
			} else if ((maiorPotDen - cont - 1) == 1) {
				if (consDerDen[cont] > 0) {
					sprintf(functemp, "+ %4.2fx", consDerDen[cont]);
					strcat(derDen, functemp);
				} else if (consDerDen[cont] < 0) {
					sprintf(functemp, "%4.2fx", consDerDen[cont]);
					strcat(derDen, functemp);
				}
			} else if (((maiorPotDen - cont - 1) > 1) && (cont != 0)) {
				if (consDerDen[cont] > 0) {
					sprintf(functemp, "+ %4.2fx^%d", consDerDen[cont], maiorPotDen - cont - 1);
					strcat(derDen, functemp);
				} else if (consDerDen[cont] < 0) {
					sprintf(functemp, "%4.2fx^%d", consDerDen[cont], maiorPotDen - cont - 1);
					strcat(derDen, functemp);
				}
			} else if ((maiorPotDen - cont - 1) == 0) {
				if (consDerDen[cont] > 0) {
					sprintf(functemp, "+ %4.2f", consDerDen[cont]);
					strcat(derDen, functemp);
				} else if (consDerDen[cont] < 0) {
					sprintf(functemp, "%4.2f", consDerDen[cont]);
					strcat(derDen, functemp);
				}
			}
		}
		strcat(derDen, ") ");
	}
	if (maiorPotDen > 0) {
		strcpy(derivada, "[");
		strcpy(derivada, derDen);
		strcpy(derivada, funcNum);
		strcpy(derivada, " - ");
		strcpy(derivada, derNum);
		strcpy(derivada, funcDen);
		strcpy(derivada, "] / ");
		strcpy(derivada, funcDen);
		strcpy(derivada, "^2");
	} else strcpy(derivada, derNum);
}
