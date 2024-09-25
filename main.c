#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

typedef struct cadastro{
    char cpf[12];
    char nome[100];
    char senha[10];
    char reais[20]; 
    char bitcoin[20];
    char Ethereum[20];
    char Ripple[20];
} cadastro;

typedef struct moedas{
    float bitcoin;
    float Ethereum;
    float Ripple;
} moedas;

typedef struct atualizar_cripto{
    int numero;
    char nome[50];
    float cripto;
    char moeda[3];
    char taxas[20];
} atualizar_cripto;

void Consultarsaldo(cadastro *p, int index);
void Consultarextrato();
void Depositar(cadastro *p, int index);
void Sacar(cadastro *p, int index);
int Criptomoedas(cadastro *p, int numero_struct, int tipo);
int Atualizar();

void limparstring(char *array){
    int i;
    for(i = 0; i < 255 ; i++){
        array[i] = '\0';
    }
}

// PESQUISAR CRIPTOMOEDAS (ctrl + f) --> fun�ao repetitiva
void ExibirInformacoesCompra(const char* nomeMoeda, float taxa, float valorCompra, float saldoNovo, float saldoCripto) {
    printf("|------------------------------|\n");
    printf("|     Informa��es transa��o    |\n");
    printf("|------------------------------|\n");
    printf("|Taxa --> (%.2f/100)\n", taxa * 100);
    printf("|Valor Bruto: %.2f\n", valorCompra);
    printf("|Saldo Novo(reais): %.2f\n", saldoNovo);
    printf("|Saldo %s: %.2f\n", nomeMoeda, saldoCripto);
    printf("|--------------------------------|\n");
}


int salvar_dados(cadastro *p){
    FILE *arquivo = fopen("usuarios.txt", "w");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
	
	int i;
    for(i = 0; i < 2; i++){
        fprintf(arquivo, "%s;%s;%s;%s;%s;%s;%s\n", p[i].cpf, p[i].nome, p[i].senha, p[i].reais, p[i].bitcoin, p[i].Ethereum, p[i].Ripple);
    }

    fclose(arquivo);
    return 0;
}

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

        switch (resposta) {
            case 1:
                Consultarsaldo(p, index);
                break;
            case 2:
                Consultarextrato();
                break;
            case 3:
                Depositar(p, index);
                salvar_dados(p);
                break;
            case 4:
                Sacar(p, index);
                salvar_dados(p);
                break;
            case 5:
                Criptomoedas(p, index, 5);
                salvar_dados(p);
                break;
            case 6:
                Criptomoedas(p, index, 6);
                salvar_dados(p);
                break;
            case 7:
                Atualizar();
                break;
            case 8:
                return 0;  // Sair do menu
            default:
                printf("Essa op��o n�o � v�lida!\n");
        }
    }
}

