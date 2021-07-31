% estado_inicial(e(1,3,5,7)).
estado_inicial(e(1,0,0,7)).

terminal(e(0,0,0,0)).


% quem tirar o ultimo perde

lista([1,2,3,5,6,7]).

op1(e(L1,L2,L3,L4), tira(1,X), e(NL1,L2,L3,L4)):-
    X#=<L1,
    lista(L),
    member(X,L),
    NL1 is L1-X.

op1(e(L1,L2,L3,L4), tira(2,X), e(L1,NL2,L3,L4)):-
    X#=<L2,
    lista(L),
    member(X,L),
    NL2 is L2-X.

op1(e(L1,L2,L3,L4), tira(3,X), e(L1,L2,NL3,L4)):-
    X#=<L3,
    lista(L),
    member(X,L),
    NL3 is L3-X.

op1(e(L1,L2,L3,L4), tira(4,X), e(L1,L2,L3,NL4)):-
    X#=<L4,
    lista(L),
    member(X,L),
    NL4 is L4-X.

valor(E,1,P):- terminal(E), X is P mod 2, X=0,!.
valor(E,-1,_):- terminal(E).