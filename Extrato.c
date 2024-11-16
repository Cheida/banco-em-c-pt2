#include "funcao.h"


int salvar_extrato(char cpf[], char tipo[], char moeda[], float *valor_mudanca, float *quantidade, char sinal, int taxa){

	FILE *arquivo;
	arquivo = fopen("banco-em-c-pt2-main/extratos.txt", "a"); // adicionar no arquivo somente

	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo !!\n");
		return 1;
	}

	char data[11];
	obterDataAtual(data); // funcao para obter data

	// "%s; %s; %s; %s; %f; %f; %c; %f\n", cpf, data, tipo, moeda, quantidade, valor_mudanca, sinal, taxa
	//  DATA -------- Tipo -- Moeda --- Saldo(Moeda) --- sinal -- valor_mudanca --- moeda (sinal) quantidade;
	// 12/09/2024 --> venda: bitcoin | Saldo(moeda): (+ ou -) quantidade | moeda: (+ ou -) valor-final| taxa: taxa;
	fprintf(arquivo, "%s ; %s ; %s ; %s ;%f;%f; %c ;%d \n", cpf, data, tipo, moeda, *valor_mudanca, *quantidade, sinal, taxa);

	fclose(arquivo);
	return 0;
}

int Consultarextrato(cadastro *p, int index) { 

    FILE *arquivo;

    arquivo = fopen("banco-em-c-pt2-main/extratos.txt","r"); 

    if(arquivo == NULL){
    	printf("Erro ao abrir o arquivo !!!\n");
    	return 1;
	}

	int verificador = 0;
	char linhas[255];
	
	while(fgets(linhas, 255 ,arquivo) != NULL){
		char cpf_linhas[12], moedas[12], tipo[20], data[11], sinal;
		float valor_mudanca, quantidade;
		int taxa;

		// valor_mudanca -- > novo saldo para a criptomoeda
		// quantidade -- > quantidade pedida
		// sinal -- > se comprar + se vender -
		// taxa -- > taxa referente ao tipo de transacao 
		
		int result = sscanf(linhas, "%s ; %s ; %s ; %s ;%f;%f; %c ;%d \n", cpf_linhas, data, tipo, moedas, &valor_mudanca, &quantidade, &sinal, &taxa); 
	
		if (result == 8 && strcmp(cpf_linhas, p[index].cpf) == 0) {
            verificador++;
            printf("%s --> %s: %s | Saldo(%s): %c %.2f | %s: %.2f | Taxa: %d \n",
                   data, tipo, moedas, moedas, sinal, quantidade, moedas, valor_mudanca, taxa);

        }
	}

	if(verificador == 0){
		printf("Nenhuma transação realizada.\n");
	}
	return 0;
}
