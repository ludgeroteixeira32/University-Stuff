
                                     "Jogo do Galo / Tic tac toe game"           Ludgero Teixeira nº41348

-------------------------------------------------------------------------------------------------------------------------------------------
Comandos para compilar e executar o jogo:

gcc servidor.c -o servidor  ----->  compila e cria um executável da parte do servidor.

gcc cliente.c -o cliente    ----->  compila e cria um executável da parte do cliente.

--------------------------------------------------------------------------------------------------------------------------------------------
"Protocolo de comunicação e ligações"

Para funções auxiliares para a criação do jogo e jogabilidade do mesmo, como a criação das tabela, a inserção de uma jogada
e o controlo das mesmas foram utlizadas as funções fornecidas pelo professor. 

O protocolo de comunicação utlizado foi o TCP (Transmission Control Protocol).

A programação em socket é uma maneira de conectar 2 nodes numa rede para comunicarem entre eles.
Um socket fica a escuta numa "port" especifica, enquanto o outro socket fala com o que está á escuta de maneira a formar uma conexão. 

TCP Variáveis:
        - socket_id
        - bind_id
Métodos:
        - socket ()
        - bind ()
        - listen ()
        - accept ()
        - connect ()
        - send ()
        - recv ()
Estrutura:
        - sockaddr_in para configurar o IP
        - address
        - portno
----------------------------------------------------------------------------------------------------------------------------------------------

"Implementação"

Tanto o servidor como o cliente estão constantemente em "loop" a "escutar" e a "ouvir", até que a condição de vitória seja válida,
fazendo com que os sockets sejam fechados.

   1- O servidor começa por esperar a primeira jogada do cliente
   2- O cliente liga-se e envia a primeira jogada
   3- O cliente espera pela jogada do servidor
   4- O servidor envia a sua jogada
   5- Volta ao início
------------------------------------------------------------------------------------------------------------------------------------------------
"Servidor":

Começa por receber uma mensagem/jogada do cliente, caso receba um 'W', significa que a última jogada feita pelo servidor foi uma
jogada de vitória, sendo que o seu adversário/cliente enviou um W.

De seguida o servidor verifica se a jogada que recebeu do cliente é uma jogada válida, ou seja, se a jogada não entra em conflito com
outra jogada previamente feita, caso a mesma não o seja o servidor envia um 'X', alertando o adversário/cliente.

Caso a jogada feita pelo adversário/cliente seja um jogada válida, é verificado se essa mesma jogada é uma jogada que resulta numa vitória,
o servidor envia um 'W' e termina a ligação.

Após estas verificações, caso uma situação de vitória seja verificada o tabuleiro de jogo é atualizado com essa mesma jogada e a ligação
é terminada.

No final destas condições o servidor manda uma jogada.

"Cliente":

O cliente que é sempre o primeiro a começar a jogar, começa imprimir do tabuleiro e envia uma jogada.

De seguida fica a espera de receber uma mensagem/jogada por parte do servidor, caso receba um 'W', é sinal que a jogada
realizada anteriormente pelo ciente resultou numa vitória.

Caso não seja um 'W' que receba e sim uma jogada, o cliente vai ver se essa mesma jogada é uma jogada que não interfira com outra jogada feita
previamente, caso o seja, o cliente envia um 'X' para o servidor.

Caso a jogada feita pelo adversário/servidor seja um jogada válida, é verificado se essa mesma jogada é uma jogada que resulta numa vitória,
o cliente envia um 'W' e termina a ligação.

Após estas verificações, caso uma situação de vitória seja verificada o tabuleiro de jogo é atualizado com essa mesma jogada e a ligação
é terminada.
-----------------------------------------------------------------------------------------------------------------------------------------------------







