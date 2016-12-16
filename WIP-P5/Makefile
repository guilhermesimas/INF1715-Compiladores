PARAM = -g

sourceFiles = ./src/

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

tipTestFolder = ./testes_p4_tipagem/
tipFilesA = $(wildcard $(tipTestFolder)*.monga)
tipFilesB = $(patsubst $(tipTestFolder)%,%,$(tipFilesA))
tipFileNames = $(patsubst %.monga,%,$(tipFilesB))

codeTestFolder = ./testes_p6_llvm/
codeFilesA = $(wildcard $(codeTestFolder)*.monga)
codeFilesB = $(patsubst $(codeTestFolder)%,%,$(codeFilesA))
codeFileNames = $(patsubst %.monga,%,$(codeFilesB))



all:  mainp6

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
	
	
	
TypesTestes: header mainp4
	@$(foreach fileName, $(tipFileNames) , (\
		printf "\n\n";\
		echo -e "Teste '"$(fileName)"' iniciado!";\
		./main_p4.out <$(tipTestFolder)$(fileName).monga;\
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
		
	@if [ $$? -eq 0 ];\
	then \
		echo -e "\e[42mTeste bem sucedido!\e[0m" ;\
	else \
		echo -e "\e[41mTeste FALHOU!\e[0m" ;\
	fi;\
	
	
AST: header mainp3b
	@echo " "	
	@echo "YACC, gramatica: Executando um teste generico:"
	@echo " "	
	
	./main_p3b.out <$(astTestFolder)geral.monga
		
	@if [ $$? -eq 0 ];\
	then \
		echo -e "\e[42mTeste bem sucedido!\e[0m" ;\
	else \
		echo -e "\e[41mTeste FALHOU!\e[0m" ;\
	fi;\


Types: header mainp4
	@echo " "	
	@echo "Tipagem: Executando um teste generico:"
	@echo " "	
	
	./main_p4.out <$(tipTestFolder)geral.monga
		
	@if [ $$? -eq 0 ];\
	then \
		echo -e "\e[42mTeste bem sucedido!\e[0m" ;\
	else \
		echo -e "\e[41mTeste FALHOU!\e[0m" ;\
	fi;\
	
	
LLVM: header mainp6
	@echo " "	
	@echo "LLVM: Executando um teste generico:"
	@echo " "	
	
	@cat -n $(codeTestFolder)geral.monga		
	
	@./main_p6.out debug <$(codeTestFolder)geral.monga
	@./main_p6.out <$(codeTestFolder)geral.monga >$(codeTestFolder)geral.ll	
	@llc -filetype=obj $(codeTestFolder)geral.ll
	@gcc $(PARAM) -o main_p6_monga.out $(codeTestFolder)geral.o $(sourceFiles)llvm_print_float.c
	@./main_p6_monga.out int	
	
	@if [ $$? -eq 0 ];\
	then \
		echo -e "\e[42mTeste bem sucedido!\e[0m" ;\
	else \
		echo -e "\e[41mTeste FALHOU!\e[0m" ;\
	fi;\


mainp1: header monga $(sourceFiles)main_p1.c 
	@echo " "
	@echo "Compilando a main_p1 e ligando com o lex.yy:"
	gcc $(PARAM) -o main_p1.out lex.yy.o $(sourceFiles)main_p1.c


mainp2: header monga $(sourceFiles)main_p2.c 
	@echo " "
	@echo "Compilando a main_2 e ligando com o lex.yy e tab:"
	gcc $(PARAM) -o main_p2.out lex.yy.o monga.tab.o $(sourceFiles)main_p2.c 


mainp3: header absSyntaxTree types monga $(sourceFiles)main_p3.c 
	@echo " "
	@echo "Compilando a main_3 e ligando:"
	gcc $(PARAM) -o main_p3.out absSyntaxTree.o types.o lex.yy.o monga.tab.o $(sourceFiles)main_p3.c 
	

mainp3b: header absSyntaxTree types monga $(sourceFiles)main_p3.c 
	@echo " "
	@echo "Compilando a main_3b e ligando:"
	gcc $(PARAM) -o main_p3b.out absSyntaxTree.o types.o lex.yy.o monga.tab.o $(sourceFiles)main_p3b.c 


mainp4: header absSyntaxTree astKnit types typeCheck monga tools $(sourceFiles)main_p4.c 
	@echo " "
	@echo "Compilando a main_4 e ligando:"
	gcc $(PARAM) -o main_p4.out absSyntaxTree.o astKnit.o typeCheck.o types.o lex.yy.o monga.tab.o tools.o $(sourceFiles)main_p4.c 


mainp5: header absSyntaxTree astKnit types codeGen typeCheck monga tools $(sourceFiles)main_p5.c 
	@echo " "
	@echo "Compilando a main_5 e ligando:"
	gcc $(PARAM) -o main_p5.out absSyntaxTree.o astKnit.o typeCheck.o llvm.o types.o lex.yy.o monga.tab.o tools.o $(sourceFiles)main_p5.c 


mainp6: header absSyntaxTree astKnit types codeGen typeCheck monga tools $(sourceFiles)main_p6.c 
	@echo " "
	@echo "Compilando a main_5 e ligando:"
	gcc $(PARAM) -o main_p6.out absSyntaxTree.o astKnit.o typeCheck.o llvm.o types.o lex.yy.o monga.tab.o tools.o $(sourceFiles)main_p6.c 
	

lexcode: header $(sourceFiles)monga.lex
	@echo " " 
	@echo "Gerando o lex.yy.c:"
	flex -o $(sourceFiles)lex.yy.c $(sourceFiles)monga.lex
	
	
yacccode: header $(sourceFiles)monga.y
	@echo " " 
	@echo "Gerando o monga.tab.c e monga.tab.h:"
	bison -o $(sourceFiles)monga.tab.c -d $(sourceFiles)monga.y

	
monga: header lexcode yacccode
	@echo " "
	@echo "Compilando o lex.yy.c:"
	gcc $(PARAM) -c $(sourceFiles)lex.yy.c $(sourceFiles)monga.tab.c


absSyntaxTree: monga $(sourceFiles)absSyntaxTree.c
		gcc  $(FLAGS) -c $(sourceFiles)absSyntaxTree.c 
		
		
types: monga $(sourceFiles)types.c
		gcc  $(FLAGS) -c $(sourceFiles)types.c 	


astKnit: monga $(sourceFiles)astKnit.c
		gcc  $(FLAGS) -c $(sourceFiles)astKnit.c 	


typeCheck: monga $(sourceFiles)typeCheck.c
		gcc  $(FLAGS) -c $(sourceFiles)typeCheck.c 	


codeGen: monga $(sourceFiles)llvm.c
		gcc  $(FLAGS) -c $(sourceFiles)llvm.c 					
		
		
tools: $(sourceFiles)tools.c
		gcc  $(FLAGS) -c $(sourceFiles)tools.c 	


header:
	@clear
	@echo " "	
	@date
	@echo " "		

	
	
	
