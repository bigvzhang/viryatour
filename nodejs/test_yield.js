var generator1 = function*(){
	yield 1;
	yield 2;
	yield 3;
	yield 4;
};

var generator2 = function*(){
	for(let i = 0; i < 5; i++)
	yield (i+1)
};

var itr = generator1();
for(let i = 0; i < 6; i++){
	console.log(itr.next());
}

var itr2 = generator2();
for(let i = 0; i < 6; i++){
	console.log(itr2.next());
}
