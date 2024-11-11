#include <stdio.h>
#include "conio.h"
#include <string.h>

int item, dados = 0, ncampoesc, ngAx, ngAy, ngAz;
float ax[10][4], ay[10][4], az[10][4], campoesc[10][4];
char mudaDados[2] = "", campovet[1000], func[1000], functemp[100] = "";

void menu(void);
void dadosin(void);
void calcgrad(void);

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
					printf("\nNão houve entrada de dados para cálculo do gradiente!\n");
					printf("Pressione uma tecla!");
					while (!kbhit());
				} else {
					calcgrad();
					clrscr();
					printf("\nGradiente do Potencial:\n\nfV(x, y, z) = %s\n\né\n\ngrad(V) = %s\n\n", func, campovet);
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
		printf("\n(2) - Calcular Gradiente\n\n->");
		scanf("%d", &item);
		if (item > 2 || item < 0) {
			printf("Inválido! Pressione uma tecla!");
			while(!kbhit());
		}
	} while(item < 0 || item > 2);
}

void dadosin(void) {
	int x;

	clrscr();
	strcpy(mudaDados, "s");
	if (dados == 1) {
		do {
			printf("\nDeseja mudar os dados do campo potencial? (s/n)\n->");
			scanf("%s", mudaDados);
		} while(strcmp(mudaDados, "s") && strcmp(mudaDados, "n"));
	}
	if (mudaDados[0] == 's') {
		x = 0;
		do {
			printf("\n\n\nEntre com o %do. termo do potencial V (termos k, p1, p2, p3, separados por espaços, para cada elemento na forma k*x^p1*y^p2*z^p3. k = 0 0 0 0 - quatros Zeros - para finalizar)\nMáximo de 10 termos!\n\n->", x + 1);
			scanf("%f %f %f %f", &campoesc[x][0], &campoesc[x][1], &campoesc[x][2], &campoesc[x][3]);
			x++;
		} while((x < 10) && (campoesc[x - 1][0] != 0));
		ncampoesc = x;
		strcpy(func, "");
		for(x = 0; x < ncampoesc; x++) {
			if (campoesc[x][0] != 0) {
				sprintf(functemp, "%6.2f*", campoesc[x][0]);
				strcat(func, functemp);
			}
			if (campoesc[x][1] != 0) {
				if (campoesc[x][1] != 1) {
					sprintf(functemp, "x^(%6.2f)", campoesc[x][1]);
					strcat(func, functemp);
				} else strcat(func, "x");
			}
			if ((campoesc[x][1] != 0) && (campoesc[x][2] != 0)) strcat(func, "*");
			if (campoesc[x][2] != 0) {
				if (campoesc[x][2] != 1) {
					sprintf(functemp, "y^(%6.2f)", campoesc[x][2]);
					strcat(func, functemp);
				} else strcat(func, "y");
			}
			if (((campoesc[x][1] != 0) && (campoesc[x][3] != 0)) || ((campoesc[x][2] != 0) && (campoesc[x][3] != 0))) strcat(func, "*");
			if (campoesc[x][3] != 0) {
				if (campoesc[x][3] != 1) {
					sprintf(functemp, "z^(%6.2f)", campoesc[x][3]);
					strcat(func, functemp);
				} else strcat(func, "z");
			}
			if ((campoesc[x + 1][0] > 0) && (x < ncampoesc)) strcat(func, " + ");
		}
	}
	printf("\n\n\n\n\nCampo Potencial:\n\nV(x, y, z) = %s[V]\n", func);
	printf("\nDados completos! Pressione uma tecla...");
	while(!kbhit());
	dados = 1;
}

