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
	
	if(nova != NULL){ /*se consegui alocar o espaço faço o novo nó receber o conteudo (palavra, sinonimo e idioma)*/
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

	if(*tree == NULL){ /*se a arvore estiver vazia ou o local que quero alocar estiver vazio, aloco um novo no na arvore*/
		*tree = aloca(str, id, s);
	}else if(strcmp(str, (*tree)->palavra) < 0) /*se a nova palavra for menor lexicograficamente, chamo a função e faço o no ser inserido na subarvore esquerda*/
		insereArvore(&nova->esq, str, id, s);
	else if(strcmp(str, (*tree)->palavra) > 0)/*se a nova palavra for maior lexicograficamente, chamo a função e faço o no ser inserido na subarvore direita*/
		insereArvore(&nova->dir, str, id, s);
	else if(strcmp(str, (*tree)->palavra) == 0){ /*se a palavra já existir, aloco somento o seu novo sinonimo*/
		q = aloca_sinonimo(s);
		q->prox_sin = nova->primeiro_conceito;
		nova->primeiro_conceito = q;
	}
}

void busca(arvore *tree, char *str){
	lista_sinonimo *q;

	if(tree == NULL) /*se a palavra não existir na arvore ou a arvore estiver vazia eu retorno a mensagem*/
		printf("hein?\n");
	else{
		if(strcmp(str, tree->palavra) == 0){ /*se a palavra existir, imprimo seus respectivos sinonimos*/
			for(q = tree->primeiro_conceito; q != NULL; q = q->prox_sin)
				printf("%s\n", q->sinonimo);
		}else if(strcmp(str, tree->palavra) < 0) /*se a palavra for menor lexicograficamento eu busco na subarvore esquerda*/
			busca(tree->esq, str);
		else if(strcmp(str, tree->palavra) > 0)/*se a palavra for maior lexicograficamento eu busco na subarvore direita*/
			busca(tree->dir, str);
	}
}

void remover(arvore **p, char *str){
	arvore *q;
	
	if((*p) != NULL){/*se tiver elementos na arvore ou ainda nao cheguei ainda não cheguei ao fim da arvore*/
		if(strcmp(str, (*p)->palavra) == 0){ /*verifico se a palavra que quero remover eh a palavra que está na arvore*/
			q = (*p); /*faco q receber o elemento que quero remover*/
			if(((*p)->esq == NULL) && ((*p)->dir == NULL)){ /*remocao para no folha*/
				free(*p); /*se for uma folha, removo direto o elemento*/
		          (*p) = NULL; 
			}else if((*p)->esq == NULL){ /*remocao para no com um filho a direita*/
				(*p) = (*p)->dir; /*faço o no receber seu filho*/
				q->dir = NULL; /*faco o filho do q ser nulo*/
				free(q); /*removo o q*/
			}else if((*p)->dir == NULL){ /*remocao para no com um filho a esquerda*/
				(*p) = (*p)->esq; /*faço o no receber seu filho*/
				q->esq = NULL; /*faco o filho do q ser nulo*/
				free(q);
			}else{ /*remocao para no com 2 filhos*/
				q = (*p)->esq; /*o q recebe o filho esquerdo do no que vou remover*/
				while(q->dir != NULL) /*procuro o maior elemento mais a esquerda do no*/
					q = q->dir;
				strcpy((*p)->palavra, q->palavra); /*passo as informacoes do no que eu encontrei para o no que vou remover*/
				strcpy((*p)->idioma, q->idioma);
				(*p)->primeiro_conceito = q->primeiro_conceito;
				remover((&(*p)->esq), (*p)->palavra); /*chamo a funcao pra remover o no que troquei as informacoes*/
			}	
		}else if(strcmp(str, (*p)->palavra) < 0) /*se a palavra for menor lexicograficamento eu busco na subarvore esquerda o elemento que vou remover*/
			remover((&(*p)->esq), str);
		else if(strcmp(str, (*p)->palavra) > 0)/*se a palavra for maior lexicograficamento eu busco na subarvore direita o elemento que vou remover*/
			remover((&(*p)->dir), str);
	}
}

void remove_sinonimo(arvore **tree, char *str1, char *str2){
	arvore *q;
	lista_sinonimo *p, *s;
	s = NULL;
	
	if(*tree != NULL){ /*se tiver elementos na arvore ou ainda nao cheguei ainda não cheguei ao fim da arvore*/
		if(strcmp(str1, (*tree)->palavra) == 0){ /*verifico se a palavra que quero remover eh a palavra que está na arvore*/
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
			if(q != NULL && q->primeiro_conceito == NULL) /*verifico se a palavra ficou sem sinonimo, se ficou eu chamo a funcao para remover ela*/
				remover((&(*tree)), str1);
		}else if(strcmp(str1, (*tree)->palavra) < 0) /*se a palavra for menor lexicograficamento eu busco na subarvore esquerda o elemento que vou remover*/
			remove_sinonimo((&(*tree)->esq), str1, str2);
		else if(strcmp(str1, (*tree)->palavra) > 0) /*se a palavra for maior lexicograficamento eu busco na subarvore direita o elemento que vou remover*/
			remove_sinonimo((&(*tree)->dir), str1, str2);
	}
}

/*Funcao para Listar as palavras atraves do idioma, usei o percurso por ordem simetrica*/
void lista_idioma(arvore *tree, char *id){ 
	lista_sinonimo *q;
	
	if (tree != NULL){ /*verifico se a arvore nao eh nula*/
		lista_idioma(tree->esq, id); /*vou ate a folha da subarvore esquerda*/
		if(strcmp(id, tree->idioma) == 0){ /*verifico se o idioma eh o que quero*/
			printf("%s: ", tree->palavra); /*imprimo a palavra com seus sinonimos*/
			printf("%s", tree->primeiro_conceito->sinonimo);
			for(q = tree->primeiro_conceito->prox_sin; q != NULL; q = q->prox_sin)
				printf(", %s", q->sinonimo);
			printf("\n");
		}
		lista_idioma(tree->dir, id); /*vou ate a folha da subarvore direita*/
	} 
}

void lista_idioma_emIntervalo(arvore *tree, char *id, char *i, char *f){
	lista_sinonimo *q;
	
	if (tree != NULL){ /*verifico se a arvore nao eh nula*/
		lista_idioma_emIntervalo(tree->esq, id, i, f); /*vou ate a folha da subarvore esquerda*/
		if((strcmp(id, tree->idioma) == 0)){ /*verifico se o idioma eh o que quero*/
			if((tree->palavra[0] >= i[0]) && (tree->palavra[0] <= f[0])){ /*verifico se a palavra esta entre as iniciais informadas*/
				printf("%s: ", tree->palavra); /*imprimo a palavra com seus sinonimos*/
				printf("%s", tree->primeiro_conceito->sinonimo);
				for(q = tree->primeiro_conceito->prox_sin; q != NULL; q = q->prox_sin)
					printf(", %s", q->sinonimo);
				printf("\n");
			}
		}
		lista_idioma_emIntervalo(tree->dir, id, i, f); /*vou ate a folha da subarvore direita*/
	} 
}

/*Funcao libera: Libera o espaco que foi armazenado em uma arvore*/
void libera(arvore *tree){/*realizo a liberacao do espaço armazenado da arvore em pos-ordem para começar dos nos folhas e por ultimo a raiz*/
	
	if(tree != NULL){ 
		libera(tree->esq);
		libera(tree->dir);
		free(tree);
	}
}
