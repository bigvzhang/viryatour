/**
 * AUTHOR
 *      VicZhang(VicBig@qq.com)
 * NAME
 *      test_iconv.js - 
 * TODO
 *      
 */
var iconv = require('iconv-lite');

var oriText = '=>你好<=';
console.log(oriText);

var encodedBuff = iconv.encode(oriText, 'utf8');
console.log(encodedBuff);
// <Buffer c4 e3>

var decodedText = iconv.decode(encodedBuff, 'utf8')
console.log(decodedText);
// 你好

var wrongText = iconv.decode(encodedBuff, 'gbk');
console.log(wrongText);
