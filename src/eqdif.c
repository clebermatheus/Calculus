#include <stdio.h>
#include <string.h>
#include "conio.h"
#include <math.h>

int maxPot = 10, cont, item, dados = 0, maiorPot = 0;
char func[300], eqdif[400];
float consFunc[10], consEd[10], constEd, valy, valx;

void menu(void);
void dadosin(void);
void calceqdif(void);

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
					calceqdif();
					printf("\n\nSolução da Equação Diferencial da função\n\ndy/dx = %s\n\n com as condições iniciais dadas (y = %4.2f em x = %4.2f), é:\n\nf(x) = %s\n", func, valx, valy, eqdif);
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
		printf("\n(2) - Calcular solução da equação diferencial\n\n->");
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
	printf("\nEntrando com a equação diferencial dy/dx: ");
	printf("\nEntre com o valor da maior potência de x da equação diferencial: ");
	do {
		scanf("%d", &maiorPot);
	} while(maiorPot > maxPot);
	for (cont = 0; cont < maiorPot + 1; cont++) {
		printf("\nEntre com o valor da constante da potência %d de x da equação diferencial: ", maiorPot - cont);
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
	printf("\nEntre com a condição inicial 'y': ");
	scanf("%f", &valy);
	printf("\nEntre com a condição inicial 'x': ");
	scanf("%f", &valx);
	clrscr();
	printf("\n\nA equação diferencial é:\ndy/dx = %s", func);
	printf("\n\nAs condições iniciais são:\ny = %4.2f em x = %4.2f", valy, valx);
	printf("\n\nDados completos! Pressione uma tecla...");
	while(!kbhit());
	dados = 1;
}

void calceqdif(void) {
	char functemp[20] = "";
	float valEd;

	for (cont = 0; cont < maiorPot + 1; cont++) {
		consEd[cont] = consFunc[cont] / (maiorPot - cont + 1);
	}
	strcpy(eqdif, "");
	for (cont = 0; cont < maiorPot + 1; cont++) {
		if (cont == 0) {
			if ((maiorPot - cont + 1) > 1) {
				sprintf(functemp, "%4.2fx^%d", consEd[cont], maiorPot - cont + 1);
				strcat(eqdif, functemp);
			} else if ((maiorPot - cont + 1) == 1) {
				sprintf(functemp, "%4.2fx", consEd[cont]);
				strcat(eqdif, functemp);
			} else if ((maiorPot - cont + 1) == 0) {
				sprintf(functemp, "%4.2f", consEd[cont]);
				strcat(eqdif, functemp);
			}
		} else if ((maiorPot - cont + 1) == 1) {
			if (consEd[cont] > 0) {
				sprintf(functemp, "+ %4.2fx", consEd[cont]);
				strcat(eqdif, functemp);
			} else if (consEd[cont] < 0) {
				sprintf(functemp, "%4.2fx", consEd[cont]);
				strcat(eqdif, functemp);
			}
		} else if (((maiorPot - cont + 1) > 1) && (cont != 0)) {
			if (consEd[cont] > 0) {
				sprintf(functemp, "+ %4.2fx^%d", consEd[cont], maiorPot - cont + 1);
				strcat(eqdif, functemp);
			} else if (consEd[cont] < 0) {
				sprintf(functemp, "%4.2fx^%d", consEd[cont], maiorPot - cont + 1);
				strcat(eqdif, functemp);
			}
		} else if ((maiorPot - cont + 1) == 0) {
			if (consEd[cont] > 0) {
				sprintf(functemp, "+ %4.2f", consEd[cont]);
				strcat(eqdif, functemp);
			} else if (consEd[cont] < 0) {
				sprintf(functemp, "%4.2f", consEd[cont]);
				strcat(eqdif, functemp);
			}
		}
	}
	valEd = 0;
	for (cont = 0; cont < maiorPot + 1; cont++) {
		if ((maiorPot + 1 - cont) > 0) {
			valEd = valEd + (consEd[cont] * pow(valx, (double) (maiorPot + 1 - cont)));
		} else valEd = valEd + consEd[cont];
	}
	constEd = valy - valEd;
	if (constEd > 0) {
		sprintf(functemp, "+ %4.2f", constEd);
	} else if (constEd < 0) {
		sprintf(functemp, "%4.2f", constEd);
	}
	strcat(eqdif, functemp);
}
