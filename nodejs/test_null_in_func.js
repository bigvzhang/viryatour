const io = require('virya_io')
function func(w){
	io.print_obj_type(w)	
}

func()
func(null)
func(1)

