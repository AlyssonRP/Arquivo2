#include <stdio.h>
#include <string.h>
#include "sgc.h"

int autenticarAdmin()
{
    char senha[50];
    printf("Digite a senha de administrador: ");
    scanf("%s", senha);

    if (strcmp(senha, "senha_admin") == 0)
    {
        printf("Autenticação bem-sucedida.\n");
        return 1; // Autenticação bem-sucedida
    }
    else
    {
        printf("Senha de administrador incorreta.\n");
        return 0; // Autenticação falhou
    }
}

void exibirMenu()
{
    printf("Menu:\n");
    printf("1. Adicionar Produto\n");
    printf("2. Listar Produtos\n");
    printf("3. Adicionar Usuário\n");
    printf("4. Excluir Usuário\n");
    printf("5. Fazer Pedido\n");
    printf("6. Listar Pedidos\n");
    printf("7. Cancelar Pedidos\n");
    printf("8. Encerrar o Programa\n");
    printf("9. Listar Usuários\n");
}

void adicionarProduto(Produto estoque[], int *numProdutos)
{
    if (*numProdutos < MAX_PRODUTOS)
    {
        Produto novoProduto;
        printf("Nome do produto: ");
        scanf("%s", novoProduto.nome);
        printf("Preço do produto: ");
        scanf("%f", &novoProduto.preco);
        printf("Quantidade do produto: ");
        scanf("%d", &novoProduto.quantidade);

        estoque[*numProdutos] = novoProduto;
        (*numProdutos)++;

        FILE *file = fopen("estoque.txt", "a");
        if (file)
        {
            fprintf(file, "%s %.2f %d\n", novoProduto.nome, novoProduto.preco, novoProduto.quantidade);
            fclose(file);
        }
        else
        {
            printf("Erro ao abrir o arquivo de estoque.\n");
        }
    }
    else
    {
        printf("Limite de produtos atingido.\n");
    }
}

void listarProdutos(Produto estoque[], int numProdutos)
{
    if (numProdutos == 0)
    {
        printf("Nenhum produto disponível no estoque.\n");
    }
    else
    {
        printf("Produtos disponíveis:\n");
        for (int i = 0; i < numProdutos; i++)
        {
            printf("Nome: %s, Preço: %.2f, Quantidade: %d\n", estoque[i].nome, estoque[i].preco, estoque[i].quantidade);
        }
    }
}

void adicionarUsuario(Usuario usuarios[], int *numUsuarios)
{
    if (*numUsuarios < MAX_USUARIOS)
    {
        Usuario novoUsuario;
        printf("Nome de usuário: ");
        scanf("%s", novoUsuario.nome);
        printf("Senha: ");
        scanf("%s", novoUsuario.senha);
        printf("Nível de privilégio (1 para admin, 0 para usuário convencional): ");
        scanf("%d", &novoUsuario.nivel_privilegio);

        usuarios[*numUsuarios] = novoUsuario;
        (*numUsuarios)++;

        FILE *file = fopen("usuarios.txt", "a");
        if (file)
        {
            fprintf(file, "%s %s %d\n", novoUsuario.nome, novoUsuario.senha, novoUsuario.nivel_privilegio);
            fclose(file);
        }
        else
        {
            printf("Erro ao abrir o arquivo de usuários.\n");
        }
    }
    else
    {
        printf("Limite de usuários atingido.\n");
    }
}

void excluirUsuario(Usuario usuarios[], int *numUsuarios)
{
    char nomeUsuario[50];
    printf("Digite o nome do usuário que deseja excluir: ");
    scanf("%s", nomeUsuario);

    int encontrado = 0;
    int indiceExcluir = -1;

    for (int i = 0; i < *numUsuarios; i++)
    {
        if (strcmp(usuarios[i].nome, nomeUsuario) == 0)
        {
            encontrado = 1;
            indiceExcluir = i;
            break;
        }
    }

    if (encontrado)
    {
        for (int i = indiceExcluir; i < (*numUsuarios - 1); i++)
        {
            usuarios[i] = usuarios[i + 1];
        }

        (*numUsuarios)--;

        FILE *file = fopen("usuarios.txt", "w");
        if (file)
        {
            for (int i = 0; i < *numUsuarios; i++)
            {
                fprintf(file, "%s %s %d\n", usuarios[i].nome, usuarios[i].senha, usuarios[i].nivel_privilegio);
            }
            fclose(file);
        }
        else
        {
            printf("Erro ao abrir o arquivo de usuários.\n");
        }

        printf("Usuário %s excluído com sucesso.\n", nomeUsuario);
    }
    else
    {
        printf("Usuário não encontrado.\n");
    }
}
