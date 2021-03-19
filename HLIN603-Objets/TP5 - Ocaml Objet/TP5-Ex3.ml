(* #use "TP5-Ex3.ml";; *)
(* Ex 3 *) 


class cte (n : int) =
object 
   val content = n
   method eval = content
   method print = print_int content ;
end;;

class inv (e : inv)  =
object 
    val content = e
    method eval = -content#eval 
    method print =
        print_string "(-"; 
        content#print;
        print_string ")";
end;;

class add (i:add) (j:add) =
  object
    val a = i
    val b = j
    method eval = a#eval + b#eval
    method print = print_string "("; 
        a#print;
        print_string " + "; 
        b#print;
        print_endline ")"
end;;

class sub (i:sub) (j:sub) =
  object
    val a = i
    val b = j
    method eval = a#eval - b#eval
    method print = print_string "("; 
        a#print;
        print_string " - "; 
        b#print;
        print_endline ")"
end;;

class mul (i:mul) (j:mul) =
  object
    val a = i
    val b = j
    method eval = a#eval * b#eval
    method print = print_string "("; 
        a#print;
        print_string " x "; 
        b#print;
        print_endline ")"
end;;

class div (i:div) (j:div) =
  object
    val a = i
    val b = j
    method eval = a#eval / b#eval
    method print = print_string "("; 
        a#print;
        print_string " / "; 
        b#print;
        print_endline ")"
end;;