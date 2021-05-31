#ifndef CONTAS
#define CONTAS

#include "clientes.h"

typedef struct _CONTA
{
    int agencia;
    int numeroConta;
    double saldo;
} CONTA;

void cadastraConta();

void listaTodasContas();

void imprimeContas();

#endif // CONTAS