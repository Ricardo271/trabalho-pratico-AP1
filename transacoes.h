#ifndef TRANSACOES
#define TRANSACOES

#include <stdbool.h>
#include <time.h>

typedef struct tm tm;

typedef struct _TRANSACAO
{
    bool debito;
    bool credito;
    double valor;
    tm *data;
    char descricao[100];
} TRANSACAO;


#endif //TRANSACOES