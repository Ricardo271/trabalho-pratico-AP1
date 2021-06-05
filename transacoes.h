#ifndef TRANSACOES
#define TRANSACOES

#include <stdbool.h>
#include <time.h>

#define descricao_size 101

typedef struct tm tm;

typedef struct _TRANSACAO
{
    int codConta;
    bool debito;
    bool credito;
    double valor;
    tm *data;
    char descricao[descricao_size];
} TRANSACAO;

void criaTransacao(int codConta, char operacao, double valor, char descrico[]);

void imprimeTransacao(TRANSACAO T);

void exibeExtrato(int codigo);

#endif //TRANSACOES