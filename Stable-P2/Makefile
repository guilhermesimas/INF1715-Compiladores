PARAM = -g

lexTestFolder = ./testes_p1_lex/
lexFilesA = $(wildcard $(lexTestFolder)*.in)
lexFilesB = $(patsubst $(lexTestFolder)%,%,$(lexFilesA))
lexFileNames = $(patsubst %.in,%,$(lexFilesB))

gramTestFolder = ./testes_p2_gramatica/
gramFilesA = $(wildcard $(gramTestFolder)*.monga)
gramFilesB = $(patsubst $(gramTestFolder)%,%,$(gramFilesA))
gramFileNames = $(patsubst %.monga,%,$(gramFilesB))


all:  mainp2


LexTestes: header mainp1
	@$(foreach fileName, $(lexFileNames) , (\
		printf "\n\n";\
		echo -e "Teste '"$(fileName)"' iniciado!";\
		./main_p1.out <$(lexTestFolder)$(fileName).in >$(lexTestFolder)$(fileName).tkn;\
		diff $(lexTestFolder)$(fileName).tkn $(lexTestFolder)$(fileName).gab;\
		if [ $$? -eq 0 ];\
		then \
			echo -e "\e[42mTeste '"$(fileName)"' bem sucedido!\e[0m" ;\
		else \
			echo -e "\e[41mTeste '"$(fileName)"' FALHOU!\e[0m" ;\
		fi;\
	);)



YaccTestes1: header mainp2
	@$(foreach fileName, $(gramFileNames) , (\
		printf "\n\n";\
		echo -e "Teste '"$(fileName)"' iniciado!";\
		./main_p2.out <$(gramTestFolder)$(fileName).monga ;\
		if [ $$? -eq 0 ];\
		then \
			echo -e "\e[42mTeste '"$(fileName)"' bem sucedido!\e[0m" ;\
		else \
			echo -e "\e[41mTeste '"$(fileName)"' FALHOU!\e[0m" ;\
		fi;\
	);)


Lex: header mainp1 
	@echo " "	
	@echo "LEX: Executando um teste generico:"
	@echo " "	
	
	./main_p1.out <$(lexTestFolder)geral.in >$(lexTestFolder)geral.tkn
	
	@echo " "	
	@echo "Comparando resultados:"
	@echo " "	
		
	diff $(lexTestFolder)geral.tkn $(lexTestFolder)geral.gab

	@if [ $$? -eq 0 ] ; then \
		echo -e "\e[42mTeste bem sucedido!\e[0m" ;\
	else \
		echo -e "\e[41mTeste FALHOU!\e[0m" ;\
	fi;\
	

Yacc: header mainp2
	@echo " "	
	@echo "YACC, gramatica: Executando um teste generico:"
	@echo " "	
	
	./main_p2.out <$(gramTestFolder)geral.monga	
		
	@if [ $$? -eq 0 ] ; then \
		echo -e "\e[42mTeste bem sucedido!\e[0m" ;\
	else \
		echo -e "\e[41mTeste FALHOU!\e[0m" ;\
	fi;\


mainp1: header monga main_p1.c 
	@echo " "
	@echo "Compilando a main_p1 e ligando com o lex.yy:"
	gcc $(PARAM) -o main_p1.out lex.yy.o main_p1.c


mainp2: header monga main_p1.c 
	@echo " "
	@echo "Compilando a main_2 e ligando com o lex.yy e tab:"
	gcc $(PARAM) -o main_p2.out lex.yy.c monga.tab.c main_p2.c


lexcode: header monga.lex
	@echo " " 
	@echo "Gerando o lex.yy.c:"
	flex monga.lex
	
	
yacccode: header monga.y
	@echo " " 
	@echo "Gerando o monga.tab.c e monga.tab.h:"
	bison -d monga.y

	
monga: header lexcode yacccode
	@echo " "
	@echo "Compilando o lex.yy.c:"
	gcc $(PARAM) -c lex.yy.c
	@echo "Compilando o monga.tab.c:"
	gcc $(PARAM) -c monga.tab.c
	

header:
	@clear
	@echo " "	
	@date
	@echo " "		
