#ifndef funcao_h
#define funcao_h

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>


// EU DEIXEI OS DIRETORIOS DOS ARQUIVOS QUANDO ABRE ASSIM: banco-em-c-pt2-main/nome_arquivo.txt <-- mudar se entrar na pasta

typedef struct cadastro {
    char cpf[12];
    char nome[100];
    char senha[10];
    char reais[20];
    char cripto_nome[10][20];
    char cripto_saldo[10][20];
} cadastro;


typedef struct moeda {
    int numero;             // Número da moeda (identificador no arquivo)
    char nome[20];          // Nome da criptomoeda
    float valor;            // Valor da moeda em reais
    float taxa_compra;      // Taxa de compra em porcentagem 
    float taxa_venda;       // Taxa de venda em porcentagem 
} moeda;

typedef struct atualizar_cripto{
    int numero;
    char nome[50];
    float cripto;
    float taxa_compra;
    float taxas_venda;
} atualizar_cripto;

typedef struct admin{
    char cpf[12];
    char nome[255];
    char senha[10];
}admin;


int achar_usuario(cadastro *p);
int login(cadastro *p, int tamanho_usuario);
int menu(cadastro *p, int index);
void Consultarsaldo(cadastro *p, int index);
int Consultarextrato(cadastro *p, int index);
int salvar_extrato(char cpf[], char tipo[], char moeda[], float *valor_mudanca, float *quantidade, char sinal, int taxa);
void Depositar(cadastro *p, int index);
void Sacar(cadastro *p, int index);
int comprarcripto(cadastro *p, int numero_struct);
int vendercripto(cadastro *p, int numero_struct);
void limparstring(char *array);
void obterDataAtual(char *data);
void ExibirInformacoesCompra(const char* nomeMoeda, float taxa, float valorCompra, float saldoNovo, float saldoCripto);
int Atualizar();

int login_adm(admin *tam, int tamanho_adm, cadastro *pessoas, int tamanho_usuario);
int achar_admin(admin *tam);
int menu_admin(admin *tam, cadastro *pessoas, int tamanho_usuario);
void cadastrar_investidor(cadastro *pessoas, int *total_usuarios);
void excluir_investidor(cadastro *usuarios, int tamanho_usuarios);
void consultar_saldo_de_um_Investidor(cadastro *p, int tamanho);
void Consultar_Extrato_adm();
int carregar_usuarios(cadastro *pessoas);
int atualizar_usuarios(cadastro *p, int tamanho_usuario);
int adicionar_cripto();
int remover_cripto();


#endif
