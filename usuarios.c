#include "funcao.h"

int carregar_usuarios(cadastro *usuarios) {
    FILE *arquivo = fopen("banco-em-c-pt2-main/usuarios.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de usuários");
        return 0;
    }

    int count = 0;
    char linha[512];

    while (fgets(linha, sizeof(linha), arquivo)) {
        // Remove o '\n' da linha, caso exista
        linha[strcspn(linha, "\n")] = '\0';

        // Lê os campos principais: CPF, Nome, Senha, Reais
        // Como a primeira parte da linha é separada por ";", usamos sscanf
        int campos = sscanf(linha, "%[^;];%[^;];%[^;];%[^;];", 
                             usuarios[count].cpf,
                             usuarios[count].nome,
                             usuarios[count].senha,
                             usuarios[count].reais);

        if (campos != 4) {
            // Se não leu exatamente 4 campos, o formato da linha pode estar incorreto
            printf("Erro ao ler dados do usuário. Linha ignorada: %s\n", linha);
            continue;
        }

        // Processa as criptomoedas a partir da parte restante da linha
        char *token = strtok(linha, ";"); // Salta os 4 primeiros campos lidos com sscanf
        int cripto_count = 0;

        // Avança para a parte onde começam as criptomoedas
        while ((token = strtok(NULL, ";")) != NULL) {
            // Verifica se o token contém ":" para identificar criptomoedas
            if (strchr(token, ':')) {
                sscanf(token, "%[^:]:%s", 
                       usuarios[count].cripto_nome[cripto_count], 
                       usuarios[count].cripto_saldo[cripto_count]);
                cripto_count++;

                if (cripto_count >= 10) {
                    break;  // Limita a 10 criptomoedas
                }
            }
        }

        // Exibe os dados para depuração
        printf("CPF: %s\n", usuarios[count].cpf);
        printf("Nome: %s\n", usuarios[count].nome);
        printf("Senha: %s\n", usuarios[count].senha);
        printf("Reais: %s\n", usuarios[count].reais);

        for (int i = 0; i < cripto_count; i++) {
            printf("%s: %s\n", usuarios[count].cripto_nome[i], usuarios[count].cripto_saldo[i]);
        }

        count++;
    }

    fclose(arquivo);
    return count;
}

int atualizar_usuarios(cadastro *p, int total_usuarios) {
    FILE *arquivo = fopen("banco-em-c-pt2-main/usuarios.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de usuários para atualização.\n");
        return 1;
    }

    for (int i = 0; i < total_usuarios; i++) {
        // Verifica se o registro é válido (CPF e nome preenchidos)
        if (strlen(p[i].cpf) > 0 && strlen(p[i].nome) > 0) {
            // Escreve os campos principais
            fprintf(arquivo, "%s;%s;%s;%s", 
                    p[i].cpf,
                    p[i].nome,
                    p[i].senha,
                    p[i].reais);

            // Escreve as criptomoedas
            for (int j = 0; j < 10; j++) {
                if (strlen(p[i].cripto_nome[j]) > 0 && strlen(p[i].cripto_saldo[j]) > 0) {
                    fprintf(arquivo, ";%s:%s", 
                            p[i].cripto_nome[j], 
                            p[i].cripto_saldo[j]);
                }
            }

            // Adiciona quebra de linha ao final do registro do usuário
            fprintf(arquivo, "\n");
        }
    }

    fclose(arquivo);
    return 0;
}
