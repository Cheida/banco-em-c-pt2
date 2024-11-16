#include "funcao.h"


int menu(cadastro *p, int index) {
  int resposta;
  while (1) {
    printf("----------------------------\n");
    printf("| 1. Consultar saldo       |\n");
    printf("| 2. Consultar extrato     |\n");
    printf("| 3. Depositar             |\n");
    printf("| 4. Sacar                 |\n");
    printf("| 5. Comprar criptomoeda   |\n");
    printf("| 6. Vender criptomoedas   |\n");
    printf("| 7. Atualizar cripto      |\n");
    printf("| 8. Sair                  |\n");
    printf("----------------------------\n");
    scanf("%d", &resposta);
    getchar();

    switch (resposta) {
    case 1:
      Consultarsaldo(p, index);
      break;
    case 2:
      Consultarextrato(p, index);
      break;
    case 3:
      Depositar(p, index);
         
      break;
    case 4:
      Sacar(p, index);
        
      break;
    case 5:
      comprarcripto(p, index);
       
      break;
    case 6:
      vendercripto(p, index);
       
      break;
    case 7:
      Atualizar(); // atualizar os valores das criptomoedas
      break;
    case 8:
      return 0; // Sair do menu
    default:
      printf("Essa opcao nao e valida!\n");
    }
  }
}

int menu_admin(admin *tam, cadastro *pessoas, int tamanho_usuario){
  int resposta;
  while (1) {
    printf("|======================================|\n");
    printf("|1. Cadastrar Novo Investidor          |\n");
    printf("|2. Excluir Investidor                 |\n");
    printf("|3. Cadastrar de Criptomoeda           |\n");
    printf("|4. Excluir Criptomoeda                |\n");
    printf("|5. Consultar Saldo de um Investidor   |\n");
    printf("|6. Consultar Extrato de um Investidor |\n");
    printf("|7. Atualizar cotação de criptomoedas  |\n");
    printf("|8. Sair                               |\n");
    printf("|======================================|\n");
    scanf(" %d", &resposta);
    getchar();

    switch (resposta) {
      case 1:
        cadastrar_investidor(pessoas, &tamanho_usuario);
        printf("fora do bagulho  %d\n", tamanho_usuario);
        atualizar_usuarios(pessoas, tamanho_usuario);
        break;
      case 2:
        excluir_investidor(pessoas, tamanho_usuario);
        atualizar_usuarios(pessoas, tamanho_usuario);
        break;
      case 3:
        adicionar_cripto();
        break;
      case 4:
        remover_cripto();
        break;
      case 5:
        consultar_saldo_de_um_Investidor(pessoas, tamanho_usuario);
        break;
      case 6:
        Consultar_Extrato_adm();
        break;
      case 7:
        Atualizar(); // atualizar os valores das criptomoedas
        break;
      case 8:
        break;
      default:
        printf("| Opção Inválida!!! |\n");
    }
    if (resposta == 8){
      return 0;
    }
  }
}  

