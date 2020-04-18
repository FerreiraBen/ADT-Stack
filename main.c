#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef void (*TImpressora)(void*);
typedef struct lista TLista;
TLista *criarLista();
void inserirInicioLSE(TLista *lst, void *e_carganova);
void inserirFinalLSE(TLista *lst, void *e_carganova);
void* removerInicioLSE(TLista *lst);
void* removerFinalLSE(TLista *lst);
void imprimirLSE(TLista *lst, TImpressora impressora);
typedef struct pilha TPilha;
TPilha *criarPilha();
void empilhar(TPilha *f, void *novoElem);
void *desempilhar(TPilha *f);

typedef struct elemento{
	void *carga;
	struct elemento *prox;
} TElemento;

struct lista{
	int nroElementos;
	TElemento *inicio;
	TElemento *final;
};

TLista *criarLista(){
	TLista *e_lista = malloc(sizeof(TLista));
	e_lista->nroElementos = 0;
	e_lista->inicio=NULL;
	e_lista->final = NULL;
	return e_lista;
}

void inserirInicioLSE(TLista *lst, void *e_carganova){
	if (lst->inicio == NULL){
		TElemento *elem = malloc(sizeof(TElemento));
		elem->carga = e_carganova;
		elem->prox = NULL;
		lst->inicio = elem;
		lst->final = elem;
		lst->nroElementos = 1;
	}else{
		TElemento *elem = malloc(sizeof(TElemento));
		elem->prox = lst->inicio;
		elem->carga = e_carganova;
		lst->inicio = elem;
		lst->nroElementos++;
	}
}

void inserirFinalLSE(TLista *lst, void *e_carganova){
	if (lst->inicio == NULL){
		TElemento *elem = malloc(sizeof(TElemento));
		elem->carga = e_carganova;
		elem->prox = NULL;
		lst->inicio = elem;
		lst->final = elem;
		lst->nroElementos = 1;
	}else{
		TElemento *elem = malloc(sizeof(TElemento));
		lst->final->prox = elem;
		elem->carga = e_carganova;
		elem->prox = NULL;
		lst->final = elem;
		lst->nroElementos++;
	}
}

void* removerInicioLSE(TLista *lst){
	void *carga=NULL;
	if (lst->inicio != NULL){
		TElemento *prim = lst->inicio;
		TElemento *e_novoInicio = prim->prox;
		carga = prim->carga;
		free(prim);
		lst->inicio = e_novoInicio;
		lst->nroElementos--;
		if (lst->inicio == NULL)
			lst->final = NULL;
	return carga;
}

void* removerFinalLSE(TLista *lst){
	void *carga=NULL;
	if(lst->inicio != NULL){
		TElemento *anterior=NULL;
		TElemento *caminhador = lst->inicio;
		while(caminhador->prox!=NULL){
			anterior = caminhador;
			caminhador = caminhador->prox;
		}
		carga = lst->final->carga;
		free(lst->final);
		lst->final = anterior;
		if (lst->final == NULL){
			lst->inicio=NULL;
		}else{
			lst->final->prox = NULL;
		}
		lst->nroElementos--;
	return carga;
}


void imprimirLSE(TLista *lst, TImpressora impressora){
	if (lst->inicio != NULL){
		TElemento *caminhador=lst->inicio;
		while(caminhador != NULL){
			impressora(caminhador->carga);
			caminhador = caminhador->prox;
		}
	}
}

struct pilha{
	int tamanho;
	TLista *lista;
};

TPilha *criarPilha(){
	TPilha *p = malloc(sizeof(TPilha));
	p->tamanho = 0;
	p->lista = criarLista();
	return p;
}

void empilhar(TPilha *f, void *novoElem){
	inserirFinalLSE(f->lista, novoElem);
	f->tamanho++;
}

void *desempilhar(TPilha *f){
	void *elemento = removerFinalLSE(f->lista);
	if(elemento != NULL)
		f->tamanho--;
	return elemento;
}

typedef struct{
	 double valor;
} TValor;

typedef struct{
	 double latitude;
	 double longitude;
	 double temperatura;
	 int idSensor;
} TMedida;

int main(){
	TPilha *pilinha = criarPilha();
	TValor *v;
	v = malloc(sizeof(TValor));
	TValor *a;
	a = malloc(sizeof(TValor));
	TMedida *m;
	v = malloc(sizeof(TMedida));
	TMedida *c;
	a = malloc(sizeof(TMedida));
	char funcao;
	char tipo[7];
	int aux;
	double auxd;

	scanf(" %s",&tipo);
	if((strcmp(tipo,"inteira") == 0) || (strcmp(tipo,"inteira") == 0) ){
		scanf(" %c",&funcao);
		while(funcao != 'X'){
			if(funcao == 'E'){
				 v = malloc(sizeof(TValor));
				 scanf("%lf",&auxd);
				 v->valor = auxd;
				 empilhar(pilinha,v);
			 }
			 else if(funcao == 'D'){
				 if(pilinha->tamanho >0){  
						a = malloc(sizeof(TValor));
						a = desempilhar(pilinha);
						printf("%d\n",(int) a->valor);
				 }
			 }
			 else if(funcao == 'T'){
				 a = malloc(sizeof(TValor));
				 a = pilinha->lista->final->carga;
				 printf("%d\n", (int) (a->valor));
			 }
			 else if(funcao == 'A'){
				 printf("%d\n", pilinha->tamanho);
			 }
			 else if(funcao == 'V'){
				 if(pilinha->tamanho == 0){
						printf("verdadeiro\n");
				 }
				 else{
						printf("falso\n");
				 }
			 }
			 scanf(" %c",&funcao);
		}
	}
	else{
			scanf(" %c",&funcao);
		while(funcao != 'X'){
			double lat, lon,temp; int id;
			if(funcao == 'E'){
				 m = malloc(sizeof(TMedida));
				 scanf("%lf %lf %lf %d",&lat, &lon, &temp, &id);
				 m->latitude = lat;
				 m->longitude = lon;
				 m->temperatura = temp;
				 m->idSensor = id;
				 empilhar(pilinha,m);
			 }
			 else if(funcao == 'D'){
				 if(pilinha->tamanho >0){
						c = malloc(sizeof(TMedida));
						c = desempilhar(pilinha);
						printf("%.3lf %.3lf %.3lf %d\n", c->latitude, c->longitude, c->temperatura, c->idSensor);
				 }
			 }
			 else if(funcao == 'T'){
				 c = malloc(sizeof(TMedida));
				 c = pilinha->lista->final->carga;
				 printf("%.3lf %.3lf %.3lf %d\n", c->latitude, c->longitude, c->temperatura, c->idSensor);
			 }
			 else if(funcao == 'A'){
				 printf("%d\n", pilinha->tamanho);
			 }
			 else if(funcao == 'V'){
				 if(pilinha->tamanho == 0){
						printf("verdadeiro\n");
				 }
				 else{
						printf("falso\n");
				 }
			 }
			 scanf(" %c",&funcao);
		}
	}
}
