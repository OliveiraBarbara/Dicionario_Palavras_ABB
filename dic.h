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

#define MAX 100

/*Struct da lista para armazenar os sinonimos*/
typedef struct lista_sinonimo{
	char sinonimo[MAX];
	struct lista_sinonimo *prox_sin; 
}lista_sinonimo;

/*Struct da arvore para armazenar as palavras*/
typedef struct arvore{
	char palavra[MAX];
	char idioma[3];
	struct lista_sinonimo *primeiro_conceito;
	struct arvore *esq; 
	struct arvore *dir;
}arvore;

/*Escopo de todas as funcoes utilizadas*/
lista_sinonimo *aloca_sinonimo(char *s);
arvore *aloca(char *str, char *id, char *s);
void insereArvore(arvore **tree, char *str, char *id, char *s);

void busca(arvore *tree, char *str);

void remover(arvore **p, char *str);
void remove_sinonimo(arvore **tree, char *str1, char *str2);

void lista_idioma(arvore *tree, char *id);
void lista_idioma_emIntervalo(arvore *tree, char *id, char *i, char *f);

void libera(arvore *tree);
