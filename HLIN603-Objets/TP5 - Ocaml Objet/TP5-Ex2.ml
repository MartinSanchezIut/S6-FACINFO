(* #use "TP5-Ex2.ml";; *)
(* Ex 2 *) 

class compte b =
	object (self)
	val mutable balance = 0.0
	method get = balance
	method depot d = balance <- balance +. d
	method retrait r = balance <- balance -. r
	method print = print_float balance; print_newline()
	initializer self#depot b
	end;;

class compte_interet b =
	object 
	inherit compte b
	method interet = balance <- balance *. 1.05
	end;;

class compte_securise b =
    object 
	inherit compte b as super
	method retrait r = 
			if balance < r
			then failwith "Picsou à découvert ... zzzzzz"
			else super#retrait r
	end;;



class bank =
	object (self)
	val mutable listOfAccounts = []
	method add ( x : compte)= x :: listOfAccounts

	method balance = List.fold_left 
		(fun a b -> a +. b#get) 0. listOfAccounts

	method fees = List.iter (fun a -> a#retrait 
		(a#get *. 5. /. 100.)) listOfAccounts
		
	method print = List.iter (fun a -> a#print) listOfAccounts
end;;


class ['a] collection = 
	object (self)
	val mutable items = []
	method add (x : 'a) = items <- x :: items
end;;

class neoBank =
	object
  	inherit [compte] collection
	method balance = List.fold_left 
		(fun a b -> a +. b#get) 0. items

	method print = List.iter (fun a -> a#print) items

	method fees = List.iter 
		(fun a -> a#retrait (a#get *. 5. /. 100.)) items
end;; 



