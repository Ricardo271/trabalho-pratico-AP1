typedef struct _CLIENTE
{
    char codigo[11];
    char nome[50];
    char CPF_CNPJ[20];
    char telefone[20]; // +55 62 91234-1234
    char endereco[100];
} CLIENTE;

CLIENTE cadastraCliente(char codigo[], char nome[], char CPF_CNPJ[], char telefone[], char endereco[]);

void listaClientes(CLIENTE C[]);

void organizaClientes(CLIENTE C[]);