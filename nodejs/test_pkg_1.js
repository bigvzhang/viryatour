function AddNumbers(a,b){
    return a+b;
}
function MinusNumbers(a,b){
    return a-b;
}

module.exports.AddNumbers = AddNumbers;
module.exports.MinusNumbers = MinusNumbers;
// form 2
//module.exports = {AddNumbers, MinusNumbers}
