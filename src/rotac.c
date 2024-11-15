#include <stdio.h>
#include "conio.h"
#include <string.h>

int item, dados = 0, nAx, nAy, nAz, nrAx, nrAy, nrAz;
float ax[10][4], ay[10][4], az[10][4], rotAx[10][4], rotAy[10][4], rotAz[10][4];
char mudaDados[2] = "", rotacional[1000], func[1000], functemp[100] = "";

void menu(void);
void dadosin(void);
void calcrotacional(void);

int main(void) {
	clrscr();
	do {
		menu();
		switch (item) {
			case 1:
				dadosin();
				break;
			case 2:
				if (!dados) {
					printf("\nNão houve entrada de dados para o cálculo do rotacional!\n");
					printf("Pressione uma tecla!");
					while (!kbhit());
				} else {
					calcrotacional();
					clrscr();
					printf("\nRotacional do Campo:\n\nf(x, y, z) = %s\n\né\n\nrot(f) = %s\n\n", func, rotacional);
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
		printf("\n(2) - Calcular Rotacional\n\n->");
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
			printf("Deseja mudar os dados do campo vetorial? (s/n)\n->");
			scanf("%s", mudaDados);
		} while(strcmp(mudaDados, "s") && strcmp(mudaDados, "n"));
	}
	if (mudaDados[0] == 's') {
		x = 0;
		do {
			printf("\n\n\nEntre com o %do. termo do campo da direção ax (termos k, p1, p2, p3, separados por espaços, para cada elemento na forma k*x^p1*y^p2*z^p3. k = 0 0 0 0 - quatros Zeros - para finalizar) \nMáximo de 10 termos!\n->", x + 1);
			scanf("%f %f %f %f", &ax[x][0], &ax[x][1], &ax[x][2], &ax[x][3]);
			x++;
		} while((x < 10) && (ax[x - 1][0] != 0));
		nAx = x;
		x = 0;
		do {
			printf("\n\n\nEntre com o %do. termo do campo da direção ay (termos k, p1, p2, p3, separados por espaços, para cada elemento na forma k*x^p1*y^p2*z^p3. k = 0 0 0 0 - quatros Zeros - para finalizar) \nMáximo de 10 termos!\n->", x + 1);
			scanf("%f %f %f %f", &ay[x][0], &ay[x][1], &ay[x][2], &ay[x][3]);
			x++;
		} while((x < 10) && (ay[x - 1][0] != 0));
		nAy = x;
		x = 0;
		do {
			printf("\n\n\nEntre com o %do. termo do campo da direção az (termos k, p1, p2, p3, separados por espaços, para cada elemento na forma k*x^p1*y^p2*z^p3. k = 0 0 0 0 - quatros Zeros - para finalizar) \nMáximo de 10 termos!\n->", x + 1);
			scanf("%f %f %f %f", &az[x][0], &az[x][1], &az[x][2], &az[x][3]);
			x++;
		} while((x < 10) && (az[x - 1][0] != 0));
		nAz = x;
		strcpy(func, "");
		if (ax[0][0] != 0) strcat(func, "(");
		for (x = 0; x < nAx; x++) {
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
		else if ((ax[0][0] == 0) && (ay[0][0] == 0) && (az[0][0] != 0)) strcat(func, " + (");
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

void calcrotacional(void) {
	int x, cont1 = 0;

	nrAx = 0;
	nrAy = 0;
	nrAz = 0;
	strcpy(rotacional, "");
	for (x = 0; x < nAz; x++) {
		if (az[x][2] != 0.0) {
			rotAx[cont1][0] = az[x][0]*az[x][2];
			rotAx[cont1][1] = az[x][1];
			rotAx[cont1][2] = az[x][2] - 1;
			rotAx[cont1][3] = az[x][3];
			cont1++;
			nrAx++;
		}
	}
	for (x = 0; x < nAy; x++) {
		if (ay[x][3] != 0.0) {
			rotAx[cont1][0] = ay[x][0]*ay[x][3];
			rotAx[cont1][1] = ay[x][1];
			rotAx[cont1][2] = ay[x][2];
			rotAx[cont1][3] = ay[x][3] - 1;
			cont1++;
			nrAy++;
		}
	}
	cont1 = 0;
	for (x = 0; x < nAx; x++) {
		if (ax[x][3] != 0.0) {
			rotAy[cont1][0] = ax[x][0]*ax[x][3];
			rotAy[cont1][1] = ax[x][1];
			rotAy[cont1][2] = ax[x][2];
			rotAy[cont1][3] = ax[x][3] - 1;
			cont1++;
			nrAx++;
		}
	}
	for (x = 0; x < nAz; x++) {
		if (az[x][1] != 0.0) {
			rotAy[cont1][0] = az[x][0]*az[x][1];
			rotAy[cont1][1] = az[x][1] - 1;
			rotAy[cont1][2] = az[x][2];
			rotAy[cont1][3] = az[x][3];
			cont1++;
			nrAy++;
		}
	}
	cont1 = 0;
	for (x = 0; x < nAy; x++) {
		if (ay[x][1] != 0.0) {
			rotAz[cont1][0] = ay[x][0]*ay[x][1];
			rotAz[cont1][1] = ay[x][1] - 1;
			rotAz[cont1][2] = ay[x][2];
			rotAz[cont1][3] = ay[x][3];
			cont1++;
			nrAz++;
		}
	}
	for (x = 0; x < nAx; x++) {
		if (ax[x][2] != 0.0) {
			rotAz[cont1][0] = ax[x][0]*ax[x][2];
			rotAz[cont1][1] = ax[x][1];
			rotAz[cont1][2] = ax[x][2] - 1;
			rotAz[cont1][3] = ax[x][3];
			cont1++;
			nrAz++;
		}
	}
	if (rotAx[0][0] != 0) strcpy(rotacional, "(");
	for (x = 0; x < nrAx; x++) {
		if (rotAx[x][0] != 0) {
			sprintf(functemp, "%6.2f*", rotAx[x][0]);
			strcat(rotacional, functemp);
		}
		if (rotAx[x][1] != 0) {
			if (rotAx[x][1] != 1) {
				sprintf(functemp, "x^(%6.2f)", rotAx[x][1]);
				strcat(rotacional, functemp);
			} else strcat(rotacional, "x");
		}
		if ((rotAx[x][1] != 0) && (rotAx[x][2] != 0)) strcat(rotacional, "*");
		if (rotAx[x][2] != 0) {
			if (rotAx[x][2] != 1) {
				sprintf(functemp, "y^(%6.2f)", rotAx[x][2]);
				strcat(rotacional, functemp);
			} else strcat(rotacional, "y");
		}
		if (((rotAx[x][1] != 0) && (rotAx[x][3] != 0)) || ((rotAx[x][2] != 0) && (rotAx[x][3] != 0))) strcat(rotacional, "*");
		if (rotAx[x][3] != 0) {
			if (rotAx[x][3] != 1) {
				sprintf(functemp, "z^(%6.2f)", rotAx[x][3]);
				strcat(rotacional, functemp);
			} else strcat(rotacional, "z");
		}
		if ((rotAx[x + 1][0] > 0) && (x < nrAx)) strcat(rotacional, " + ");
	}
	if (rotAx[0][0] != 0) strcat(rotacional, ")ax ");
	if ((rotAx[0][0] != 0) && (rotAy[0][0] != 0)) strcat(rotacional, " + (");
	else if ((rotAx[0][0] == 0) && (rotAy[0][0] != 0)) strcat(rotacional, "(");
	for (x = 0; x < nrAy; x++) {
		if (rotAy[x][0] != 0) {
			sprintf(functemp, "%6.2f*", rotAy[x][0]);
			strcat(rotacional, functemp);
		}
		if (rotAy[x][1] != 0) {
			if (rotAy[x][1] != 1) {
				sprintf(functemp, "x^(%6.2f)", rotAy[x][1]);
				strcat(rotacional, functemp);
			} else strcat(rotacional, "x");
		}
		if ((rotAy[x][1] != 0) && (rotAy[x][2] != 0)) strcat(rotacional, "*");
		if (rotAy[x][2] != 0) {
			if (rotAy[x][2] != 1) {
				sprintf(functemp, "y^(%6.2f)", rotAy[x][2]);
				strcat(rotacional, functemp);
			} else strcat(rotacional, "y");
		}
		if (((rotAy[x][1] != 0) && (rotAy[x][3] != 0)) || ((rotAy[x][2] != 0) && (rotAy[x][3] != 0))) strcat(rotacional, "*");
		if (rotAy[x][3] != 0) {
			if (rotAy[x][3] != 1) {
				sprintf(functemp, "z^(%6.2f)", rotAy[x][3]);
				strcat(rotacional, functemp);
			} else strcat(rotacional, "z");
		}
		if ((rotAy[x + 1][0] > 0) && (x < nrAy)) strcat(rotacional, " + ");
	}
	if (rotAy[0][0] != 0) strcat(rotacional, ")ay ");
	if (((rotAy[0][0] != 0) && (rotAz[0][0] != 0)) || ((rotAx[0][0] != 0) && (rotAz[0][0] != 0))) strcat(rotacional, " + (");
	else if ((rotAx[0][0] == 0) && (rotAy[0][0] == 0) && (rotAz[0][0] != 0)) strcat(rotacional, "(");
	for (x = 0; x < nrAz; x++) {
		if (rotAz[x][0] != 0) {
			sprintf(functemp, "%6.2f*", rotAz[x][0]);
			strcat(rotacional, functemp);
		}
		if (rotAz[x][1] != 0) {
			if (rotAz[x][1] != 1) {
				sprintf(functemp, "x^(%6.2f)", rotAz[x][1]);
				strcat(rotacional, functemp);
			} else strcat(rotacional, "x");
		}
		if ((rotAz[x][1] != 0) && (rotAz[x][2] != 0)) strcat(rotacional, "*");
		if (rotAz[x][2] != 0) {
			if (rotAz[x][2] != 1) {
				sprintf(functemp, "y^(%6.2f)", rotAz[x][2]);
				strcat(rotacional, functemp);
			} else strcat(rotacional, "y");
		}
		if (((rotAz[x][1] != 0) && (rotAz[x][3] != 0)) || ((rotAz[x][2] != 0) && (rotAz[x][3] != 0))) strcat(rotacional, "*");
		if (rotAz[x][3] != 0) {
			if (rotAz[x][3] != 1) {
				sprintf(functemp, "z^(%6.2f)", rotAz[x][3]);
				strcat(rotacional, functemp);
			} else strcat(rotacional, "z");
		}
		if ((rotAz[x + 1][0] > 0) && (x < nrAz)) strcat(rotacional, " + ");
	}
	if (rotAz[0][0] != 0) strcat(rotacional, ")az");
}