void login(cadastro *p){
    char nome[255], senha[255], cpf[12];
    int posicao_struct = -1;

    while (1) {
        printf("------------------------------\n");
        printf("| BEM-VINDO AO BANCO DE CRIPTO |\n");
        
        printf("| NOME: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0';  // Remove o '\n' no final
        
        printf("| LOGIN: ");
        scanf("%s", cpf);
        getchar();  // Limpa buffer
        
        printf("| SENHA (max 10): ");
        scanf("%s", senha);
        getchar();  // Limpa buffer
        
        printf("------------------------------\n");

        int i, contador = 0;
        for (i = 0; i < 2; i++) {
            if (strcmp(cpf, p[i].cpf) == 0 && strcmp(nome, p[i].nome) == 0 && strcmp(senha, p[i].senha) == 0) {
                contador++;
                posicao_struct = i;
                break;
            }
        }

        if(contador != 0){
            printf("BEM-VINDO AO BANCO\nUsu�rio: %s\n", nome);
            menu(p, posicao_struct);

            char letra;
            printf("Deseja sair (s/n)?\n");
            scanf(" %c", &letra);
            getchar();  // Limpa buffer
            if(letra == 's'){
                break;
            }
        } else {
            printf("Usu�rio n�o cadastrado ou dados incorretos\n");
            printf("Tente novamente!\n");
        }
    }
}

int achar_usuario(cadastro *p) {
    FILE *arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    char linhas[255];
    int posicao_struct = 0;
    while (fgets(linhas, 255, arquivo)) {
        char *token = strtok(linhas, ";");
        int contador = 0;

        while (token != NULL) {
            if (contador == 0) {
                strcpy(p[posicao_struct].cpf, token);  
            } else if (contador == 1) {
                strcpy(p[posicao_struct].nome, token);
            } else if (contador == 2) {
                strcpy(p[posicao_struct].senha, token);
            } else if (contador == 3) {
                strcpy(p[posicao_struct].reais, token);
            } else if (contador == 4) {
                strcpy(p[posicao_struct].bitcoin, token);
            } else if (contador == 5) {
                strcpy(p[posicao_struct].Ethereum, token);
            } else if (contador == 6) {
                strcpy(p[posicao_struct].Ripple, token);
            }
            contador++;
            token = strtok(NULL, ";");
        }
        posicao_struct++;
    }

    fclose(arquivo);
    return 0;
}

void Consultarsaldo(cadastro *p, int index) {
    printf("------------------------------\n");
    printf("Nome: %s\n", p[index].nome);
    printf("CPF: %s\n", p[index].cpf);
    printf("Reais: %s\n", p[index].reais);
    printf("Bitcoin: %s\n", p[index].bitcoin);
    printf("Ethereum: %s\n", p[index].Ethereum);
    printf("Ripple: %s\n", p[index].Ripple);
    printf("------------------------------\n");
}

void Depositar(cadastro *p, int index) {
    float valor;
    printf("Qual o valor que vai ser depositado: ");
    scanf("%f", &valor);
    getchar();

    float saldoAtual = atof(p[index].reais);
    saldoAtual += valor;
    sprintf(p[index].reais, "%.2f", saldoAtual);

    printf("Dep�sito Bem-Sucedido! Novo saldo: %.2f\n", saldoAtual);
}

void Sacar(cadastro *p, int index) {
    float valor;
    char senha[10];

    printf("Digite sua senha: ");
    scanf("%s", senha);
    getchar();

    if (strcmp(senha, p[index].senha) == 0) {
        printf("Qual o valor que vai ser sacado: ");
        scanf("%f", &valor);
        getchar();

        float saldoAtual = atof(p[index].reais);
        if (valor > saldoAtual) {
            printf("Saldo insuficiente!\n");
        } else {
            saldoAtual -= valor;
            sprintf(p[index].reais, "%.2f", saldoAtual);
            printf("Saque Bem-Sucedido! Novo saldo: %.2f\n", saldoAtual);
        }
    } else {
        printf("Senha incorreta!\n");
    }
}

int Criptomoedas(cadastro *p,int numero_struct, int tipo){

	moedas *valor;
	valor = malloc(sizeof(moedas) * 3);
    FILE *arquivo = fopen("arquivo_cripto.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    char linhas[255];
    int escolha, contador = 0;
    float quantidade, compra, venda, conversao, conversao2;

    // Leitura dos valores das criptomoedas
    while (fgets(linhas, sizeof(linhas), arquivo)) {
        int number1;
        float number2;
        char name[20];
		printf("%s\n", linhas);

        int result = sscanf(linhas, "%d %s %f", &number1, name, &number2);
        if (result == 3) {
            if (contador == 0) {
                valor[0].bitcoin = number2;
            } else if (contador == 1) {
                valor[0].Ethereum = number2;
            } else {
                valor[0].Ripple = number2;
            }
            contador++;
        }
    }
    fclose(arquivo);
	
	char confirmacao;
    char saldo_novo[50], saldo_cripto[50];
	
	
	if(tipo == 5){ //comprar
		printf("Qual moeda deseja comprar?: \n");
		scanf("%d", &escolha);
		getchar();
		
		printf("Quantidade que deseja comprar?: \n");
		scanf("%f", &quantidade);
		getchar();
		
		char senha[10];
		printf("Digite sua senha: \n");
		scanf(" %s", senha);
		getchar();
	
		if (strcmp(senha, p[numero_struct].senha) != 0) {
	            printf("Senha incorreta!\n");
	            return 1;
	    }else{	
    
			if(escolha == 1){
				
				compra = quantidade * (valor[0].bitcoin + valor[0].bitcoin* 0.02); // taxa de 2% para bitcoin
		
				if(atof(p[numero_struct].reais) < compra){
					printf("N�o possui dinheiro suficiente !!\n");
		
				}else{
					
					conversao = atof(p[numero_struct].reais) - compra;           // modificar reais 
					conversao2 = atof(p[numero_struct].bitcoin) + quantidade;   // modificar criptomoeda
					
					ExibirInformacoesCompra("bitcoin", 0.02, compra, conversao, conversao2);
					
					printf("Deseja continuar?(s/n): \n");
					scanf(" %c", &confirmacao);
					getchar();
					if(confirmacao == 's'){
						sprintf(saldo_novo, "%.2f", conversao);
						printf("Novo Saldo: %s\n",saldo_novo);
						strcpy(p[numero_struct].reais, saldo_novo);
					
						sprintf(saldo_cripto, "%.2f", conversao2);
						strcpy(p[numero_struct].bitcoin, saldo_cripto);
						

						printf("Transa��o feita com sucesso.\n");
					}else{
						printf("Transa��o cancelada.\n");
					}
					
				}
			}else if(escolha == 2){
		
				compra = quantidade * (valor[0].Ethereum + valor[0].Ethereum* 0.01); // Cobra uma taxa de 1% na compra de ethereum
		
				if(atof(p[numero_struct].reais) < compra){
					printf("N�o possui dinheiro suficiente !!\n");
		
				}else{
					conversao = atof(p[numero_struct].reais) - compra;
					conversao2 = atof(p[numero_struct].Ethereum) + quantidade;
					
					ExibirInformacoesCompra("Ethereum", 0.01, compra, conversao, conversao2);
					
					printf("Deseja continuar?(s/n): \n");
					scanf(" %c", &confirmacao);
					getchar();
					if(confirmacao == 's'){
						sprintf(saldo_novo, "%.2f", conversao);
						printf("Novo Saldo: %s\n",saldo_novo);
						strcpy(p[numero_struct].reais, saldo_novo);
			
						sprintf(saldo_cripto, "%.2f", conversao2);
						strcpy(p[numero_struct].Ethereum, saldo_cripto);

						printf("Transa��o feita com sucesso.\n");
					}else{
						printf("Transa��o cancelada.\n");
					}
					
				}
		
			}else if(escolha == 3){
		
				compra = quantidade * (valor[0].Ripple + valor[0].Ripple* 0.01); // Cobra uma taxa de 1% na compra de ripple
		
				if(atof(p[numero_struct].reais) < compra){
		  			printf("N�o possui dinheiro suficiente !!\n");
		
				}else{
					conversao = atof(p[numero_struct].reais) - compra;
					conversao2 = atof(p[numero_struct].Ripple) + quantidade;
					
					ExibirInformacoesCompra("Ripple", 0.01, compra, conversao, conversao2);
					
					printf("Deseja continuar?(s/n): \n");
					scanf(" %c", &confirmacao);
					getchar();
					if(confirmacao == 's'){
						sprintf(saldo_novo, "%.2f", conversao);
						printf("Novo saldo: %s\n",saldo_novo);
						strcpy(p[numero_struct].reais, saldo_novo);
			
			            sprintf(saldo_cripto, "%.2f", conversao2);
						strcpy(p[numero_struct].Ripple, saldo_cripto);

						printf("Transa��o feita com sucesso.\n");
						
					}else{
						printf("Transa��o cancelada.\n");
					}
				}
		
			}else{
				printf("Escolha inv�lida\n");
			}		
		}
	}else{ //vender cripto
	
		printf("Qual moeda deseja vender?: \n");
		scanf("%d", &escolha);
		getchar();
		
		printf("Quantidade que deseja vender?: \n");
		scanf("%f", &quantidade);
		getchar();
		
		if(escolha == 1){
 
			venda = quantidade * (valor[0].bitcoin - valor[0].bitcoin* 0.03); // taxa de 3% para bitcoin --> venda
			
			
			if(atof(p[numero_struct].bitcoin) < quantidade){
				printf("N�o possui cripto suficiente !!\n");
			
			}else{
				conversao = atof(p[numero_struct].reais) + venda;
				conversao2 = atof(p[numero_struct].bitcoin)	- quantidade;
				
				ExibirInformacoesCompra("bitcoin", 0.03, venda, conversao, conversao2);
				
				printf("Deseja continuar?(s/n): \n");
				scanf(" %c", &confirmacao);
				getchar();
				if(confirmacao == 's'){
					sprintf(saldo_novo, "%.2f", conversao);
					printf("Novo Saldo: %s\n",saldo_novo);
					strcpy(p[numero_struct].reais, saldo_novo);
					
					sprintf(saldo_cripto, "%.2f", conversao2);
					strcpy(p[numero_struct].bitcoin, saldo_cripto);

					printf("Transa��o feita com sucesso.\n");
					
				}else{
					printf("Transa��o cancelada.\n");
				}
			}
		}else if(escolha == 2){
	
			venda = quantidade * (valor[0].Ethereum - valor[0].Ethereum* 0.02); // Cobra uma taxa de 2% na venda de ethereum
	
			if(atof(p[numero_struct].reais) < compra){
				printf("N�o possui dinheiro suficiente !!\n");
	
			}else{
				conversao = atof(p[numero_struct].reais) + venda;
				conversao2 = atof(p[numero_struct].Ethereum) - quantidade;
				
				ExibirInformacoesCompra("Ethereum", 0.02, venda, conversao, conversao2);
				
				printf("Deseja continuar?(s/n): \n");
				scanf(" %c", &confirmacao);
				getchar();
				if(confirmacao == 's'){
					sprintf(saldo_novo, "%.2f", conversao);
					printf("Novo Saldo: %s\n",saldo_novo);
					strcpy(p[numero_struct].reais, saldo_novo);
					
					sprintf(saldo_cripto, "%.2f", conversao2);
					strcpy(p[numero_struct].Ethereum, saldo_cripto);

					printf("Transa��o feita com sucesso.\n");
					
				}else{
					printf("Transa��o cancelada.\n");

				}
			}
	
		}else if(escolha == 3){
	
			venda = quantidade * (valor[0].Ripple - valor[0].Ripple* 0.01); // Cobra uma taxa de 1% na venda de ripple
	
			if(atof(p[numero_struct].reais) < compra){
	  			printf("N�o possui dinheiro suficiente !!\n");
	
			}else{
				conversao = atof(p[numero_struct].reais) + venda;
				conversao2 = atof(p[numero_struct].Ripple)	- quantidade;
				
				ExibirInformacoesCompra("Ripple", 0.01, venda, conversao, conversao2);
				
				printf("Deseja continuar?(s/n): \n");
				scanf(" %c", &confirmacao);
				getchar();
				if(confirmacao == 's'){
					sprintf(saldo_novo, "%.2f", conversao);
					printf("Novo saldo: %s\n",saldo_novo);
					strcpy(p[numero_struct].reais, saldo_novo);
					
		            sprintf(saldo_cripto, "%.2f", conversao2);
					strcpy(p[numero_struct].Ripple, saldo_cripto);
					
					printf("Transa��o feita com sucesso.\n");
				}else{
					printf("Transa��o cancelada.\n");
				}
			}
	
		}else{
			printf("Escolha inv�lida\n");
		}		
	}
}

void Consultarextrato(){
	printf("Hello World!!\n");
}


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


// MENU PRINCIPAL
int main() {
	setlocale(LC_ALL, "portuguese");

    cadastro *pessoas;
    pessoas = malloc(2 * sizeof(pessoas)); //mudar para 10
    
    achar_usuario(pessoas);
	login(pessoas);
	
	system("pause");
	return 0;
}
