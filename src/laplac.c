#include <stdio.h>
#include "conio.h"
#include <string.h>

int item, dados = 0, nFunc, nLaplacx, nLaplacy, nLaplacz;
float consfunc[10][4], conslaplacx[10], conslaplacy[10], conslaplacz[10];
char mudaDados[2] = "", laplac[1000], func[1000], functemp[100] = "";

void menu(void);
void dadosin(void);
void calclaplac(void);

int main () {
	clrscr();
	do {
		menu();
		switch (item) {
			case 1:
				dadosin();
				break;
			case 2:
				if (!dados) {
					printf("\nNão houve entrada de dados do campo para o cálculo do laplaciano!\n");
					printf("Pressione uma tecla!");
					while (!kbhit());
				} else {
					calclaplac();
					clrscr();
					printf("\n\nLaplaciano do Campo:\n\nf(x, y, z) = %s\n\né\n\nlaplac(f) = %s\n\n", func, laplac);
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
		printf("\n(2) - Calcular Laplaciano do campo\n\n->");
		scanf("%d", &item);
		if (item > 2 || item < 0) {
			printf("Inválido! Pressione uma tecla!");
			while(!kbhit());
		}
	} while(item < 0 || item > 2);
}

void dadosin(void) {
	int x = 0;

	clrscr();
	strcpy(mudaDados, "s");
	if (dados == 1) {
		do {
			printf("\nDeseja mudar os dados do campo escalar? (s/n)\n->");
			scanf("%s", mudaDados);
		} while(strcmp(mudaDados, "s") && strcmp(mudaDados, "n"));
	}
	if (mudaDados[0] == 's') {
		do {
			printf("\n\n\nEntre com o %dº termo do campo escalar (termos k, p1, p2, p3, separados por espaços, para cada elemento na forma k*x^p1*y^p2*z^p3. k = 0 0 0 0 - quatros Zeros - para finalizar) \nMáximo de 10 termos!\n->", x + 1);
			scanf("%f %f %f %f", &consfunc[x][0], &consfunc[x][1], &consfunc[x][2], &consfunc[x][3]);
			x++;
		} while(x < 10 && consfunc[x - 1][0] != 0);
		nFunc = x;
		x = 0;
		strcpy(func, "");
		for (x = 0; x < nFunc; x++) {
			if (consfunc[x][0] != 0) {
				sprintf(functemp, "%4.2f*", consfunc[x][0]);
				strcat(func, functemp);
			}
			if (consfunc[x][1] != 0) {
				if (consfunc[x][1] != 1) {
					sprintf(functemp, "x^(%4.2f)", consfunc[x][1]);
					strcat(func, functemp);
				} else strcat(func, "x");
			}
			if ((consfunc[x][1] != 0) && (consfunc[x][2] != 0)) strcat(func, "*");
			if (consfunc[x][2] != 0) {
				if (consfunc[x][2] != 1) {
					sprintf(functemp, "y^(%4.2f)", consfunc[x][2]);
					strcat(func, functemp);
				} else strcat(func, "y");
			}
			if (((consfunc[x][1] != 0) && (consfunc[x][3] != 0)) || ((consfunc[x][2] != 0) && (consfunc[x][3] != 0))) strcat(func, "*");
			if (consfunc[x][3] != 0) {
				if (consfunc[x][3] != 1) {
					sprintf(functemp, "z^(%4.2f)", consfunc[x][3]);
					strcat(func, functemp);
				} else strcat(func, "z");
			}
			if ((consfunc[x + 1][0] > 0) && (x < nFunc)) strcat(func, " + ");
		}
	}
	printf("\n\n\n\n\nCampo Escalar:\n\nf(x, y, z) = %s\n", func);
	printf("\nDados Completos| Pressione uma tecla...");
	while(!kbhit());
	dados = 1;
}

void calclaplac(void) {
	int x, cont1 = 0;

	nLaplacx = 0;
	nLaplacy = 0;
	nLaplacz = 0;

	for (x = 0; x < nFunc; x++) {
		if (consfunc[x][1] > 1) {
			conslaplacx[x] = consfunc[x][0] * consfunc[x][1] * (consfunc[x][1] - 1);
			nLaplacx++;
		}
		if (consfunc[x][2] > 1) {
			conslaplacy[x] = consfunc[x][0] * consfunc[x][2] * (consfunc[x][2] - 1);
			nLaplacy++;
		}
		if (consfunc[x][3] > 1) {
			conslaplacz[x] = consfunc[x][0] * consfunc[x][3] * (consfunc[x][3] - 1);
			nLaplacz++;
		}
	}
	if (nLaplacx != 0) strcpy(laplac, "[");
	for (x = 0; x < nLaplacx; x++) {
		if (conslaplacx[x] != 0) {
			sprintf(functemp, "%4.2f*", conslaplacx[x]);
			strcat(laplac, functemp);
			if (((consfunc[x][1] - 2) != 1) && ((consfunc[x][1] - 2) != 0)) {
				sprintf(functemp, "x^(%4.2f)", consfunc[x][1] - 2);
				strcat(laplac, functemp);
			} else if ((consfunc[x][1] - 2) == 1) strcat(laplac, "x");
			if (consfunc[x][2] != 0) {
				if (consfunc[x][2] != 1) {
					sprintf(functemp, "y^(%4.2f)", consfunc[x][2]);
					strcat(laplac, functemp);
				} else strcat(laplac, "y");
			}
			if (consfunc[x][3] != 0) {
				if (consfunc[x][3] != 1) {
					sprintf(functemp, "z^(%4.2f)", consfunc[x][3]);
					strcat(laplac, functemp);
				} else strcat(laplac, "z");
			}
		}
		if (x < nLaplacx - 1) strcat(laplac, " + ");
	}
	if (nLaplacx != 0) strcat(laplac, "]");
	if ((nLaplacx != 0) && (nLaplacy != 0)) strcat(laplac, " + ");
	if (nLaplacy != 0) strcat(laplac, "[");
	for (x = 0; x < nLaplacy; x++) {
		if (conslaplacy[x] != 0) {
			sprintf(functemp, "%4.2f*", conslaplacy[x]);
			strcat(laplac, functemp);
			if (consfunc[x][1] != 1) {
				sprintf(functemp, "x^(%4.2f)", consfunc[x][1]);
				strcat(laplac, functemp);
			} else strcat(laplac, "x");
			if (((consfunc[x][2] - 2) != 1) && ((consfunc[x][2] - 2) != 0)) {
				sprintf(functemp, "y^(%4.2f)", consfunc[x][2] - 2);
				strcat(laplac, functemp);
			} else if ((consfunc[x][2] - 2) == 1) strcat(laplac, "y");
			if (consfunc[x][3] != 0) {
				if (consfunc[x][3] != 1) {
					sprintf(functemp, "z^(%4.2f)", consfunc[x][3]);
					strcat(laplac, functemp);
				} else strcat(laplac, "z");
			}
		}
		if (x < nLaplacy - 1) strcat(laplac, " + ");
	}
	if (nLaplacy != 0) strcat(laplac, "]");
	if (((nLaplacx != 0) && (nLaplacz != 0)) || ((nLaplacy != 0) && (nLaplacz != 0))) strcat(laplac, " + ");
	if (nLaplacz != 0) strcat(laplac, "[");
	for (x = 0; x < nLaplacz; x++) {
		if (conslaplacz[x] != 0) {
			sprintf(functemp, "%4.2f*", conslaplacz[x]);
			strcat(laplac, functemp);
			if (consfunc[x][1] != 1) {
				sprintf(functemp, "x^(%4.2f)", consfunc[x][1]);
				strcat(laplac, functemp);
			} else strcat(laplac, "x");
			if (consfunc[x][2] != 0) {
				if (consfunc[x][2] != 1) {
					sprintf(functemp, "y^(%4.2f)", consfunc[x][2]);
					strcat(laplac, functemp);
				} else strcat(laplac, "y");
			}
			if (((consfunc[x][3] - 2) != 1) && ((consfunc[x][3] - 2) != 0)) {
				sprintf(functemp, "z^(%4.2f)", consfunc[x][3] - 2);
				strcat(laplac, functemp);
			} else if ((consfunc[x][3] - 2) == 1) strcat(laplac, "z");
		}
		if (x < nLaplacz - 1) strcat(laplac, " + ");
	}
	if (nLaplacz != 0) strcat(laplac, "]");
}
