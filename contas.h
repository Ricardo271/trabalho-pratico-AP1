#ifndef CONTAS
#define CONTAS

#include "clientes.h"
#include "transacoes.h"

typedef struct _CONTA
{
    int agencia;
    int numeroConta;
    double saldo;
    TRANSACAO *ptTransacoes;
    int transacoes_realizadas;
} CONTA;

void cadastraConta();

void listaTodasContas();

void imprimeContas();

void buscaConta(int agencia, int numeroConta, int *indexCliente, int *indexConta);

CONTA realizarSaque(CONTA conta);

CONTA realizaDeposito(CONTA conta);

#endif // CONTAS