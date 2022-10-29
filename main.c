#include <stdio.h>	       //Biblioteca padrão de entrada e saída
#include <stdlib.h>	       //Biblioteca padrão de funções e constantes básicas
#include <locale.h>	       //Permite a alteração da linguagem de exibição do Software
#include <conio.h>         //Disponibiliza mais opções de entrada e saída
#include <string.h>	 	   //Permite a manipulação de Strings
#include <mysqld_error.h>  //Permite a exibição de erros do MySQL
#include <mysql.h> 		   //Permite a execução de comandos do MySQL
#include <unistd.h> 	   //Disponibiliza outras funções como o "sleep"

//Variáveis para conexão com o banco de dados
#define HOST "127.0.0.1"
#define USER "root"
#define PASSWORD "password"
#define DATABASE "Projeto"

// Variáveis Comuns
unsigned int cont;
int nOpcao;
char nCpfLogin[11], sqlQuery[500], cargo[15], nSenha[25];

//Variável do cadastro de funcionários
char dadosFunc[6][150];

//Variáveis do cadastro de produtos
char dadosProd[6][150];
int qtdEstoque;

//Variável do cadastro de clientes
char dadosCli[10][150];

//Declaração das funções para uso global
void Menu(), cadProd(), cadFunc(), cadCli(), Cadastro(), prodEstoque(), Controle(), listaTransacoes();
int main();

