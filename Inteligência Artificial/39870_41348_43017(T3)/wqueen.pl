% num tabuleiro n*n, qualquer posição inicial pode ser escolhida

estado_inicial(e(7,4)).

terminal(e(0,0)).

% Lista para um tabuleiro 8x8
lista([1,2,3,4,5,6,7]).

menor(X,Y,X):- X<Y, !.
menor(X,Y,Y).

op1(e(X,Y), move(N, N), e(Xn, Yn)):-
    menor(X,Y,M),
    N#=<M,
    lista(L),
    member(N, L),
    Xn is X-N,
    Yn is Y-N.

op1(e(X,Y), move(Mx, 0), e(Xn, Y)):-
    Mx#=<X,
    lista(L),
    member(Mx, L),
    Xn is X-Mx.
    
op1(e(X,Y), move(0, My), e(X, Yn)):-
    My#=<Y,
    lista(L),
    member(My, L),
    Yn is Y-My.

valor(E,-1,P):- terminal(E), X is P mod 2, X=0,!.
valor(E,1,_):- terminal(E).