#ifndef CLIENTES
#define CLIENTES

#include "contas.h"

typedef struct _CLIENTE
{
    char codigo[5];
    char nome[50];
    char CPF_CNPJ[20];
    char telefone[20]; // +55 62 91234-1234
    char endereco[100];
    int contas_registradas;
    CONTA conta[2];
} CLIENTE;

CLIENTE cadastraCliente();

void organizaClientes();

void listaClientes();

int buscaClientes(char opcao, char string[]);

int atualizaCliente(int indice);

int excluiCliente(int indice);

void imprimeCliente();

#endif // CLIENTES