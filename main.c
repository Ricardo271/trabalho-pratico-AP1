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
        if (escolha == 'C') {
            while (escolha != 'S')
            {
                escolha = imprimeGerenciarClientes();
                if (escolha == 'C')
                {
                    char nome[100];
                    printf("Nome: ");
                    fgets(nome, sizeof(nome), stdin);
                    //getchar();

                    char CPF_CNPJ[12];
                    printf("CPF/CNPJ: ");
                    scanf("%s", &CPF_CNPJ);
                    getchar();

                    char telefone[14];
                    printf("Telefone: ");
                    scanf("%s", &telefone);
                    getchar();

                    char endereco[100];
                    printf("Endereço: ");
                    scanf("%s", endereco);
                    getchar();

                    int i = 0;
                    while (cliente[i].nome[0] != 0)i++;
                    cliente[i] = cadastraCliente("1234", nome, CPF_CNPJ, telefone, endereco); 
                }
                if (escolha != 'S') escolha = '0';
            }
        }
        else if (escolha == 'T')
            escolha = imprimeGerenciarContas();
        escolha = imprimeBemVindo();
    }
    

    cadastraCliente("1234", "Ricardo", "123456789xx", "+5562912341234", "Rua 1, Casa 2, Apt 3");
}

CLIENTE cadastraCliente(char codigo[], char nome[], char CPF_CNPJ[], char telefone[], char endereco[])
{
    CLIENTE C;
    strcpy(C.codigo,codigo);
    strcpy(C.nome, nome);
    strcpy(C.CPF_CNPJ, CPF_CNPJ);
    strcpy(C.telefone, telefone);
    strcpy(C.endereco, endereco);
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

char imprimeBemVindo()
{
    char escolha = '0';
    while(escolha != 'C' && escolha != 'T' && escolha != 'S')
    {
        printf("=============== Bem vindo! =================\n"
               "Digite um comando para prosseguir:\n"
               "C - Gerenciar Clientes\n"
               "T - Gerenciar Contas\n"
               "S - Sair\n-> "
        );
        scanf("%c", &escolha);
        getchar();
        escolha = paraMaiuscula(escolha);
        if (escolha != 'C' && escolha != 'T' && escolha != 'S') printf("\nPor favor escolha uma das opções\n\n");
    }
    return escolha;
}

char imprimeGerenciarClientes()
{
    char escolha = '0';
    while(escolha != 'C' && escolha != 'L' && escolha != 'B' && escolha != 'A' && escolha != 'E' && escolha != 'S')
    {
        printf("=============== Gerenciar Clientes =================\n"
               "Digite um comando para prosseguir:\n"
               "C - Cadastrar um cliente\n"
               "L - Listar todos os clientes cadastrados\n"
               "B - Buscar cliente já cadastrado\n"
               "A - Atualizar um cliente cadastrado\n"
               "E - Excluir um cliente cadastrado\n"
               "S - Sair\n"
               "-> "
        );
        scanf("%c", &escolha);
        getchar();
        escolha = paraMaiuscula(escolha);
        if (escolha != 'C' && escolha != 'T' && escolha != 'S') printf("\nPor favor escolha uma das opções\n\n");
    }
    return escolha;
}

char imprimeGerenciarContas()
{
    char escolha = '0';
    while(escolha != 'C' && escolha != 'L' && escolha != 'B' && escolha != 'A' && escolha != 'E' && escolha != 'S')
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
               "-> "
        );
        scanf("%c", &escolha);
        getchar();
        escolha = paraMaiuscula(escolha);
        if (escolha != 'C' && escolha != 'T' && escolha != 'S') printf("\nPor favor escolha uma das opções\n\n");
    }
    return escolha;
}

char paraMaiuscula(char c)
{
    if (c >= 97 && c <= 122) c -= 32;
    return c;
}