#include "funcao.h"

int adicionar_cripto() {
    FILE *arquivo, *temp_arquivo;
    char nome[20], conversao[50], taxa[10];
    char linha[255];
    int numero_cripto = 0;
    int cont = 0;

    printf("+==========================================+\n");
    printf("|          Adicionando criptomoeda         |\n");
    printf("+==========================================+\n");

    // Coleta os dados da nova criptomoeda
    printf("| Nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';  // Remove o '\n' da string

    printf("| Conversão (ex: 2000): ");
    fgets(conversao, sizeof(conversao), stdin);
    conversao[strcspn(conversao, "\n")] = '\0';  // Remove o '\n' da string

    printf("| Taxa (compra/venda, ex: 0.02/0.03): ");
    fgets(taxa, sizeof(taxa), stdin);
    taxa[strcspn(taxa, "\n")] = '\0';  // Remove o '\n' da string

    // Abrir o arquivo de criptomoedas para leitura
    arquivo = fopen("banco-em-c-pt2-main/arquivo_cripto.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de criptomoedas.\n");
        return 1;
    }

    // Verifica se a criptomoeda já existe
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';
        char existing_nome[20];

        // Lê os dados da linha (número, nome, conversão e taxa)
        sscanf(linha, "%d %s %s %s", &numero_cripto, existing_nome, conversao, taxa);

        // Se o nome já existir, avisa o usuário e retorna
        if (strcmp(existing_nome, nome) == 0) {
            printf("Criptomoeda %s já existe no arquivo!\n", nome);
            fclose(arquivo);
            return 1;
        }
        cont++;  // Incrementa o contador para o número da próxima criptomoeda
    }

    // Fechar o arquivo após a verificação
    fclose(arquivo);

    // Agora abre o arquivo para adicionar a nova criptomoeda
    temp_arquivo = fopen("banco-em-c-pt2-main/arquivo_cripto.txt", "a");
    if (temp_arquivo == NULL) {
        printf("Erro ao abrir o arquivo para adicionar a criptomoeda.\n");
        return 1;
    }

    // Escrever a nova criptomoeda no arquivo
    fprintf(temp_arquivo, "%d %s %s %s\n", cont + 1, nome, conversao, taxa);

    printf("Nova criptomoeda %s cadastrada com sucesso!\n", nome);

    fclose(temp_arquivo);  // Fecha o arquivo

    return 0;
}

int remover_cripto() {
    FILE *arquivo, *temp_arquivo;
    char linha[255], nome_cripto[20];
    int numero_cripto;
    char nome[20], conversao[50], taxa[10];

    // Solicita o nome da criptomoeda a ser removida
    printf("+==========================================+\n");
    printf("|        Removendo criptomoeda            |\n");
    printf("+==========================================+\n");
    printf("| Nome da criptomoeda a remover: ");
    fgets(nome_cripto, sizeof(nome_cripto), stdin);
    nome_cripto[strcspn(nome_cripto, "\n")] = '\0';  // Remove o '\n' ao final da string

    // Abrir o arquivo original para leitura
    arquivo = fopen("banco-em-c-pt2-main/arquivo_cripto.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de criptomoedas.\n");
        return 1;
    }

    // Criar um arquivo temporário para armazenar as criptomoedas restantes
    temp_arquivo = fopen("banco-em-c-pt2-main/temp_arquivo_cripto.txt", "w");
    if (temp_arquivo == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(arquivo);
        return 1;
    }

    int found = 0;
    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Lê os dados da criptomoeda
        sscanf(linha, "%d %19s %s %s", &numero_cripto, nome, conversao, taxa);

        // Verifica se o nome da criptomoeda corresponde ao nome digitado
        if (strcmp(nome, nome_cripto) != 0) {
            // Se não for a criptomoeda a ser removida, escreve no arquivo temporário
            fprintf(temp_arquivo, "%s", linha);
        } else {
            // Caso contrário, marca que encontrou a criptomoeda e não escreve no arquivo
            found = 1;
        }
    }

    fclose(arquivo);        // Fecha o arquivo original
    fclose(temp_arquivo);   // Fecha o arquivo temporário

    // Se a criptomoeda foi encontrada, substituímos o arquivo original pelo temporário
    if (found) {
        remove("banco-em-c-pt2-main/arquivo_cripto.txt");  // Apaga o arquivo original
        rename("banco-em-c-pt2-main/temp_arquivo_cripto.txt", "banco-em-c-pt2-main/arquivo_cripto.txt");  // Renomeia o temporário para o nome original
        printf("Criptomoeda %s removida com sucesso!\n", nome_cripto);
    } else {
        // Caso a criptomoeda não tenha sido encontrada
        remove("banco-em-c-pt2-main/temp_arquivo_cripto.txt");  // Apaga o arquivo temporário
        printf("Criptomoeda não encontrada!\n");
        return 1;
    }

    return 0;
}
