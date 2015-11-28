#include <stdio.h>
#include <stdlib.h>

int numeroSCC=0;
int numeroMaximoDeTrocas=0;
int numeroApenasDentro=0;

typedef struct adjacentes{
	int node;
	struct adjacentes *next;
}adjacentes; /**lista com os numeros adjancentes*/

typedef struct{
	int d;
	int low;
	int flag;
	int flagStack;
	adjacentes *primeiro;
}nos;/**vector de estrutura*/

typedef struct pilha{
	int node;
	struct pilha *next;
}pilha;/**pilha*/

typedef struct SCC{
	int node;
	struct SCC *next;
}SCC;

void Tarjan_Visit(nos *listaAdj, pilha *p ,int posicao, int* visited);

/** VERIFICADO*/

void inserePilha(pilha *p, int i){
	if(p->next == NULL){
		p->next = (pilha *)malloc(sizeof(pilha));
		p->next->node = i;
		p->next->next = NULL;	
	}else{
		pilha *temp = (pilha *)malloc(sizeof(pilha));
	 	temp->next = p->next;
	 	p->next = temp;
	 	p->next->node = i;
	}
}

/** PELO MENOS PARECE BEM VERIFICAR */
void SCC_Tarjan(nos *listaAdj, pilha *p, int N, int P){
	int visited = 0;
	int i;
	p->next = NULL;
	/**limpar a pilha necessário?*/
	
	for(i = 0; i < N; i++){
		listaAdj[i].d = -1;}

	for(i = 0; i < N; i++){
		if(listaAdj[i].d == -1){
			Tarjan_Visit(listaAdj, p, i, &visited);
		}
	}
}

/** SUPOR QUE ISTO ESTA BEM **/
int min(int a, int b){
	if((a < b) || (b == -1))
		return a;
	if((b < a) || (a == -1))
		return b;
	return a;
}	

void insereSCC(int node, SCC* head){
	if(head->next == NULL){
		head->next = (SCC*)malloc(sizeof(SCC));
		head->next->next = NULL;
		head->next->node = node;
	}else{
		SCC *temp = (SCC*)malloc(sizeof(SCC));
		temp->next = head->next;
		head->next = temp;
		head->next->node = node;
	}
}


int verifica(SCC *head, nos *listaAdj){
	SCC *temp = head->next;
	adjacentes *aux;
	SCC *temp1 = head->next;

	if(listaAdj[head->next->node -1].primeiro == NULL){
		return 1;}

	while(temp != NULL){
		aux = listaAdj[temp->node - 1].primeiro;
		while(aux != NULL){
			if(listaAdj[aux->node-1].flag == 0){
				return 0;
			}
			while(temp1 != NULL){
				if(listaAdj[aux->node-1].low != listaAdj[temp1->node-1].low){return 0;}
					
				temp1 = temp1->next;
			}
			
			aux = aux->next;
		}
		temp = temp->next;
	}
	return 1;
}
void limpaSCC(SCC *head,nos *listaAdj){
	while(head->next != NULL){
		listaAdj[head->next->node-1].flag = 0;
		head->next = head->next->next;
	}
}

/** A VERIFICAR AGORA */ /** TEORICAMENTE BEM*/
void Tarjan_Visit(nos *listaAdj, pilha *p ,int posicao, int* visited){
	int v, controle;
	int numeroDeLigacoes = 0;
	adjacentes *temp;
	SCC *head = (SCC *)malloc(sizeof(SCC));
	head->next = NULL;
	

	listaAdj[posicao].d = listaAdj[posicao].low = (*visited);
	(*visited) += 1;
	
	inserePilha(p, (posicao+1)); /**PUSH*/
	listaAdj[posicao].flagStack = 1;
	
	temp = listaAdj[posicao].primeiro;
	
	while(temp != NULL){
		if( (listaAdj[temp->node-1].d == -1) || (listaAdj[temp->node-1].flagStack)){
			if(!(listaAdj[temp->node-1].flagStack)){
				Tarjan_Visit(listaAdj, p, temp->node - 1, visited);
			}
			
			listaAdj[posicao].low = min(listaAdj[posicao].low, listaAdj[temp->node-1].low);
			listaAdj[temp->node -1].low = min(listaAdj[posicao].low, listaAdj[temp->node -1].low);
		}
		
		temp = temp->next;
		
	}
	
	if(listaAdj[posicao].d == listaAdj[posicao].low){
		
		controle = listaAdj[posicao].low;
		
		while(listaAdj[p->next->node - 1].low == controle){

			v = p->next->node;

			p->next = p->next->next;/**troca o primeiro com o segundo na pilha*/
			
			listaAdj[v-1].flag = 1;
			listaAdj[v-1].flagStack = 0;

			insereSCC(v, head);

			numeroDeLigacoes += 1;

			if((listaAdj[v-1].d == listaAdj[v-1].low) && (numeroMaximoDeTrocas < numeroDeLigacoes))
				numeroMaximoDeTrocas = numeroDeLigacoes;

			if(listaAdj[v-1].d == listaAdj[v-1].low){
				numeroSCC += 1;
					if(listaAdj[v-1].primeiro != NULL) {
						if(verifica(head, listaAdj)){
						numeroApenasDentro += 1;
				
						}
					}
					else{
					numeroApenasDentro +=1;
					}	
				
			
				limpaSCC(head, listaAdj);
				numeroDeLigacoes = 0;

			}
			if(p->next == NULL)
				break;
			
			

		}
	}
	
}

/** VERIFICADO */
void readFile() {

	int N, P;
	int i, o;

	nos *listaAdj;
	pilha *p = (pilha *)malloc(sizeof(pilha));
	

	fscanf(stdin, "%d %d", &N, &P);

	listaAdj = (nos *)malloc(N * sizeof(nos));

	for(i = 0; i < N; i++){
		listaAdj[i].primeiro = NULL;
		listaAdj[i].flag = 0;
	}
	

	while(1){/**ciclo de inserção/criação do grafo/lista de adjacencias*/
		fscanf(stdin, "%d %d", &i, &o);
		
		if(listaAdj[i-1].primeiro == NULL){
			listaAdj[i-1].primeiro = (adjacentes *)malloc(sizeof(adjacentes));/**aloca memoria para a primeira adjacencia*/
			listaAdj[i-1].primeiro->node = o;/**primeira adjancencia*/
			listaAdj[i-1].primeiro->next = NULL;/**proximo a null*/
		}else{
			adjacentes *temp = listaAdj[i-1].primeiro;

			while(temp->next != NULL){/**avança ate ao fim*/
				temp = temp->next;
			}
			temp->next = (adjacentes *)malloc(sizeof(adjacentes));
			temp->next->node = o;
			temp->next->next = NULL;
		}


		if(feof(stdin)){
			break;
		}
	}
	
	SCC_Tarjan(listaAdj, p, N, P);
}

/**VERIFICADO*/	
int main(){
	
	readFile();
	
	printf("%d\n", numeroSCC);
	printf("%d\n", numeroMaximoDeTrocas);
	printf("%d\n", numeroApenasDentro);

	return (0);

}
