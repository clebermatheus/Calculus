#include <stdio.h>
#include <string.h>
#include <math.h>
#include "conio.h"

int item, dados = 0;
float coordsa[3], coordsb[3], coordvet[3], escalar, prodesc;
char veta[50], vetb[50], vetAxB[50], vetaA[50], vetaB[50], somaAB[50], subAB[50];

void menu(void);
void dadosin(void);
void cprods(void);

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
					cprods();
					printf("\nVetor A = %s\n\nVetor B = %s\n\n", veta, vetb);
					printf("Produto de:\n%4.2f x (%s) = %s\n\nProduto de %4.2f x (%s) = %s\n\n", escalar, veta, vetaA, escalar, vetb, vetaB);
					printf("Soma:\n(%s) + (%s) = %s\n\n", veta, vetb, somaAB);
					printf("Subtração:\n(%s) - (%s) = %s\n\n", veta, vetb, subAB);
					printf("Produto escalar:\n (%s) . (%s) = %f\n\n", veta, vetb, prodesc);
					printf("Produto vetorial:\n (%s) x (%s) = %s\n\n", veta, vetb, vetAxB);
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
		printf("\n(2) - Calcular\n\n->");
		scanf("%d", &item);
		if (item > 2 || item < 0) {
			printf("Inválido! Pressione uma tecla!");
			while(!kbhit());
		}
	} while(item < 0 || item > 2);
}

void dadosin(void) {
	char functemp[20] = "";
	int cont = 0;

	clrscr();
	printf("Entre com as constantes x, y e z do vetor A:\n->");
	do {
		scanf("%f", &coordsa[cont]);
		cont++;
	} while(cont < 3);
	printf("Entre com as constantes x, y e z do vetor B:\n->");
	cont = 0;
	do {
		scanf("%f", &coordsb[cont]);
		cont++;
	} while(cont < 3);
	printf("Entre com o valor escalar 'a' para multiplicar os vetores:\n->");
	scanf("%f", &escalar);

	strcpy(veta, "");
	for(cont = 0; cont < 3; cont++) {
		switch (cont) {
			case 0:
				if (coordsa[cont] != 0) {
					sprintf(functemp, "%4.2fax", coordsa[cont]);
					strcat(veta, functemp);
				}
				break;
			case 1:
				if (coordsa[cont] > 0) {
					sprintf(functemp, "+ %4.2fay", coordsa[cont]);
					strcat(veta, functemp);
				} else if (coordsa[cont] < 0) {
					sprintf(functemp, " %4.2fay", coordsa[cont]);
					strcat(veta, functemp);
				}
				break;
			case 2:
				if (coordsa[cont] > 0) {
					sprintf(functemp, "+ %4.2faz", coordsa[cont]);
					strcat(veta, functemp);
				} else if (coordsa[cont] < 0) {
					sprintf(functemp, " %4.2faz", coordsa[cont]);
					strcat(veta, functemp);
				}
				break;
			default: break;
		}
	}

	strcpy(vetb, "");
	for(cont = 0; cont < 3; cont++) {
		switch (cont) {
			case 0:
				if (coordsb[cont] != 0) {
					sprintf(functemp, "%4.2fax", coordsb[cont]);
					strcat(vetb, functemp);
				}
				break;
			case 1:
				if (coordsb[cont] > 0) {
					sprintf(functemp, "+ %4.2fay", coordsb[cont]);
					strcat(vetb, functemp);
				} else if (coordsb[cont] < 0) {
					sprintf(functemp, " %4.2fay", coordsb[cont]);
					strcat(vetb, functemp);
				}
				break;
			case 2:
				if (coordsb[cont] > 0) {
					sprintf(functemp, "+ %4.2faz", coordsb[cont]);
					strcat(vetb, functemp);
				} else if (coordsb[cont] < 0) {
					sprintf(functemp, " %4.2faz", coordsb[cont]);
					strcat(vetb, functemp);
				}
				break;
			default: break;
		}
	}

	printf("\n\nVetores:\nA = %s\nB = %s", veta, vetb);
	printf("\n\nEscalar:\na = %4.2f", escalar);
	printf("\n\nDados completos! Pressione uma tecla...");
	while(!kbhit());
	dados = 1;
}

