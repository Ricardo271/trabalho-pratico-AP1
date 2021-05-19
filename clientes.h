typedef struct _CLIENTE
{
    char codigo[11];
    char nome[50];
    char CPF_CNPJ[20];
    char telefone[20]; // +55 62 91234-1234
    char endereco[100];
} CLIENTE;

CLIENTE cadastraCliente();

void organizaClientes(CLIENTE C[]);

void listaClientes(CLIENTE C[]);

int buscaClientes(CLIENTE C[], char opcao, char string[]);

int atualizaCliente(int indice);

void imprimeCliente();