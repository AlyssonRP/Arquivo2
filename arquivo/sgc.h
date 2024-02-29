#ifndef SGC_H
#define SGC_H


typedef struct {
    char nome[50];
    float preco;
    int quantidade;
} Produto;

typedef struct {
    char nome[50];
    char senha[50];
    int nivel_privilegio;
} Usuario;

typedef struct {
    char nome_produto[50];
    int quantidade;
} Pedido;

int autenticarAdmin();
void exibirMenu();
void adicionarProduto(Produto estoque[], int *numProdutos);
void listarProdutos(Produto estoque[], int numProdutos);
void adicionarUsuario(Usuario usuarios[], int *numUsuarios);
void excluirUsuario(Usuario usuarios[], int *numUsuarios);
void fazerPedido(Usuario usuario, Pedido pedidos[], int *numPedidos, Produto estoque[], int numProdutos);
void listarPedidos(Pedido pedidos[], int numPedidos);
void listarUsuarios(Usuario usuarios[], int numUsuarios);

#endif