#include "funcao.h"

void Sacar(cadastro *p, int index) {
    float valor;
    char senha[10];

    printf("Digite sua senha: ");
    scanf("%s", senha);
    getchar();

    if (strcmp(senha, p[index].senha) == 0) {
        printf("Qual o valor que vai ser sacado: ");
        scanf("%f", &valor);
        getchar();

        float saldoAtual = atof(p[index].reais);
        if (valor > saldoAtual) {
            printf("Saldo insuficiente!\n");
        } else {
            saldoAtual -= valor;
            sprintf(p[index].reais, "%.2f", saldoAtual);
            printf("Saque Bem-Sucedido! Novo saldo: %.2f\n", saldoAtual);

            salvar_extrato(p[index].cpf, "Sacar" , "Reais", &saldoAtual, &valor, '-', 0);
        }
    } else {
        printf("Senha incorreta!\n");
    }
} // salvar_extrato(p[numero_struct].cpf, "compra", nome_cripto , conversao2, quantidade, taxa);
