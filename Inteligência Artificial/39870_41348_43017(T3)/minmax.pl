

g(Jogo):- [Jogo], estado_inicial(Ei), minimax_decidir(Ei,Op, Ess),
write(Op),nl,(Jogo=nim->escNim(Ess);escWQueen(Ess)),nl, nos(X), write(X).

jogar(Jogo):- [Jogo], estado_inicial(E1),
        write('Inicio - '),nl,
        (Jogo=nim -> escNim(E1),agenteNim(E1); escWQueen(E1),agenteWQueen(E1)).

it(Ei, Ess):- minimax_decidir(Ei, Opf, Ess).

ganhou(-1):- nl, write('Computador Ganha'),nl.
ganhou(1):- nl, write('Jogador Ganha'),nl.


% Whythoff's Queen

agenteWQueen(Ei):- terminal(Ei), valor(Ei, V, 1), ganhou(V), escWQueen(Ei).
agenteWQueen(Ei):- minimax_decidir(Ei,Op, Ess), write('Agente joga - '), write(Op), escWQueen(Ess),  jogadorWQueen(Ess).

jogadorWQueen(Ei):- terminal(Ei), valor(Ei, V, 2), ganhou(V), escWQueen(Ei).
jogadorWQueen(Ess):-lerJogadaWQueen(I,J), op1(Ess, move(I,J), Ne), agenteWQueen(Ne).

lerJogadaWQueen(I,J):- write('linha = '), read(I), write('coluna = '), read(J), nl.

% Writes

escWQueen(e(X,Y)):- nl, escWQueenAux(e(X,Y), e(0,7)).

escWQueenAux(_, e(0,-1)).
escWQueenAux(e(X,Y), e(7,Cy)):- ((X,Y)=(7,Cy) -> write(' R '); write(' - ')), nl, Ncy is Cy-1 , escWQueenAux(e(X,Y), e(0, Ncy)).
escWQueenAux(e(X,Y), e(Cx,Cy)):- ((X,Y)=(Cx, Cy)-> write(' R '); write(' - ')), Ncx is Cx+1, escWQueenAux(e(X,Y), e(Ncx, Cy)).

% Nim

agenteNim(Ei):- terminal(Ei), valor(Ei, V, 1), ganhou(V), escNim(Ei).
agenteNim(Ei):- minimax_decidir(Ei,Op, Ess), write('Agente joga - '), write(Op), escNim(Ess),  jogadorNim(Ess).

jogadorNim(Ei):- terminal(Ei), valor(Ei, V, 2), ganhou(V), escNim(Ei).
jogadorNim(Ess):-lerJogadaNim(I,J), op1(Ess, tira(I,J), Ne), agenteNim(Ne).

lerJogadaNim(I,J):- write('linha = '), read(I), write('quantidade = '), read(J), nl.

% Writes

escLinha(0):-nl.
escLinha(N):- write(' |'), M is N-1, escLinha(M).

escNim(e(L1,L2,L3,L4)):- nl,write('1 - '), escLinha(L1), nl,write('2 - '), escLinha(L2), 
                        nl,write('3 - '), escLinha(L3), nl, write('4 - '),escLinha(L4),nl.



:- dynamic(maxNL/1).
:- dynamic(nos/1).

maxNL(0).
nos(0).

inc:- retract(nos(N)), N1 is N+1, asserta(nos(N1)).


% decide qual é a melhor jogada num estado do jogo
% minimax_decidir(Estado, MelhorJogada)

% se é estado terminal não há jogada 
minimax_decidir(Ei,terminou, Ei):- terminal(Ei), inc.

%Para cada estado sucessor de Ei calcula o valor minimax do estado
%Opf é o operador (jogada) que tem maior valor

minimax_decidir(Ei, Opf, Ess):-
findall(Es-Op, op1(Ei,Op,Es),L),
findall(Vc-Op,(member(E-Op,L), minimax_valor(E,Vc,1)),L1),
escolhe_max(L1,Opf), member(Ess-Opf, L).

% se um estado é terminal o valor é dado pela função de utilidade
minimax_valor(Ei,Val,P):- terminal(Ei),inc, valor(Ei,Val,P).

%Se o estado não é terminal o valor é:
% -se a profundidade é par, o maior valor dos sucessores de Ei
% -se aprofundidade é impar o menor valor dos sucessores de Ei
minimax_valor(Ei,Val,P):- inc, findall(Es,op1(Ei,_,Es),L),
P1 is P+1,
findall(Val1,(member(E,L),minimax_valor(E,Val1,P1)),V),
seleciona_valor(V,P,Val).


% Se a profundidade (P) é par, retorna em Val o maximo de V
seleciona_valor(V,P,Val):- X is P mod 2, X=0,!, maximo(V,Val).

% Senão retorna em Val o minimo de V
seleciona_valor(V,_,Val):- minimo(V,Val).


maximo([A|R],Val):- maximo(R,A,Val).

maximo([],A,A).
maximo([A|R],X,Val):- A < X,!, maximo(R,X,Val).
maximo([A|R],_,Val):- maximo(R,A,Val).


escolhe_max([A|R],Val):- escolhe_max(R,A,Val).

escolhe_max([],_-Op,Op).
escolhe_max([A-_|R],X-Op,Val):- A < X,!, escolhe_max(R,X-Op,Val).
escolhe_max([A|R],_,Val):- escolhe_max(R,A,Val).


minimo([A|R],Val):- minimo(R,A,Val).

minimo([],A,A).
minimo([A|R],X,Val):- A > X,!, minimo(R,X,Val).
minimo([A|R],_,Val):- minimo(R,A,Val).