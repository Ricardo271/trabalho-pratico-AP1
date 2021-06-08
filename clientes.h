#ifndef CLIENTES
#define CLIENTES

#include "contas.h"

#define codigo_size 6
#define nome_size 101
#define CPF_CNPJ_size 16 // CPF 123456789xx(11) & CNPJ XX.XXX.XXX/XXXX.XX(14)
#define telefone_size 16 // +5562912341234(14)
#define endereco_size 101

typedef struct _CLIENTE
{
    char codigo[codigo_size];
    char nome[nome_size];
    char CPF_CNPJ[CPF_CNPJ_size];
    char telefone[telefone_size]; // +55 62 91234-1234
    char endereco[endereco_size];
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