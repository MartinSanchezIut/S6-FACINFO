Exo 1:
(* # Inverser une liste *)
let rec inverser_liste = function 
  | []->[]
  | t :: r -> (inverser_liste r)@ [t];;

(inverser_liste [1;2;3])


(* # Nombre d'occurences de n dans la liste *)
let rec occ n = function 
  | []->0 
  | e::tl-> if e==n then 1+(occ n tl) else 0+(occ n tl) ;;

(occ 1 [1;1;2;3])


(* # Une liste est trie ? *)
let rec is_sorted = function
  | [] | [ _ ] -> true
  | a :: b :: tl -> (a <= b) && (is_sorted (b :: tl));;
    

(is_sorted  [1;3;2;3])


(* # Insérer dans une liste en gardant le tri *)
let rec insert_sorted n = function
  | [] -> [n]
  | e::tl -> (if n>e then (e::(insert_sorted n tl)) else n::e::tl);;

(insert_sorted 0 [1;3;2;3])


(* # Trier une liste *)
let rec insert_sorted n = function
  | [] -> [n]
  | e::tl -> (if n>e then (e::(insert_sorted n tl)) else n::e::tl);;

let rec sort = function
  | [] -> []
  | e :: tl -> insert_sorted e (sort tl);;


(sort [1;3;2;3])


Exo 2:
(* Type expression logique *)
type form =
  | Top | Bot
  | Var of string
  | Not of form
  | And of form * form
  | Or of form * form
  | Imp of form * form
  | Equ of form * form;;

let f1 = Top;;
let f2 = Var "A";;
let f3 = And (Var "A", Var "B");;

(* Afficher une expression logique *)
let rec print_form = function
  | Top -> print_string "T"
  | Bot -> print_string "F"
  | Var s -> print_string s
  | Not s -> print_string "!"; print_string s
  | And (s, t)-> print_string s; print_string "&"; print_string t
  | Or (s, t) -> print_string s; print_string "|"; print_string t
  | Imp (s, t)-> print_string s; print_string "->"; print_string t
  | Equ (s, t)->  print_string s; print_string "<->"; print_string t;;

(* Operation de simplification *)
let simplifier_and = function
  | And(f, Top) | And(Top, f) -> f
  | And(f, Bot) | And(Bot, f) -> Bot
  | e -> e ;;

let simplifier_or = function
  | Or(f, Top) | Or(Top, f) -> Top
  | Or(f, Bot) | Or(Bot, f) -> f
  | e -> e ;;

let simplifier_imp = function
  | Imp(f, Top) -> Top
  | Imp(f, Bot) -> Not f
  | Imp(Top, f) -> f
  | Imp(Bot, f) -> Top
  | e -> e ;;

let simplifier_equ = function
  | Equ(f, Top) -> f | Equ(Top, f) -> f
  | Equ(f, Bot) -> Not f | Equ(Bot, f) -> Not f
  | e -> e ;;


let simplifier_form = function
  | And(f1, f2) -> let f1' simplifier_form f1 
      and f2' simplifier_form f2 in simplififier_and(f1'; f2')
  | Or(f1, f2) -> let f1' simplifier_form f1 
      and f2' simplifier_form f2 in simplififier_or(f1'; f2')
  | Imp(f1, f2) -> let f1' simplifier_form f1 
      and f2' simplifier_form f2 in simplififier_imp(f1'; f2')       
  | Equ(f1, f2) -> let f1' simplifier_form f1 
      and f2' simplifier_form f2 in simplififier_equ(f1'; f2')



