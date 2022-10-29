CREATE DATABASE Projeto;
USE Projeto;

CREATE TABLE Funcionario(
id_func INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
nome_func VARCHAR(255) NOT NULL,
cargo_func VARCHAR(255) NOT NULL,
cpf_func DOUBLE NOT NULL,
dt_admissao DATE NOT NULL,
senha_func VARCHAR(255) NOT NULL,
email_func VARCHAR(255) NOT NULL
);

CREATE TABLE Cliente(
id_cliente INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
nome_cliente VARCHAR(255) NOT NULL,
cpf_cliente DOUBLE NOT NULL,
sexo_cliente VARCHAR(9),
telefone_cliente DOUBLE NOT NULL,
ano_nasc DATE NOT NULL,
email_cliente VARCHAR(255) NOT NULL,
cidade_cliente VARCHAR(255) NOT NULL,
endereco_cliente VARCHAR(255) NOT NULL,
cep_cliente INT NOT NULL,
senha_cliente VARCHAR(255) NOT NULL
);

CREATE TABLE Produto(
id_produto INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
nome_produto VARCHAR(255) NOT NULL,
categoria_produto VARCHAR(255) NOT NULL,
valor_produto FLOAT NOT NULL,
estoque_produto INT NOT NULL,
descricao_produto VARCHAR(255),
link_url VARCHAR(255) NOT NULL,
imagem_produto_path VARCHAR(255)
);

CREATE TABLE Pagamento(
tipo_pagamento INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
nome_pagamento VARCHAR(255) NOT NULL
);

CREATE TABLE Transacao(
id_transacao INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
status_transacao BOOLEAN NOT NULL,
valor_total FLOAT NOT NULL,
dt_transacao DATE NOT NULL,
descricao_transacao VARCHAR(255) NOT NULL,
id_func_selecionado INT,
id_cliente_selecionado INT NOT NULL,
tipo_pagamento_selecionado INT NOT NULL,
CONSTRAINT fk_funcionario FOREIGN KEY(id_func_selecionado) REFERENCES Funcionario(id_func),
CONSTRAINT fk_cliente FOREIGN KEY(id_cliente_selecionado) REFERENCES Cliente(id_cliente),
CONSTRAINT fk_tipopagamento FOREIGN KEY(tipo_pagamento_selecionado) REFERENCES Pagamento(tipo_pagamento)
);

SELECT * From Cliente;
SELECT * From Funcionario;
SELECT * From Pagamento;
SELECT * From Produto;
SELECT * From Transacao;

ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'password';
flush privileges
