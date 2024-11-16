#include "funcao.h"

int Atualizar() {

    atualizar_cripto *criptos = malloc(sizeof(atualizar_cripto) * 10); 
    if (criptos == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    
    FILE *arquivo = fopen("banco-em-c-pt2-main/arquivo_cripto.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        free(criptos);
        return 1;
    }

    // Buffer para armazenar as linhas do arquivo
    char linhas[255];
    int contador = 0;

    printf("Lendo o conteudo do arquivo...\n");

    // Leitura e processamento do arquivo
    while (fgets(linhas, sizeof(linhas), arquivo)) {

        linhas[strcspn(linhas, "\n")] = '\0';

        // VariÃ¡veis para capturar os dados da linha
        char nome[50];
        float moeda, taxas, valor_cripto;
        int numero1;

        float randomNumber = ((rand() / (float)RAND_MAX) * 10 - 5) / 100.0; // Gera variaÃ§Ã£o entre -5% e +5%

        // ExtraÃ§Ã£o dos dados da linha
        int result = sscanf(linhas, "%d %s %f %f/%f", &numero1, nome, &valor_cripto, &moeda, &taxas);

        if (result == 5) {
            // Armazena os dados na struct, aplicando a variaÃ§Ã£o aleatÃ³ria
            criptos[contador].numero = numero1;
            strcpy(criptos[contador].nome, nome);
            criptos[contador].cripto = valor_cripto * (1 + randomNumber); // Aplica a variaÃ§Ã£o
            criptos[contador].taxa_compra = moeda;
            criptos[contador].taxas_venda = taxas;
            contador++;
        }
    }

    fclose(arquivo); // Fecha o arquivo apÃ³s a leitura

    // Segunda etapa: abrir o arquivo em modo "w" para sobrescrever
    arquivo = fopen("banco-em-c-pt2-main/arquivo_cripto.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        free(criptos);
        return 1;
    }

    // Escrita dos valores atualizados no arquivo
    for (int i = 0; i < contador; i++) {
        fprintf(arquivo, "%d %s %.2f %.2f/%.2f\n", criptos[i].numero, criptos[i].nome,
                criptos[i].cripto, criptos[i].taxa_compra, criptos[i].taxas_venda);
    }

    fclose(arquivo); // Fecha o arquivo apÃ³s a escrita
    free(criptos);   // Libera a memÃ³ria alocada

    printf("Atualizacao feita com sucesso !!!\n");

    return 0;
}
