#include <stdio.h>
#include "conio.h"
#include <string.h>

int item, dados = 0, nAx, nAy, nAz, ndAx, ndAy, ndAz;
float ax[10][4], ay[10][4], az[10][4], divAx[10][4], divAy[10][4], divAz[10][4];
char mudaDados[2] = "", diverg[1000], func[1000], functemp[100] = "";

void menu(void);
void dadosin(void);
void calcdiv(void);

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
					printf("\nNão houve entrada dos dados do campo para o cálculo do divergente!\n");
					printf("Pressione uma tecla!");
					while (!kbhit());
				} else {
					calcdiv();
					clrscr();
					printf("\n\nDivergente do Campo:\n\nf(x, y, z) = %s\n\né\n\ndiv(f) = %s\n\n", func, diverg);
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
		printf("\n(2) - Calcular Divergente do campo\n\n->");
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
	strcpy(mudaDados, "");
	if (dados == 1) {
		do {
			printf("\nDeseja mudar os dados do campo vetorial? (s/n)\n->");
			scanf("%s", mudaDados);
		} while(strcmp(mudaDados, "s") && strcmp(mudaDados, "n"));
	}
	if (mudaDados[0] == 's') {
		x = 0;
		do {
			printf("\n\n\nEntre com o %do. termo do campo da direção ax (termos k, p1, p2, p3, separados por espaços, para cada elemento na forma k*x^p1*y^p2*z^p3. k = 0 0 0 0 - quatros Zeros - para finalizar)\nMáximo de 10 termos!\n->", x + 1);
			scanf("%f %f %f %f", &ax[x][0], &ax[x][1], &ax[x][2], &ax[x][3]);
			x++;
		} while((x < 10) && (ax[x - 1][0] != 0));
		nAx = x;
		x = 0;
		do {
			printf("\n\n\nEntre com o %do. termo do campo da direção ax (termos k, p1, p2, p3, separados por espaços, para cada elemento na forma k*x^p1*y^p2*z^p3. k = 0 0 0 0 - quatros Zeros - para finalizar)\nMáximo de 10 termos!\n->", x + 1);
			scanf("%f %f %f %f", &ay[x][0], &ay[x][1], &ay[x][2], &ay[x][3]);
			x++;
		} while ((x < 10) && (ay[x][0] != 0));
		nAy = x;
		x = 0;
		do {
			printf("\n\n\nEntre com o %do. termo do campo da direção ax (termos k, p1, p2, p3, separados por espaços, para cada elemento na forma k*x^p1*y^p2*z^p3. k = 0 0 0 0 - quatros Zeros - para finalizar)\nMáximo de 10 termos!\n->", x + 1);
			scanf("%f %f %f %f", &az[x][0], &az[x][1], &az[x][2], &az[x][3]);
			x++;
		} while ((x < 10) && (az[x][0] != 0));
		nAz = x;
		strcpy(func, "");
		if (ax[0][0] != 0) strcat(func, "(");
		for(x = 0; x < nAx; x++) {
			if (ax[x][0] != 0) {
				sprintf(functemp, "%6.2f*", ax[x][0]);
				strcat(func, functemp);
			}
			if (ax[x][1] != 0) {
				if (ax[x][1] != 1) {
					sprintf(functemp, "x^(%6.2f)", ax[x][1]);
					strcat(func, functemp);
				} else strcat(func, "x");
			}
			if ((ax[x][1] != 0) && (ax[x][2] != 0)) strcat(func, "*");
			if (ax[x][2] != 0) {
				if (ax[x][2] != 1) {
					sprintf(functemp, "y^(%6.2f)", ax[x][2]);
					strcat(func, functemp);
				} else strcat(func, "y");
			}
			if (((ax[x][1] != 0) && (ax[x][3] != 0)) || ((ax[x][2] != 0) && (ax[x][3] != 0))) strcat(func, "*");
			if (ax[x][3] != 0) {
				if (ax[x][3] != 1) {
					sprintf(functemp, "z^(%6.2f)", ax[x][3]);
					strcat(func, functemp);
				} else strcat(func, "z");
			}
			if ((ax[x + 1][0] > 0) && (x < nAx)) strcat(func, " + ");
		}
		if (ax[0][0] != 0) strcat(func, ")ax");
		if ((ax[0][0] != 0) && (ay[0][0] != 0)) strcat(func, " + (");
		else if ((ax[0][0] == 0) && (ay[0][0] != 0)) strcat(func, "(");
		for (x = 0; x < nAy; x++) {
			if (ay[x][0] != 0) {
				sprintf(functemp, "%6.2f*", ay[x][0]);
				strcat(func, functemp);
			}
			if (ay[x][1] != 0) {
				if (ay[x][1] != 1) {
					sprintf(functemp, "x^(%6.2f)", ay[x][1]);
					strcat(func, functemp);
				} else strcat(func, "x");
			}
			if ((ay[x][1] != 0) && (ay[x][2] != 0)) strcat(func, "*");
			if (ay[x][2] != 0) {
				if (ay[x][2] != 1) {
					sprintf(functemp, "y^(%6.2f)", ay[x][2]);
					strcat(func, functemp);
				} else strcat(func, "y");
			}
			if (((ay[x][1] != 0) && (ay[x][3] != 0)) || ((ay[x][2] != 0) && (ay[x][3] != 0))) strcat(func, "*");
			if (ay[x][3] != 0) {
				if (ay[x][3] != 1) {
					sprintf(functemp, "z^(%6.2f)", ay[x][3]);
					strcat(func, functemp);
				} else strcat(func, "z");
			}
			if ((ay[x + 1][0] > 0) && (x < nAy)) strcat(func, " + ");
		}
		if (ay[0][0] != 0) strcat(func, ")ay");
		if (((ay[0][0] != 0) && (az[0][0] != 0)) || ((ax[0][0] != 0) && (az[0][0] != 0))) strcat(func, " + (");
		else if ((ax[0][0] == 0) && (ay[0][0] == 0) && (az[0][0] != 0)) strcat(func, "(");
		for (x = 0; x < nAz; x++) {
			if (az[x][0] != 0) {
				sprintf(functemp, "%6.2f*", az[x][0]);
				strcat(func, functemp);
			}
			if (az[x][1] != 0) {
				if (az[x][1] != 1) {
					sprintf(functemp, "x^(%6.2f)", az[x][1]);
					strcat(func, functemp);
				} else strcat(func, "x");
			}
			if ((az[x][1] != 0) && (az[x][2] != 0)) strcat(func, "*");
			if (az[x][2] != 0) {
				if (az[x][2] != 1) {
					sprintf(functemp, "y^(%6.2f)", az[x][2]);
					strcat(func, functemp);
				} else strcat(func, "y");
			}
			if (((az[x][1] != 0) && (az[x][3] != 0)) || ((az[x][2] != 0) && (az[x][3] != 0))) strcat(func, "*");
			if (az[x][3] != 0) {
				if (az[x][3] != 1) {
					sprintf(functemp, "z^(%6.2f)", az[x][3]);
					strcat(func, functemp);
				} else strcat(func, "z");
			}
			if ((az[x + 1][0] > 0) && (x < nAz)) strcat(func, " + ");
		}
		if (az[0][0] != 0) strcat(func, ")az");
	}
	printf("\n\n\n\n\nCampo Vetorial:\n\nf(x, y, z) = %s\n", func);
	printf("\nDados Completos| Pressione uma tecla...");
	while(!kbhit());
	dados = 1;
}

