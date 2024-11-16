#include "funcao.h"

// falta as moedas fazer funcao
void cadastrar_investidor(cadastro *pessoas, int *total_usuarios) {
    FILE *arquivo_cripto;

    // Abrir o arquivo de criptomoedas para leitura
    arquivo_cripto = fopen("banco-em-c-pt2-main/arquivo_cripto.txt", "r");
    if (arquivo_cripto == NULL) {
        printf("Erro ao abrir o arquivo de criptomoedas!\n");
        return;
    }

    // Verificar se o limite de usuários foi atingido
    if (*total_usuarios == 9) {
        printf("Limite de usuários atingido!\n");
        fclose(arquivo_cripto);
        return;
    }
    printf("Total antes: %d\n", *total_usuarios);

    char cpf[12], nome[100], senha[10];
        
   

    // Coletar dados do novo investidor
    printf("+==========================================+\n");
    printf("|          Cadastrando investidor          |\n");
    printf("+==========================================+\n");
    printf("|Digite o CPF: ");
    scanf(" %s", cpf); // Limita o CPF a 11 caracteres
    getchar(); // Limpa o buffer

    printf("|Digite o nome: ");
    fgets(nome, 255, stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remove o '\n' ao final

    printf("|Digite a senha: ");
    scanf(" %s", senha); // Limita a senha a 9 caracteres
    getchar(); // Limpa o buffer

    printf("+==========================================+\n");

    strcpy(pessoas[*total_usuarios].cpf, cpf);    
    strcpy(pessoas[*total_usuarios].nome, nome);    
    strcpy(pessoas[*total_usuarios].senha, senha);    
    strcpy(pessoas[*total_usuarios].reais, "0.00");
    
    // Inicializar criptomoedas com base no arquivo
    char linha[255];
    int cripto_count = 0;

    while (fgets(linha, sizeof(linha), arquivo_cripto)) {
        linha[strcspn(linha, "\n")] = '\0'; // Remove o '\n' ao final da linha

        int numero;
        char nome[20];
        float valor, taxa_compra, taxa_venda;

        // Exemplo de linha: "1 Bitcoin 2000 0.02/0.03"
        if (sscanf(linha, "%d %19s %f %f/%f", &numero, nome, &valor, &taxa_compra, &taxa_venda) == 5) {
            strcpy(pessoas[*total_usuarios].cripto_nome[cripto_count], nome);
            strcpy(pessoas[*total_usuarios].cripto_saldo[cripto_count], "0.00"); // Saldo inicial zero
            cripto_count++;
        }
    }

    fclose(arquivo_cripto); // Fecha o arquivo de criptomoedas

    // Incrementar o total de usuários apenas após o cadastro
    (*total_usuarios)++;

    printf("Total depois: %d\n", *total_usuarios);

    printf("Investidor cadastrado com sucesso!\n");
}

// EXCLUIR INVESTIDOR
void excluir_investidor(cadastro *usuarios, int tamanho_usuarios) {
        char cpf[12];
        char resposta[3];  // Para resposta 'S' ou 'N'
        int encontrado = -1; // Índice do usuário encontrado

        // Solicitar o CPF do investidor a ser excluído
        printf("Digite o CPF do investidor a ser excluído: ");
        scanf(" %s", cpf);
        getchar();

        // Buscar o investidor no array de structs
        for (int i = 0; i < tamanho_usuarios; i++) {
            if (strncmp(usuarios[i].cpf, cpf, 11) == 0) { // CPF encontrado
                encontrado = i;
                break;
            }
        }

        if (encontrado == -1) {
            printf("| Investidor não encontrado!\n");
            return;
        }

        // Exibir informações do investidor encontrado
        printf("+====================================================================+\n");
        printf("| CPF: %s\n", usuarios[encontrado].cpf);
        printf("| Nome: %s\n", usuarios[encontrado].nome);
        printf("| Saldo em reais: %s\n", usuarios[encontrado].reais);
        printf("| Criptomoedas:\n");
        for (int j = 0; j < 10; j++) {
            if (strlen(usuarios[encontrado].cripto_nome[j]) > 0) {
                printf("| - %s: %s\n", usuarios[encontrado].cripto_nome[j], usuarios[encontrado].cripto_saldo[j]);
            }
        }
        printf("+====================================================================+\n");

        // Confirmar exclusão
        printf("Deseja confirmar a exclusão desse investidor? (S/N): ");
        scanf(" %s", resposta);

        if (strcmp(resposta, "S") != 0 ) {
            printf("| Exclusão cancelada. O investidor não será excluído.\n");
            return;
        }

        strcpy(usuarios[encontrado].cpf, "");
        strcpy(usuarios[encontrado].nome, "");
        strcpy(usuarios[encontrado].senha, "");
        strcpy(usuarios[encontrado].reais, "");
        for (int j = 0; j < 10; j++) {
            if (strlen(usuarios[encontrado].cripto_nome[j]) > 0) {
                strcpy(usuarios[encontrado].cripto_nome[j], "");
                strcpy(usuarios[encontrado].cripto_saldo[j], "");
            }
        }
    
        printf("| Investidor excluído com sucesso!\n");
    }
