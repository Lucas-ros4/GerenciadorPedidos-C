# Gerenciador de Pedidos em C

Este projeto é um sistema simples de **gerenciamento de pedidos** desenvolvido em **C**, utilizando arquivos binários para salvar os dados de forma persistente.  

Ele foi criado com o objetivo de praticar conceitos como:
- Estruturas (`struct`)
- Manipulação de arquivos binários (`fopen`, `fwrite`, `fread`, `fseek`)
- Criação de menus interativos
- Funções para CRUD (Create, Read, Update, Delete)
- Cálculo de **lucro líquido** automático

---

## Funcionalidades

- **Adicionar Pedido** – Insere novos pedidos com cálculo automático de custo, receita e lucro líquido.
- **Listar Pedidos** – Exibe todos os pedidos cadastrados.
- **Editar Pedido** – Permite atualizar os dados de um pedido existente.
- **Remover Pedido** – Remove um pedido pelo seu identificador (ID).
- **Backup Automático** – Cria uma cópia dos pedidos ao sair do programa.
- **Lucro Total** – Calcula e exibe o lucro líquido acumulado de todos os pedidos.

