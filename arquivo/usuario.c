// usuario.c
#include <stdio.h>
#include <string.h>


void fazerPedido(Usuario usuario, Pedido pedidos[], int *numPedidos, Produto estoque[], int numProdutos) {
    if (*numPedidos < MAX_PEDIDOS) {
        Pedido novoPedido;
        printf("Nome do produto a ser pedido: ");
        scanf("%s", novoPedido.nome_produto);
        printf("Quantidade desejada: ");
        scanf("%d", &novoPedido.quantidade);

        int produtoEncontrado = 0;
        int indiceProduto = -1;

        for (int i = 0; i < numProdutos; i++) {
            if (strcmp(novoPedido.nome_produto, estoque[i].nome) == 0) {
                produtoEncontrado = 1;
                indiceProduto = i;
                break;
            }
        }

        if (produtoEncontrado) {
            if (estoque[indiceProduto].quantidade >= novoPedido.quantidade) {
                pedidos[*numPedidos] = novoPedido;
                (*numPedidos)++;

                estoque[indiceProduto].quantidade -= novoPedido.quantidade;

                FILE *file = fopen("estoque.txt", "w");
                if (file) {
                    for (int i = 0; i < numProdutos; i++) {
                        fprintf(file, "%s %.2f %d\n", estoque[i].nome, estoque[i].preco, estoque[i].quantidade);
                    }
                    fclose(file);
                } else {
                    printf("Erro ao abrir o arquivo de estoque.\n");
                }

                printf("Pedido realizado com sucesso!\n");
            } else {
                printf("Quantidade insuficiente em estoque.\n");
            }
        } else {
            printf("Produto não encontrado no estoque.\n");
        }
    } else {
        printf("Limite de pedidos atingido.\n");
    }
}

void listarPedidos(Pedido pedidos[], int numPedidos) {
    if (numPedidos == 0) {
        printf("Nenhum pedido foi feito ainda.\n");
    } else {
        printf("Pedidos realizados:\n");
        for (int i = 0; i < numPedidos; i++) {
            printf("Produto: %s, Quantidade: %d\n", pedidos[i].nome_produto, pedidos[i].quantidade);
        }
    }
}
