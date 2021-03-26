(* #use "Exo2.ml";; *)
(* PAS FINI *) 

class virtual ['a] add_magma =
object
    method virtual add : 'a -> 'a -> 'a
end;;

class virtual ['a] mul_magma =
object
    method virtual mul : 'a -> 'a -> 'a
end;;

class virtual ['a] add_monoid =
object
    inherit ['a] add_magma
    method virtual add_id : 'a
end;;

class virtual ['a] mul_monoid =
object
    inherit ['a] mul_magma
    method virtual mul_id : 'a
end;;

class virtual ['a] add_group =
object
    inherit ['a] add_monoid
    method virtual add_inv : 'a -> 'a
end;;

class virtual ['a] ring =
object
    inherit ['a] add_group
    inherit ['a] mul_monoid
end ;;

class int_ring =
    object (self)
    inherit [int] ring 
    method add x y = x + y
    method add_id = 0
    method add_inv (a:int)= -a  
    method mul x y = x * y
    method mul_id = 1
end;;

class ['a, 'b] polynomial (r : 'b) (p : ('a * int) list) =
object (self)
    constraint 'b = 'a ring
    val ra = r
    val rep = p
    method private monomial (c, n) x =
        if n = 0 then c
        else ra#mul x (self#monomial (c, (n - 1)) x)
    method eval x =
        List.fold_left (fun a b -> ra#add a (self#monomial b x)) ra#add_id rep
end;;

let ir = new int_ring;;
class int_polynomial (p : (int * int) list) =
object
  inherit [int, int ring] polynomial ir p
end;;