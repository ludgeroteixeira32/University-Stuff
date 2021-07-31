FILE:=resources/config.properties

PORT:=$(shell cat ${FILE} | grep "regPort" | cut -d'=' -f2)

rmi: compile run

run:
	rmiregistry -J-classpath -Jbin $(PORT)
	
compile:
	javac -d bin -classpath bin:resources/postgresql.jar src/vacinacao/*a 
	
server:
	java -classpath  bin:resources/postgresql.jar vacinacao.VacinacaoServer

client:
	java -classpath  bin vacinacao.VacinacaoClient