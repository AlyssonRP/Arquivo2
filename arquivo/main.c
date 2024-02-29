#include <stdio.h>
#include <string.h>
#include "sgc.h"


int main() {
    int escolha;
    int numProdutos = 0;
    int numUsuarios = 0;
    int numPedidos = 0;
    Produto estoque[MAX_PRODUTOS];
    Usuario usuarios[MAX_USUARIOS];
    Pedido pedidos[MAX_PEDIDOS];

    if (!autenticarAdmin()) {
        printf("Senha de administrador incorreta. Encerrando o programa.\n");
        return 1;
    }

    do {
        exibirMenu();
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                adicionarProduto(estoque, &numProdutos);
                break;
            case 2:
                listarProdutos(estoque, numProdutos);
                break;
            case 3:
                adicionarUsuario(usuarios, &numUsuarios);
                break;
            case 4:
                excluirUsuario(usuarios, &numUsuarios);
                break;
            case 5:
                fazerPedido(usuarios[0], pedidos, &numPedidos, estoque, numProdutos);
                break;
            case 6:
                listarPedidos(pedidos, numPedidos);
                break;
            case 7:
                if (usuarios[0].nivel_privilegio == 1) {
                    listarPedidos(pedidos, numPedidos);
                    int numeroPedidoParaCancelar;
                    printf("Digite o número do pedido que deseja cancelar: ");
                    scanf("%d", &numeroPedidoParaCancelar);

                    if (numeroPedidoParaCancelar >= 1 && numeroPedidoParaCancelar <= numPedidos) {
                        for (int i = numeroPedidoParaCancelar - 1; i < numPedidos - 1; i++) {
                            pedidos[i] = pedidos[i + 1];
                        }

                        (numPedidos)--;

                        FILE *file = fopen("pedidos.txt", "w");
                        if (file) {
                            for (int i = 0; i < numPedidos; i++) {
                                fprintf(file, "%s %d\n", pedidos[i].nome_produto, pedidos[i].quantidade);
                            }
                            fclose(file);
                        } else {
                            printf("Erro ao abrir o arquivo de pedidos.\n");
                        }

                        printf("Pedido cancelado com sucesso.\n");
                    } else {
                        printf("Número de pedido inválido.\n");
                    }
                } else {
                    printf("Você não tem permissão para cancelar pedidos.\n");
                }
                break;
            case 8:
                printf("Encerrando o programa.\n");
                return 0;
            case 9:
                listarUsuarios(usuarios, numUsuarios);
                break;
            default:
                printf("Escolha inválida. Tente novamente.\n");
        }
    } while (escolha != 8);

    return 0;
}
