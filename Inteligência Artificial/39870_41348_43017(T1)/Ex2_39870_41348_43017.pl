listaX([(1,2),(3,1),(3,2),(4,4),(4,5),(4,6),(7,2)]).

% estado_inicial
estado_inicial(((2,7), (2,6))).

% estado_final
estado_final((_, (5,1))).

% Verificar se está dentro dos limites do tabuleiro

limites(N,M) :- N>0, M>0, N<8, M<8, listaX(Lx), \+member((N,M),Lx).

op(((Xa, Ya),(Xc, Yc)), (N,0), ((Nxa, Ya),(Nxc, Yc)), 1) :- member(N, [-1,1]),
                                                        Nxa is Xa+N,
                                                        ((Nxa,Ya) = (Xc,Yc) -> Nxc is Xc+N ; Nxc is Xc),
                                                        limites(Nxa, Ya), limites(Nxc, Yc).

op(((Xa, Ya),(Xc, Yc)), (0,M), ((Xa, Nya),(Xc, Nyc)), 1) :- member(M, [-1,1]),
                                                        Nya is Ya+M,
                                                        ((Xa,Nya) = (Xc,Yc) -> Nyc is Yc+M ; Nyc is Yc ),
                                                        limites(Xa, Nya), limites(Xc, Nyc).

h(E, Val) :- h1(E, Val).

max(A, B, A):- A>B,!.
max(_, B, B).

min(A,B,A) :- A<B, !.
min(_,B,B).

% modulo da subtração
modSub(A, B, Res):- max(A, B, Max), min(A, B, Min), Res is Max - Min.

% heuristica 1 - distância da caixa ao estado final
h1(E,Val) :- estado_final((_,(Fx,Fy))),
            E= (_,(Cx,Cy)), 
            modSub(Fx, Cx, DistX),
            modSub(Fy, Cy, DistY),
            Val is (DistX + DistY).
        
% Heuristica 2 - Distância no eixo do X à casa final
h2(E, Val) :- estado_final((_,(Fx,_))),
            E = (_,(Cx,_)),
            modSub(Fx,Cx,Val).
