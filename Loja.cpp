//
// Created by lucas on 22/09/2025.
//

#include <stdio.h>
#include <string.h>

typedef struct Custos {
    int numIdentificador;
    char nome[50];
    double custo_de_venda;  //quanto ele custa na para o comprador
    double custo_produto;  //custo do produto inclui embalagens e etiqueta
    double receita_liquida; //quanto realmente cai na minha conta
    double lucro_liquido;  //quanto eu realmente tenho de lucro por produto
}Pedidos;

double preco_servo = 4.6;
double custo_embalagem = 1; //custo da etiquita e embalagem

int descobreUltimoID() {  //estava enfentendo serio problemas apos terminar ele e tenter adicionar novos pedidos
    FILE *arq = fopen("pedidos.dat", "rb");

    Pedidos pedidos;
    int ultimoID = 0;
    while (fread(&pedidos, sizeof(Pedidos), 1 , arq)) {
        if (pedidos.numIdentificador > ultimoID) {
            ultimoID = pedidos.numIdentificador;
        }
    }
    fclose(arq);
    return ultimoID;

}

void backup() {
    FILE *arq = fopen("pedidos.dat", "rb");
    FILE *arqBackup = fopen("pedidosBackup.dat", "wb");  //wb para ele reescrever as informaçoes e não adicionar
    Pedidos pedidos;
    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }
    while (fread(&pedidos, sizeof(Pedidos), 1, arq)) {
        if (pedidos.numIdentificador != 0) {
            fwrite(&pedidos, sizeof(Pedidos), 1, arqBackup);
        }
    }
    fclose(arq);
    fclose(arqBackup);
    printf("Backup realizado com sucesso!\n");
}

void remover(int id) {
    FILE *arq = fopen("pedidos.dat", "rb+");
    Pedidos pedidosNulo = {0, "", 0, 0, 0, 0};
    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }
    fseek(arq, (id - 1) * sizeof(Pedidos), SEEK_SET);
    fwrite(&pedidosNulo, sizeof(Pedidos), 1,  arq);
    fclose(arq);
    printf("Pedido %d removido com sucesso!.\n", id);
}

void EditarPedido(int id) {
    FILE *arq = fopen("pedidos.dat", "rb+");
    Pedidos pedidos;
    fseek(arq, (id - 1) * sizeof(Pedidos), SEEK_SET);
    fread(&pedidos, sizeof(Pedidos), 1, arq);

    if (pedidos.numIdentificador == 0) {
        printf("Nenhum contato encontrado com esse ID.\n");
        fclose(arq);
        return;
    }
    printf("Nome atual do produto %s\nNovo Nome: ", pedidos.nome);
    getchar();
    fgets(pedidos.nome, 50, stdin);
    pedidos.nome[strcspn(pedidos.nome, "\n")] =  '\0';

    printf("Custo de venda atual: %.2f\nNovo Custo de venda: ", pedidos.custo_de_venda);
    scanf("%lf" , &pedidos.custo_de_venda);

    printf("Custo atual do produto: %.2f\nNovo Custo do produto: ", pedidos.custo_produto);
    scanf("%lf" , &pedidos.custo_produto);

    printf("Receita Liquida atual: %.2f\nNovo Receita Liquida: ", pedidos.receita_liquida);
    scanf("%lf" , &pedidos.receita_liquida);

    printf("Lucro liquido atual: %.2f\nNovo lucro liquido: ", pedidos.lucro_liquido);
    scanf("%lf" , &pedidos.lucro_liquido);

    fseek(arq, (id - 1) * sizeof(Pedidos), SEEK_SET);
    fwrite(&pedidos, sizeof(Pedidos), 1, arq);

    fclose(arq);
    printf("Pedido editado com sucesso!\n");

}

