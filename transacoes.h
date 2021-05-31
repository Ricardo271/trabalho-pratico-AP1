#ifndef TRANSACOES
#define TRANSACOES

#include <stdbool.h>
#include <time.h>

typedef struct tm tm;

typedef struct _TRANSACAO
{
    int codConta;
    bool debito;
    bool credito;
    double valor;
    tm *data;
    char descricao[100];
} TRANSACAO;

void criaTransacao(int codConta, char operacao, double valor);

#endif //TRANSACOES