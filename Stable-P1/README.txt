INF1715 - Compiladores
Professor: Roberto Ierusalimschy


Rafael Augusto Gaseta França 	- 1421436
Daniela Brazão Maksound			- 1321873


1) Requisitos
	bash
	make
	gcc
	flex
	diff


2) Decisões de projeto
	2.1) Warnings
	Warning é notificado mas não aborta o LEX.
	No monga.lex é possível desativar os warnings editando _SHOW_WARNINGS 1 para 0
	
	O unico warning gerado é quando simbolos não esperados são encontrados.
	Estes simbolos geram token com o proprio codigo ASCII.
	O tratamento deve ser feiro em outro nivel.
	
	2.2) Error ( Fatal )
	-Comentários e strings não fechados ao final do arquivo
	-Strings não fechato ao final da linha
	-Escapes invalidos
	-Plics que não contem sequencias conhecidas
	
	2.3) Plics
	Escapes e caracteres entre plics são convertidos para seu inteiro correspondente em ASCII


3) Testes
	3.1) Conceito
	O sucesso ou falha de um teste não está vinculado ao sucesso ou falha do LEX.
	Ou seja, se o erro no LEX for esperado pelo teste, o teste tem sucesso.
	Generalizando: o teste tem sucesso quando o resultado no LEX é o resperado pelo teste.
	Obs.: Para "testar o teste", um dos testes, o "teste_que_falha", falha propositalmente.
	
	O teste consiste em "parsear" um arquivo de entrada com um programa, o monga.out.
	O monga.out utiliza o yylex do flex e gera um arquivo *.tkn
	Os tokens de multi simbolos são escritos como seu "ENUM"
	Ao final, o arquivo *.tkn é comparado com o *.gab correspondente com o programa "diff"
	
	3.2) Teste geral de funcionamento
	Comando: make Lex
	Monta tudo desde o *.lex e ao final executa um teste geral, o "geral"
	
	3.3) Testes do LEX
	Comando: make LexTestes
	Faz tudo que o "make Lex" faz, além disso executa todos os testes da pasta "testes_lex"
	
	
	
	
	
