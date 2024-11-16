#include "funcao.h"

void Consultarsaldo(cadastro *p, int index) {
    printf("============================\n");
    printf("CPF: %s\n", p[index].cpf);
    printf("Nome: %s\n", p[index].nome);
    printf("Senha: %s\n", p[index].senha);
    printf("Reais: %s\n", p[index].reais);

    for (int j = 0; j < 10; j++) {
        if (strlen(p[index].cripto_nome[j]) > 0) {
            printf("%s: %s\n", p[index].cripto_nome[j], p[index].cripto_saldo[j]);
        }
    }
    printf("============================\n");
}

void consultar_saldo_de_um_Investidor(cadastro *p, int tamanho) {
    char cpf[12];
    int encontrado = 0;

    // Pedir o CPF do investidor
    printf("Digite o CPF do investidor: ");
    scanf("%s", cpf);
    getchar(); // Limpa o buffer

    int i, index = -1;
    for (i = 0; i < tamanho; i++) {
        if (strcmp(p[i].cpf, cpf) == 0) {
            encontrado = 1;
            index = i;
            break;
        }
    }

    if (encontrado) {
        // Exibir os dados do investidor
        printf("============================\n");
        printf("CPF: %s\n", p[index].cpf);
        printf("Nome: %s\n", p[index].nome);
        printf("Senha: %s\n", p[index].senha);
        printf("Reais: %s\n", p[index].reais);

        // Exibir as criptomoedas do investidor
        for (int j = 0; j < 10; j++) {
            if (strlen(p[index].cripto_nome[j]) > 0) {
                printf("%s: %s\n", p[index].cripto_nome[j], p[index].cripto_saldo[j]);
            }
        }
        printf("============================\n");
    } else {
        printf("Investidor com CPF %s nÃ£o encontrado!\n", cpf);
    }
}
