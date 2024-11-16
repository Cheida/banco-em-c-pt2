#include "funcao.h"

// Função para ver o extrato de um investidor 
void Consultar_Extrato_adm(){
  FILE *arquivo;
  char linhas[255];
  char cpf[12], data[11], tipo[20], moeda[20], sinal, cpf_encontrado[12];
  double valor_total, valor_parcial;

  printf("Qual o CPF do investidor?\n");
  scanf(" %s", cpf_encontrado);
  getchar(); // Limpa o buffer
  
  // Abre o arquivo para a leitura
  arquivo = fopen("banco-em-c-pt2-main/extratos.txt", "r");
  if (arquivo == NULL){
    printf("Erro ao abrir arquivos !!!\n");
    return;
  }
  // Lê cada linha do arquivo
  while(fgets(linhas, 255, arquivo) != NULL){
    linhas[strcspn(linhas, "\n")] = '\0';
    sscanf(linhas, "%s ; %s ; %s ; %s ; %lf ; %lf ; %c ;",
         cpf, data, tipo, moeda, &valor_total, &valor_parcial, &sinal);
      // Verifica se o CPF da linha corresponde ao CPF do investidor e mostra o extrato correspondente
      if (strcmp(cpf, cpf_encontrado) == 0) {
          printf("CPF: %s | Data: %s | Operação: %s | Moeda: %s | Valor Total: %.6lf | Valor Parcial: %.6lf | Sinal: %c |\n",
                 cpf, data, tipo, moeda, valor_total, valor_parcial, sinal);
      }
  }
  fclose(arquivo);
}
