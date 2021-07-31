% condições
% ligacao(c1, lisboa, porto) - significa que o c1 faz a ligação lisboa-porto
% ligacao(c2, lisboa, evora) - significa que o c2 faz a ligação lisboa-evora

% fluentes
% esta_cidade(obj, cidade) - O obj está na cidade
% esta_comboio(obj, c) - O obj está no comboio
% comboio_cidade(c, cidade) - O comboio está na cidade

% açoes 
% entra_comboio(obj, c) - Obj entra no comboio
% sai_comboio(obj) - Obj sai do comboio
% move_comboio(c, cidade) - Comboio move


estado_inicial([ligacao(c1, lisboa, porto),ligacao(c2, lisboa, evora),
                ligacao(c1, porto, lisboa),ligacao(c2, evora, lisboa),
                esta_cidade(obj1, porto),
                esta_cidade(obj2, lisboa),esta_cidade(obj3, lisboa),
                esta_cidade(obj4,evora),esta_cidade(obj5,evora),
                comboio_cidade(c1,lisboa),comboio_cidade(c2,lisboa)]).

estado_final(F):-estado_finalI(F).

estado_finalI([esta_cidade(obj2, porto),esta_cidade(obj4,porto),
                esta_cidade(obj5, lisboa),
                esta_cidade(obj1, evora),esta_cidade(obj3,evora)]).

% estado_finalIntermedio([esta_cidade(obj1,lisboa),esta_cidade(obj2,lisboa),esta_cidade(obj3,lisboa),
%                         esta_cidade(obj4,lisboa),esta_cidade(obj5,lisboa)]).

estado_final1([esta_cidade(obj1, lisboa),esta_cidade(obj2, lisboa),esta_cidade(obj3, lisboa),
                esta_cidade(obj4,evora),esta_cidade(obj5,evora)]).




% ação (Nome, Precondições, ADDList, DELlist)
accao(entra_comboio(Obj, C), [esta_cidade(Obj, Cidade), comboio_cidade(C, Cidade)],
                                [esta_comboio(Obj, C)],
                                [esta_cidade(Obj, Cidade)]):- member(Obj, [obj1,obj2,obj3,obj4,obj5]), member(C,[c1,c2]),member(Cidade, [lisboa,porto,evora]).

accao(sai_comboio(Obj), [esta_comboio(Obj, C), comboio_cidade(C, Cidade)],
                        [esta_cidade(Obj,Cidade)],
                        [esta_comboio(Obj, C)]):-member(Obj, [obj1,obj2,obj3,obj4,obj5]),member(C,[c1,c2]),member(Cidade, [lisboa,porto,evora]).

accao(move_comboio(C, Cidade2), [comboio_cidade(C, Cidade1),ligacao(C, Cidade1, Cidade2)],
                        [comboio_cidade(C, Cidade2)],
                        [comboio_cidade(C, Cidade1)]):- member(Cidade2, [lisboa,porto,evora]), member(Cidade1, [lisboa,porto,evora]),member(C,[c1,c2]).


