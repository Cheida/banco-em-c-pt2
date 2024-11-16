#include "funcao.h"

int vendercripto(cadastro *p, int numero_struct) {

    moeda *moedas;
    moedas = malloc(7 * sizeof(moeda));
    int total_moedas = 0;

    FILE *arquivo = fopen("banco-em-c-pt2-main/arquivo_cripto.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    char linha[255];
    // Leitura do arquivo e preenchimento do array de moedas
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';
        int numero;
        char nome[20];
        float valor, taxa_compra, taxa_venda;

        // Exemplo de linha no arquivo: 1 Bitcoin 200000.00 0.02/0.03
        int result = sscanf(linha, "%d %s %f %f/%f", &numero, nome, &valor, &taxa_compra, &taxa_venda);
        if (result == 5) {
            moedas[total_moedas].numero = numero;
            strcpy(moedas[total_moedas].nome, nome);
            moedas[total_moedas].valor = valor;
            moedas[total_moedas].taxa_compra = taxa_compra;
            moedas[total_moedas].taxa_venda = taxa_venda;
            total_moedas++;
        }
    }
    fclose(arquivo);

// Verificação se o arquivo foi lido corretamente
    if (total_moedas == 0) {
        printf("Nenhuma criptomoeda foi lida do arquivo.\n");
        free(moedas);
        return 1;
    }

    // Exibe menu de criptomoedas disponíveis
    printf("Escolha uma criptomoeda para vender:\n");
    printf("+====================================+\n");
    for (int i = 0; i < total_moedas; i++) {
        printf("%d - %s (Valor: R$ %.2f)\n", moedas[i].numero, moedas[i].nome, moedas[i].valor);
    }
    printf("+====================================+\n");

    int escolha;
    printf("Digite o número da criptomoeda: ");
    scanf("%d", &escolha);
    getchar(); // Limpar o buffer

    // Localiza a criptomoeda escolhida
    moeda *moeda_selecionada = NULL;
    for (int i = 0; i < total_moedas; i++) {
        if (moedas[i].numero == escolha) {
            moeda_selecionada = &moedas[i];
            break;
        }
    }

    if (moeda_selecionada == NULL) {
        printf("Criptomoeda inválida.\n");
        free(moedas);
        return 1;
    }

    float quantidade;
    printf("Quantidade que deseja vender?: \n");
    scanf("%f", &quantidade);
    getchar(); // Limpar buffer

    // Verifica se o saldo é suficiente para venda
    float saldo_cripto = atof(p[numero_struct].cripto_saldo[escolha - 1]);
    if (saldo_cripto < quantidade) {
        printf("Não possui essa quantidade de %s!\n", moeda_selecionada->nome);
        free(moedas);
        return 1;
    }

    // Cálculo da venda com a taxa de venda
    float venda = quantidade * moeda_selecionada->valor * (1 - moeda_selecionada->taxa_venda);

    // Exibe informações e confirma a transação
    printf("Valor total da venda: R$ %.2f (com taxa de %.2f%%)\n", venda, moeda_selecionada->taxa_venda * 100);
    printf("Deseja continuar? (s/n): ");
    char confirmacao;
    scanf(" %c", &confirmacao);
    getchar(); // Limpar buffer

    if (confirmacao == 's') {
        // Atualiza os saldos
        float novo_saldo_reais = atof(p[numero_struct].reais) + venda;
        float novo_saldo_cripto = saldo_cripto - quantidade;

        // Converte valores para strings para atualizar no struct
        sprintf(p[numero_struct].reais, "%.2f", novo_saldo_reais);
        sprintf(p[numero_struct].cripto_saldo[escolha - 1], "%.2f", novo_saldo_cripto);

        printf("Transação de venda concluída!\nNovo saldo em Reais: R$ %.2f\nNovo saldo em %s: %.2f\n", 
               novo_saldo_reais, moeda_selecionada->nome, novo_saldo_cripto);

        // Salva o extrato
        salvar_extrato(p[numero_struct].cpf, "Venda", moeda_selecionada->nome, &novo_saldo_cripto, &quantidade, '-', moeda_selecionada->taxa_venda * 100);
    } else {
        printf("Transação cancelada.\n");
    }

    free(moedas);  // Libera a memória alocada
    return 0;
}

