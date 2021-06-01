#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "clientes.h"
#include "menus.h"
#include "contas.h"
#include "transacoes.h"

#define SIZE 100

CLIENTE cliente[SIZE];
int clientes_registrados = 0;

TRANSACAO *transacao;
int transacoes_realizadas = 0;

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
                    cliente[clientes_registrados] = cadastraCliente();
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
                    int agencia = 0;
                    int numeroConta = 0;
                    int indexCliente = 0;
                    int indexConta = 0;
                    printf("Insira a agencia: ");
                    scanf("%d", &agencia);
                    getchar();
                    printf("Insira o número da conta: ");
                    scanf("%d", &numeroConta);
                    getchar();
                    buscaConta(agencia, numeroConta, &indexCliente, &indexConta);
                    if(indexCliente == -1)
                    {
                        printf("Cliente não encontrado\n");
                    } else{
                        double valor;
                        printf("Conta: %i-%i\n", cliente[indexCliente].conta[indexConta].agencia, cliente[indexCliente].conta[indexConta].numeroConta);
                        printf("Saldo atual: %.2lf\n", cliente[indexCliente].conta[indexConta].saldo);
                        printf("\nInsira o valor a ser sacado: ");
                        scanf("%lf", &valor);
                        getchar();
                        while(getchar() != '\n');

                        realizarSaque(&cliente[indexCliente].conta[indexConta], valor);
                    }
                } else if (escolha == 'D')
                {
                    int agencia = 0;
                    int numeroConta = 0;
                    int indexCliente = -1;
                    int indexConta = -1;
                    printf("Insira a agencia: ");
                    scanf("%d", &agencia);
                    getchar();
                    printf("Insira o número da conta: ");
                    scanf("%d", &numeroConta);
                    getchar();
                    buscaConta(agencia, numeroConta, &indexCliente, &indexConta);
                    if(indexCliente == -1)
                    {
                        printf("Cliente não encontrado\n");
                    } else 
                    {
                        double valor = 0;
                        printf("Conta: %i-%i\n", cliente[indexCliente].conta[indexConta].agencia, cliente[indexCliente].conta[indexConta].numeroConta);
                        printf("Saldo atual: %.2lf\n", cliente[indexCliente].conta[indexConta].saldo);
                        printf("\nInsira o valor a ser depositado: ");
                        scanf("%lf", &valor);
                        //getchar();
                        while(getchar() != '\n');

                        realizaDeposito(&cliente[indexCliente].conta[indexConta], valor);
                    }
                } else if (escolha == 'T')
                {
                    int indexClienteOrigem = -1;
                    int indexContaOrigem = -1;
                    int indexClienteDestino = -1;
                    int indexContaDestino = -1;
                    int agencia = 0;
                    int numeroConta = 0;
                    printf(" Conta Origem \n");
                    printf("Insira a agencia: ");
                    scanf("%d", &agencia);
                    getchar();
                    printf("Insira o numero da conta: ");
                    scanf("%d", &numeroConta);
                    getchar();
                    buscaConta(agencia, numeroConta, &indexClienteOrigem, &indexContaOrigem);
                    if(indexClienteOrigem == -1)
                    {
                        printf("Conta de origem não encontrada\n");
                    } else
                    {
                        // O cliente da conta origem existe, portanto seus dados são imprimidos
                        imprimeCliente(cliente[indexClienteOrigem]);
                        imprimeUmaConta(cliente[indexClienteOrigem].conta[indexContaOrigem]);

                        printf(" Conta Destino \n");
                        printf("Insira a agencia: ");
                        scanf("%d", &agencia);
                        getchar();
                        printf("Insira o numero da conta: ");
                        scanf("%d", &numeroConta);
                        getchar();
                        buscaConta(agencia, numeroConta, &indexClienteDestino, &indexContaDestino);
                        if(indexClienteDestino == -1)
                        {
                            printf("Conta de destino não encontrada\n");
                        } else
                        {
                            // O cliente da conta destino exite, portanto seus dados são imprimidos
                            imprimeCliente(cliente[indexClienteDestino]);
                            imprimeUmaConta(cliente[indexClienteDestino].conta[indexContaDestino]);

                            realizaTransferencia(&cliente[indexClienteOrigem].conta[indexContaOrigem], &cliente[indexClienteDestino].conta[indexContaDestino]);
                        }
                    }
                } else if (escolha == 'E')
                {
                    int agencia = 0;
                    int numeroConta = 0;
                    int indexCliente = -1;
                    int indexConta = -1;
                    printf("Insira a agencia: ");
                    scanf("%d", &agencia);
                    getchar();
                    printf("Insira o número da conta: ");
                    scanf("%d", &numeroConta);
                    getchar();
                    buscaConta(agencia, numeroConta, &indexCliente, &indexConta);
                    if(indexConta == -1)
                    {
                        printf("Conta não encontrada\n");
                    } else
                    {
                        imprimeCliente(cliente[indexCliente]);
                        imprimeUmaConta(cliente[indexCliente].conta[indexConta]);
                        exibeExtrato(cliente[indexCliente].conta[indexConta].codConta);
                    }
                }

                // Reseta a escolha
                if (escolha != 'S')
                    escolha = '0';
            }
        }
        escolha = imprimeBemVindo();
    }
}

