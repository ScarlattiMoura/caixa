# 🛒 Supermarket Management System

Um sistema simples de gerenciamento de supermercado feito em **C** utilizando **Ncurses** para a interface de terminal.  
Permite gerenciar **Produtos**, **Funcionários**, **Estabelecimento** e realizar **Pagamentos** (com nota fiscal fictícia).

---

## ✨ Funcionalidades

- **Produtos**
  - Cadastrar produto
  - Buscar produto
  - Modificar produto
  - Listar produtos
  - Deletar produto

- **Funcionários**
  - Cadastrar funcionário
  - Buscar funcionário
  - Modificar funcionário
  - Listar funcionários
  - Deletar funcionário

- **Estabelecimento**
  - Cadastrar dados do supermercado
  - Modificar dados
  - Visualizar dados

- **Pagamento**
  - Selecionar funcionário atendente
  - Escolher produtos disponíveis
  - Definir forma de pagamento (Dinheiro / Cartão / Pix)
  - Gerar nota fiscal fictícia
  - Registrar venda em arquivo

---

## 🏗 Estrutura de Pastas

```bash
caixa/
├── employee/
│   ├── employee.c
│   └── employee.h
├── establishment/
│   ├── establishment.c
│   └── establishment.h
├── items/
│   ├── items.c
│   └── items.h
├── main/
│   └── main.c
├── menu/
│   ├── menu.c
│   └── menu.h
├── payment/
│   ├── payment.c
│   └── payment.h
├── registration/
│   ├── items.txt
│   ├── employee.txt
│   ├── establishment.txt
│   └── sales.txt
├── Makefile
└── README.md

## 📦 Pré-requisitos

Antes de compilar o projeto, você precisa ter:

    Sistema Linux

    Compilador GCC instalado

    Biblioteca Ncurses instalada

Instalar GCC e Ncurses no Ubuntu/Debian

sudo apt update
sudo apt install build-essential libncurses5-dev libncursesw5-dev


## ⚙️ Como compilar o projeto

Para compilar usando o Makefile, basta rodar:

make

Isso vai gerar o executável chamado ./caixa.

Se quiser limpar os arquivos compilados:

make clean

