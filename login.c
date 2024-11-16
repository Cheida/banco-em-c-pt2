#include "funcao.h"

int login(cadastro *p, int tamanho_usuario) {
  char nome[255], senha[255], cpf[12];
  int posicao_struct = -1;

  while (1) {
    printf("------------------------------\n");
    printf("| BEM-VINDO AO BANCO DE CRIPTO |\n");

    printf("| NOME: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remove o '\n' no final

    printf("| LOGIN: ");
    scanf("%s", cpf);
    getchar(); // Limpa buffer

    printf("| SENHA (max 10): ");
    scanf("%s", senha);
    getchar(); // Limpa buffer

    printf("------------------------------\n");

    int i, contador = 0;
    for (i = 0; i < 10;i++) { // Carregar os usuarios que estao cadastrados verificando se o
                               // cpf, nome e senha batem com os dados preenchidos
      if (strcmp(cpf, p[i].cpf) == 0 && strcmp(nome, p[i].nome) == 0 && strcmp(senha, p[i].senha) == 0) {
        contador++;
        posicao_struct = i;
        break; // caso achou a semelhanca nao precisa continuar vendo.
      }
    }

    if (contador != 0) {
      printf("BEM-VINDO AO BANCO\nUsuario: %s\n", nome);
      
      menu(p, posicao_struct);
      atualizar_usuarios(p, tamanho_usuario);
      
      char letra;
      printf("Deseja sair (s/n)?\n"); // opcao de saida
      scanf(" %c", &letra);
      getchar(); // Limpa buffer
      if (letra == 's') {
        return 0;
      }
    } else {
      printf("Usuario nao cadastrado ou dados incorretos\n");
      printf("Tente novamente!\n");
    }
  }
}

// --- ACHAR ADMIN ---
int achar_admin(admin *tam){

  FILE *arquivo = fopen("banco-em-c-pt2-main/administradores.txt", "r");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    return 0;  // Retorna 0 em caso de erro
  }

  int i = 0;
  char linha[512];  // Buffer para ler cada linha do arquivo

  while (fgets(linha, sizeof(linha), arquivo)) {
    // Remove o caractere de nova linha (se houver)
    linha[strcspn(linha, "\n")] = '\0';

    // Usando sscanf para separar os dados baseados no delimitador ';'
    sscanf(linha, "%11[^;];%255[^;];%9s", tam[i].cpf, tam[i].nome, tam[i].senha);

    i++;
  }

  fclose(arquivo);
  return i;  // Retorna o número de administradores lidos
}

//  ----- LOGIN ADM -------
int login_adm(admin *tam, int tamanho_usuario, cadastro *pessoas, int tamanho_adm) {
    char nome[255], senha[255], cpf[12];
    int posicao_struct = -1;
    int i;

    while (1) {
        printf("------------------------------\n");

        printf("| CPF: ");
        scanf("%s", cpf);
        getchar();  // Limpa buffer

        printf("| Nome: ");
        fgets(nome, 255, stdin);

        printf("| SENHA (max 10): ");
        scanf("%s", senha);
        getchar();  // Limpa buffer

        printf("------------------------------\n");

        for(i = 0; i < tamanho_adm; i++){
            if (strcmp(cpf, tam[i].cpf) == 0  && strcmp(senha, tam[i].senha) == 0 ) {
                posicao_struct = i;
                break;
            }
        }
      
        if (posicao_struct != -1) {
              printf("BEM-VINDO ADMINISTRADOR\n");
          
              menu_admin(tam, pessoas, tamanho_usuario);
          
              char letra;
              printf("Deseja sair (s/n)?\n");
              scanf(" %c", &letra);
              getchar();  // Limpa buffer
              if (letra == 's') {
                  printf("Ficando off...\n");
                  return 0;
              }
               
        }else {
          printf("Administrador não cadastrado ou dados incorretos\n");
          printf("Tente novamente!\n");
          return 0;
        }
    }
}