void AdicionarPedido(int cont, int opcao2) {
    Pedidos pedidos;
    pedidos.numIdentificador = cont;

    switch (opcao2) {
        case 1:
            strcpy(pedidos.nome, "1 Servo");
            pedidos.custo_de_venda = 18.50;
            pedidos.custo_produto = preco_servo + custo_embalagem;
            pedidos.receita_liquida = 8.80;
            pedidos.lucro_liquido = pedidos.receita_liquida - pedidos.custo_produto;
            break;
        case 2:
            strcpy(pedidos.nome, "2 Servos");
            pedidos.custo_de_venda = 27.50;
            pedidos.custo_produto = (preco_servo * 2) + custo_embalagem;
            pedidos.receita_liquida = 18;
            pedidos.lucro_liquido = pedidos.receita_liquida - pedidos.custo_produto;
            break;
        case 3:
            strcpy(pedidos.nome, "3 Servos");
            pedidos.custo_de_venda = 39;
            pedidos.custo_produto = 3 * preco_servo + custo_embalagem;
            pedidos.receita_liquida = 27.20;
            pedidos.lucro_liquido = pedidos.receita_liquida - pedidos.custo_produto;
            break;
        case 4:
            strcpy(pedidos.nome, "4 Servos");
            pedidos.custo_de_venda = 50;
            pedidos.custo_produto = 4 * preco_servo + custo_embalagem;
            pedidos.receita_liquida = 36;
            pedidos.lucro_liquido = pedidos.receita_liquida - pedidos.custo_produto;
            break;
        case 5:
            strcpy(pedidos.nome, "5 Servos");
            pedidos.custo_de_venda = 62.50;
            pedidos.custo_produto = 5 * preco_servo + custo_embalagem;
            pedidos.receita_liquida = 46;
            pedidos.lucro_liquido = pedidos.receita_liquida - pedidos.custo_produto;
            break;
        case 6:
            strcpy(pedidos.nome, "6 Servos");
            pedidos.custo_de_venda = 71;
            pedidos.custo_produto = 6 * preco_servo + custo_embalagem;
            pedidos.receita_liquida = 52.80;
            pedidos.lucro_liquido = pedidos.receita_liquida - pedidos.custo_produto;
            break;
        case 7:
            strcpy(pedidos.nome, "Sensor Ultrassanico + kit");
            pedidos.custo_de_venda = 19;
            pedidos.custo_produto = 5 + custo_embalagem;
            pedidos.receita_liquida = 11.20;
            pedidos.lucro_liquido = pedidos.receita_liquida - pedidos.custo_produto;
            break;
        default:
            printf("Opcao invalida!\n");
            return;
    }
    FILE *arq = fopen("pedidos.dat", "rb+");   //não usar o wb pq vai sobreescrever
    if (arq == NULL) {
        arq = fopen("pedidos.dat", "wb+");
        if (arq == NULL) {
            printf("Nao foi possivel abrir o arquivo.\n");
            return;
        }
    }

    fseek(arq, (cont -1) * sizeof(Pedidos), SEEK_SET);
    fwrite(&pedidos, sizeof(Pedidos), 1, arq);
    fclose(arq);

    printf("Pedidos adicionado com sucesso!\n");

}

void ListarPedidos() {
    FILE *arq = fopen("pedidos.dat", "rb");
    Pedidos pedidos;
    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }
    while (fread(&pedidos, sizeof(Pedidos), 1, arq)) {
        if (pedidos.numIdentificador != 0) {
            printf("ID: %d\n", pedidos.numIdentificador);
            printf("Nome: %s\n" , pedidos.nome);
            printf("Custo de venda: %.2f\n", pedidos.custo_de_venda);
            printf("Receita liquida: %.2f\n", pedidos.receita_liquida);
            printf("Lucro Liquido: %.2f\n", pedidos.lucro_liquido);
            printf("\n");
        }
    }
    fclose(arq);
}

void LucroLiquido() {
    FILE *arq = fopen("pedidos.dat", "rb");
    double totalLucro = 0;
    Pedidos pedidos;
    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }
    while (fread(&pedidos, sizeof(Pedidos), 1, arq)) {
        if (pedidos.numIdentificador != 0) {
            totalLucro += pedidos.lucro_liquido;
        }
    }
    fclose(arq);
    printf("O total de lucro liquido: %.2f" , totalLucro);
}


int main() {
    int opcao1, opcao2;
    int cont = descobreUltimoID();
    do {
        printf("\n1 - Adicionar Produto."
                     "\n2 - Listar pedidos."
                     "\n3 - Editar pedido."
                     "\n4 - Remover pedido."
                     "\n5 - Total de Lucro Liquido."
                     "\n0 - Sair.\n");
        scanf("%d", &opcao1);

        switch (opcao1) {
            case 1:
                printf("\n1 - 1x Servos."
                             "\n2 - 2x Servos."
                             "\n3 - 3x Servos."
                             "\n4 - 4x Servos."
                             "\n5 - 5x Servos."
                             "\n6 - 6x Servos."
                             "\n7 - Sensor ultrassonico + kit."
                             "\n0 - Sair.\n");
                scanf("%d", &opcao2);

                if (opcao2 == 0) {
                    cont++;
                    AdicionarPedido(cont, opcao2);
                    break;
                }

                cont++;
                AdicionarPedido(cont, opcao2);
                break;
            case 2:
                ListarPedidos();
                break;
            case 3:
                int id;
                printf("Digite o ID do produto que deseja editar: ");
                scanf("%d", &id);
                EditarPedido(id);

                break;
            case 4:
                int id2;
                printf("Digite o ID do pedido que deseja remover: ");
                scanf("%d", &id2);
                remover(id2);
                break;
            case 5:
                LucroLiquido();
                break;
            case 0:
                printf("saindo do programa.\n");
                backup();
                break;

        }
    }while (opcao1 != 0);
    return 0;
}