void cprods(void) {
	int cont;
	float coordsomaAB[3], coordsubAB[3], coordsaA[3], coordsaB[3];
	char functemp[20] = "";

	for (cont = 0; cont < 3; cont++) {
		coordsomaAB[cont] = coordsa[cont] + coordsb[cont];
		coordsubAB[cont] = coordsa[cont] - coordsb[cont];
		coordsaA[cont] = coordsa[cont] * escalar;
		coordsaB[cont] = coordsb[cont] * escalar;
	}

	prodesc = 0;
	for(cont = 0; cont < 3; cont++) {
		prodesc = prodesc + coordsa[cont] * coordsb[cont];
	}

	coordvet[0] = coordsa[1] * coordsb[2] - coordsa[2] * coordsb[1];
	coordvet[1] = coordsa[2] * coordsb[0] - coordsa[0] * coordsb[2];
	coordvet[2] = coordsa[0] * coordsb[1] - coordsa[1] * coordsb[0];

	strcpy(somaAB, "");
	strcpy(subAB, "");
	strcpy(vetaA, "");
	strcpy(vetaB, "");
	strcpy(vetAxB, "");
	for(cont = 0; cont < 3; cont++) {
		switch (cont) {
			case 0:
				if (coordsomaAB[cont] != 0) {
					sprintf(functemp, "%4.2fax", coordsomaAB[cont]);
					strcat(somaAB, functemp);
				}
				if (coordsubAB[cont] != 0) {
					sprintf(functemp, "%4.2fax", coordsubAB[cont]);
					strcat(subAB, functemp);
				}
				if (coordsaA[cont] != 0) {
					sprintf(functemp, "%4.2fax", coordsaA[cont]);
					strcat(vetaA, functemp);
				}
				if (coordsaB[cont] != 0) {
					sprintf(functemp, "%4.2fax", coordsaB[cont]);
					strcat(vetaB, functemp);
				}
				if (coordvet[cont] != 0) {
					sprintf(functemp, "%4.2fax", coordvet[cont]);
					strcat(vetAxB, functemp);
				}
				break;
			case 1:
				if (coordsomaAB[cont] > 0) {
					sprintf(functemp, "+ %4.2fay", coordsomaAB[cont]);
					strcat(somaAB, functemp);
				} else if (coordsomaAB[cont] < 0) {
					sprintf(functemp, " %4.2fay", coordsomaAB[cont]);
					strcat(somaAB, functemp);
				}
				if (coordsubAB[cont] > 0) {
					sprintf(functemp, "+ %4.2fay", coordsubAB[cont]);
					strcat(subAB, functemp);
				} else if (coordsubAB[cont] < 0) {
					sprintf(functemp, " %4.2fay", coordsubAB[cont]);
					strcat(subAB, functemp);
				}
				if (coordsaA[cont] > 0) {
					sprintf(functemp, "+ %4.2fay", coordsaA[cont]);
					strcat(vetaA, functemp);
				} else if (coordsaA[cont] < 0) {
					sprintf(functemp, " %4.2fay", coordsaA[cont]);
					strcat(vetaA, functemp);
				}
				if (coordsaB[cont] > 0) {
					sprintf(functemp, "+ %4.2fay", coordsaB[cont]);
					strcat(vetaB, functemp);
				} else if (coordsaB[cont] < 0) {
					sprintf(functemp, " %4.2fay", coordsaB[cont]);
					strcat(vetaB, functemp);
				}
				if (coordvet[cont] > 0) {
					sprintf(functemp, "+ %4.2fay", coordvet[cont]);
					strcat(vetAxB, functemp);
				} else if (coordvet[cont] < 0) {
					sprintf(functemp, " %4.2fay", coordvet[cont]);
					strcat(vetAxB, functemp);
				}
				break;
			case 2:
				if (coordsomaAB[cont] > 0) {
					sprintf(functemp, "+ %4.2faz", coordsomaAB[cont]);
					strcat(somaAB, functemp);
				} else if (coordsomaAB[cont] < 0) {
					sprintf(functemp, " %4.2faz", coordsomaAB[cont]);
					strcat(somaAB, functemp);
				}
				if (coordsubAB[cont] > 0) {
					sprintf(functemp, "+ %4.2faz", coordsubAB[cont]);
					strcat(subAB, functemp);
				} else if (coordsubAB[cont] < 0) {
					sprintf(functemp, " %4.2faz", coordsubAB[cont]);
					strcat(subAB, functemp);
				}
				if (coordsaA[cont] > 0) {
					sprintf(functemp, "+ %4.2faz", coordsaA[cont]);
					strcat(vetaA, functemp);
				} else if (coordsaA[cont] < 0) {
					sprintf(functemp, " %4.2faz", coordsaA[cont]);
					strcat(vetaA, functemp);
				}
				if (coordsaB[cont] > 0) {
					sprintf(functemp, "+ %4.2faz", coordsaB[cont]);
					strcat(vetaB, functemp);
				} else if (coordsaB[cont] < 0) {
					sprintf(functemp, " %4.2faz", coordsaB[cont]);
					strcat(vetaB, functemp);
				}
				if (coordvet[cont] > 0) {
					sprintf(functemp, "+ %4.2faz", coordvet[cont]);
					strcat(vetAxB, functemp);
				} else if (coordvet[cont] < 0) {
					sprintf(functemp, " %4.2faz", coordvet[cont]);
					strcat(vetAxB, functemp);
				}
				break;
			default: break;
		}
	}

	if (vetAxB[0] == '\0') {
		strcat(vetAxB, "0");
	}
}
