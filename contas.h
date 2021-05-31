#ifndef CONTAS
#define CONTAS

#include "clientes.h"

typedef struct _CONTA
{
    char agencia[20];
    int numeroConta;
    double saldo;
} CONTA;

void cadastraConta();

#endif // CONTAS