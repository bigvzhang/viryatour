const io = require('virya_io')
class A {
	constructor(){
		this.a = 1
	}
}

class B extends A{
	constructor(){
		super()
		this.b = 2
	}
}

class C extends A{
	c = 3
	print = function(){io.printf("%d %d\n",a,c)}
	speak(){io.printf("I am c!\n",a,c)}
}

let a = new A()
let b = new B()
let c = new C()
io.print_obj(a, "Object A")
io.print_obj(b, "Object B")
io.print_obj(c, "Object C")
c.speak()
io.print_obj_type(c,       "Class C  => ")
io.print_obj_type(c.print, "C::print => ")
io.print_obj_type(c.speak, "C::speak => ")