/* -- CLIENTES -- */

// Essa função pede os dados do cliente cria um CLIENTE com esses dados e retorna esse cliente
CLIENTE cadastraCliente()
{
    CLIENTE C;

    if(clientes_registrados >= 100)
    {
        printf("Numero maximo de clientes atingido\n");
        return C;
    }

    char nome[100];
    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);

    char CPF_CNPJ[20];
    printf("CPF/CNPJ: ");
    fgets(CPF_CNPJ, sizeof(CPF_CNPJ), stdin);

    char codigo[5];
    printf("Codigo: ");
    fgets(codigo, sizeof(codigo), stdin); 
    getchar();

    for(int i = 0; i < clientes_registrados; i++)
    {
        if(!strcmp(CPF_CNPJ, cliente[i].CPF_CNPJ))
        {
            printf("CPF/CNPJ inválido\n");
            return C;
        }
        if(codigo == cliente[i].codigo)
        {
            printf("Codigo invalido\n");
            return C;
        }
    }

    char telefone[20];
    printf("Telefone: ");
    fgets(telefone, sizeof(telefone), stdin);

    char endereco[100];
    printf("Endereço: ");
    fgets(endereco, sizeof(endereco), stdin);

    strcpy(C.codigo, codigo);
    strcpy(C.nome, nome);
    strcpy(C.CPF_CNPJ, CPF_CNPJ);
    strcpy(C.telefone, telefone);
    strcpy(C.endereco, endereco);
    C.contas_registradas = 0;

    clientes_registrados++;
    return C;
}

// Essa função organiza os elementos do array de cliente por ordem alfabética, usando um bubble sort
void organizaClientes()
{
    CLIENTE temp;
    bool trocou = true;

    while(trocou)
    {
        trocou = false;
        for(int i = 0; i < clientes_registrados - 1; i++)
        {
            if(strcmp(cliente[i+1].nome, cliente[i].nome) < 0)
            {
                temp = cliente[i];
                cliente[i] = cliente[i+1];
                cliente[i+1] = temp;
                trocou = true;
            }
        }
    }
}

// Essa função lista todos os clientes cadastrados
void listaClientes()
{
    organizaClientes();

    if(clientes_registrados == 0)
    {
        printf("Nenhum cliente cadastrado\n");
        return;
    }

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
    // - Essa parte não é necessária pois o número de clientes registrados deve ser reduzido logo após o uso dessa função
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

/* -- MENUS -- */

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
        printf("Cliente não existente\n");
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
    printf("Cadastrando na 'conta[%d]' do cliente %s\n", aux, cliente[indexCliente].nome);

    printf("Insira a agência: ");
    scanf("%d", &cliente[indexCliente].conta[aux].agencia);
    //getchar();
    while(getchar() != '\n');

    printf("Insira o número da conta: ");
    scanf("%d", &cliente[indexCliente].conta[aux].numeroConta);
    //getchar()
    while(getchar() != '\n');

    cliente[indexCliente].conta[aux].codConta = (cliente[indexCliente].conta[aux].agencia * 1000) + cliente[indexCliente].conta[aux].numeroConta;

    cliente[indexCliente].conta[aux].saldo = 0;

    cliente[indexCliente].contas_registradas++;
    printf("Conta cadastrada\n");
}

void organizaContas(CLIENTE *C)
{
    CONTA temp;
    bool trocou = true;

    while(trocou)
    {
        trocou = false;
        for(int j = 1; j < C->contas_registradas; j++)
        {
            if(C->conta[j].saldo > C->conta[j-1].saldo)
            {
                temp = C->conta[j];
                C->conta[j] = C->conta[j-1];
                C->conta[j-1] = temp;
                trocou = true; 
            }
        }
    }
}

// Lista todas as contas
void listaTodasContas()
{
    for(int i = 0; i < clientes_registrados; i++)
    {
        organizaContas(&cliente[i]);
    }
    for(int i = 0; i < clientes_registrados; i++)
    {
        imprimeContas(cliente[i]);
    }
}

// Recebe um cliente e imprime as contas desse cliente
void imprimeContas(CLIENTE C)
{
    if(C.contas_registradas == 0)
    {
        printf("Nenhuma conta encontrada\n");
        printf("---------------------------\n");
        return;
    }
        imprimeCliente(C);
    for(int i = 0; i < C.contas_registradas; i++)
    {
        imprimeUmaConta(C.conta[i]);
    }
}

