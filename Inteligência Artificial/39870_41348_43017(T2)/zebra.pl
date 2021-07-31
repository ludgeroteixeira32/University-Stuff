% estado_inicial
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 4 PESSOAS
% estado_inicial(e([
%     v(c(1),D,_),
%     v(c(2),D,_),
%     v(c(3),D,_),
%     v(c(4),D,_)],[])):- pessoas(D).

% pessoas(['Maria', 'Manuel', 'Joaquim', 'Ana']).

% restricoes([esq('Manuel','Maria'), 
%             frente('Joaquim','Manuel')]).

% % Sucede se alguma restrição falhar
% %frente
% restric(I, X, J, Y):- restricoes(L), member(frente(X,Y), L), \+ (((I=1, J=3);
%                                                                 (I=2, J=4))).
% % esq
% restric(I, X, J, Y):- restricoes(L), member(esq(X,Y), L), \+((I is J+1; I=1,J=4)).
% % dir
% restric(I, X, J, Y):- restricoes(L), member(dir(X,Y), L), \+((I is J-1; I=4,J=1)).
% % lado
% restric(I, X, J, Y):- restricoes(L), member(lado(X,Y), L), \+(((I is J+1; I=1,J=4) ; (I is J-1; I=4,J=1))).

% % cabeceira esq
% restric(I, X):- restricoes(L), member(cabeceira_esq(X), L), I\=1.
% % cabeceira dir
% restric(I, X):- restricoes(L), member(cabeceira_dir(X), L), I\=3.
% % cabeceira
% restric(I, X):- restricoes(L), member(cabeceira(X), L), \+((I=1;I=3)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 6 PESSOAS
% estado_inicial(e([
%     v(c(1),D,_),
%     v(c(2),D,_),
%     v(c(3),D,_),
%     v(c(4),D,_),
%     v(c(5),D,_),
%     v(c(6),D,_)],[])):- pessoas(D).

% pessoas(['Maria', 'Manuel', 'Madalena', 'Joaquim', 'Ana','Julio']).

% restricoes([esq('Manuel','Maria'), 
%             frente('Joaquim','Maria'), 
%             dir('Joaquim','Madalena'),
%             cabeceira_esq('Julio')]).

% % Sucede se alguma restrição falhar
% %frente
% restric(I, X, J, Y):- restricoes(L), member(frente(X,Y), L), \+ (((I=1, J=4);
%                                                                 (I=2, J=6);
%                                                                 (I=3, J=5))).
% % esq
% restric(I, X, J, Y):- restricoes(L), member(esq(X,Y), L), \+((I is J+1; I=1,J=6)).
% % dir
% restric(I, X, J, Y):- restricoes(L), member(dir(X,Y), L), \+((I is J-1; I=6,J=1)).
% % lado
% restric(I, X, J, Y):- restricoes(L), member(lado(X,Y), L), \+(((I is J+1; I=1,J=6) ; (I is J-1; I=6,J=1))).

% % cabeceira esq
% restric(I, X):- restricoes(L), member(cabeceira_esq(X), L), I\=1.
% % cabeceira dir
% restric(I, X):- restricoes(L), member(cabeceira_dir(X), L), I\=4.
% % cabeceira
% restric(I, X):- restricoes(L), member(cabeceira(X), L), \+((I=1;I=4)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 8 PESSOAS
estado_inicial(e([
    v(c(1),D,_),
    v(c(2),D,_),
    v(c(3),D,_),
    v(c(4),D,_),
    v(c(5),D,_),
    v(c(6),D,_),
    v(c(7),D,_),
    v(c(8),D,_)],[])):- pessoas(D).

pessoas(['Maria', 'Manuel', 'Madalena', 'Joaquim', 'Ana','Julio','Matilde','Gabriel']).

restricoes([esq('Manuel','Maria'), 
            frente('Joaquim','Maria'), 
            lado('Joaquim','Matilde'),
            cabeceira('Gabriel')]).

% Sucede se alguma restrição falhar
%frente
restric(I, X, J, Y):- restricoes(L), member(frente(X,Y), L), \+ (((I=1, J=5);
                                                                (I=2, J=8);
                                                                (I=3, J=7);
                                                                (I=4, J=6))).
% esq
restric(I, X, J, Y):- restricoes(L), member(esq(X,Y), L), \+((I is J+1; I=1,J=8)).
% dir
restric(I, X, J, Y):- restricoes(L), member(dir(X,Y), L), \+((I is J-1; I=8,J=1)).
% lado
restric(I, X, J, Y):- restricoes(L), member(lado(X,Y), L), \+(((I is J+1; I=1,J=8) ; (I is J-1; I=8,J=1))).

% cabeceira esq
restric(I, X):- restricoes(L), member(cabeceira_esq(X), L), I\=1.
% cabeceira dir
restric(I, X):- restricoes(L), member(cabeceira_dir(X), L), I\=5.
% cabeceira
restric(I, X):- restricoes(L), member(cabeceira(X), L), \+((I=1;I=5)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 12 PESSOAS
% estado_inicial(e([
%     v(c(1),D,_),
%     v(c(2),D,_),
%     v(c(3),D,_),
%     v(c(4),D,_),
%     v(c(5),D,_),
%     v(c(6),D,_),
%     v(c(7),D,_),
%     v(c(8),D,_),
%     v(c(9),D,_),
%     v(c(10),D,_),
%     v(c(11),D,_),
%     v(c(12),D,_)],[])):- pessoas(D).

% pessoas(['Maria', 'Manuel', 'Madalena', 'Joaquim', 'Ana','Julio','Matilde','Gabriel','Pedro','Joao','Carlos','Isa']).

% restricoes([esq('Manuel','Maria'),
%             cabeceira_dir('Joaquim'),
%             frente('Julio','Matilde'),
%             lado('Matilde','Gabriel')]).

% % Sucede se alguma restrição falhar
% %frente
% restric(I, X, J, Y):- restricoes(L), member(frente(X,Y), L), \+ (((I=1, J=7);
%                                                                 (I=2, J=12);
%                                                                 (I=3, J=11);
%                                                                 (I=4, J=10);
%                                                                 (I=5, J=9);
%                                                                 (I=6, J=8))).
% % esq
% restric(I, X, J, Y):- restricoes(L), member(esq(X,Y), L), \+((I is J+1; I=1,J=12)).
% % dir
% restric(I, X, J, Y):- restricoes(L), member(dir(X,Y), L), \+((I is J-1; I=12,J=1)).
% % lado
% restric(I, X, J, Y):- restricoes(L), member(lado(X,Y), L), \+(((I is J+1; I=1,J=12) ; (I is J-1; I=12,J=1))).

% % cabeceira esq
% restric(I, X):- restricoes(L), member(cabeceira_esq(X), L), I\=1.
% % cabeceira dir
% restric(I, X):- restricoes(L), member(cabeceira_dir(X), L), I\=7.
% % cabeceira
% restric(I, X):- restricoes(L), member(cabeceira(X), L), \+((I=1;I=7)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

op(E1,_,E2,1):- sucessor(E1,E2).

sucessor(e([v(N,D,V)|R],E),e(R,[v(N,D,V)|E])):- member(V,D).  

estado_final(e([],Afect)):-  ve_restricoes(e([],Afect)).

ve_restricoes(e(_Nafec,Afect)):- \+ ((member(v(c(I),_Di,Vi),Afect),
                                    member(v(c(J),_Dj,Vj),Afect),
                                    I \= J,                        
                                    (Vi=Vj;
                                    restric(I,Vi,J,Vj);
                                    restric(I,Vi);
                                    restric(J,Vj)))).


%% escreve
esc(L):- sort(L,L1), write(L1), nl, esc1(L1).
esc1([]).
esc1([v(c(V),_,J)|R]):- esc(V,J),  esc1(R).
esc(V,J):- write(J),write(' - '), write(V),nl.


% BACKWARDS CHECKING
p:- estado_inicial(E0), back(E0,A), esc(A).

back(e([],A),A).
back(E,Sol):- sucessor(E,E1), ve_restricoes(E1),
                    back(E1,Sol).


% FORWARD CHECKING
% :- dynamic(nos/1).

% nos(0).

% inc:- retract(nos(N)), N1 is N+1, asserta(nos(N1)).


f:- estado_inicial(E0), forward(E0,A),  esc(A).

forward(e([],A),A).
forward(E,Sol):- sucessor(E,E1), ve_restricoes(E1),
                        forCheck(E1,E2),
                        forward(E2,Sol).


forCheck(e(Lni,[v(N,D,V)|Li]), e(Lnii,[v(N,D,V)|Li])):-  corta(V,Lni,Lnii).

corta(_,[],[]).
corta(V,[v(N,D,_)|Li], [v(N,D1,_)|Lii]):- delete(D,V,D1), corta(V,Li,Lii).
