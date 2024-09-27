#include "funcao.h"

int Atualizar(){ //atualiza os valores das criptomoedas

	atualizar_cripto *criptos = malloc(sizeof(atualizar_cripto) * 3);
    if (criptos == NULL) {
        printf("Erro ao alocar mem�ria.\n");
        return 1;
    }

    FILE *arquivo = fopen("arquivo_cripto.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        free(criptos);
        return 1;
    }

    // Buffer para armazenar linhas do arquivo
    char linhas[255];
    int contador = 0;

    printf("Lendo o conte�do do arquivo...\n");

    // Leitura e processamento do arquivo
    while (fgets(linhas, sizeof(linhas), arquivo) && contador < 3) {

        // Vari�veis para capturar os dados da linha
        char nome[50], moeda[3], taxas[20];
        float valor_cripto;
        int numero1;

        float randomNumber = ((rand() / (float)RAND_MAX) * 10 - 5) / 100.0; // Gera varia��o entre -5% e +5%

        // Extra��o dos dados da linha
        int result = sscanf(linhas, "%d %s %f %s %s", &numero1, nome, &valor_cripto, moeda, taxas);

        if (result == 5) {
            // Armazena os dados na struct, aplicando a varia��o aleat�ria
            criptos[contador].numero = numero1;
            strcpy(criptos[contador].nome, nome);
            criptos[contador].cripto = valor_cripto * (1 + randomNumber); // Aplica a varia��o
            strcpy(criptos[contador].moeda, moeda);
            strcpy(criptos[contador].taxas, taxas);
            contador++;
        }
    }

    fclose(arquivo);   // Fecha o arquivo ap�s a leitura

    // Segunda etapa: abrir o arquivo em modo "w" para sobrescrever
    arquivo = fopen("arquivo_cripto.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        free(criptos);
        return 1;
    }

    // Escrita dos valores atualizados no arquivo
    int i;
    for (i = 0; i < 3; i++) {
        fprintf(arquivo, "%d %s %.2f %s %s\n", criptos[i].numero, criptos[i].nome, criptos[i].cripto, criptos[i].moeda, criptos[i].taxas);
    }

    fclose(arquivo);  // Fecha o arquivo ap�s a escrita
    free(criptos);    // Libera a mem�ria alocada

    printf("Atualiza��o feita com sucesso !!!\n");

    return 0;
}
