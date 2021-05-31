#include <stdio.h>
#include <string.h>

#include "clientes.h"
#include "menus.h"
#include "contas.h"
#include "transacoes.h"

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
                }
                else if (escolha == 'L')
                {
                    listaClientes();
                }
                else if (escolha == 'B')
                {
                    escolha = imprimeMenuBusca();
                    printf("Insira o Termo de busca: ");
                    char string[100];
                    scanf("%s", &string);
                    getchar();
                    int aux = buscaClientes(escolha, string);
                    if (aux == -1)
                        printf("\nNenhum cliente foi encontrado.\n\n");
                    else
                        imprimeCliente(cliente[aux]);
                }
                else if (escolha == 'A')
                {
                    escolha = imprimeMenuEscolhaCodOuCPF_CNPJ();
                    char string[15];
                    scanf("%s", &string);
                    getchar();
                    int aux = atualizaCliente(buscaClientes(escolha, string));
                    if (aux == 1)
                        printf("O cliente foi atualizado com sucesso\n");
                    else if (aux == 0)
                        printf("A atualização foi cancelada\n");
                    else if (aux == -1)
                        printf("Cliente não encontrado\n");
                    else if (aux == -2)
                        printf("Ocorreu um erro durante a atualização do cliente\n");
                }
                else if (escolha == 'E')
                {
                    escolha = imprimeMenuEscolhaCodOuCPF_CNPJ();
                    char string[15];
                    scanf("%s", &string);
                    getchar();
                    int aux = excluiCliente(buscaClientes(escolha, string));
                    if (aux == 0)
                        printf("A operação de exculsão foi cancelada\n");
                    else if (aux == 1) 
                    {
                        printf("O cliente foi excluído\n");
                        clientes_registrados--;
                    }
                }
                
                // Reseta a escolha
                if (escolha != 'S')
                    escolha = '0';
            }
        }
        else if (escolha == 'T')
        {
            while (escolha != 'S')
            {
                escolha = imprimeGerenciarContas();
                if (escolha == 'R')
                {
                    listaTodasContas();
                } else if (escolha == 'C')
                {
                    cadastraConta();
                } else if (escolha == 'L')
                {
                    escolha = imprimeMenuEscolhaCodOuCPF_CNPJ();
                    char string[15];
                    scanf("%s", &string);
                    getchar();
                    int aux;
                    aux = buscaClientes(escolha, string);
                    if(aux == -1)
                    {
                        printf("\nCliente não encontrado\n\n");
                    } else
                    {
                        imprimeContas(cliente[aux]);
                    }
                } else if (escolha == 'W')
                {

                } else if (escolha == 'D')
                {

                } else if (escolha == 'T')
                {

                } else if (escolha == 'E')
                {

                }

                // Reseta a escolha
                if (escolha != 'S')
                    escolha = '0';
            }
        }
        escolha = imprimeBemVindo();
    }
}

// Essa função pede os dados do cliente cria um CLIENTE com esses dados e retorna esse cliente
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

// Essa função lista todos os clientes cadastrados
void listaClientes()
{
    // TODO
    //organizaClientes(cliente);
    for (int i = 0; i < clientes_registrados; i++)
    {
        // Valores obtidos com o fgets() ficam com o ENTER final
        printf("----- CLIENTE %d -----\n"
               "Nome: %s"
               "CPF/CNPJ: %s"
               "Codigo: %s\n"
               "Telefone: %s"
               "Endereço: %s"
               "---------------------\n",
               i + 1, cliente[i].nome, cliente[i].CPF_CNPJ, cliente[i].codigo, cliente[i].telefone, cliente[i].endereco);
    }
}

// Essa função recebe um char, que define em qual variável do cliente vai ocorrer a busca, e uma string, que é o que vai ser buscado
// Se a string recebida for encontrada em algum dos clientes do array, o ídice desse cliente é retornado
// Se a string não for necontrada em nenhum cliente -1 é retornado
int buscaClientes(char opcao, char string[])
{
    for (int i = 0; i < clientes_registrados; i++)
    {
        switch (opcao)
        {
        case 'N':
            if (strstr(cliente[i].nome, string) != NULL)
                return i;
            break;

        case 'C':
            if (strstr(cliente[i].codigo, string) != NULL)
                return i;
            break;

        case 'D':
            if (strstr(cliente[i].CPF_CNPJ, string) != NULL)
                return i;
            break;
        }
    }
    return -1;
}

// Essa função recebe o índice do cliente que deve ser atualizado
// Ela pede uma confirmação para a atualização do cliente
// Ela chama a cadastraCliente para retornar um novo cliente que substitui o cliente do índice recebido
// Se o índice recebido for inválido ela retrona -1
// Se o pedido de confirmação for negado ela retorna 0
// Se o cliente for atualizado ela retorna 1
int atualizaCliente(int indice)
{
    if (indice < 0 || indice >= clientes_registrados)
        return -1;
    char escolha = '0';
    printf("São esses o nome e CPF/CNPJ do cliente que vc deseja atualizar?(S/N)\n"
           " - %s"
           " - %s",
           cliente[indice].nome, cliente[indice].CPF_CNPJ);
    while (escolha != 'N' && escolha != 'S')
    {
        scanf("%c", &escolha);
        getchar();
        escolha = paraMaiuscula(escolha);
        switch (escolha)
        {
        case 'N':
            return 0;
            break;
        case 'S':
            cliente[indice] = cadastraCliente();
            return 1;
            break;
        }
    }
    //TODO: lembrar de colocar alguma verificação se o cliente realmente foi cadastrado
}

