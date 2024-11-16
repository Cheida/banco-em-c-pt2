#include "funcao.h"

void limparstring(char *array){ 
    int i;
    for(i = 0; i < 255 ; i++){
        array[i] = '\0';
    }
}

void obterDataAtual(char *data) { // pega o dia/mes/ano atual
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    // Formatar a data no formato "DD/MM/AAAA"
    strftime(data, 11, "%d/%m/%Y", tm_info);
}

// PESQUISAR CRIPTOMOEDAS (ctrl + f) --> funçao repetitiva
void ExibirInformacoesCompra(const char* nomeMoeda, float taxa, float valorCompra, float saldoNovo, float saldoCripto) {
    printf("|---------------------------------|\n");
    printf("|     Informaçõees transação      |\n");
    printf("|---------------------------------|\n");
    printf("|Taxa --> (%.2f/100)\n", taxa * 100);
    printf("|Valor liquido: %.2f\n", valorCompra);
    printf("|Saldo Novo(reais): %.2f\n", saldoNovo);
    printf("|Saldo %s: %.2f\n", nomeMoeda, saldoCripto);
    printf("|--------------------------------|\n");
}
