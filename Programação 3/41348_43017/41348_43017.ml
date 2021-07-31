(* Print de uma lista de inteiros *)
let print_list l = print_string "[";List.iter (fun x -> print_int x; print_string ";") l; print_string "] ";;
(* Print de uma lista de strings *)
let print_list_string l = print_string "[";List.iter (fun x -> print_string (String.make 1 x); print_string ";") l; print_string "] ";;
(* Print de uma lista de listas *)
let print_ll ll = print_string "[";List.iter (fun l -> print_list l) ll; print_string "]\n";;

let print_final (a,b,c) = print_string "(";
                            print_list a;
                            print_string",";
                            print_list_string b;
                            print_string",";
                            print_list_string c;
                            print_string")\n";;

(* Dado um tuplo devolve o simbolo *)
let getSymb (l,arr) = l;;
(* Dado um tuplo devolve o arrat *)
let getArr (l,arr) = arr;;

(* compara se duas listas são iguais *)
let rec compList l1 l2 =

  match(l1,l2) with
  | [],[] -> true
  | [],_ -> false
  | _,[] -> false
  | (x::xs),(y::ys) -> if x!=y then false
                      else compList xs ys;;

(* Converte um tuplo para que tenha array de simbolos *)
let converte (l,arr)=([l],arr);;

(* Converte uma lista inteira de tuplos *)
let converterLista lt =
  let rec converterLista_rec arr = function
  | []->arr
  | x::xs -> converterLista_rec (arr @ [(converte x)]) xs
  in converterLista_rec [] lt;;


(* Dados dois new_tuplos junta-os *)
let joinTuple (s1, a1) (s2, a2) = (s1@s2, a1@a2);;



(* Dado uma lista de códigos e um código, todas as combinações com esse código *)
let combinacoesEntreListas_aux a codes =
  let rec combinacoesEntreListas_aux_rec aux = function
    | [] -> aux
    | x::xs -> combinacoesEntreListas_aux_rec ( aux @ [ joinTuple a x ]) xs
  in combinacoesEntreListas_aux_rec [] codes ;;

(* Dado duas listas, calcula a combinação da primeira lista com a combinacoesEntreListas *)
let combinacoesEntreListas l1 l2 =
  let rec combinacoesEntreListas_rec aux = function
    | [] -> aux
    | x::xs -> combinacoesEntreListas_rec (aux @ combinacoesEntreListas_aux x l2) xs
  in combinacoesEntreListas_rec [] l1;;


(* Vemos se os arrays são iguais *)
let elementoNaLista el l =
  let rec elementoNaLista_rec = function
    | [] -> false
    | x::xs -> if not (compList (getSymb x) (getSymb el)) && compList (getArr el) (getArr x)
               then true else (elementoNaLista_rec xs)
  in elementoNaLista_rec l;;

(* Ver se algum elemento da lista L1 tem um array igual ao da lista L2, se sim guarda na variável *)
let verNaLista l1 l2 =
  let rec verNaLista_rec aux = function
    | [] -> aux (* No final devolvemos o aux *)
    | x::xs -> if (elementoNaLista x l2) then verNaLista_rec (aux @ [x]) xs else verNaLista_rec aux xs  (* Se o elemento estiver na lista adicionamos a aux e continuamos*)
  in verNaLista_rec [] l1;;

(* Dada uma lista, devolve o tamanho do arrat do tuplo com menor tamanho *)
let menorLengthDaLista l =
  let rec menorLengthDaLista_rec i = function
    | [] -> i
    | x::xs -> if List.length (getArr x)<i
              then menorLengthDaLista_rec (List.length (getArr x)) xs
              else menorLengthDaLista_rec i xs
  in menorLengthDaLista_rec 1000 l;;

