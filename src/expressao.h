#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum Tipo
{
    TIPO_NULL,
    TIPO_OPERADOR,
    TIPO_OPERANDO
} Tipo;
typedef struct
{
    Tipo tipo;
    union
    {
        int ndo;
        char dor;
    } opera;
} Particle;

const Particle PARTICLE_NULLL = {TIPO_NULL, {0}};

Particle *new_particle()
{
    Particle *var;
    var = (Particle *)malloc(sizeof(Particle));
    *var = PARTICLE_NULLL;
    return var;
}

Particle calculate(Particle number1, Particle operador, Particle number2)
{
    if (number1.tipo != TIPO_OPERANDO && number2.tipo != TIPO_OPERANDO && operador.tipo != TIPO_OPERADOR)
    {
        return PARTICLE_NULLL;
    }

    Particle result = {TIPO_OPERANDO, {0}};
    switch (operador.opera.dor)
    {
    case '+':
        result.opera.dor = number1.opera.dor + number2.opera.dor;
        break;
    case '-':
        result.opera.dor = number1.opera.dor - number2.opera.dor;
        break;
    case '*':
        result.opera.dor = number1.opera.dor * number2.opera.dor;
        break;
    case '/':
        result.opera.dor = number1.opera.dor / number2.opera.dor;
        break;
    }

    return result;
}

/*int verify_particle(Particle p)
{
    if (p.tipo == TIPO_OPERADOR)
    {
        if( p.opera.dor != '+' || 
            p.opera.dor != '-' || 
            p.opera.dor != '*' || 
            p.opera.dor != '/' || 
            p.opera.dor != '(' || 
            p.opera.dor != ')')
            {
                return 0;
            }
    }
    return 1;
}*/

void print_particle(Particle *p){
    if(p->tipo == TIPO_NULL)
        printf("Vazio");
    if(p->tipo == TIPO_OPERADOR)
        printf("%c", p->opera.dor);
    if(p->tipo == TIPO_OPERANDO)
        printf("%d", p->opera.ndo);
}

void delete_particle(Particle *p){
    free(p);
}

int get_Priority(Particle *p){
    if(p->tipo == TIPO_OPERADOR){
        switch (p->opera.dor)
		{
			case '+':   return 1;   break;
			case '-':   return 1;   break;
			case '*':   return 2;   break;
			case '/':   return 2;   break;
			case '(':   return 0;   break;
			case ')':   return 0;   break;
			default:	return 0;	break;
		}
    }
    return 0;
} 