// Imprime uma conta específica
void imprimeUmaConta(CONTA CNT)
{
    printf("Agencia: %d\n", CNT.agencia);
    printf("Numero da conta: %d\n", CNT.numeroConta);
    printf("Codigo da conta: %d\n", CNT.codConta);
    printf("Saldo: %.2lf\n", CNT.saldo);
    printf("-------------------------------\n");
}

void buscaConta(int agencia, int numeroConta, int *indexCliente, int *indexConta)
{
    for(int i = 0; i < clientes_registrados; i++)
    {
        for(int j = 0; j < cliente[i].contas_registradas; j++)
        {
            if(cliente[i].conta[j].agencia == agencia && cliente[i].conta[j].numeroConta == numeroConta)
            {
                *indexCliente = i;
                *indexConta = j;
                return;
            }
        }
    }
    *indexCliente = -1;
}

void realizarSaque(CONTA *conta, double valor)
{
    if(valor <= 0 || conta->saldo < valor)
    {
        printf("Valor inválido ou saldo insuficiente\n");
        return;
    }

    conta->saldo -= valor;
    char descricao[100];
    printf("Insira uma descrição para a sua transacao: ");
    fgets(descricao, sizeof(descricao), stdin);
    criaTransacao(conta->codConta, 'D', valor, descricao);
    printf("Saque realizado\n");
    printf("Saldo final: %.2lf\n", conta->saldo);

}

void realizaDeposito(CONTA *conta, double valor)
{
    if(valor <= 0)
    {
        printf("Valor inválido\n");
        return;
    }

    conta->saldo += valor;
    char descricao[100];
    printf("Insira uma descrição para a sua transacao: ");
    fgets(descricao, sizeof(descricao), stdin);
    criaTransacao(conta->codConta, 'C', valor, descricao);
    printf("Depósito realizado\n");
    printf("Saldo final: %.2lf\n", conta->saldo);
}

void realizaTransferencia(CONTA *contaOrigem, CONTA *contaDestino)
{
    double valor;
    printf("Realizando Transferencia da Conta %d-%d para a conta %d-%d\n", contaOrigem->agencia, contaOrigem->numeroConta, contaDestino->agencia, contaDestino->numeroConta);
    printf("Insira o valor a ser transferido: ");
    scanf("%lf", &valor);
    while(getchar() != '\n');

    if(valor <= 0)
    {
        printf("O valor a ser transferido não pode ser nulo ou negativo\n");
        return;
    } else if(valor > contaOrigem->saldo)
    {
        printf("A conta de origem não tem fundos o suficiente\n");
        return;
    }

    contaOrigem->saldo -= valor;
    criaTransacao(contaOrigem->codConta, 'D', valor, "Descricao conta origem");
    contaDestino->saldo += valor;
    criaTransacao(contaDestino->codConta, 'C', valor, "Descricao conta destino");
    printf("Transferencia realizada\n");
}

void criaTransacao(int codConta, char operacao, double valor, char descricao[])
{
    if(transacoes_realizadas == 0)
    {
        transacao = (TRANSACAO *) malloc(sizeof(TRANSACAO));
    } else
    {
        transacao = (TRANSACAO *) realloc(transacao, sizeof(TRANSACAO) * (transacoes_realizadas + 1));
    }
    strcpy(transacao[transacoes_realizadas].descricao, descricao);

    if(operacao == 'C')
    {
        transacao[transacoes_realizadas].credito = true;
        transacao[transacoes_realizadas].debito = false;
    } else 
    {
        transacao[transacoes_realizadas].credito = false;
        transacao[transacoes_realizadas].debito = true;
    }

    transacao[transacoes_realizadas].codConta = codConta;
    transacao[transacoes_realizadas].valor = valor;

    time_t agora;
    transacao[transacoes_realizadas].data = localtime(&agora);
    transacoes_realizadas++;
}

//TODO: período de dias
void imprimeTransacao(TRANSACAO T)
{
    if(T.credito)
    {
        printf("Tipo de operacao: CREDITO\n");
    } else
    {
        printf("Tipo de operacao: DEBITO\n");
    }
    printf("Descricao: %s\n", T.descricao);
    printf("Valor: %lf\n", T.valor);
    printf("Data: %d/%d/%d\n", T.data->tm_mday + 1, T.data->tm_mon - 1, T.data->tm_year - 1900);
}

void exibeExtrato(int codigo)
{
    for(int i = 0; i < transacoes_realizadas; i++)
    {
        if(transacao[i].codConta == codigo)
        {
            imprimeTransacao(transacao[i]);
        }
    }
}
