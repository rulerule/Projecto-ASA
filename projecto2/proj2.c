#include <stdio.h>
#include <stdlib.h>

/** STRUCTS */

typedef struct _adjacentes{
	int node;
	int anterior;
	int flow;
	struct _adjacentes *next;
}adjacentes; /**lista com os numeros adjancentes*/

struct nos{
	int node;
	adjacentes *prev;
	adjacentes *primeiro;
	struct nos *next;
}*head;/**vector de estrutura*/

/**queue para BFS*/
struct queue {
	int node;
	struct nos *first;
	struct nos *last;
}*fila;

/**incializacoes*/
void limpaFlows();
int fordfulkerson ( int raiz , int target);
int bfs(int raiz , int target);
void addQueue (struct nos *no);
struct nos *deQueue();
struct nos *encontraNode(int raiz);

/**globals*/
struct queue *fila = NULL;
struct nos *head = NULL;
int *vectemp;
int flow_max = 1000000;
int flow_temp = 0;

int fordfulkerson (int raiz , int target)  {
	struct nos* temp;
	temp = encontraNode(raiz);
	
	while(bfs(raiz , target)){
		printf(" eu nunca venho aqui\n");
		flow_temp = flow_temp + 1;
			
	}
	
	return flow_temp;
	
}


int bfs (int raiz , int target) {
	struct nos *temp = NULL;
	struct nos *path_node = NULL; 
	adjacentes * aux = NULL;
	addQueue(encontraNode(raiz));
	vectemp[raiz] = 1;
		while (fila->first != NULL) {
			temp = deQueue(); 
			if (temp->node == target) { /** Chegamos ao target devolvemos 1*/
				return 1; 
			}
			aux = temp->primeiro;
			while (aux != NULL){
				if (aux->flow == 0 && vectemp[aux->node] == 0){
					vectemp[aux->node] = 1;
					addQueue(encontraNode(aux->node));
					path_node = encontraNode(aux->node);
					path_node->prev = aux;
				}
				aux = aux->next;
			}
			
		}
return 0;
}
	

/**adicionar a queue do BFS*/
void addQueue (struct nos *no) {
	if ( fila->first == NULL ) {
		fila->first = no; 
		fila->last = no;
		fila->first->next = NULL;
	}else{
		fila->last->next = no; 
		fila->last = no;
		no->next = NULL;
	}
}

/** tirar da queue do BFS*/
struct nos *deQueue() {
	struct nos *toreturn;
	if (fila->first == NULL) {
		printf(" fila vazia\n");
	}else{
		toreturn = fila->first;
		fila->first = fila->first->next;
		toreturn->next = NULL;
	}
	return toreturn;
}

/** encontra um no dado um inteiro correspondente ao node*/
struct nos *encontraNode(int raiz) {
	struct nos *temp;
	temp = head;
	while(temp != NULL) {
		if (temp->node == raiz){
			return temp;}
			temp = temp->next;}
			
			return 0;
		}
		
/**funcao que limpa o valor dos flows depois da execucao de um fordfulkerson*/
void limpaFlows () {
	struct nos* temp;
	temp = head;
	while(temp->next != NULL ) {
		
		while (temp->primeiro != NULL){
			temp->primeiro->flow = 0; 
			temp->primeiro = temp->primeiro->next; 
		}
		temp = temp->next; 
	}
}

void readFile() {

	int N, P;
	int i, o, v;
	int a;
	int problemas;
	int pontosCriticos;
	int pontoA , pontoB;
	int test;
	
	fscanf(stdin, "%d %d", &N, &P);
	

	vectemp = (int *) malloc(N * sizeof(int));
	
	for (i = 0; i < N; i++){
		vectemp[i] = 0;}

	for(i = 0; i < N; i++){
			
			struct nos *temp ; 
			temp = (struct nos *)malloc(sizeof(struct nos));
			temp->node = i;
			temp->primeiro = NULL;
			if(head == NULL){
				head = temp;
				head->next = NULL;
			}else{
				temp->next = head;
				head = temp;
	}
}
	
	for (a = 0 ; a < P ; a++){ 
		struct nos *temp1;
		struct nos *temp2;
		fscanf(stdin, "%d %d", &i, &o);
		
		temp1 = head;
		while (temp1 != NULL){
			if (temp1->node == i) {
				break;}
			temp1 = temp1->next;
		}
		
		if(temp1->primeiro == NULL){
			temp1->primeiro = (adjacentes *)malloc(sizeof(adjacentes));/**aloca memoria para a primeira adjacencia*/
			temp1->primeiro->node = o;/**primeira adjancencia*/
			temp1->primeiro->next = NULL;/**proximo a null*/
		}else{
			adjacentes *temp = temp1->primeiro;
			while(temp->next != NULL){/**avança ate ao fim*/
				temp = temp->next;
			}
			temp->next = (adjacentes *)malloc(sizeof(adjacentes));
			temp->next->node = o;
			temp->next->next = NULL;
		}
		
		temp2 = head;
		while (temp2 != NULL){
			if (temp2->node == i) {
				break;}
			temp2 = temp2->next;
		}
		
		if(temp2->primeiro == NULL){
			temp2->primeiro = (adjacentes *)malloc(sizeof(adjacentes));/**aloca memoria para a primeira adjacencia*/
			temp2->primeiro->node = i;/**primeira adjancencia*/
			temp2->primeiro->next = NULL;/**proximo a null*/
		}else{
			adjacentes *temp = temp2->primeiro;
			while(temp->next != NULL){/**avança ate ao fim*/
				temp = temp->next;
			}
			temp->next = (adjacentes *)malloc(sizeof(adjacentes));
			temp->next->node = i;
			temp->next->next = NULL;
		}
		
	}
	
	/**apanhar o numero de problemas*/
	fscanf(stdin, "%d", &problemas);
	
	/** ciclo para resolver os problemas*/
	for (i = 0; i < problemas; i ++){
	fscanf(stdin, "%d" , &pontosCriticos);
		if (pontosCriticos == 2) {
			fscanf(stdin , "%d %d" , &pontoA , &pontoB);
			printf("eu chamo o fordfulkerson\n");
			test = fordfulkerson(pontoA , pontoB);
			printf("%d\n" , test);
			/**LIMPAR O VECTOR DE VISITADAS*/
			for (v = 0; v < N; v++){
				vectemp[v] = 0;}
			/**LIMPAR OS FLOWS*/
			limpaFlows();
				
		}else{
			fscanf(stdin , "%d" , &pontoA);
			while (pontosCriticos > 1){
				fscanf (stdin , "%d" , &pontoB);
		
		/** flow_max = min(flow_max , fordfulkerson (pontoA , pontoB); */
		pontosCriticos = pontosCriticos - 1; 
		
		/**LIMPAR O VECTOR DE VISITADAS*/
			for (v = 0; v < N; v++){
				vectemp[v] = 0;}
		/**LIMPAR OS FLOWS*/
			limpaFlows();	
		
			}
			/**printf(" %d\n", flow_max); */
		}
	}
		
}
	


int main(){
	fila = (struct queue*) malloc (sizeof( struct queue));
	fila->first = NULL;
	fila->last = NULL;
	readFile();
	
	return (0);

}
