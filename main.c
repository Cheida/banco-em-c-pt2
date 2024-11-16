#include "funcao.h"

// MENU PRINCIPAL
int main(){
	setlocale(LC_ALL, "portuguese");

	while (1){

		int res, tamanho_usuario = 0, tamanho_adm = 0;

		printf("+--------------------------+\n");
		printf("|BEM-VINDO AO BANCO CRIPTO |\n");	
		printf("|Qual menu deseja acessar ?|\n");
		printf("+--------------------------+\n");
		printf("|1. Investirdor            |\n");
		printf("|2. Administrador          |\n");
		printf("|3. Sair                   |\n");
		printf("|--------------------------|\n");
		scanf("%d", &res);
		getchar();

		// certo investidor
		cadastro *pessoas;
		pessoas = malloc(10 * sizeof(cadastro)); // max 10 usuarios
		tamanho_usuario = carregar_usuarios(pessoas);

		if (tamanho_usuario == 0) {
				printf("Nenhum usuário cadastrado ou erro ao carregar usuários.\n");
				free(pessoas);
				continue;
		}
		
		if (res == 1){

			login(pessoas, tamanho_usuario);
			atualizar_usuarios(pessoas, tamanho_usuario);

		} else if(res == 2){
			
			admin *tam;
			tam = malloc(6 * sizeof(admin)); // maximo de 6 administradores

			tamanho_adm = achar_admin(tam);
			printf("tamanho dos adm lidos: %d\n", tamanho_adm);
			login_adm(tam, tamanho_usuario, pessoas, tamanho_adm);
			free(tam);

		}else{
			
			atualizar_usuarios(pessoas, tamanho_usuario);
			free(pessoas);
			break;
		}
		free(pessoas);
	}	
	system("pause");
	return 0;
}

