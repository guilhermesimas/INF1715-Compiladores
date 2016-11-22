PARAM = -g

lexTestFolder = ./testes_p1_lex/
lexFilesA = $(wildcard $(lexTestFolder)*.in)
lexFilesB = $(patsubst $(lexTestFolder)%,%,$(lexFilesA))
lexFileNames = $(patsubst %.in,%,$(lexFilesB))

gramTestFolder = ./testes_p2_gramatica/
gramFilesA = $(wildcard $(gramTestFolder)*.monga)
gramFilesB = $(patsubst $(gramTestFolder)%,%,$(gramFilesA))
gramFileNames = $(patsubst %.monga,%,$(gramFilesB))

astTestFolder = ./testes_p3_ast/
astFilesA = $(wildcard $(gramTestFolder)*.monga)
astFilesB = $(patsubst $(gramTestFolder)%,%,$(gramFilesA))
astFileNames = $(patsubst %.monga,%,$(gramFilesB))

all:  mainp3


LexTestes: header mainp1
	@echo " "	
	@echo "LEX: Executando um teste generico:"
	@echo " "	
	
	@echo " "	
	@echo "TESTES NAO ATUALIZADOS PARA ESSE BUILD"
	@echo "para fazer os testes do lexico, use a build 1 ou 2"	
	@echo " "	



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
	
	
	
ASTTestes1: header mainp3
	@$(foreach fileName, $(astFileNames) , (\
		printf "\n\n";\
		echo -e "Teste '"$(fileName)"' iniciado!";\
		./main_p3.out <$(astTestFolder)$(fileName).monga >$(astTestFolder)$(fileName).out;\
		if [ $$? -eq 0 ];\
		then \
			echo -e "\e[42mTeste '"$(fileName)"' bem sucedido!\e[0m" ;\
		else \
			echo -e "\e[41mTeste '"$(fileName)"' FALHOU!\e[0m" ;\
		fi;\
	);)
	
	
	
ASTTestes2: header mainp3b
	@$(foreach fileName, $(astFileNames) , (\
		printf "\n\n";\
		echo -e "Teste '"$(fileName)"' iniciado!";\
		./main_p3b.out <$(astTestFolder)$(fileName).monga;\
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
	
	@echo " "	
	@echo "TESTES NAO ATUALIZADOS PARA ESSE BUILD"
	@echo "para fazer os testes do lexico, use a build 1 ou 2"	
	@echo " "	
	

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
	
	
AST: header mainp3b
	@echo " "	
	@echo "YACC, gramatica: Executando um teste generico:"
	@echo " "	
	
	./main_p3b.out <$(astTestFolder)geral.monga
		
	@if [ $$? -eq 0 ] ; then \
		echo -e "\e[42mTeste bem sucedido!\e[0m" ;\
	else \
		echo -e "\e[41mTeste FALHOU!\e[0m" ;\
	fi;\


mainp1: header monga main_p1.c 
	@echo " "
	@echo "Compilando a main_p1 e ligando com o lex.yy:"
	gcc $(PARAM) -o main_p1.out lex.yy.o main_p1.c


mainp2: header monga main_p2.c 
	@echo " "
	@echo "Compilando a main_2 e ligando com o lex.yy e tab:"
	gcc $(PARAM) -o main_p2.out lex.yy.o monga.tab.o main_p2.c 


mainp3: header absSyntaxTree types monga main_p2.c 
	@echo " "
	@echo "Compilando a main_3 e ligando:"
	gcc $(PARAM) -o main_p3.out absSyntaxTree.o types.o lex.yy.o monga.tab.o main_p3.c 
	

mainp3b: header absSyntaxTree types monga main_p2.c 
	@echo " "
	@echo "Compilando a main_3b e ligando:"
	gcc $(PARAM) -o main_p3b.out absSyntaxTree.o types.o lex.yy.o monga.tab.o main_p3b.c 


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
	gcc $(PARAM) -c lex.yy.c monga.tab.c


absSyntaxTree: monga absSyntaxTree.c
		gcc  $(FLAGS) -c absSyntaxTree.c 
	
		
types: monga types.c
		gcc  $(FLAGS) -c types.c 	


header:
	@clear
	@echo " "	
	@date
	@echo " "		

	
	
	
