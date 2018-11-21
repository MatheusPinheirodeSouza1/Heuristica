#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<map>
#include <string.h> 

using namespace std;

int main(int argc, char* argv[]){
// gera_lp <nome_do_arquivo_entrada> 
FILE *fp1;

/* parametros de entrada */
int i,j,k;	
int n_paradas;
int n_onibus;
int n_paradas_escolas;
int custo_aresta[100][100];
int custo_fixo[100];
int quantidade_parada[100];
int capacidade[100];
int estudante_escola[100];
/* ********************** */

fp1 = fopen(argv[1],"r");

/* Lê  numero de paradas e o número de arestas e o número de onibus */
fscanf(fp1, "%d %d %d\n\n", &n_paradas, &n_onibus,&n_paradas_escolas); 

printf("O numero de paradas é %d e o numero de onibus é %d e o numero de escolas é %d\n", n_paradas,n_onibus,n_paradas_escolas);

/* Lê o custo do arquivo de entrada e coloca na matriz custo*/
for(i = 1; i <= n_paradas+n_paradas_escolas; i++){
	for(j = 1; j <= n_paradas+n_paradas_escolas; j++)
	{
		fscanf(fp1, "%d ", &custo_aresta[i][j]);
		fscanf(fp1,"\n");
	}
}
/***************************************************************/
	
/* Lê a parada por escola do arquivo de entrada e coloca no array de estudante_escola*/
for(i = 1; i <= n_paradas; i++){
	fscanf(fp1, "%d ", &estudante_escola[i]);
	fscanf(fp1,"\n");
}

/***************************************************************/
	
/* Lê o custo fixo do arquivo de entrada e coloca na matriz de custo fixo*/
for(i = 1; i <= n_onibus; i++){
	fscanf(fp1, "%d ", &custo_fixo[i]);
	fscanf(fp1,"\n");
}
/***************************************************************/
/* Lê a quantidade de alunos na parada do arquivo de entrada e coloca na vetor quantidade_parada*/

for(i = 2 ; i <= n_paradas; i++){
    fscanf(fp1, "%d ", &quantidade_parada[i]);
	fscanf(fp1,"\n");
}
fscanf(fp1,"\n");
/***************************************************************/
/* Lê acapacidade de entrada e coloca no vetor capacidade*/

for(j = 1; j <= n_onibus; j++){
	fscanf(fp1, "%d ", &capacidade[j]);
}
fscanf(fp1,"\n");

/*Metodo guloso*/
bool it = false;
int menorcusto=100;
int parada_atual=1;
int cargatotal = capacidade[1];
int parada_anterior;
int passou[n_paradas][n_paradas];//Indica as paradas que passou
int aux_quantidade_parada[100];
copy(begin(quantidade_parada), end(quantidade_parada), begin(aux_quantidade_parada));
while(!it){
	parada_anterior = parada_atual;
	menorcusto = 100;
	for(j = 1;j <= n_paradas;j++){
		//Só pega o menor custo se a proxima aresta tiver aluno para pegar
		if((custo_aresta[parada_atual][j] != 0) && (custo_aresta[parada_atual][j] < menorcusto) && (aux_quantidade_parada[j] > 0)){
			menorcusto = custo_aresta[parada_atual][j];
			parada_atual = j;
			if((cargatotal - aux_quantidade_parada[parada_atual]) >= 0)
				passou[parada_atual][j] = 1;
		}

	}
	for(i = 1;i <= n_paradas;i++){
		if((custo_aresta[i][parada_atual] != 0) && (custo_aresta[i][parada_atual]< menorcusto) && (aux_quantidade_parada[i] > 0)){
			menorcusto = custo_aresta[i][parada_atual];
			parada_atual = i;
			if((cargatotal - aux_quantidade_parada[parada_atual]) >= 0)
				passou[i][parada_atual] = 1;
		}
	}
	if((cargatotal - aux_quantidade_parada[parada_atual]) >= 0){
		cargatotal = cargatotal - aux_quantidade_parada[parada_atual];
		aux_quantidade_parada[parada_atual] = 0 ;
	}
	else{
		aux_quantidade_parada[parada_atual] = 0 ;
		parada_atual = parada_anterior;
	}
	if(menorcusto == 100){
		passou[parada_atual+1][parada_atual] = 1;
		it = true;
	}
}

for(i=1;i <n_paradas;i++){
	for(j=1; j <n_paradas ;j++){
		if(passou[i][parada_atual] == 1)
			printf("x%d_%d = 1\n",i,j);
	}
}
return 0;
}



