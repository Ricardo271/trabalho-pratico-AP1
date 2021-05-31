#ifndef CONTAS
#define CONTAS

#include "clientes.h"
#include "transacoes.h"

typedef struct _CONTA
{
    int agencia;
    int numeroConta;
    int codConta; // O código é a agencia concatenada com o número da conta
    double saldo;
} CONTA;

void cadastraConta();

void listaTodasContas();

void imprimeContas();

void buscaConta(int agencia, int numeroConta, int *indexCliente, int *indexConta);

CONTA realizarSaque(CONTA conta);

CONTA realizaDeposito(CONTA conta);

#endif // CONTAS