#include <stdio.h>
#include <string.h>

#include "clientes.h"
#include "menus.h"

#define SIZE 100

CLIENTE cliente[SIZE];
int clientes_registrados = 0;

//TODO: colocar esse protótipo em algum dos arquivos .h
void carregaClientes();

int main()
{
    carregaClientes();    

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
                    cliente[clientes_registrados] = cadastraCliente();
                    clientes_registrados++;
                } else if (escolha == 'L')
                {
                    listaClientes(cliente);
                } else if (escolha == 'B')
                {
                    escolha = imprimeMenuBusca();
                    // printf("Insira Nome, Codigo ou CPF/CNPJ do cliente:\n-> ");
                    printf("Insira o Termo de busca: ");
                    char string[100];
                    //fgets(string, sizeof(string), stdin);
                    scanf("%s", &string);
                    getchar();
                    int aux = buscaClientes(cliente, escolha, string);
                    if (aux == -1)
                        printf("\nNenhum cliente foi encontrado.\n\n");
                    else
                        imprimeCliente(cliente[aux]);
                } else if (escolha == 'A')
                {
                    escolha = imprimeMenuAtualizacao();
                    char string[15];
                    scanf("%s", &string);
                    getchar();
                    int aux = atualizaCliente(buscaClientes(cliente, escolha, string));
                    if (aux == 1)
                        printf("O cliente foi atualizado com sucesso\n");
                    else if (aux == 0)
                        printf("A atualização foi cancelada\n");
                    else if (aux == -1)
                        printf("Ocorreu um erro durante a atualização do cliente\n");
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

CLIENTE cadastraCliente()
{
    char codigo[15] = "1234";

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

    CLIENTE C;

    strcpy(C.codigo, codigo);
    strcpy(C.nome, nome);
    strcpy(C.CPF_CNPJ, CPF_CNPJ);
    strcpy(C.telefone, telefone);
    strcpy(C.endereco, endereco);

    return C;
}

// TODO!: 
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

int buscaClientes(CLIENTE C[], char opcao, char string[])
{
    for (int i = 0; i < clientes_registrados; i++)
    {
        switch (opcao)
        {
            case 'N' :
                if (strstr(cliente[i].nome, string) != NULL)
                    return i;           
            break;

            case 'C' :
                if (strstr(cliente[i].codigo, string) != NULL)
                    return i;
            break;

            case 'D' :
                if (strstr(cliente[i].CPF_CNPJ, string) != NULL)
                    return i;
            break;
        }
    }
    return -1;
}

int atualizaCliente(int indice)
{
    char escolha = '0';
    printf("São esses o nome e CPF/CNPJ do cliente que vc deseja atualizar?(S/N)\n"
            " - %s"
            " - %s", cliente[indice].nome, cliente[indice].CPF_CNPJ);
    while (escolha != 'N' && escolha != 'S')
    {
        scanf("%c", &escolha);
        getchar();
        paraMaiuscula(escolha);
        switch (escolha)
        {
            case 'N' :
                return 0;
                break;
            case 'S' :
                cliente[indice] = cadastraCliente();
                return 1;
                break;
        } 
    }
    //TODO: lembrar de colocar alguma verificação se o cliente realmente foi cadastrado
    return -1;
}

void imprimeCliente(CLIENTE C)
{
    printf("----------------------\n"
            "Nome: %s"
            "CPF/CNPJ: %s"
            "Codigo: %s\n"
            "Telefone: %s"
            "Endereço: %s"
            "---------------------\n",
            C.nome, C.CPF_CNPJ, C.codigo, C.telefone, C.endereco);
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
        if (escolha != 'C' && escolha != 'L' && escolha != 'B' && escolha != 'A' && escolha != 'E' && escolha != 'S')
            printf("\nPor favor escolha uma das opções\n\n");
    }
    return escolha;
}

char imprimeMenuBusca()
{
    char escolha = '0';
    while (escolha != 'N' && escolha != 'C' && escolha != 'D')
    {
        printf("==================================================\n"
               "Deseja realizar a busca por:\n"
               "N – Nome\n"
               "C – Codigo\n"
               "D - CPF/CNPJ\n"
               "-> ");
        scanf("%c", &escolha);
        getchar();
        escolha = paraMaiuscula(escolha);
        if (escolha != 'N' && escolha != 'C' && escolha != 'D')
            printf("\nPor favor escolha uma das opções\n\n");
    }
    return escolha;
}

char imprimeMenuAtualizacao()
{
    char escolha = '0';
    while (escolha != 'C' && escolha != 'D')
    {
        printf("==================================================\n"
               "Deseja buscar o cliente por Codigo ou CPF/CNPJ :\n"
               "C – Codigo\n"
               "D - CPF/CNPJ\n"
               "-> ");
        scanf("%c", &escolha);
        getchar();
        escolha = paraMaiuscula(escolha);
        if (escolha != 'C' && escolha != 'D')
            printf("\nPor favor escolha uma das opções\n\n");
    }
    if (escolha == 'C')
        printf("Insira o codigo: ");
    else if (escolha == 'D')
        printf("Insira o CPF/CNPJ: ");
    return escolha;
}

char paraMaiuscula(char c)
{
    if (c >= 97 && c <= 122)
        c -= 32;
    return c;
}

//TODO:
void carregaClientes()
{
    int i = 0;
    while (cliente[i].nome[0] != 0)
    {
        i++;
    }
    clientes_registrados = i;
}
