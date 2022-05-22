#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "pilha.h"
#include "lista.h"
#include "expressao.h"

Tipo_lista addStringList(char *str);
Tipo_pilha addStringStack(char *str);
char getOperador(char c);
void printList(Tipo_lista lista);
void printStack(Tipo_pilha pilha);
Tipo_pilha convertInfixaToPosFixa(Tipo_lista lista);
int calculaPosFixa(Tipo_pilha pilha);
void invert_stack(Tipo_pilha pilha);

int main(void) {
    char expressao[120];
    Tipo_lista infixa;
    Tipo_pilha posfixa;
    int result = 0;

    do{
        printf("(obs: 0 - sair)\n");
        printf("Expressao Infixa: ");
        scanf(" ");
        scanf("%[^\n]", expressao);
        
        if(strcmp(expressao,"0")!=0){
            infixa = addStringList(expressao);
            posfixa = convertInfixaToPosFixa(infixa);
            printStack(posfixa);
            result = calculaPosFixa(posfixa);
            printf("Resultado: %d\n\n", result);
            //system("pause");
            //system("cls");
        }

    }while (strcmp(expressao,"0")!=0);
    printf("Programa encerrado.\n");
    return 0;
}

int calculaPosFixa(Tipo_pilha pilha){
	Particle *aux_part;
	Tipo_pilha auxPilha = new_stack();
	
	while(!empity_stack(pilha)){
		aux_part = desempilharElemento(pilha);
		
		if(aux_part->tipo == TIPO_OPERADOR){
			Particle *num1, *num2, result;

			num2 = desempilharElemento(auxPilha);
			num1 = desempilharElemento(auxPilha);

            result = calculate(*num1, *aux_part, *num2);
			*aux_part = result;
		}
		
		empilharElemento(auxPilha, aux_part);
	}
	
	aux_part = desempilharElemento(auxPilha);
	return aux_part->opera.ndo;
}

Tipo_lista addStringList(char *str){
    Tipo_lista lista = new_list();

    for (int i = 0; i < (int) strlen(str); )
    {
        if(ispunct(str[i]))
        {
            Particle *p1 = new_particle();
            p1->tipo = TIPO_OPERADOR;
            p1->opera.dor = getOperador(str[i]);
            
            strcpy(str, (str+i+1));

            add_element(lista, get_size(lista)+1, p1);
        }     
        else if (isdigit(str[i]))
        {
            Particle *p1 = new_particle();
            p1->tipo = TIPO_OPERANDO;
            p1->opera.ndo = strtol(str, &str, 10);

            add_element(lista, get_size(lista)+1, p1);
        }
    }
    return lista;
}

char getOperador(char c){
    switch (c)
    {
        case '+':  return '+'; break;
        case '-':  return '-'; break;
        case '*':  return '*'; break;
        case '/':  return '/'; break;
        case '(':  return '('; break;
        case ')':  return ')'; break;
    }
    return 0;
}

void printList(Tipo_lista lista){
    Particle *p1;

    printf("Lista: ");
    for (int i = 1; i <= get_size(lista); i++)
    {
        p1 = (Particle*) get_element(lista, i);
        print_particle(p1);
        
    }
    printf("\n");
}

Tipo_pilha convertInfixaToPosFixa(Tipo_lista lista){
    Tipo_pilha aux_pilha = new_stack();
    Tipo_pilha pilha_final = new_stack();
    Tipo_lista aux_lista = new_list();
    Particle *aux_part = new_particle();

    while(get_size(lista)>0){
        aux_part = (Particle*) get_element(lista, INICIO);
        remove_element(lista, INICIO);
        add_element(aux_lista, get_size(aux_lista)+1, aux_part);

        if(aux_part->tipo == TIPO_OPERADOR){
            if(aux_part->opera.dor != '(' && aux_part->opera.dor != ')'){ 
                Particle *p1 = (Particle*) obterTopo(aux_pilha);
                while(!empity_stack(aux_pilha) && get_Priority(p1) >= get_Priority(aux_part)){
                    p1 = desempilharElemento(aux_pilha);
                    empilharElemento(pilha_final, p1);
                    p1 = (Particle*) obterTopo(aux_pilha);
                }
                empilharElemento(aux_pilha, aux_part);
            }
            else if(aux_part->opera.dor == '('){
                empilharElemento(aux_pilha, aux_part);
            }
            else if(aux_part->opera.dor == ')'){
                while(aux_part->opera.dor != '(' && !empity_stack(aux_pilha)){
                    aux_part = desempilharElemento(aux_pilha);
                    if(aux_part->opera.dor != '('){
                        empilharElemento(pilha_final, aux_part);
                    }
                }
                
            }
        }
        else if(aux_part->tipo == TIPO_OPERANDO){
            empilharElemento(pilha_final, aux_part);
        }
    }
    while (!empity_stack(aux_pilha))
    {
        aux_part = desempilharElemento(aux_pilha);
        empilharElemento(pilha_final, aux_part);
    }
    *lista = *aux_lista;
    invert_stack(pilha_final);
    return pilha_final;
}

void invert_stack(Tipo_pilha pilha){
    Tipo_pilha aux_pilha = new_stack();
    Particle *a;

    while (!empity_stack(pilha))
    {
        a = desempilharElemento(pilha);
        empilharElemento(aux_pilha, a);
    }
    *pilha = *aux_pilha;
}

void printStack(Tipo_pilha pilha){
    Tipo_pilha aux_pilha = new_stack();
    Particle *aux_part;

    printf("Pilha: ");
    if(!empity_stack(pilha)){
        while (!empity_stack(pilha))
        {
            aux_part = desempilharElemento(pilha);
            print_particle(aux_part);
            empilharElemento(aux_pilha, aux_part);
        }
        *pilha = *aux_pilha;
        invert_stack(pilha);
        printf("\n");
    }
    else
        printf("Vazia\n");
}
