(* Dado uma lista e um inteiro, devolve todos os tuplos, cujo array tem length == sz *)
let menoresCombinacoes l sz =
  let rec menoresCombinacoes_rec arr = function
    | [] -> arr
    | x::xs -> if List.length (getArr x) == sz (* Se o elemento tem tamanho igual ao minimo*)
              then menoresCombinacoes_rec (arr @ [x]) xs (* Adicionamos a aux e continuamos a iteração*)
              else menoresCombinacoes_rec arr xs (* Se não continuamos a iterar*)
  in menoresCombinacoes_rec [] l;;

(* Dado uma lista, devolve as sublistas com menor tamanho *)
let menorSubL l = menoresCombinacoes l (menorLengthDaLista l);;

(* Cria o tuplo utilizado para o return final *)
let addInicioTuplo a (b,c) = (c,a,b);;

(* Procura um elemento numa lista, se encontrar devolve o simbolo, se não devolve [] *)
let elementoIgual t l =
  let rec elementoIgual_rec = function
    | [] -> []
    | x::xs -> if compList (getArr t) (getArr x) && not (compList (getSymb t) (getSymb x))
              then (getSymb x)
              else elementoIgual_rec xs
  in elementoIgual_rec l;;


(* função auxiliar na criação da combinação dos arranjos *)
  let combinacoesN n codes =
    let rec combinacoesN_rec aux = function
      | 1 -> aux
      | n -> combinacoesN_rec (combinacoesEntreListas (List.tl aux) codes) (n-1)
    in combinacoesN_rec codes n;;

(* Dada uma lista e um n, devolve todas as combinações  *)
let listaComb codes n =
  let rec listaComb_rec aux = function
    | 0 -> aux
    | n -> listaComb_rec ([combinacoesN n codes] @ aux) (n-1)
  in listaComb_rec [] n;;
  


(* auxiliar recursiva que vai percorrer a lista, e procura se um código semelhante ao dado *)
let menorIgual_aux codigo lista=
  let rec menorIgual_aux_rec = function
  | [] -> ([],[])
  | x::xs -> if (List.length (verNaLista x codigo))>0
            then (List.hd (menorSubL (verNaLista x codigo)))
            else menorIgual_aux_rec xs
  in menorIgual_aux_rec lista;;

(* Recebe a lista de arranjos *)
(* Procura na lista dada, qual o menor elemento diferente de ele mesmo que tem o mesmo  *)
let menorIgual lista =
  let rec menorIgual_rec = function
  | [] -> ([],[])
  | x::xs -> if List.length (getArr (menorIgual_aux x lista)) >0 then menorIgual_aux x lista
              else menorIgual_rec xs
  in menorIgual_rec lista;;

(* Dado um elemento e uma lista de listas , procura na lista qual o elemento que tem um código igual ao dado *)
let elementoIgualLista e ll =
  let rec elementoIgualLista_rec = function
  | [] -> []
  | x::xs -> if (List.length (elementoIgual e x) > 0) (* Vemos se o elemento existe na primeira lista *)
            then (elementoIgual e x) (* Se existir devolvemos esse elemento *)
            else elementoIgualLista_rec xs (* Se não continuamos a procurar*)
  in elementoIgualLista_rec ll;;

  let ambiguo codes =
    let ambiguo_aux listaCombinacoes = addInicioTuplo ((elementoIgualLista (menorIgual listaCombinacoes)) listaCombinacoes) (menorIgual listaCombinacoes)
    in ambiguo_aux (listaComb (converterLista codes) 6);;

  (* let codes = [('a', [0;1;0]);('c', [0;1]);('j', [0;0;1]);('l', [1;0]);('p', [0]);('s', [1]);('v', [1;0;1])];; *)
  let codes = [('a', [0;1;1;0]);
    ('b', [0;1;1;1;1;1]);
    ('c', [1;1;0;0;1;1;1;1]);
    ('f', [1;0;1;1;1;0]);
    ('j', [0;1;0]);
    ('l', [0;1;0;0]);
    ('r', [0;1;1;1;0])];;


let i = (ambiguo codes);;

print_final i;;