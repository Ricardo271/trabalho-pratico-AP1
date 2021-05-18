#include <stdio.h>
#include <string.h>

#include "clientes.h"
#include "menus.h"

#define SIZE 100

CLIENTE cliente[SIZE];

int main()
{
    char escolha = imprimeBemVindo();
    while (escolha != 'S')
    {
        if (escolha == 'C')
        {
            while (escolha != 'S')
            {
                escolha = imprimeGerenciarClientes();
                if (escolha == 'C')
                {
                    char nome[100];
                    printf("Nome: ");
                    fgets(nome, sizeof(nome), stdin);

                    char CPF_CNPJ[20];
                    printf("CPF/CNPJ: ");
                    fgets(CPF_CNPJ, sizeof(CPF_CNPJ), stdin);

                    char telefone[20];
                    printf("Telefone: ");
                    fgets(telefone, sizeof(telefone), stdin);

                    char endereco[100];
                    printf("Endereço: ");
                    fgets(endereco, sizeof(endereco), stdin);

                    int i = 0;
                    while (cliente[i].nome[0] != 0)
                        i++;
                    cliente[i] = cadastraCliente("1234", nome, CPF_CNPJ, telefone, endereco);
                } else if (escolha == 'L')
                {
                    listaClientes(cliente);
                }

                // Reseta a escolha
                if (escolha != 'S')
                    escolha = '0';
            }
        }
        else if (escolha == 'T')
            escolha = imprimeGerenciarContas();
        escolha = imprimeBemVindo();
    }
}

CLIENTE cadastraCliente(char codigo[], char nome[], char CPF_CNPJ[], char telefone[], char endereco[])
{
    CLIENTE C;
    strcpy(C.codigo, codigo);
    strcpy(C.nome, nome);
    strcpy(C.CPF_CNPJ, CPF_CNPJ);
    strcpy(C.telefone, telefone);
    strcpy(C.endereco, endereco);
    return C;
}

int verificaCodigos()
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            if (!strcmp(cliente[i].codigo, cliente[j].codigo))
            {
                return 0;
            }
        }
    }
}

// !TODO
void organizaClientes(CLIENTE C[])
{
    return;
}

void listaClientes(CLIENTE C[])
{
    //organizaClientes(cliente);
    int i = 0;
    while (C[i].nome[0] != 0)
    {
        // Valores obtidos com o fgets() ficam com o ENTER final
        printf("----- CLIENTE %d -----\n"
                "Nome: %s"
                "CPF/CNPJ: %s"
                "Codigo: %s\n"
                "Telefone: %s"
                "Endereço: %s"
                "---------------------\n",
                i, C[i].nome, C[i].CPF_CNPJ, C[i].codigo, C[i].telefone, C[i].endereco);

        i++;
    }
    
}

char imprimeBemVindo()
{
    char escolha = '0';
    while (escolha != 'C' && escolha != 'T' && escolha != 'S')
    {
        printf("=============== Bem vindo! =================\n"
               "Digite um comando para prosseguir:\n"
               "C - Gerenciar Clientes\n"
               "T - Gerenciar Contas\n"
               "S - Sair\n-> ");
        scanf("%c", &escolha);
        getchar();
        escolha = paraMaiuscula(escolha);
        if (escolha != 'C' && escolha != 'T' && escolha != 'S')
            printf("\nPor favor escolha uma das opções\n\n");
    }
    return escolha;
}

char imprimeGerenciarClientes()
{
    char escolha = '0';
    while (escolha != 'C' && escolha != 'L' && escolha != 'B' && escolha != 'A' && escolha != 'E' && escolha != 'S')
    {
        printf("=============== Gerenciar Clientes =================\n"
               "Digite um comando para prosseguir:\n"
               "C - Cadastrar um cliente\n"
               "L - Listar todos os clientes cadastrados\n"
               "B - Buscar cliente já cadastrado\n"
               "A - Atualizar um cliente cadastrado\n"
               "E - Excluir um cliente cadastrado\n"
               "S - Sair\n"
               "-> ");
        scanf("%c", &escolha);
        getchar();
        escolha = paraMaiuscula(escolha);
        if (escolha != 'C' && escolha != 'L' && escolha != 'B' && escolha != 'A' && escolha != 'E' && escolha != 'S')
            printf("\nPor favor escolha uma das opções\n\n");
    }
    return escolha;
}

char imprimeGerenciarContas()
{
    char escolha = '0';
    while (escolha != 'C' && escolha != 'L' && escolha != 'B' && escolha != 'A' && escolha != 'E' && escolha != 'S')
    {
        printf("=============== Gerenciar Contas =================\n"
               "Digite um comando para prosseguir:\n"
               "R – Listagem de todas as contas cadastradas\n"
               "C – Cadastrar uma conta para um cliente\n"
               "L – Listar todas as contas de um cliente\n"
               "W – Realizar um saque em uma conta\n"
               "D – Realizar um depósito em uma conta\n"
               "T – Realizar transferência entre contas\n"
               "E – Exibir extrato de uma conta\n"
               "S - Sair\n"
               "-> ");
        scanf("%c", &escolha);
        getchar();
        escolha = paraMaiuscula(escolha);
        if (escolha != 'C' && escolha != 'T' && escolha != 'S')
            printf("\nPor favor escolha uma das opções\n\n");
    }
    return escolha;
}

char paraMaiuscula(char c)
{
    if (c >= 97 && c <= 122)
        c -= 32;
    return c;
}