MYSQL* conn()
{	
	// Variável MySql
	MYSQL *con = mysql_init(NULL);

	// Verificação da inicialização correta da variável de conexão (con)
	if (con == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    
    // Conexão com a base de dados. Ordem: Objeto MYSQL, servidor, usuário, senha, base de dados, porta, unix_socket (padrão NULL), client_flag (padrão 0)
    if (mysql_real_connect(con, HOST, USER, PASSWORD, DATABASE, 3306, NULL, 0) == NULL)
	{
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        system("PAUSE");
        exit(1);
    }
    
    return con;
}

int login(MYSQL *con, char cpf[11], char senha[25])
{
	//Variáveis MYSQL
	MYSQL_ROW linhas;
	MYSQL_RES *consultaMysql;
	
	//Criando uma consulta SQL com os devidos valores 
	sprintf(sqlQuery, "SELECT cargo_func FROM Funcionario WHERE senha_func = md5('%s') AND cpf_func = %s", senha, cpf);
	
	//Verificando se a consulta funcionou corretamente
	if(mysql_query(con, sqlQuery))
	{
		//Caso houver erros, mostrar na tela e encerrar a conexão
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
	}
	
	//Inserindo os dados da consulta em uma variável
	consultaMysql = mysql_store_result(con);
	
	//Se a consulta executar corretamente
	if(consultaMysql)
	{
		//Inserir todas as linhas que retornou na consulta em uma variável
		while((linhas = mysql_fetch_row(consultaMysql)) != NULL)
		{
			//Se não encontrar campos correspondendes retorna 0, caso encontre um campo retorna 1
			if(mysql_num_fields(consultaMysql) < 1)
				return 0;
			else
			{
				sprintf(cargo, linhas[0]);
				return 1;
			}
		}
	}
	
	return 0;
}

//Tela inicial
int main() 
{
	system("MODE con cols=100 lines=25");
	setlocale(LC_ALL, "Portuguese");
	system("title WireTech Server");
	system("cls");
	//Alterando o tamanho do console
	//system("MODE con cols=100 lines=25");
	
	printf("\n -------------- WireTech Server --------------");	

	printf("\n\n Digite o CPF (somente números): ");
	fflush(stdin);
	scanf("%s", nCpfLogin);	 
	
	printf("\n Digite a senha: ");
	scanf("%s", nSenha);	 
	
	//Verifica o cpf e senha digitados através da função Login. 
	//Se estiverem corretos entrará no software, caso contrário mostra uma mensagem e reinicia a página
	if(login(conn(), nCpfLogin, nSenha))
		Menu(cargo);
	else
	{
		printf("\n --------------------------------------------");
		printf("\n\t CPF ou Senha inválidos!!");
		sleep(1.85);
		main();
	}
	
	return 0;	
}

//Tela de Seleção das operações
void Menu(char cargo[15])
{
	system("cls");
	
	printf("\n ------------------ WireTech Server ----------------- \n\n");
	
	//Verificando os cargos e atribuindo suas funções
	if(strcmp(cargo, "Gerente") == 0)
	{
		printf(" [1] - Cadastro \n");
		printf(" [2] - Controle \n");
		printf(" [3] - Sair \n");
		printf("\n Selecione uma das opções acima para continuar: ");
		scanf("%d", &nOpcao);
		
		switch(nOpcao)
		{
			case 1: 	
				Cadastro();
				break;
				
			case 2:
				Controle();
				break;
				
			case 3: 
				system("cls");
				printf("\n ------------------ WireTech Server ----------------- \n\n");
				printf(" Obrigado por utilizar o Software, até mais!! \n\n");
				printf(" Pressione qualquer tecla para Sair...");
				getch();
				break;
	
			default: 
				system("cls");
				Menu(cargo);
				break;
		}
	}
	else
	{
		printf(" [1] - Controle \n");
		printf(" [2] - Sair \n");
		printf("\n Selecione uma das opções acima para continuar: ");
		scanf("%d", &nOpcao);
		
		switch(nOpcao)
		{
			case 1: 	
				Controle();
				break;
				
			case 2:
				system("cls");
				printf("\n ------------------ WireTech Server ----------------- \n\n");
				printf(" Obrigado por utilizar o Software, até mais!! \n\n");
				printf(" Pressione qualquer tecla para Sair...");
				getch();
				break;
	
			default: 
				system("cls");
				Menu(cargo);
				break;
		}
	}
}

//Tela de Seleção das exibições
void Controle()
{
	//Alterando o tamanho do console
	system("MODE con cols=100 lines=25");
    system("cls");

	printf("\n ------------------ WireTech Server ----------------- \n\n");
	
	printf(" [1] - Controle de Estoque \n");
	printf(" [2] - Transações Pendentes\n");
	printf(" [3] - Histórico de Transações\n");
	printf(" [4] - Voltar \n");
	printf("\n Selecione uma das opções acima para continuar: ");
	scanf("%d", &nOpcao);
	
	switch(nOpcao)
	{
		case 1: 	
			prodEstoque(conn());
			break;
			
		case 2:
			listaTransacoes(conn(), 0);
			break;
			
		case 3: 
			listaTransacoes(conn(), 1);
			break;

		case 4: 
			Menu(cargo);
			break;
			
		default: 
			system("cls");
			Controle();
			break;
	}
}

//Tela de Seleção dos Cadastros
void Cadastro()
{
	system("cls");
	
	printf("\n ------------------ WireTech Server ----------------- \n\n");
	
	printf(" [1] - Cadastro de Clientes \n");
	printf(" [2] - Cadastro de Funcionários \n");
	printf(" [3] - Cadastro de Produtos \n");
	printf(" [4] - Voltar \n");
	printf("\n Selecione uma das opções acima para continuar: ");
	scanf("%d", &nOpcao);
	
	switch(nOpcao)
	{
		case 1: 	
			cadCli(conn());
			break;
			
		case 2:
			cadFunc(conn());
			break;
			
		case 3: 
			cadProd(conn());
			break;

		case 4: 
			Menu(cargo);
			break;
			
		default: 
			system("cls");
			Cadastro();
			break;
	}
}

//Cadastro de Produtos
void cadProd(MYSQL *con)
{
	system("cls");
	
	printf("\n ---------------------------------- WireTech Server --------------------------------- \n");

	printf("\n *Para cadastrar novos produtos, preencha corretamente as informações abaixo.* \n\n");
	
	printf("\n Nome do Produto: ");
	scanf(" %[^\n]s", dadosProd[0]);
	
	printf(" Categoria do Produto: ");
	scanf(" %[^\n]s", dadosProd[1]);

	printf(" Valor de Custo em R$: ");
	scanf(" %s", dadosProd[2]);
	
	printf(" Quantidade de Estoque: ");
	scanf(" %d", &qtdEstoque);
	
	printf(" Url de Imagem do Produto: ");
	scanf(" %s", dadosProd[3]);
	
	printf(" Descrição: ");
	scanf(" %[^\n]s", dadosProd[4]);
	
	printf(" Link para o Cliente: ");
	scanf(" %s", dadosProd[5]);
	
	// Inserindo os dados digitados na tabela
    sprintf(sqlQuery, "INSERT INTO Produto (nome_produto, categoria_produto, valor_produto, estoque_produto, imagem_produto_path, descricao_produto, link_url) VALUES ('%s', '%s', %s, %d, '%s', '%s', '%s')", dadosProd[0], dadosProd[1], dadosProd[2], qtdEstoque, dadosProd[3], dadosProd[4], dadosProd[5]);
	
	//Enviando o comando pro banco e executando-o
	if (mysql_query(con, sqlQuery)) 
	{
        fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
	}
	
	//Encerrando a conexão com o banco (segurança)
	mysql_close(con);
	
	printf("\n ---------------------------------");
	printf("\n Produto cadastrado com sucesso!!");
	
	//A função sleep faz um "delay" na execução usando os segundos informados
	sleep(1.85);
	
	//Volta pra tela de Cadastros
	Cadastro();
}
 
//Cadastro de Funcionários 
void cadFunc(MYSQL *con)
{
	system("cls");
	
	printf("\n ---------------------------- WireTech Server --------------------------- \n");

	printf("\n *Para cadastrar novos funcionários, preencha as informações abaixo.* \n\n");
	
	printf("\n Nome: ");
	scanf(" %[^\n]s", dadosFunc[0]);

	printf(" CPF (somente números): ");
	scanf(" %[^\n]s", dadosFunc[1]);
	
	printf(" Data de Admissão (dd/mm/yyyy): ");
	scanf(" %s", dadosFunc[2]);
	
	printf(" Cargo: ");
	scanf(" %s", dadosFunc[3]);
	
	printf(" E-mail: "); 
	scanf(" %s", dadosFunc[4]);
	
	printf(" Senha: ");
	scanf(" %s", dadosFunc[5]);
	
	// Inserindo os dados digitados na tabela
    sprintf(sqlQuery, "INSERT INTO Funcionario (nome_func, cargo_func, cpf_func, dt_admissao, senha_func, email_func) VALUES ('%s', '%s', %s, STR_TO_DATE('%s',\"%%d/%%m/%%Y\"), md5('%s'), '%s')", dadosFunc[0], dadosFunc[3], dadosFunc[1], dadosFunc[2], dadosFunc[5], dadosFunc[4]);
	
	//Enviando o comando pro banco e executando-o
	if (mysql_query(con, sqlQuery)) 
	{
        fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
	}
	
	//Encerrando a conexão com o banco (segurança)
	mysql_close(con);
	
	printf("\n ---------------------------------");
	printf("\n Funcionário cadastrado com sucesso!!");
	
	//A função sleep faz um "delay" na execução usando os segundos informados
	sleep(1.85);
	
	//Volta pra tela de Cadastros
	Cadastro();
}

//Cadastro de Clientes
void cadCli(MYSQL *con)
{
	system("cls");
	
	printf("\n ---------------------------------- WireTech Server --------------------------------- \n");

	printf("\n *Para cadastrar novos clientes, preencha corretamente as informações abaixo.* \n\n");
	
	printf("\n Nome do Cliente: ");
	scanf(" %[^\n]s", dadosCli[0]);
	
	printf(" CPF (Somente números): ");
	scanf(" %[^\n]s", dadosCli[1]);
	
	printf(" Sexo: ");
	scanf(" %[^\n]s", dadosCli[2]);
	
	printf(" Telefone: ");
	scanf(" %[^\n]s", dadosCli[3]);
	
	printf(" Data de Nascimento (dd/mm/yyyy): ");
	scanf(" %[^\n]s", dadosCli[4]);
	
	printf(" E-mail: ");
	scanf(" %[^\n]s", dadosCli[5]);
	
	printf(" Cidade: ");
	scanf(" %[^\n]s", dadosCli[6]);
	
	printf(" CEP (somente números): ");
	scanf(" %[^\n]s", dadosCli[7]);
	
	printf(" Endereço: ");
	scanf(" %[^\n]s", dadosCli[8]);
	
	printf(" Senha: ");
	scanf(" %[^\n]s", dadosCli[9]);
	
	
	// Inserindo os dados digitados na tabela
    sprintf(sqlQuery, "INSERT INTO Cliente (nome_cliente, cpf_cliente, sexo_cliente, telefone_cliente, ano_nasc, email_cliente, cidade_cliente, endereco_cliente, cep_cliente, senha_cliente) VALUES ('%s', %s, '%s', %s, STR_TO_DATE('%s',\"%%d/%%m/%%Y\"), '%s', '%s', '%s', %s, '%s')",
					  dadosCli[0], dadosCli[1], dadosCli[2], dadosCli[3], dadosCli[4], dadosCli[5], dadosCli[6], dadosCli[8], dadosCli[7], dadosCli[9]);
	
	//Enviando o comando pro banco e executando-o
	if (mysql_query(con, sqlQuery)) 
	{
        fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
	}
	
	//Encerrando a conexão com o banco (segurança)
	mysql_close(con);
	
	printf("\n ---------------------------------");
	printf("\n Cliente cadastrado com sucesso!!");
	
	//A função sleep faz um "delay" na execução usando os segundos informados
	sleep(1.85);
	
	//Volta pra tela de Cadastros
	Cadastro();
}

void prodEstoque(MYSQL *con)
{
	//Variável comum
	char alterar, wordwrap[20];
	int novoEstoque, idEstoque;
		
	// Variáveis MySql
    MYSQL_FIELD *colunas;
    MYSQL_RES *consultaMysql;
    MYSQL_ROW linhas;
	
	//Alterando o tamanho do console
	system("MODE con cols=98 lines=40");
	
	system("cls");
	printf("\n ---------------------------------------- WireTech Server --------------------------------------- \n\n");
	printf("\t\t\t\t\tControle de Estoque \n");
	        
	//Faz a consulta no Banco de Dados
	if (mysql_query(con, "SELECT id_produto AS \"ID\", nome_produto AS \"Nome do Produto\", categoria_produto AS \"Categoria\", estoque_produto  AS \"Qtde\" from produto;"))
	{
        fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
	}
	
	//Insere os dados da consulta realizada em uma variável
	consultaMysql = mysql_store_result(con);
	
	//Verifica se a consulta foi executada com sucesso
	if(consultaMysql)
	{
		//Insere os dados das colunas/campos em uma variável
		colunas = mysql_fetch_fields(consultaMysql);
		
		//Formatação da tabela
		printf("\n\t +");
		for (cont = 0; cont < 7; cont++)
			printf("-----------");
		printf("-+\n");	
		
		//Para cada valor encontrado, exibe em tela tais valores
		for(cont = 0; cont < mysql_num_fields(consultaMysql); cont++)
		{
			//Exibe o conteúdo dos campos separados por tabulação
			if(cont == 0)
				printf("\t |  %s", (colunas[cont]).name);	
			else if(cont == 1)
				printf("%s   ", (colunas[cont]).name);	
			else if(cont == 2)
				printf("%s ", (colunas[cont]).name);
			else 
				printf("%s\t|", (colunas[cont]).name);
				
			//Caso haja mais de uma coluna, separar por tabulação
			if(mysql_num_fields(consultaMysql) > 1)
			{
				if(cont == 0 || cont == 1 || cont == 2) 
					printf("\t|\t");
			}
		}
		
		//Formatação da tabela
		printf("\n\t +");
		for (cont = 0; cont < 7; cont++)
			printf("-----------");
		printf("-+\n");	
		
		//Verifica as linhas da consulta e realiza uma ação enquanto restar dados
		while((linhas = mysql_fetch_row(consultaMysql)) != NULL)
		{	
			//Para cada linha encontrada, exibe em tela seus respectivos valores na ordem da consulta realizada
			for (cont = 0; cont < mysql_num_fields(consultaMysql); cont++)
			{
				//Formatação visual da consulta no console
				//Exibe em tela os valores das linhas separados por tabulação 
				
				if(cont == 0)
				{
					//ID
					if(strlen(linhas[0]) >= 2)
						printf("\t |   %s  ", linhas[cont]);
					else
						printf("\t |   %s \t ", linhas[cont]);
				
				}
				else if (cont == 1)
				{
					//Nome do Produto
					if(strlen(linhas[1]) < 6)
						printf("\t%s \t\t ", linhas[cont]);
					else if(strlen(linhas[1]) < 15)
						printf("\t%s \t ", linhas[cont]);
					else if(strlen(linhas[1]) < 21)
						printf("\t%s  ", linhas[cont]);
					else 
					{
						memmove(wordwrap, linhas[cont], 20);
						printf("\t%s...  ", wordwrap);
					}
				}
				else if(cont == 2)
				{
					//Categoria
				    if(strlen(linhas[1]) < 21)
						printf("\t\t%s \t", linhas[cont]);
					else	
						printf("\t%s \t", linhas[cont]);
				}
				else
				{
					//Quantidade em Estoque
					if(strlen(linhas[2]) <= 6) 
						printf("\t\t%s \t|", linhas[cont]);
					else 
						printf("\t%s \t|", linhas[cont]);
				}
			}
			printf("\n");
		}
		
		//Formatação da tabela
		printf("\t +");
		for (cont = 0; cont < 7; cont++)
		printf("-----------");
		printf("-+\n");	
	}
	printf("\n\n --------------------------------");
	printf("\n Deseja alterar o estoque? (S/N) ");
	fflush(stdin);
	scanf("%c", &alterar);
	
	if(alterar == 's' || alterar == 'S')
	{
		printf("\n ID do produto: ");
		fflush(stdin);
		scanf("%d", &idEstoque);
		
		printf(" Nova quantidade em estoque: ");
		scanf("%d", &novoEstoque);
		
		// Alterando os dados digitados na tabela
    	sprintf(sqlQuery, "UPDATE Produto SET estoque_produto = %d WHERE id_produto = %d", novoEstoque, idEstoque); 
					  	   
		//Enviando o comando pro banco e executando-o
		if (mysql_query(con, sqlQuery)) 
		{
	        fprintf(stderr, "%s\n", mysql_error(con));
			mysql_close(con);
		}
		
		printf("\n ---------------------------------");
		printf("\n Estoque alterado com sucesso!!");
		
		//A função sleep faz um "delay" na execução usando os segundos informados
		sleep(1.85);
		
		//Atualiza a página Estoque com o valor atualizado
		prodEstoque(conn());
	}
	else
		Controle();
		
	//Libera a variável utilizada e encerra/exclui a consulta
	mysql_free_result(consultaMysql);
    
    //Fechando a conexão com o banco de dados
    mysql_close(con);
}

void listaTransacoes(MYSQL* con, int status)
{
	char autorizar, wordwrap[9], descricao[38];
	int id_transacao;	
	
	// Variáveis MySql
    MYSQL_FIELD *colunas;
    MYSQL_RES *consultaMysql;
    MYSQL_ROW linhas;
	
	//Modifica o tamando do cmd 
	system("MODE con cols=152 lines=30");
		
	system("cls");
	printf("\n ---------------------------------------------------------------- WireTech Server -------------------------------------------------------------------- \n\n");

	if(status == 0)
		printf("\t\t\t\t\t\t\t      Controle de Transações \n");
	else
		printf("\t\t\t\t\t\t\t      Histórico de Transações \n");
	
	sprintf(sqlQuery, "SELECT Transacao.id_transacao AS \"ID\", Cliente.cpf_cliente AS \"CPF\", Cliente.nome_cliente AS \"Cliente\", Pagamento.nome_pagamento AS \"Pagamento\", Transacao.valor_total AS \"Valor\", DATE_FORMAT(Transacao.dt_transacao, '%%d/%%m/%%Y') AS \"Emissao\", Transacao.descricao_transacao AS \"Descricao\" FROM Transacao INNER JOIN Cliente ON Transacao.id_cliente_selecionado = Cliente.id_cliente INNER JOIN Pagamento ON Transacao.tipo_pagamento_selecionado = Pagamento.tipo_pagamento WHERE Transacao.status_transacao = %d", status);
	
	//Faz a consulta no Banco de Dados
	if (mysql_query(con, sqlQuery))	
	{
        fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
	}
	
	//Insere os dados da consulta realizada em uma variável
	consultaMysql = mysql_store_result(con);
	
	//Verifica se a consulta foi executada com sucesso
	if(consultaMysql)
	{
		//Insere os dados das colunas/campos em uma variável
		colunas = mysql_fetch_fields(consultaMysql);
		
		//Formatação da tabela
		printf("\n\t +");
		for (cont = 0; cont < 12; cont++)
			printf("-----------");
		printf("+\n");
		
		//Para cada valor encontrado, exibe em tela tais valores
		for(cont = 0; cont < mysql_num_fields(consultaMysql); cont++)
		{
			//Exibe o conteúdo dos campos separados por tabulação
			if(cont == 0)
				printf("\t | %s", (colunas[cont]).name);	
			else if(cont == 1 || cont == 2)
				printf("     %s     ", (colunas[cont]).name);	
			else if(cont == 3)
				printf("   %s   ", (colunas[cont]).name);	
			else if(cont == 4 || cont == 5)
				printf("   %s   ", (colunas[cont]).name);	
			else
				printf("\t\t    %s\t\t     ", (colunas[cont]).name);	
				
			//Caso haja mais de uma coluna
			if(mysql_num_fields(consultaMysql) > 1)
			{
					printf(" | ");
			}
		}
		
		//Formatação da tabela
		printf("\n\t +");
		for (cont = 0; cont < 12; cont++)
			printf("-----------");
		printf("+\n");
		
		//Verifica as linhas da consulta e realiza uma ação enquanto restar dados
		while((linhas = mysql_fetch_row(consultaMysql)) != NULL)
		{	
			//Para cada linha encontrada, exibe em tela seus respectivos valores na ordem da consulta realizada
			for (cont = 0; cont < mysql_num_fields(consultaMysql); cont++)
			{
				//Formatação visual da consulta no console
				//Exibe em tela os valores das linhas separados por tabulação 
				
				if(cont == 0)
				{
					//ID
					if(strlen(linhas[0]) >= 2)
						printf("\t | %s \t ", linhas[cont]);
					else
						printf("\t | %s \t ", linhas[cont]);
				
				}
				else if (cont == 1)
				{
					//CPF do Cliente
					printf(" %s  ", linhas[cont]);
				}
				else if(cont == 2)
				{
					//Nome do Cliente	
					if(strlen(linhas[cont]) < 10)
						printf("\t   %s \t", linhas[cont]);
					else 
					{
						memmove(wordwrap, linhas[cont], 10);
						printf("\t   %s...", wordwrap);
					}
				}
				else if(cont == 3)
				{
					//Tipo de Pagamento
					printf("\t  %s\t", linhas[cont]);
				}
				else if(cont == 4)
				{
					//Valor Total
					if(strlen(linhas[cont]) < 5)
						printf("\tR$%s     ", linhas[cont]);
					else if(strlen(linhas[cont]) == 5)
						printf("\tR$%s   ", linhas[cont]);
					else if(strlen(linhas[cont]) < 7)
						printf("\tR$%s  ", linhas[cont]);
					else 
						printf("\tR$%s ", linhas[cont]);
				}
				else if(cont == 5)
				{
					//Data de Emissão
					printf("    %s    ", linhas[cont]);
				}
				else
				{
					//Descrição
					if(strlen(linhas[cont]) <= 6)
						printf(" %s\t\t\t\t\t      |", linhas[cont]);
					else if(strlen(linhas[cont]) < 15)
						printf(" %s\t\t\t\t      |", linhas[cont]);
					else if(strlen(linhas[cont]) < 23) 
						printf(" %s\t\t\t      |", linhas[cont]);
					else if(strlen(linhas[cont]) <= 30)
						printf(" %s\t\t      |", linhas[cont]);
					else if(strlen(linhas[cont]) < 32)
						printf(" %s\t      |", linhas[cont]);
					else
					{						
						memmove(descricao, linhas[cont], 37);
						printf(" %s... |", descricao);
					}
					
				}
			}
			printf("\n");
		}
		
		//Formatação da tabela
		printf("\t +");
		for (cont = 0; cont < 12; cont++)
			printf("-----------");
		printf("+\n");
	}
	
	if(!status)
	{
		printf("\n\n ----------------------------------------");
		printf("\n Deseja autorizar alguma transação? (S/N) ");
		fflush(stdin);
		scanf("%c", &autorizar);
		
		if(autorizar == 's' || autorizar == 'S')
		{
			printf("\n ID da transação: ");
			fflush(stdin);
			scanf("%d", &id_transacao);
		
			printf("\n Confira todos os dados corretamente, esta operação não poderá ser alterada posteriormente.");
			printf("\n Deseja realmente finalizar esta transação? (S/N) ");
			fflush(stdin);
			scanf("%c", &autorizar);
			
			if(autorizar == 'S' || autorizar == 's')
			{
				//Faz a alteração no Banco de Dados
	    		sprintf(sqlQuery, "UPDATE Transacao SET status_transacao = 1 WHERE id_transacao = %d", id_transacao); 
	    	
				if (mysql_query(con, sqlQuery))	
				{
			        fprintf(stderr, "%s\n", mysql_error(con));
					mysql_close(con);
				}
				
				printf("\n ----------------------------------");
				printf("\n Transação finalizada com sucesso!!");
				
				//A função sleep faz um "delay" na execução usando os segundos informados
				sleep(1.85);
				
				//Atualiza a página de transações com resultado alterado
				listaTransacoes(conn(), status);	
			}
			else
				listaTransacoes(conn(), status);
		}
		else
			Controle();
	}
	else
	{
		printf("\n\n ---------------------");
		printf("\n Deseja voltar? (S/N) ");
		fflush(stdin);
		scanf("%c", &autorizar);
		
		if(autorizar == 's' || autorizar == 'S')
		{
			Controle();
		}
		else
			listaTransacoes(conn(), 1);
	}
}
