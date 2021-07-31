estado_inicial(e([v(c(1,1),D,_),v(c(1,3),D,_),v(c(1,4),D,_),v(c(1,5),D,_),v(c(1,7),D,_),
				v(c(2,1),D,_),v(c(2,2),D,_),v(c(2,3),D,_),v(c(2,5),D,_),v(c(2,7),D,_),v(c(2,8),D,_),v(c(2,9),D,_),
				v(c(3,2),D,_),v(c(3,3),D,_),v(c(3,4),D,_), v(c(3,5),D,_),v(c(3,6),D,_),v(c(3,8),D,_),
				v(c(4,1),D,_),v(c(4,2),D,_),v(c(4,3),D,_),v(c(4,4),D,_),v(c(4,5),D,_),v(c(4,7),D,_),v(c(4,8),D,_),v(c(4,9),D,_),
				v(c(5,1),D,_),v(c(5,2),D,_),v(c(5,3),D,_),v(c(5,4),D,_),v(c(5,7),D,_),
				v(c(6,2),D,_),v(c(6,3),D,_),v(c(6,5),D,_),v(c(6,6),D,_),v(c(6,7),D,_),v(c(6,8),D,_),v(c(6,9),D,_),
				v(c(7,1),D,_),v(c(7,2),D,_),v(c(7,3),D,_),v(c(7,5),D,_),v(c(7,6),D,_),v(c(7,7),D,_),v(c(7,8),D,_),v(c(7,9),D,_),
				v(c(8,3),D,_),v(c(8,4),D,_),v(c(8,6),D,_),v(c(8,7),D,_),v(c(8,9),D,_),
				v(c(9,1),D,_),v(c(9,2),D,_),v(c(9,4),D,_),v(c(9,5),D,_),v(c(9,7),D,_),v(c(9,8),D,_),v(c(9,9),D,_)],

				[v(c(1,2),D,1),v(c(1,6),D,8),v(c(1,8),D,7),v(c(1,9),D,3),
				v(c(2,4),D,5),v(c(2,6),D,9),
				v(c(3,1),D,7),v(c(3,7),D,9),v(c(3,9),D,4),
				v(c(4,6),D,4),
				v(c(5,5),D,3),v(c(5,6),D,5),v(c(5,8),D,1),v(c(5,9),D,8),
				v(c(6,1),D,8),v(c(6,4),D,9),
				v(c(7,4),D,7),
				v(c(8,1),D,2),v(c(8,2),D,6),v(c(8,5),D,4),v(c(8,8),D,3),
				v(c(9,3),D,5),v(c(9,6),D,3)])):-numeros(D).

numeros([1,2,3,4,5,6,7,8,9]).

op(E1,_,E2,1):- sucessor(E1,E2).

sucessor(e([v(N,D,V)|R],E),e(R,[v(N,D,V)|E])):- member(V,D).  

estado_final(e([],Afect)):-  ve_restricoes(e([],Afect)).

ve_restricoes(e(_Nafect,Afect)):-
	\+((member(v(c(Y1,X1),_,Vi),Afect),
		member(v(c(Y2,X2),_,Vj),Afect),
		c(Y1,X1)\=c(Y2,X2),
		(linCol(X1,Vi,X2,Vj);
		linCol(Y1,Vi,Y2,Vj);
		quadrantes(c(Y1,X1), Vi, c(Y2,X2), Vj)))).


% Sucede se alguma restrição falhar
linCol(X1,Vi,X2,Vj):-
	X1=X2,
	Vi=Vj.

quadrantes(A, Vi, B, Vj):-
	Vi=Vj,
	get_quadrante(A, Q1),
	get_quadrante(B, Q2),
	!,
	Q1=Q2.

get_quadrante(c(Y, X), Q):-
	(X<4, Y<4, Q=1);
	(X<7, Y<4, Q=2);
	(X<10, Y<4, Q=3);
	(X<4, Y<7, Q=4);
	(X<7, Y<7, Q=5);
	(X<10, Y<7, Q=6);
	(X<4, Y<10, Q=7);
	(X<7, Y<10, Q=8);
	(X<10, Y<10, Q=9).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

newL([10,19,28,37,46,55,64,73]).
barraV([3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57,60,63,66,69,72,75,78,81]).
barraH([1,28,55]).

escBarraH:-nl, write(' -----------------------------------'),nl.

% esc(L):- sort(L,L1), write(L1), nl, esc1(L1,0).
esc(L):- sort(L,L1),esc1(L1,0), escBarraH.
esc1([],_).
esc1([v(_,_,J)|R], X):- Y is X+1, esc(J,Y),  esc1(R,Y).
esc(J, Y):- barraH(H), (member(Y,H)-> escBarraH,write('| '),write(J), write(' . ') ; newL(L), member(Y, L), nl, write('| '), write(J), write(' . ')).
esc(J, Y):- barraV(L), member(Y, L) , write(J), write(' | ').
esc(J, Y):- barraV(L1),newL(L2),  \+ (member(Y, L2);member(Y,L1)), write(J), write( ' . ').


% Backwards search
p:- estado_inicial(E0), 
    back(E0,A),
    esc(A).

back(e([],A),A).

back(E,Sol):- sucessor(E,E1), 
			ve_restricoes(E1),
			back(E1,Sol).

% FORWARD CHECKING
:- dynamic(nos/1).

nos(0).

inc:- retract(nos(N)), N1 is N+1, asserta(nos(N1)).


f:- estado_inicial(E0), forward(E0,A),  esc(A).

forward(e([],A),A).
forward(E,Sol):- sucessor(E,E1),inc, ve_restricoes(E1),
                        forCheck(E1,E2),
                        forward(E2,Sol).


forCheck(e(Lni,[v(c(Y,X),D,V)|Li]), e(Lnii,[v((Y,X),D,V)|Li])):- corta(p(c(Y,X),V),Lni,Lnii).

corta(_,[],[]).
corta(p(c(Y,X), V),[v(c(Y1,X1),D,_)|Lni], [v(c(Y1,X1),D1,_)|Lnii]):- 
	(((X=X1); (Y=Y1);(quadrantes(c(Y,X),1,c(Y1,X1),1))) -> delete(D,V,D1), corta(p(c(Y,X),V),Lni,Lnii);
															D1=D, corta(p(c(Y,X),V),Lni,Lnii)).

% corta(p(c(Y,X), V),[v(c(Y1,X1),D,_)|Lni], [v(c(Y1,X1),D,_)|Lnii]) :- corta(p(c(Y,X),V),Lni,Lnii).