void calcdiv(void) {
	int x, cont1 = 0;
	ndAx = 0;
	ndAy = 0;
	ndAz = 0;

	strcpy(diverg, "");
	for (x = 0; x < nAx; x++) {
		if (ax[x][1] != 0.0) {
			divAx[cont1][0] = ax[x][0]*ax[x][1];
			divAx[cont1][1] = ax[x][1] - 1;
			divAx[cont1][2] = ax[x][2];
			divAx[cont1][3] = ax[x][3];
			cont1++;
			ndAx++;
		}
	}
	cont1 = 0;
	for (x = 0; x < nAy; x++) {
		if (ay[x][2] != 0.0) {
			divAy[cont1][0] = ay[x][0]*ay[x][2];
			divAy[cont1][1] = ay[x][1];
			divAy[cont1][2] = ay[x][2] - 1;
			divAy[cont1][3] = ay[x][3];
			cont1++;
			ndAy++;
		}
	}
	cont1 = 0;
	for (x = 0; x < nAz; x++) {
		if (az[x][3] != 0.0) {
			divAz[cont1][0] = az[x][0]*az[x][3];
			divAz[cont1][1] = az[x][1];
			divAz[cont1][2] = az[x][2];
			divAz[cont1][3] = az[x][3] - 1;
			cont1++;
			ndAz++;
		}
	}
	if (divAx[0][0] != 0) strcpy(diverg, "(");
	for (x = 0; x < ndAx; x++) {
		if (divAx[x][0] != 0) {
			sprintf(functemp, "%6.2f*", divAx[x][0]);
			strcat(diverg, functemp);
		}
		if (divAx[x][1] != 0) {
			if (divAx[x][1] != 1) {
				sprintf(functemp, "x^(%6.2f)", divAx[x][1]);
				strcat(diverg, functemp);
			} else strcat(diverg, "x");
		}
		if ((divAx[x][1] != 0) && (divAx[x][2] != 0)) strcat(diverg, "*");
		if (divAx[x][2] != 0) {
			if (divAx[x][2] != 1) {
				sprintf(functemp, "y^(%6.2f)", divAx[x][2]);
				strcat(diverg, functemp);
			} else strcat(diverg, "y");
		}
		if (((divAx[x][1] != 0) && (divAx[x][3] != 0)) || ((divAx[x][2] != 0) && (divAx[x][3] != 0))) strcat(diverg, "*");
		if (divAx[x][3] != 0) {
			if (divAx[x][3] != 1) {
				sprintf(functemp, "z^(%6.2f)", divAx[x][3]);
				strcat(diverg, functemp);
			} else strcat(diverg, "z");
		}
		if ((divAx[x + 1][0] > 0) && (x < ndAx)) strcat(diverg, " + ");
	}
	if (divAx[0][0] != 0) strcat(diverg, ")");
	if ((divAx[0][0] != 0) && (divAy[0][0] != 0)) strcat(diverg, " + (");
	else if ((divAx[0][0] == 0) && (divAy[0][0] != 0)) strcat(diverg, "(");
	for (x = 0; x < ndAy; x++) {
		if (divAy[x][0] != 0) {
			sprintf(functemp, "%6.2f*", divAy[x][0]);
			strcat(diverg, functemp);
		}
		if (divAy[x][1] != 0) {
			if (divAy[x][1] != 1) {
				sprintf(functemp, "x^(%6.2f)", divAy[x][1]);
				strcat(diverg, functemp);
			} else strcat(diverg, "x");
		}
		if ((divAy[x][1] != 0) && (divAy[x][2] != 0)) strcat(diverg, "*");
		if (divAy[x][2] != 0) {
			if (divAy[x][2] != 1) {
				sprintf(functemp, "y^(%6.2f)", divAy[x][2]);
				strcat(diverg, functemp);
			} else strcat(diverg, "y");
		}
		if (((divAy[x][1] != 0) && (divAy[x][3] != 0)) || ((divAy[x][2] != 0) && (divAy[x][3] != 0))) strcat(diverg, "*");
		if (divAy[x][3] != 0) {
			if (divAy[x][3] != 1) {
				sprintf(functemp, "z^(%6.2f)", divAy[x][3]);
				strcat(diverg, functemp);
			} else strcat(diverg, "z");
		}
		if ((divAy[x + 1][0] > 0) && (x < ndAy)) strcat(diverg, " + ");
	}
	if (divAy[0][0] != 0) strcat(diverg, ") ");
	if (((divAy[0][0] != 0) && (divAz[0][0] != 0)) || ((divAx[0][0] != 0) && (divAz[0][0] != 0))) strcat(diverg, " + (");
	else if ((divAx[0][0] == 0) && (divAy[0][0] == 0) && (divAz[0][0] != 0)) strcat(diverg, "(");
	for (x = 0; x < ndAz; x++) {
		if (divAz[x][0] != 0) {
			sprintf(functemp, "%6.2f*", divAz[x][0]);
			strcat(diverg, functemp);
		}
		if (divAz[x][1] != 0) {
			if (divAz[x][1] != 1) {
				sprintf(functemp, "x^(%6.2f)", divAz[x][1]);
				strcat(diverg, functemp);
			} else strcat(diverg, "x");
		}
		if ((divAz[x][1] != 0) && (divAz[x][2] != 0)) strcat(diverg, "*");
		if (divAz[x][2] != 0) {
			if (divAz[x][2] != 1) {
				sprintf(functemp, "y^(%6.2f)", divAz[x][2]);
				strcat(diverg, functemp);
			} else strcat(diverg, "y");
		}
		if (((divAz[x][1] != 0) && (divAz[x][3] != 0)) || ((divAz[x][2] != 0) && (divAz[x][3] != 0))) strcat(diverg, "*");
		if (divAz[x][3] != 0) {
			if (divAz[x][3] != 1) {
				sprintf(functemp, "z^(%6.2f)", divAz[x][3]);
				strcat(diverg, functemp);
			} else strcat(diverg, "z");
		}
		if ((divAz[x + 1][0] > 0) && (x < ndAz)) strcat(diverg, " + ");
	}
	if (divAz[0][0] != 0) strcat(diverg, ")");
}
