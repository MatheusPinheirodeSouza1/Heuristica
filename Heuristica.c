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
bool it;
int menorcusto;
int parada_atual;
int cargatotal;
int parada_anterior;

for(k = 1; k <= n_onibus;k++){
	cargatotal = capacidade[k];
	parada_atual=1;
	it = false;
	while(!it){
		parada_anterior = parada_atual;
		menorcusto = 100;
		if(parada_atual <= n_paradas)
			for(j = 1;j <= n_paradas;j++){
				//Só pega o menor custo se a proxima aresta tiver aluno para pegar, e não utrapassar a carga maxima
				if((custo_aresta[parada_anterior][j] != 0) && (custo_aresta[parada_anterior][j] < menorcusto) && (quantidade_parada[j] > 0) && ((cargatotal - quantidade_parada[j]) >= 0)){
					menorcusto = custo_aresta[parada_anterior][j];
					parada_atual = j;
				}
			}
		if(menorcusto == 100){//Caso não consiga mais percorrer um caminho ele vai para as escolas
			for(i = n_paradas+1;i <=n_paradas+n_paradas_escolas;i++){
				printf("x%d_%d_%d = 1\n",parada_atual,i,k);
				parada_atual = i;
			}
			it = true;
		}else{//Adiciona a parada que passou e exclui o numero de alunos daquela parada
			cargatotal = cargatotal - quantidade_parada[parada_atual];
			quantidade_parada[parada_atual] = 0 ;
			printf("x%d_%d_%d = 1\n",parada_anterior,parada_atual,k);
		}
	}
}


return 0;
}



