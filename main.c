#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define QUANT_FRUTAS 10

double valorTotal = 0.0;

void divConsole() {
    printf("-----------------------------------------\n");
}

void exibirMenu(double precoFrutas[], char *frutas[], int qntdLoop) {
    if (qntdLoop < 1) {
        printf("0. Nada, tô só olhando.\n");
    } else {
        printf("0. Desistirei de todas as compras.\n");
    }
    printf("ID |  Frutas   | Preço\n");
    divConsole();
    for (int i = 0; i < QUANT_FRUTAS; i++) {
        printf("%-3d| %-10s| R$%4.2f\n", i + 1, frutas[i], precoFrutas[i]);
    }
    divConsole();
}

void exibirNF(double precosFrutaNF[], int quantFrutasNF[], char *frutasNF[], int size, double precoFrutas[]) {
    printf("              NOTA FISCAL              \n");
    divConsole();
    printf("%-10s %-8s %-6s %s\n", "Fruta", "Valor Unit", "Quant", "Preço (R$)");
    divConsole();
    for (int i = 0; i < size; i++) {
        printf("%-10s R$%-10.2f %-8d R$%-2.2f\n", frutasNF[i], precoFrutas[i], quantFrutasNF[i], precosFrutaNF[i]);
        valorTotal += precosFrutaNF[i];
    }
    divConsole();
    printf("TOTAL: R$%.2f\n", valorTotal);
    divConsole();
}

int main() {
    int qntdLoop = 0;
    double precosFrutaNF[1000];
    int quantFrutasNF[1000];
    char *frutasNF[1000];
    int frutaEscolhida, quantFrutas, size = 0;
    char continuar = 'S';
    char *frutas[QUANT_FRUTAS] = {"Abacaxi", "Banana", "Kiwi", "Laranja", "Manga", "Goiaba", "Maçã", "Morango", "Pera", "Maracujá"};
    double precoFrutas[QUANT_FRUTAS] = {4.0, 0.8, 2.8, 1.2, 2.0, 2.5, 1.5, 3.5, 2.0, 1.85};

    printf("Bem vindo à loja de frutas!\nQual fruta deseja?\n");

    do {
        exibirMenu(precoFrutas, frutas, qntdLoop);
        printf("Resposta: ");
        scanf("%d", &frutaEscolhida);
        if (frutaEscolhida == 0) {
            printf("Tá bom, Até mais tarde :D!\n");
            exit(0);
        }
        if (frutaEscolhida < 0 || frutaEscolhida > QUANT_FRUTAS) {
            printf("Escolha uma opção entre 0 e %d!\n", QUANT_FRUTAS);
            divConsole();
            continue;
        }
        do {
            printf("Digite a quantidade (limitada a 1000): ");
            scanf("%d", &quantFrutas);
            if (quantFrutas < 1 || quantFrutas > 1000) {
                printf("Você não pode colocar quantidades negativas ou absurdas!\n");
            }
        } while (quantFrutas < 1 || quantFrutas > 1000);
        divConsole();
        printf("Pedido: %s\n", frutas[frutaEscolhida - 1]);
        frutasNF[size] = frutas[frutaEscolhida - 1];
        printf("Quantidade: %d\n", quantFrutas);
        quantFrutasNF[size] = quantFrutas;
        double soma = precoFrutas[frutaEscolhida - 1] * quantFrutas;
        precosFrutaNF[size] = soma;
        size++;
        printf("O valor do pedido vai ser de R$%.2f\n", soma);
        printf("Vai querer mais alguma coisa? [S/N]: ");
        getchar();  // Consumir o '\n' restante
        continuar = toupper(getchar());
        divConsole();
        system("clear");
        qntdLoop++;
    } while (continuar == 'S');

    exibirNF(precosFrutaNF, quantFrutasNF, frutasNF, size, precoFrutas);
    int opcMetodoPag;

    do {
        printf("Qual o método de pagamento?\n");
        printf("1. Cartão de crédito/débito\n");
        printf("2. Dinheiro\n");
        printf("3. Pix\n");
        printf("Resposta: ");
        scanf("%d", &opcMetodoPag);
        divConsole();

        switch (opcMetodoPag) {
            case 1:
            case 3:
                printf("Aguardando pagamento.\n");
                for (int i = 0; i < 3; i++) {
                    printf(".");
                    fflush(stdout);
                    sleep(1);
                }
                printf("\nPagamento aprovado!\n");
                break;
            case 2: {
                double dinheiroTotal = 0.0, dinheiroEnviado;
                do {
                    printf("Valor da compra: R$%.2f\n", valorTotal);
                    printf("Dinheiro dado: R$%.2f\n", dinheiroTotal);
                    printf("Valor que você dará: R$");
                    scanf("%lf", &dinheiroEnviado);
                    dinheiroTotal += dinheiroEnviado;
                    if (dinheiroTotal < valorTotal) {
                        printf("O dinheiro que você deu não é suficiente para pagar a compra!\n");
                        divConsole();
                    } else {
                        printf("Seu troco é de R$%.2f\n", (float) (dinheiroTotal - valorTotal));
                    }
                } while (dinheiroTotal < valorTotal);
                break;
            }
            default:
                printf("Digite um valor válido!\n");
        }
    } while (opcMetodoPag < 1 || opcMetodoPag > 3);

    printf("Volte sempre! :)\n");
    return 0;
}
