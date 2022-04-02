#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdbool.h>
#include <time.h>


#define clear printf("\e[1;1H\e[2J"); // "Limpa" o terminal

#define SIZE 100

/* -- Formatos de salvamento -- */
const char *FORMATO_ENTRADA_CLIENTES = "{\"cod\": \"%[^\"]\", \"nome\": \"%[^\"]\", \"CPF_CNPJ\": \"%[^\"]\", \"tele\": \"%[^\"]\", \"end\": \"%[^\"]\", \"contas_registradas\": \"%d\", \"conta_1\": \"%d\", \"conta_2\": \"%d\"}";
const char *FORMATO_SAIDA_CLIENTES   = "{\"cod\": \"%s\", \"nome\": \"%s\", \"CPF_CNPJ\": \"%s\", \"tele\": \"%s\", \"end\": \"%s\", \"contas_registradas\": \"%d\", \"conta_1\": \"%d\", \"conta_2\": \"%d\"}\n";

const char *FORMATO_ENTRADA_CONTAS = "{\"cod\": \"%d\", \"agencia\": \"%d\", \"numero\": \"%d\", \"saldo\": \"%lf\"}";
const char *FORMATO_SAIDA_CONTAS   = "{\"cod\": \"%d\", \"agencia\": \"%d\", \"numero\": \"%d\", \"saldo\": \"%lf\"}\n";

const char *FORMATO_ENTRADA_TRANSACOES = "{\"cod\": \"%d\", \"debito\": \"%d\", \"credito\": \"%d\", \"valor\": \"%lf\", \"dia\": \"%d\", \"mes\": \"%d\", \"ano\": \"%d\", \"desc\": \"%[^\"]\"}";
const char *FORMATO_SAIDA_TRANSACOES   = "{\"cod\": \"%d\", \"debito\": \"%d\", \"credito\": \"%d\", \"valor\": \"%lf\", \"dia\": \"%d\", \"mes\": \"%d\", \"ano\": \"%d\", \"desc\": \"%s\"}\n";


/* -- Prototipos -- */
bool eInteiro(double n);
void leClientes(char arquivo[]);
void escreveClientes(char arquivo[]);
void leContas(char arquivo[]);
void escreveContas(char arquivo[]);
void leTransacoes(char arquivo[]);
void escreveTransacoes(char arquivo[]);


/* -- Contas -- */
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


/* -- Clientes -- */
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


/* -- Menus -- */
char imprimeBemVindo();
char imprimeGerenciarClientes();
char imprimeGerenciarContas();
char imprimeMenuBusca();
char imprimeMenuEscolhaCodOuCPF_CNPJ();
char paraMaiuscula(char c);


/* -- Transacoes -- */
#define descricao_size 101

typedef struct tm tm;

typedef struct _TRANSACAO
{
    int codConta;
    bool debito;
    bool credito;
    double valor;
    tm *data;
    char descricao[descricao_size];
} TRANSACAO;

void criaTransacao(int codConta, char operacao, double valor, char descrico[]);
void imprimeTransacao(TRANSACAO T);
void exibeExtrato(int codigo);


CLIENTE cliente[SIZE];
int clientes_registrados = 0;

TRANSACAO *transacao;
int transacoes_realizadas = 0;

