# Banco de Exchange de Criptomoedas

## Gustavo Novais Cheida RA: 24.124.065-4
## Felipe Bechelli Prado RA: 24.124.002-7

# Objetivo do Projeto
O sistema tem como objetivo gerenciar contas de usuários, permitindo operações como compra e venda de criptomoedas, depósito e saque de valores, consulta de saldos e extratos, além de funcionalidades administrativas. <br />

# Compilação e observações: <br />
A forma de compilação recomendada é pelo REPLIT, uma plataforma virtual que permite rodar diversos tipos de linguagens de programação, voce só precisa criar sua conta e criar um REPL e escolha um nome de seu gosto e o template de C para o projeto , já que a liguagem do projeto é em c. <br />

#Cuidados: Depois de ter feito o projeto no replit e inserido a pasta do zip extraido nele, para garantir o funcionamento correto do código é necessário que voce insira a pasta que contem os arquivos no projeto ao invés dos arquivos separadamente !!! <br />


# Sistema de Gerenciamento de Criptomoedas

Um sistema em C para gerenciamento de contas financeiras e operações com criptomoedas. Permite aos usuários realizar operações como compra e venda de criptomoedas, consultar saldos, extratos, e realizar transações bancárias. Administradores têm acesso a funcionalidades avançadas para gerenciar os dados do sistema.  <br />

## Tabela de Conteúdo
- [Descrição](#descrição)
- [Funcionalidades](#funcionalidades)
- [Como Executar](#como-executar)

## Descrição

Este projeto foi desenvolvido para simular um sistema de gerenciamento de contas financeiras com suporte para operações envolvendo criptomoedas. Ele é modular, com cada funcionalidade implementada em arquivos separados, e utiliza persistência de dados por meio de arquivos de texto. 

O sistema foi projetado para uso em terminais e oferece um menu interativo para fácil navegação pelas operações.

## Funcionalidades

- **Gerenciamento de Usuários**:
  - Cadastro e login de usuários com autenticação.
  
- **Operações com Criptomoedas**:
  - Compra e venda de criptomoedas com cálculo automático de valores.
  - Adição de novas criptomoedas (apenas para administradores).

- **Consultas**:
  - Consulta de saldo em reais e criptomoedas.
  - Geração de extratos de transações.

- **Operações Bancárias**:
  - Depósito e saque de valores em reais.

- **Administração**:
  - Consulta de extratos gerais.
  - Atualização de dados de usuários e criptomoedas.

## Como Executar

### Requisitos
- Compilador C (MinGW, GCC, ou equivalente)
- Ambiente de desenvolvimento como Dev C++ ou terminal com suporte a `make`.

# As entradas do Banco estão em um arquivo txt chamado usuarios.txt, já está inserido 2 usuários testes para testar as funcionalidades, e como é possivel a entrada de novos investidores por meio das funcionalidades do administrador é melhor testar dentro do programa. <br />

## Usuários teste:
12345678901;Joao Silva;35123;882.00;bitcoin:0.5;Ethereum:1.2;Ripple:0.70 <br />
98765432100;Maria Souza;23456;2000.00;bitcoin:1.0;Ethereum:0.8;Ripple:0.9 <br />

## Administradores: 
12345678900;Felipe Prado;12345 <br />

OBS: só existe um administrador pois não tinha nada específicado no projeto que precisaria ter um cadastro de administradores. <br />
