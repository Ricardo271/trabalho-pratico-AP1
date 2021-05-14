typedef struct _CLIENTE
{
    int codigo;
    char nome[50];
    char CPF_CNPJ[12];
    char telefone[14]; // +55 62 91234-1234
    char endereco[100];
} CLIENTE;

void cadastraCliente(CLIENTE C);