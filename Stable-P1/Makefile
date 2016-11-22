PARAM = -g

lexTestFolder = ./testes_lex/
lexFilesA = $(wildcard $(lexTestFolder)*.in)
lexFilesB = $(patsubst $(lexTestFolder)%,%,$(lexFilesA))
lexFileNames = $(patsubst %.in,%,$(lexFilesB))

all:  main 

LexTestes: header main
	@$(foreach fileName, $(lexFileNames) , (\
		printf "\n\n";\
		echo -e "Teste '"$(fileName)"' iniciado!";\
		./monga.out <$(lexTestFolder)$(fileName).in >$(lexTestFolder)$(fileName).tkn;\
		diff $(lexTestFolder)$(fileName).tkn $(lexTestFolder)$(fileName).gab;\
		if [ $$? -eq 0 ];\
		then \
			echo -e "\e[42mTeste '"$(fileName)"' bem sucedido!\e[0m" ;\
		else \
			echo -e "\e[41mTeste '"$(fileName)"' FALHOU!\e[0m" ;\
		fi;\
	);)


Lex: header main 
	@echo " "	
	@echo "Executando um teste generico:"
	@echo " "	
	
	./monga.out <./testes_lex/geral.in >./testes_lex/geral.tkn
	
	@echo " "	
	@echo "Comparando resultados:"
	@echo " "	
		
	diff ./testes_lex/geral.tkn ./testes_lex/geral.gab
	@if [ $$? -eq 0 ] ; then echo "Teste ok!" ; fi


main: header monga monga.c 
	@echo " "
	@echo "Compilando a main e ligando com o lex.yy:"
	gcc $(PARAM) -o monga.out lex.yy.o monga.c


lexcode: header monga.lex
	@echo " " 
	@echo "Gerando o lex.yy.c:"
	flex monga.lex

	
monga: header lexcode
	@echo " "
	@echo "Compilando o lex.yy.c:"
	gcc $(PARAM) -c lex.yy.c
	

header:
	@clear
	@echo " "	
	@date
	@echo " "		
