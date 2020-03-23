#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
//implementacao do metodo da Secante para calcular raizes de polinomios e da funcao trigonometrica 3-sen(X)+(2*tan(x))
int ler_ficheiro(float* polinomio){ //realiza a leitura dos coeficientes do polinomio
    FILE *fp;
    float coeff;
    int grau, i;

    fp = fopen("numeros.txt", "r");
    if (fp == NULL){
        printf("Erro ao abrir o ficheiro!\n");
        return -1;
    }

    fscanf(fp, "%d", &grau);

    for(i=0; i<=grau; i++){
        fscanf(fp, "%f", &coeff);
        *(polinomio+i) = coeff;
    }
    fclose(fp);
    return grau;
}

void ler_parametros(float params[]){ //Funcao que realiza a leitura dos parametros, feita via ficheiro, e os salva num array.
    float param;
    int i;
    FILE *fp;
    fp=fopen("parametros.txt","r");
    if (fp == NULL){
        printf("Erro!\n");
    }
    else{
        for(i=0;i<3;i++){
    	fscanf(fp,"%f",&param);
    	params[i]=param;
	    }
    }
    fclose(fp);
}


float calcula_polinomio(float* polinomio, int grau, float x){ //Funcao que realiza a soma do polinomio e retorna o valor (f(x) ou  Y da funcao).
    int i;
    float resultado = 0;
    for(i=0; i<=grau; i++){
        resultado += polinomio[i] * pow(x, grau-i);
    }
    return resultado;
}

int bolzano(float* polinomio, int grau,float x0, float x1){ //Funcao que realiza o metodo de Bolzano com intuito de identificar se ha ou nao raizes no intervalo selecionado
	system ("cls");
    float fx0,fx1;
    int raizes=0;
    fx0=calcula_polinomio(polinomio, grau, x0);
    fx1=calcula_polinomio(polinomio, grau, x1);
    if(fx0*fx1<=0){
        raizes++;
        printf("Ha pelo menos uma raiz no intervalo. Prima qualquer tecla para continuar\n");
        getch();
    }
    else{
        printf("A existencia de raizes no intervalo eh incerta\n\n\n");
        getch();
    }
    return raizes;
}

void secante(float* polinomio, int grau,float x0, float x1, float erro){ //Funcao que executa o metodo da secante para polinomios.
    system ("cls");
    float fx0=0,fx1=0,diff,x2=0;
    int i,raizes=0;
    raizes= bolzano(polinomio, grau, x0, x1);
    printf("X0=%f \t X1=%f \t Erro=%f\n\n",x0,x1,erro);
    diff=fabs((x1-x0));
	while(diff>=erro){
    		diff=fabs((x1-x0));
        	fx0=calcula_polinomio(polinomio, grau, x0);
        	fx1=calcula_polinomio(polinomio, grau, x1);
        	x2=((x0*fx1)-(x1*fx0))/(fx1-fx0);
        	x0=x1;
        	x1=x2;
    };
    printf("raiz=%f\n", x1);
    printf("\n\n\n\n\n\n Prima qualquer tecla para Continuar: \n");
    getch();
}

float solvtrig(float x){ //resolve a funcao trigonometrica 3-sen(X)+(2*tan(x)) 
    float sol;
    sol=3-sin(x)+(2*tan(x));
    return sol;
}

int bolzano_trig(float x0, float x1){ //Bolzano aplicado a funcao trigonometrica 3-sen(X)+(2*tan(x))
	int raizes=0;
	float fx0,fx1;
	fx0=solvtrig(x0);
	fx1=solvtrig(x1);
	if(fx0*fx1<0){
		raizes++;
	}
	return raizes;
}

float secante_trig(float x0, float x1, float erro){ //Metodo da Secante para a funcao trigonometrica 3-sen(X)+(2*tan(x))
	system ("cls");
	int raizes;
	raizes= bolzano_trig(x0, x1);
    float x2,diff,fx0,fx1;
    diff=fabs((x1-x0));
    if(raizes!=0){
    	while(diff>=erro){
        	diff=fabs((x1-x0));
        	fx0=solvtrig(x0);
        	fx1=solvtrig(x1);
        	x2=((x0*fx1)-(x1*fx0))/(fx1-fx0);
        	x0=x1;
        	x1=x2;
    	};
    	printf("raiz=%f\n", x1);
	}
	else{
		printf("Nao ha raiz no intervalo!\n");
	}
    printf("\n\n\n\n\n\n Prima qualquer tecla para Continuar: \n");
    getch();
}




int menunlinear(float* polinomio, int grau){ //Menu que chama o metodo da secante
	ler_ficheiro(polinomio);
	system ("cls");
    char op;
    float params[3];
    float x0, x1, erro;
    x0=params[0];
    x1=params[1];
    erro=params[2];
    while(op!='S'){
        system ("cls");
        system ("cls");
        printf("\t\t\t Menu Equacoes nao lineares pelo metodo da secante\n");
        printf("1 - Verificar se existem raizes no intervalo \n");
        printf("2 - Polinomio  \n");
        printf("3 - funcao trigonometrica 3-sen(X)+(2*tan(x))\n");
        printf("0 - Instrucoes de Uso\n");
        printf("\n\n\n s - Voltar ao Menu Inicial \n\n");
       op=toupper(getch());
        switch(op){
            case '1': bolzano(polinomio, grau, x0, x1); break;
            case '2': secante(polinomio, grau,x0, x1, erro); break;
            case '3': secante_trig(x0, x1, erro); break;
            case '0': printf("\n\n\n Para a resolucao de polinomios eh necessario entrar com o grau e os coeficientes (em ordem crescente de importancia) no ficheiro numeros.txt, apos isso eh preciso entrar com os parametros(a,b,erro. Exatamente nesta ordem) no arquivo parametros.txt, a alteracao tanto dos coeficientes quanto dos parametros pode ser realizada simplismente alterando os valores nos respetivos arquivos de texto, para a resolucao da equacao trigonometrica 3-sen(X)+(2*tan(x)) basta entrar com os parametros pois a equacao foi definida dentro do codigo. Prima qualquer tecla para retornar ao menu\n\n\n");getch(); break;
            case 'S': return(0);
        }

    };
}

void menu1(float* polinomio, int grau){ //Menu geral
	ler_ficheiro(polinomio);
    float params[3];
    float x0, x1, erro;
    x0=params[0];
    x1=params[1];
    erro=params[2];
    unsigned char op;
    while(op!='S'){
        system ("cls");
        printf("\t\t\t   Trabalho de Analise Numerica\n");
        printf("\t\t\t   MENU INICIAL \n");
        printf("1 - Resolver Equacao Nao Linear \n");
        printf("s - SAIR\n\n");
        op=toupper(getch());
        switch(op){
            case '1': menunlinear(polinomio, grau); break;
            case 'S': exit(0);
        }
    };
}

int main(){
    int grau;
    float params[3];
    float* polinomio;  //Definicao do array dinamico para os coeficientes do polinomio
    polinomio=calloc(2, sizeof(float)); //Configuracao do array dinamico
    ler_parametros(params);
    grau=ler_ficheiro(polinomio);
    if(grau < 0){ //Para evitar funcoes de grau negativo
        return 1;
    }
    
    menu1(polinomio,grau);


    return 0;
}
