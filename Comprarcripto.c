#include "funcao.h"

int comprarcripto(cadastro *p, int numero_struct) {

    moeda *moedas;
    moedas = malloc(7 * sizeof(moeda));  // Aloca espaÃ§o para atÃ© 7 criptomoedas
    int total_moedas = 0;

    FILE *arquivo = fopen("banco-em-c-pt2-main/arquivo_cripto.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    char linha[255];
    // Leitura do arquivo e preenchimento do array de moedas
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';  // Remove a nova linha
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

    // Exibe menu de criptomoedas disponÃ­veis
    printf("Escolha uma criptomoeda para comprar:\n");
    printf("+====================================+\n");
    for (int i = 0; i < total_moedas; i++) {
        printf("%d - %s (Valor: R$ %.2f)\n", moedas[i].numero, moedas[i].nome, moedas[i].valor);
    }
    printf("+====================================+\n");

    int escolha;
    printf("Digite o nÃºmero da criptomoeda: ");
    scanf("%d", &escolha);
    getchar();  // Limpar o buffer

    // Localiza a criptomoeda escolhida
    moeda *moeda_selecionada = NULL;
    for (int i = 0; i < total_moedas; i++) {
        if (moedas[i].numero == escolha) {
            moeda_selecionada = &moedas[i];
            break;
        }
    }

    if (moeda_selecionada == NULL) {
        printf("Criptomoeda invÃ¡lida.\n");
        return 1;
    }

    float quantidade;
    printf("Quantidade que deseja comprar?: \n");
    scanf("%f", &quantidade);
    getchar();  // Limpar buffer

    // CÃ¡lculo da compra com a taxa de compra
    float valor_total_compra = quantidade * moeda_selecionada->valor * (1 + moeda_selecionada->taxa_compra);

    // Verifica se o saldo em reais Ã© suficiente para a compra
    float saldo_reais = atof(p[numero_struct].reais);
    if (saldo_reais < valor_total_compra) {
        printf("Saldo insuficiente em reais para esta compra!\n");
        return 1;
    }

    // Exibe informaÃ§Ãµes e confirma a transaÃ§Ã£o
    printf("Valor total da compra: R$ %.2f (com taxa de %.2f%%)\n", valor_total_compra, moeda_selecionada->taxa_compra * 100);
    printf("Deseja continuar? (s/n): ");
    char confirmacao;
    scanf(" %c", &confirmacao);
    getchar();  // Limpar buffer

    if (confirmacao == 's' || confirmacao == 'S'){
        // Atualiza os saldos
        float novo_saldo_reais = saldo_reais - valor_total_compra;

        // Determina o saldo atual na criptomoeda e adiciona a quantidade comprada
        float saldo_cripto_atual = atof(p[numero_struct].cripto_saldo[escolha - 1]);
        float novo_saldo_cripto = saldo_cripto_atual + quantidade;

        // Converte valores para strings para atualizar no struct
        sprintf(p[numero_struct].reais, "%.2f", novo_saldo_reais);
        sprintf(p[numero_struct].cripto_saldo[escolha - 1], "%.2f", novo_saldo_cripto);

        printf("Compra de %s concluÃ­da!\nNovo saldo em Reais: R$ %.2f\n%s adicionados: %.2f\n", 
               moeda_selecionada->nome, novo_saldo_reais, moeda_selecionada->nome, novo_saldo_cripto);

        // Salva o extrato
        salvar_extrato(p[numero_struct].cpf, "Compra", moeda_selecionada->nome, &novo_saldo_cripto, &quantidade, '+', moeda_selecionada->taxa_compra * 100);
    } else {
        printf("TransaÃ§Ã£o cancelada.\n");
    }

    return 0;
}
