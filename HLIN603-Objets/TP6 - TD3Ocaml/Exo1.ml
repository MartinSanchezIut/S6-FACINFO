(* #use "TD3.ml";; *)
(* PAS FINI *) 

class min ( init : int) =
  object(self)
    val x = init
    method get = x
    method min y = if self#get < y then self#get else y
  end;;

class min_max ( init : int ) =
  object ( self )
    inherit min init
    method max y = if self#min y = y then self#get else y
  end;;

class other =
  object
    method get = 1
    method min n = n-1
    method max n = n+1
  end;;

class ['a] cell ( init : 'a ) =
  object
    val mutable cont = init
    method get = cont
    method set n = cont <- n
  end;;

let m = new min 1 ;;
let mm = new min_max 2 ;;
let o = new other ;;
let c = new cell 1 ;;


let natural (o:min) = o#min(0) = 0;;
let negative ( o : #min ) = o#min ( 0 ) = o#get ;;
let positive o = o#get > 0 ;;