// Essa função recebe o índice do cliente que deve ser excluído
// Ela pede uma confirmação para a exclusão do cliente
// Ela remove aquele cliente do array passando todos os clientes que estão em posições depois dele para uma posição anterior
// e remove o último cliente do array
// Se o pedido de confirmação for negado ela retorna 0
// Se o cliente for excluído ela retorna 1
// É importante lembrar de reduzir em 1 a var clientes_registrados após o uso dessa função
int excluiCliente(int indice)
{
    char escolha = '0';
    printf("Esse é o cliente a ser excluído?(S/N)\n");
    imprimeCliente(cliente[indice]);
    while (escolha != 'S')
    {
        scanf("%c", &escolha);
        getchar();
        escolha = paraMaiuscula(escolha);
        if (escolha == 'N')
            return 0;
    }
    for (int i = indice; i < clientes_registrados; i++)
    {
        cliente[i] = cliente[i+1];
    }
    // - Essa parte não é necessária pois o número de clientes registrados deve ser redizido logo após o uso dessa função
    // Para remover o último cliente do array, um cliente vazio auxiliar é criado e o ultimo cliente recebe o valor dele
    //CLIENTE aux; 
    //cliente[clientes_registrados - 1] = aux;
    return 1;
}

// Essa função recebe um cliente e imprime os dados desse cliente
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

// Imprime o Menu "Bem Vindo"
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

// Imprime o Menu "Gerenciar Clientes"
// Retorna o char relativo a alguma das opções do Menu
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

// Imprime o Menu "Busca"
// Retorna o char relativo a alguma das opções do Menu
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

// Imprime o Menu "Atualização/Exclusão"
// Retorna o char relativo a alguma das opções do Menu
char imprimeMenuEscolhaCodOuCPF_CNPJ()
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

// Imprime o Menu "Gerenciar Contas"
// Retorna o char relativo a alguma das opções do Menu
char imprimeGerenciarContas()
{
    char escolha = '0';
    while (escolha != 'R' && escolha != 'C' && escolha != 'L' && escolha != 'W' && escolha != 'D' && escolha != 'T' && escolha != 'E' && escolha != 'S')
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
        if (escolha != 'R' && escolha != 'C' && escolha != 'L' && escolha != 'W' && escolha != 'D' && escolha != 'T' && escolha != 'E' && escolha != 'S')
            printf("\nPor favor escolha uma das opções\n\n");
    }
    return escolha;
}

// Essa função recebe um char
// Se o char recebido for uma letra minúscula, ela retorna esse char maiúsculo
// Se não uma letra minúscula, o próprio char recebido é retornado
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


/* -- CONTAS -- */

void cadastraConta()
{
    char escolha;
    char string[15];
    int indexCliente;
    int aux = 0;
    escolha = imprimeMenuEscolhaCodOuCPF_CNPJ();
    scanf("%s", &string);
    getchar();
    indexCliente = buscaClientes(escolha, string);
    if(indexCliente == -1)
    {
        printf("Cliente não existente");
        return;
    }
    
    // Confere quantas contas o cliente possui
    if(cliente[indexCliente].contas_registradas == 0)
    {
        aux = 0;
    } else if(cliente[indexCliente].contas_registradas == 1)
    {
        aux = 1;
    } else if(cliente[indexCliente].contas_registradas == 2)
    {
        printf("\nO cliente já possui o máximo de contas cadastradas\n\n");
        return;
    }

    //TODO: deletar depois
    printf("Cadastrando na 'conta[%d]'\n", aux);
    printf("Insira a agência: ");
    scanf("%d", &cliente[indexCliente].conta[aux].agencia);
    while(getchar() != '\n');

    //cliente[indexCliente].conta[aux].agencia = 20;

    printf("Insira o número da conta: ");
    scanf("%d", &cliente[indexCliente].conta[aux].numeroConta);
    while(getchar() != '\n');

    //cliente[indexCliente].conta[aux].numeroConta = 200;

    cliente[indexCliente].conta[aux].saldo = 0;

    cliente[indexCliente].contas_registradas++;
    printf("Conta cadastrada");
}

// Lista todas as contas
void listaTodasContas()
{
    for(int i = 0; i < clientes_registrados; i++)
    {
        imprimeContas(cliente[i]);
    }
}

// Recebe um cliente e imprime as contas desse cliente
void imprimeContas(CLIENTE C)
{
    imprimeCliente(C);
    for(int i = 0; i < C.contas_registradas; i++)
    {
        printf("Agencia: %d\n", C.conta[i].agencia);
        printf("Numero da conta: %d\n", C.conta[i].numeroConta);
        printf("Saldo: %lf\n", C.conta[i].saldo);
    }
}

