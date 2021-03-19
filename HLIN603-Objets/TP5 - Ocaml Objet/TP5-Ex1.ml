(* #use "TP5-Ex1.ml";; *)
(* Ex 1 *) 

class min (xi : int) =
	object (self)
	val mutable x = xi
	method get = x
	method set n = x <- n
	method min y = print_int(self#get); print_string(" vs "); print_int(y);
			if self#get < y then self#get else y
end;;

class min_zero xi =
	object
	inherit min xi
	method get = 0
end;;

let o1 = new min 4;;
let o2 = new min_zero 4;;
o1#min 2;;  (* int = 2    min de mon*)
o1#min 7;;  (* int = 4    min de mon*)
o2#min 2;;  (* int = 0    min de min zero*)
o2#min(-2);;(* int = -2   min de min zero*)




