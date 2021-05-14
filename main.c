#include <stdio.h>
#include <string.h>

#include "clientes.h"
#include "menus.h"

CLIENTE cliente[100];

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
                    //O problema está nessa parte
                    int i = 0;
                    while (cliente[i].codigo != 0)
                        i++;
                    cadastraCliente(cliente[0]);
                }
                if (escolha != 'S')
                    escolha = '0';
            }
        }
        else if (escolha == 'T')
            escolha = imprimeGerenciarContas();
        escolha = imprimeBemVindo();
    }
}

void cadastraCliente(CLIENTE C)
{
    C.codigo = 1;

    char nome[100];
    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);
    strcpy(C.nome, nome);

    char CPF_CNPJ[12];
    printf("CPF/CNPJ: ");
    fgets(CPF_CNPJ, sizeof(CPF_CNPJ), stdin);
    strcpy(C.CPF_CNPJ, CPF_CNPJ);

    char telefone[14];
    printf("Telefone: ");
    fgets(telefone, sizeof(telefone), stdin);
    strcpy(C.telefone, telefone);

    char endereco[100];
    printf("Endereço: ");
    fgets(endereco, sizeof(endereco), stdin);
    strcpy(C.endereco, endereco);
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
        if (escolha != 'C' && escolha != 'T' && escolha != 'S')
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