int main()
{
    leClientes("Clientes.txt");
    leContas("Contas.txt");

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
                    scanf("%s", string);
                    while(getchar() != '\n');
                    int aux = buscaClientes(escolha, string);
                    if (aux == -1)
                        printf("\nNenhum cliente foi encontrado com esses parâmetros.\n\n");
                    else
                        imprimeCliente(cliente[aux]);
                }
                else if (escolha == 'A')
                {
                    escolha = imprimeMenuEscolhaCodOuCPF_CNPJ();
                    char string[15];
                    scanf("%s", string);
                    while(getchar() != '\n');
                    int aux = atualizaCliente(buscaClientes(escolha, string));
                    if (aux == 1)
                        printf("O cliente foi atualizado com sucesso\n");
                    else if (aux == 0)
                        printf("A atualização foi cancelada\n");
                    else if (aux == -1)
                        printf("Cliente não encontrado\n");
                }
                else if (escolha == 'E')
                {
                    escolha = imprimeMenuEscolhaCodOuCPF_CNPJ();
                    char string[15];
                    scanf("%s", string);
                    while(getchar() != '\n');
                    int aux = excluiCliente(buscaClientes(escolha, string));
                    if (aux == 0)
                        printf("A operação de exclusão foi cancelada\n");
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
                    scanf("%s", string);
                    while(getchar() != '\n');
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
                    while(getchar() != '\n');
                    printf("Insira o número da conta: ");
                    scanf("%d", &numeroConta);
                    while(getchar() != '\n');
                    buscaConta(agencia, numeroConta, &indexCliente, &indexConta);
                    if(indexCliente == -1)
                    {
                        printf("Cliente não encontrado\n");
                    } else{
                        double valor;
                        imprimeCliente(cliente[indexCliente]);
                        printf("Conta: %i-%i\n", cliente[indexCliente].conta[indexConta].agencia, cliente[indexCliente].conta[indexConta].numeroConta);
                        printf("Saldo atual: %.2lf\n", cliente[indexCliente].conta[indexConta].saldo);
                        printf("\nInsira o valor a ser sacado: ");
                        scanf("%lf", &valor);
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
                    while(getchar() != '\n');
                    printf("Insira o número da conta: ");
                    scanf("%d", &numeroConta);
                    while(getchar() != '\n');
                    buscaConta(agencia, numeroConta, &indexCliente, &indexConta);
                    if(indexCliente == -1)
                    {
                        printf("Cliente não encontrado\n");
                    } else 
                    {
                        double valor = 0;
                        imprimeCliente(cliente[indexCliente]);
                        printf("Conta: %i-%i\n", cliente[indexCliente].conta[indexConta].agencia, cliente[indexCliente].conta[indexConta].numeroConta);
                        printf("Saldo atual: %.2lf\n", cliente[indexCliente].conta[indexConta].saldo);
                        printf("\nInsira o valor a ser depositado: ");
                        scanf("%lf", &valor);
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
                    while(getchar() != '\n');
                    printf("Insira o numero da conta: ");
                    scanf("%d", &numeroConta);
                    while(getchar() != '\n');
                    buscaConta(agencia, numeroConta, &indexClienteOrigem, &indexContaOrigem);
                    if(indexClienteOrigem == -1)
                    {
                        printf("Conta de origem não encontrada\n");
                    } else
                    {
                        // O cliente da conta origem existe, portanto seus dados são imprimidos
                        imprimeCliente(cliente[indexClienteOrigem]);
                        printf("Conta: %i-%i\n", cliente[indexClienteOrigem].conta[indexContaOrigem].agencia, cliente[indexClienteOrigem].conta[indexContaOrigem].numeroConta);
                        printf("Saldo atual: %.2lf\n", cliente[indexClienteOrigem].conta[indexContaOrigem].saldo);

                        printf(" Conta Destino \n");
                        printf("Insira a agencia: ");
                        scanf("%d", &agencia);
                        while(getchar() != '\n');
                        printf("Insira o numero da conta: ");
                        scanf("%d", &numeroConta);
                        while(getchar() != '\n');
                        buscaConta(agencia, numeroConta, &indexClienteDestino, &indexContaDestino);
                        if(indexClienteDestino == -1)
                        {
                            printf("Conta de destino não encontrada\n");
                        } else
                        {
                            // O cliente da conta destino exite, portanto seus dados são imprimidos
                            imprimeCliente(cliente[indexClienteDestino]);
                            printf("Conta: %i-%i\n", cliente[indexClienteDestino].conta[indexContaDestino].agencia, cliente[indexClienteDestino].conta[indexContaDestino].numeroConta);
                            printf("Saldo atual: %.2lf\n", cliente[indexClienteDestino].conta[indexContaDestino].saldo);

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
                    while(getchar() != '\n');
                    printf("Insira o número da conta: ");
                    scanf("%d", &numeroConta);
                    while(getchar() != '\n');
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

    if (clientes_registrados > 0)
    {
        organizaClientes();
    }
    escreveClientes("Clientes.txt");
    escreveContas("Contas.txt");
    escreveTransacoes("Transacoes.txt");
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

    char nome[nome_size];
    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    char CPF_CNPJ[CPF_CNPJ_size];
    printf("CPF/CNPJ: ");
    fgets(CPF_CNPJ, sizeof(CPF_CNPJ), stdin);
    CPF_CNPJ[strcspn(CPF_CNPJ, "\n")] = 0;

    for(int i = 0; i < clientes_registrados; i++)
    {
        if(!strcmp(CPF_CNPJ, cliente[i].CPF_CNPJ))
        {
            printf("Cliente já cadastrado\n");
            return C;
        }
    }

    char codigo[codigo_size];
    printf("Codigo: ");
    fgets(codigo, sizeof(codigo), stdin); 
    codigo[strcspn(codigo, "\n")] = 0;

    for(int i = 0; i < clientes_registrados; i++)
    {

        if(!strcmp(codigo, cliente[i].codigo))
        {
            printf("Cliente já cadastrado\n");
            return C;
        }
    }

    char telefone[telefone_size];
    printf("Telefone: ");
    fgets(telefone, sizeof(telefone), stdin);
    telefone[strcspn(telefone, "\n")] = 0;

    char endereco[endereco_size];
    printf("Endereço: ");
    fgets(endereco, sizeof(endereco), stdin);
    endereco[strcspn(endereco, "\n")] = 0;

    strcpy(C.codigo, codigo);
    strcpy(C.nome, nome);
    strcpy(C.CPF_CNPJ, CPF_CNPJ);
    strcpy(C.telefone, telefone);
    strcpy(C.endereco, endereco);
    C.contas_registradas = 0;

    C.conta[0].codConta = 0;
    C.conta[1].codConta = 0;

    clientes_registrados++;
    printf("\nCliente Cadastrado\n\n");
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

    if(clientes_registrados <= 0)
    {
        printf("Nenhum cliente cadastrado\n");
        return;
    }

    for (int i = 0; i < clientes_registrados; i++)
    {
        printf("----- CLIENTE %d -----\n", i+1);
        imprimeCliente(cliente[i]);
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
           " - %s\n"
           "->",
           cliente[indice].nome, cliente[indice].CPF_CNPJ);
    while (escolha != 'N' && escolha != 'S')
    {
        scanf("%c", &escolha);
        while(getchar() != '\n');
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
    printf("Esse é o cliente a ser excluído?(S/N)\n ");
    imprimeCliente(cliente[indice]);
    while (escolha != 'S')
    {
        printf("-> ");
        scanf("%c", &escolha);
        while(getchar() != '\n');
        escolha = paraMaiuscula(escolha);
        if (escolha == 'N')
            return 0;
    }
    for (int i = indice; i < clientes_registrados; i++)
    {
        cliente[i] = cliente[i+1];
    }
    return 1;
}

// Essa função recebe um cliente e imprime os dados desse cliente
void imprimeCliente(CLIENTE C)
{
    printf("----------------------\n"
           "Nome: %s\n"
           "CPF/CNPJ: %s\n"
           "Codigo: %s\n"
           "Telefone: %s\n"
           "Endereço: %s\n"
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
        while(getchar() != '\n');
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
        while(getchar() != '\n');
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
               "N - Nome\n"
               "C - Codigo\n"
               "D - CPF/CNPJ\n"
               "-> ");
        scanf("%c", &escolha);
        while(getchar() != '\n');
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
               "C - Codigo\n"
               "D - CPF/CNPJ\n"
               "-> ");
        scanf("%c", &escolha);
        while(getchar() != '\n');
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
               "R - Listagem de todas as contas cadastradas\n"
               "C - Cadastrar uma conta para um cliente\n"
               "L - Listar todas as contas de um cliente\n"
               "W - Realizar um saque em uma conta\n"
               "D - Realizar um depósito em uma conta\n"
               "T - Realizar transferência entre contas\n"
               "E - Exibir extrato de uma conta\n"
               "S - Sair\n"
               "-> ");
        scanf("%c", &escolha);
        while(getchar() != '\n');
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
    scanf("%s", string);
    while(getchar() != '\n');
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

    printf("Cadastrando na 'conta[%d]' do cliente %s\n", aux, cliente[indexCliente].nome);

    printf("Insira a agência: ");
    scanf("%d", &cliente[indexCliente].conta[aux].agencia);
    while(getchar() != '\n');

    printf("Insira o número da conta: ");
    scanf("%d", &cliente[indexCliente].conta[aux].numeroConta);
    while(getchar() != '\n');

    cliente[indexCliente].conta[aux].codConta = (cliente[indexCliente].conta[aux].agencia * 1000) + cliente[indexCliente].conta[aux].numeroConta;

    cliente[indexCliente].conta[aux].saldo = 0;

    cliente[indexCliente].contas_registradas++;
    printf("Conta cadastrada\n");
}

// Essa função organiza as contas
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
        printf("Nenhuma conta cadastrada\n");
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

// Essa função recebe a agencia e o numeroConta de uma conta e modifica os dois ponteiros indexCliente e indexConta de onde essa conta foi encontrada
// Caso nehuma conta seja encontrada o index do cliente é modificado para -1 
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

// Essa função checa se um número é inteiro
bool eInteiro(double n)
{
    int truncado = (int)n;
    return(n == truncado);
}

void realizarSaque(CONTA *conta, double valor)
{
    if(valor <= 0)
    {
        printf("Valor inválido\nValores nulos ou negativos não são permitidos\n");
        return;
    }
    if(conta->saldo < valor)
    {
        printf("Saldo insuficiente\n");
        return;
    }
    if(!eInteiro(valor))
    {
        printf("Valor inválido\nSó são aceitos valores inteiros\n");
        return;
    }

    int notas = (int)valor;

    int aux = notas;

    aux = notas;
    aux = (aux % 200);
    aux = (aux % 100);
    aux = (aux % 50);
    aux = (aux % 20);
    aux = (aux % 10);
    aux = (aux % 5);
    aux = (aux % 2);

    if(aux > 0)
    {
        printf("Valor inválido\nSó são aceitos valores que podem ser distribuídos entre as seguintes notas: R$ 200,00, R$ 100,00, R$ 50,00, R$ 20,00, R$ 10,00, R$ 5,00, R$ 2,00.\n");
        return;
    }

    conta->saldo -= valor;
    char descricao[descricao_size];
    printf("Insira uma descrição para a sua transacao: ");
    fgets(descricao, sizeof(descricao), stdin);
    descricao[strcspn(descricao, "\n")] = 0;
    criaTransacao(conta->codConta, 'D', valor, descricao);

    printf("Saque realizado\nForam entregues: \n");

    aux = notas;

    if(aux / 200 != 0)
        printf("%d nota(s) de R$ 200,00\n", aux / 200);
    aux = (aux % 200);

    if(aux / 100 != 0)
        printf("%d nota(s) de R$ 100,00\n", aux / 100);
    aux = (aux % 100);

    if(aux / 50 != 0)
        printf("%d nota(s) de R$ 50,00\n", aux / 50);
    aux = (aux % 50);

    if(aux / 20 != 0)
        printf("%d nota(s) de R$ 20,00\n", aux / 20);
    aux = (aux % 20);

    if(aux / 10 != 0)
        printf("%d nota(s) de R$ 10,00\n", aux / 10);
    aux = (aux % 10);

    if(aux / 5 != 0)
        printf("%d nota(s) de R$ 5,00\n", aux / 5);
    aux = (aux % 5);

    if(aux / 2 != 0)
        printf("%d nota(s) de R$ 2,00\n", aux / 2);

    
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
    char descricao[descricao_size];
    printf("Insira uma descrição para a sua transacao: ");
    fgets(descricao, sizeof(descricao), stdin);
    descricao[strcspn(descricao, "\n")] = 0;
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

    char desc[34];

    contaOrigem->saldo -= valor;
    snprintf(desc, sizeof(desc), "Transferência para conta: %d-%d", contaDestino->agencia, contaDestino->numeroConta);
    criaTransacao(contaOrigem->codConta, 'D', valor, desc);

    contaDestino->saldo += valor;
    snprintf(desc, sizeof(desc), "Transferência de conta: %d-%d", contaOrigem->agencia, contaOrigem->numeroConta);
    criaTransacao(contaDestino->codConta, 'C', valor, desc);

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

    if(transacao == NULL)
    {
        printf("Falha de alocação de memória para transacao\n");
        return;
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
    agora = time(NULL);
    transacao[transacoes_realizadas].data = localtime(&agora);
    transacoes_realizadas++;
}

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
    printf("Valor: %.2lf\n", T.valor);
    printf("Data: %d/%d/%d\n", T.data->tm_mday, T.data->tm_mon + 1, T.data->tm_year + 1900);
}

void exibeExtrato(int codigo)
{
    int qtdDias = 0;
    printf("Insira a quantidade de dias: ");
    scanf("%d", &qtdDias);
    while(getchar() != '\n');
    time_t agora;
    agora = time(NULL);
    struct tm* hoje;
    hoje = localtime(&agora);
    for(int i = 0; i < transacoes_realizadas; i++)
    {
        if(transacao[i].codConta == codigo && transacao[i].data->tm_yday > hoje->tm_yday - qtdDias)
        {
            imprimeTransacao(transacao[i]);
        }
    }
}

/* -- ARQUIVOS -- */

void leClientes(char arquivo[])
{
    FILE *fp;
    fp = fopen(arquivo, "r");
    if(fp == NULL)
    {
        printf("Ocorreu um errro durante a abertura do arquivo para leitura ou o arquivo não existe\n");
        return;
    }

    char buffer[250];
    fgets(buffer, 250, fp);

    int i = 0;
    while(!feof(fp))
    {
        CLIENTE *c = cliente + i;
        sscanf(buffer, FORMATO_ENTRADA_CLIENTES, c->codigo, c->nome, c->CPF_CNPJ, c->telefone, c->endereco, &c->contas_registradas, &c->conta[0].codConta, &c->conta[1].codConta);
        clientes_registrados++;
        i++;
        fgets(buffer, 250, fp);
    }

    fclose(fp);
}

void escreveClientes(char arquivo[])
{
    FILE *fp;
    fp = fopen(arquivo, "w");
    if(fp == NULL)
    {
        printf("Ocorreu um erro durante a abertura do arquivo para gravação\n");
        return;
    }

    for(int index = 0; index < clientes_registrados; index++)
    {
        fprintf(fp, FORMATO_SAIDA_CLIENTES, cliente[index].codigo, cliente[index].nome, cliente[index].CPF_CNPJ, cliente[index].telefone, cliente[index].endereco, cliente[index].contas_registradas, cliente[index].conta[0].codConta, cliente[index].conta[1].codConta);
    }

    fclose(fp);
}

void leContas(char arquivo[])
{   
    FILE *fp;
    fp = fopen(arquivo, "r");
    if(fp == NULL)
    {
        printf("Ocorreu um errro durante a abertura do arquivo para leitura ou o arquivo não existe\n");
        return;
    }

    char buffer[100];
    fgets(buffer, 100, fp);


    while(!feof(fp))
    {
        CONTA c;
        sscanf(buffer, FORMATO_ENTRADA_CONTAS, &c.codConta, &c.agencia, &c.numeroConta, &c.saldo);
        for(int i = 0; i < clientes_registrados; i++)
        {
            for(int j = 0; j < cliente[i].contas_registradas; j++)
            {
                if(cliente[i].conta[j].codConta == c.codConta)
                {
                    cliente[i].conta[j] = c;
                }
            }
        }
        fgets(buffer, 100, fp);
    }
    
    fclose(fp);
}

void escreveContas(char arquivo[])
{
    FILE *fp;
    fp = fopen(arquivo, "w");
    if(fp == NULL)
    {
        printf("Ocorreu um erro durante a abertura do arquivo");
        return;
    }

    for(int i = 0; i < clientes_registrados; i++)
    {
        for(int j = 0; j < cliente[i].contas_registradas; j++)
        {
            fprintf(fp, FORMATO_SAIDA_CONTAS, cliente[i].conta[j].codConta, cliente[i].conta[j].agencia, cliente[i].conta[j].numeroConta, cliente[i].conta[j].saldo);
        }
    }
     
    fclose(fp);
}

void leTransacoes(char arquivo[])
{
    FILE *fp;
    fp = fopen(arquivo, "r");
    if(fp == NULL)
    {
        printf("Ocorreu um errro durante a abertura do arquivo para leitura ou o arquivo não existe\n");
        return;
    }

    char buffer[250];
    fgets(buffer, 250, fp);

    printf("aqui\n");
    int i = 0;
    while(!feof(fp))
    {
        TRANSACAO *t = transacao + i;
        printf("aqui12\n");

        if(transacoes_realizadas == 0)
        {
            transacao = (TRANSACAO *) malloc(sizeof(TRANSACAO));
            printf("aqui13\n");
        } else
        {
            transacao = (TRANSACAO *) realloc(transacao, sizeof(TRANSACAO) * (transacoes_realizadas + 1));
            printf("aqui15\n");
        }

        if(transacao == NULL)
        {
            printf("Falha de alocação de memória para transacao\n");
            return;
        }

        printf("aqui17\n");
        sscanf(buffer, FORMATO_ENTRADA_TRANSACOES, &t->codConta, &t->debito, &t->credito, &t->valor, &t->data->tm_mday, &t->data->tm_mon, &t->data->tm_year, t->descricao);
        printf("aqui\n");
        transacoes_realizadas++;
        i++;
        fgets(buffer, 250, fp);
    }
    
    fclose(fp);
}

void escreveTransacoes(char arquivo[])
{
    FILE *fp;
    fp = fopen(arquivo, "w");
    if(fp == NULL)
    {
        printf("Ocorreu um erro durante a abertura do arquivo para gravação\n");
        return;
    }

    for(int index = 0; index < transacoes_realizadas; index++)
    {
        fprintf(fp, FORMATO_SAIDA_TRANSACOES, transacao[index].codConta, transacao[index].debito, transacao[index].credito, transacao[index].valor, transacao[index].data->tm_mday, transacao[index].data->tm_mon, transacao[index].data->tm_year, transacao[index].descricao);
    }

    fclose(fp);
}