#ifndef CONTAS
#define CONTAS

#include "clientes.h"

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

void imprimeUmaConta();

void buscaConta(int agencia, int numeroConta, int *indexCliente, int *indexConta);

void realizarSaque(CONTA *conta, double valor);

void realizaDeposito(CONTA *conta, double valor);

void realizaTransferencia(CONTA *contaOrigem, CONTA *contaDestino);

#endif // CONTAS