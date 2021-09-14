/***************************************************
Nome: Bárbara Beatriz Bueno de Oliveira
RGA: 2019.0743.014-8
Implementacao 2
Disciplina: Estruturas de Dados e Programacao I
Professor: Ronaldo Fiorilo
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dic.h"

lista_sinonimo *aloca_sinonimo(char *s){
	lista_sinonimo *nova;
	
	nova = (lista_sinonimo *) malloc (sizeof (lista_sinonimo)); /*aloco um espaco na memoria*/
	
	if(nova != NULL){
		strcpy(nova->sinonimo, s); /*na posição da lista na variavel do sinonimo eu atribuo o sinonimo correto*/
		nova->prox_sin = NULL;
	}else{ /*se a alocacao nao deu certo, informo na tela*/
		printf("Erro ao alocar memória\n");
	}
	return nova;
}

arvore *aloca(char *str, char *id, char *s){
	arvore *nova;
	
	nova = (arvore *) malloc (sizeof (arvore)); /*aloco um espaço na memória*/
	
	if(nova != NULL){ /*se consegui alocar o espaço faço a nova parte da lista receber uma acao do tipo arvore*/
		strcpy(nova->palavra, str);
		strcpy(nova->idioma, id);
		nova->primeiro_conceito = aloca_sinonimo(s);
		nova->esq = NULL;
		nova->dir = NULL;
	}else{ /*se a alocacao nao deu certo, informo na tela*/
		printf("Erro ao alocar memória\n");
	}
	return nova;
}

void insereArvore(arvore **tree, char *str, char *id, char *s){
	arvore *nova;
	lista_sinonimo *q;
	nova = *tree; 

	if(*tree == NULL){
		*tree = aloca(str, id, s);
	}else if(strcmp(str, (*tree)->palavra) < 0)
		insereArvore(&nova->esq, str, id, s);
	else if(strcmp(str, (*tree)->palavra) > 0)
		insereArvore(&nova->dir, str, id, s);
	else if(strcmp(str, (*tree)->palavra) == 0){
		q = aloca_sinonimo(s);
		q->prox_sin = nova->primeiro_conceito;
		nova->primeiro_conceito = q;
	}
}

void busca(arvore *tree, char *str){
	lista_sinonimo *q;

	if(tree == NULL)
		printf("hein?\n");
	else{
		if(strcmp(str, tree->palavra) == 0){
			for(q = tree->primeiro_conceito; q != NULL; q = q->prox_sin)
				printf("%s\n", q->sinonimo);
		}else if(strcmp(str, tree->palavra) < 0)
			busca(tree->esq, str);
		else if(strcmp(str, tree->palavra) > 0)
			busca(tree->dir, str);
	}
}

void remover(arvore **p, char *str){
	arvore *q;
	
	if(strcmp(str, (*p)->palavra) == 0){
		q = (*p);
		if(((*p)->esq == NULL) && ((*p)->dir == NULL)){ /*remocao para no folha*/
			free(q);
               (*p) = NULL; 
		}else if((*p)->esq == NULL){ /*remocao para no com um filho a direita*/
			(*p) = (*p)->dir;
			q->dir = NULL;
			free(q);
			q = NULL;
		}else if((*p)->dir == NULL){ /*remocao para no com um filho a esquerda*/
			(*p) = (*p)->esq;
			q->esq = NULL;
			free(q);
			q = NULL;
		}else{ /*remocao para no com 2 filhos*/
			q = (*p)->esq;
			while(q->dir != NULL)
				q = q->dir;
			strcpy((*p)->palavra, q->palavra);
			strcpy((*p)->idioma, q->idioma);
			(*p)->primeiro_conceito = q->primeiro_conceito;
			remover((&(*p)->esq), (*p)->palavra);
		}	
	}else if(strcmp(str, (*p)->palavra) < 0)
		remover((&(*p)->esq), str);
	else if(strcmp(str, (*p)->palavra) > 0)
		remover((&(*p)->dir), str);
}

void remove_sinonimo(arvore **tree, char *str1, char *str2){
	arvore *q;
	lista_sinonimo *p, *s;
	s = NULL;
	
	if(*tree == NULL)
		printf("Palavra já foi removida.\n");
	else if(strcmp(str1, (*tree)->palavra) == 0){
		p = (*tree)->primeiro_conceito;
		q = (*tree);
		while (p != NULL && (strcmp(p->sinonimo, str2) != 0)){ /*procuro o sinonimo na lista de sinonimo*/
			s = p;
			p = p->prox_sin;
		}
		if (p != NULL){ /*se ele estiver na lista eu verifico se ele é o primeiro sinonimo, se for o primeiro eu faco a primeira posicao da lista de sinonimo receber o sinonimo seguinte do que eu vou remover, e se ele nao for o primeiro, faco o sinonimo anterior receber o sinonimo seguinte do que vou remover*/
			if(s != NULL){
				s->prox_sin = p->prox_sin;
			}else{
				(*tree)->primeiro_conceito = p->prox_sin;
			}
			free(p); /*removo o sinonimo*/
		}
		if(q != NULL && q->primeiro_conceito == NULL)
			remover((&(*tree)), str1);
	}else if(strcmp(str1, (*tree)->palavra) < 0)
		remove_sinonimo((&(*tree)->esq), str1, str2);
	else if(strcmp(str1, (*tree)->palavra) > 0)
		remove_sinonimo((&(*tree)->dir), str1, str2);
}

void lista_idioma(arvore *tree, char *id){ 
	lista_sinonimo *q;
	
	if (tree != NULL){
		lista_idioma(tree->esq, id);
		if(strcmp(id, tree->idioma) == 0){
			printf("%s: ", tree->palavra);
			printf("%s", tree->primeiro_conceito->sinonimo);
			for(q = tree->primeiro_conceito->prox_sin; q != NULL; q = q->prox_sin)
				printf(", %s", q->sinonimo);
			printf("\n");
		}
		lista_idioma(tree->dir, id); 
	} 
}

void lista_idioma_emIntervalo(arvore *tree, char *id, char *i, char *f){
	lista_sinonimo *q;
	
	if (tree != NULL){
		lista_idioma_emIntervalo(tree->esq, id, i, f);
		if((strcmp(id, tree->idioma) == 0)){
			if((tree->palavra[0] >= i[0]) && (tree->palavra[0] <= f[0])){
				printf("%s: ", tree->palavra);
				printf("%s", tree->primeiro_conceito->sinonimo);
				for(q = tree->primeiro_conceito->prox_sin; q != NULL; q = q->prox_sin)
					printf(", %s", q->sinonimo);
				printf("\n");
			}
		}
		lista_idioma_emIntervalo(tree->dir, id, i, f); 
	} 
}

