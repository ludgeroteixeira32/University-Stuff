listaX([(1,2),(3,1),(3,2),(4,4),(4,5),(4,6),(7,2)]).

% estado inicial
estado_inicial((2,7)).

% estado final
estado_final((5,1)).

% Verificar se está dentro dos limites do tabuleiro

limites(N,M) :- N>0, M>0, N<8, M<8, listaX(Lx), \+member((N,M),Lx).

% (X,Y) - posicao do A
% Lx    - lista de X's
% Ef    - estado final
% (Nx,Ny) - New X, NewY

op((X,Y), (0,M), (X,Ny), 1) :- member(M, [-1,1]),
                            Ny is Y+M,
                            limites(X,Ny).

op((X,Y), (N,0), (Nx,Y), 1) :- member(N, [-1,1]),
                            Nx is X+N,
                            limites(Nx,Y).

h(E,Val) :- h1(E,Val1), h2(E,Val2), min(Val1,Val2,Val).

max(A, B, A):- A>B,!.
max(_, B, B).

min(A,B,A) :- A<B, !.
min(_,B,B).

% modulo da subtração
modSub(A, B, Res):- max(A, B, Max), min(A, B, Min), Res is Max - Min.

% Heuristica 1 - Distância à casa final
h1(E,Val) :- estado_final((Fx,Fy)),
            E=(Cx,Cy), 
            modSub(Fx, Cx, DistX),
            modSub(Fy, Cy, DistY),
            Val is (DistX + DistY).

% Heuristica 2 - Distância no eixo do X à casa final
h2(E,Val) :- estado_final((Fx,_)),
            E = (Cx,_),
            modSub(Fx, Cx, Val).