void calcgrad(void) {
	int x, cont1 = 0;

	ngAx = 0;
	ngAy = 0;
	ngAz = 0;
	strcpy(campovet, "");
	for (x = 0; x < ncampoesc; x++) {
		if (campoesc[x][1] != 0.0) {
			ax[cont1][0] = campoesc[x][0] * campoesc[x][1];
			ax[cont1][1] = campoesc[x][1] - 1;
			ax[cont1][2] = campoesc[x][2];
			ax[cont1][3] = campoesc[x][3];
			cont1++;
			ngAx++;
		}
	}
	cont1 = 0;
	for (x = 0; x < ncampoesc; x++) {
		if (campoesc[x][2] != 0.0) {
			ay[cont1][0] = campoesc[x][0] * campoesc[x][2];
			ay[cont1][1] = campoesc[x][1];
			ay[cont1][2] = campoesc[x][2] - 1;
			ay[cont1][3] = campoesc[x][3];
			cont1++;
			ngAy++;
		}
	}
	cont1 = 0;
	for (x = 0; x < ncampoesc; x++) {
		if (campoesc[x][3] != 0.0) {
			az[cont1][0] = campoesc[x][0] * campoesc[x][3];
			az[cont1][1] = campoesc[x][1];
			az[cont1][2] = campoesc[x][2];
			az[cont1][3] = campoesc[x][3] - 1;
			cont1++;
			ngAz++;
		}
	}
	if (ax[0][0] != 0) strcpy(campovet, "(");
	for (x = 0; x < ngAx; x++) {
		if (ax[x][0] != 0) {
			sprintf(functemp, "%6.2f*", ax[x][0]);
			strcat(campovet, functemp);
		}
		if (ax[x][1] != 0) {
			if (ax[x][1] != 1) {
				sprintf(functemp, "x^(%6.2f)", ax[x][1]);
				strcat(campovet, functemp);
			} else strcat(campovet, "x");
		}
		if ((ax[x][1] != 0) && (ax[x][2] != 0)) strcat(campovet, "*");
		if (ax[x][2] != 0) {
			if (ax[x][2] != 1) {
				sprintf(functemp, "y^(%6.2f)", ax[x][2]);
				strcat(campovet, functemp);
			} else strcat(campovet, "y");
		}
		if (((ax[x][1] != 0) && (ax[x][3] != 0)) || ((ax[x][2] != 0) && (ax[x][3] != 0))) strcat(campovet, "*");
		if (ax[x][3] != 0) {
			if (ax[x][3] != 1) {
				sprintf(functemp, "z^(%6.2f)", ax[x][3]);
				strcat(campovet, functemp);
			} else strcat(campovet, "z");
		}
		if ((ax[x + 1][0] > 0) && (x < ngAx)) strcat(campovet, " + ");
	}
	if (ax[0][0] != 0) strcat(campovet, ")ax");
	if ((ax[0][0] != 0) && (ay[0][0] != 0)) strcat(campovet, " + (");
	else if ((ax[0][0] == 0) && (ay[0][0] != 0)) strcat(campovet, "(");
	for (x = 0; x < ngAy; x++) {
		if (ay[x][0] != 0) {
			sprintf(functemp, "%6.2f*", ay[x][0]);
			strcat(campovet, functemp);
		}
		if (ay[x][1] != 0) {
			if (ay[x][1] != 1) {
				sprintf(functemp, "x^(%6.2f)", ay[x][1]);
				strcat(campovet, functemp);
			} else strcat(campovet, "x");
		}
		if ((ay[x][1] != 0) && (ay[x][2] != 0)) strcat(campovet, "*");
		if (ay[x][2] != 0) {
			if (ay[x][2] != 1) {
				sprintf(functemp, "y^(%6.2f)", ay[x][2]);
				strcat(campovet, functemp);
			} else strcat(campovet, "y");
		}
		if (((ay[x][1] != 0) && (ay[x][3] != 0)) || ((ay[x][2] != 0) && (ay[x][3] != 0))) strcat(campovet, "*");
		if (ay[x][3] != 0) {
			if (ay[x][3] != 1) {
				sprintf(functemp, "z^(%6.2f)", ay[x][3]);
				strcat(campovet, functemp);
			} else strcat(campovet, "z");
		}
		if ((ay[x + 1][0] > 0) && (x < ngAy)) strcat(campovet, " + ");
	}
	if (ay[0][0] != 0) strcat(campovet, ")ay");
	if ((ay[0][0] != 0) && (az[0][0] != 0) || ((ax[0][0] != 0) && (az[0][0] != 0))) strcat(campovet, " + (");
	else if ((ax[0][0] == 0) && (ay[0][0] == 0) && (az[0][0] != 0)) strcat(campovet, "(");
	for (x = 0; x < ngAz; x++) {
		if (az[x][0] != 0) {
			sprintf(functemp, "%6.2f*", az[x][0]);
			strcat(campovet, functemp);
		}
		if (az[x][1] != 0) {
			if (az[x][1] != 1) {
				sprintf(functemp, "x^(%6.2f)", az[x][1]);
				strcat(campovet, functemp);
			} else strcat(campovet, "x");
		}
		if ((az[x][1] != 0) && (az[x][2] != 0)) strcat(campovet, "*");
		if (az[x][2] != 0) {
			if (az[x][2] != 1) {
				sprintf(functemp, "y^(%6.2f)", az[x][2]);
				strcat(campovet, functemp);
			} else strcat(campovet, "y");
		}
		if (((az[x][1] != 0) && (az[x][3] != 0)) || ((az[x][2] != 0) && (az[x][3] != 0))) strcat(campovet, "*");
		if (az[x][3] != 0) {
			if (az[x][3] != 1) {
				sprintf(functemp, "z^(%6.2f)", az[x][3]);
				strcat(campovet, functemp);
			} else strcat(campovet, "z");
		}
		if ((az[x + 1][0] > 0) && (x < ngAz)) strcat(campovet, " + ");
	}
	if (az[0][0] != 0) strcat(campovet, ")az");
}

