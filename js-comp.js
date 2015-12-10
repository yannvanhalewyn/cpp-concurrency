#! /usr/bin/env node

var NUMBER = 500000000; // 5 * 10^8
if (process.argv.length == 3)
  NUMBER = parseInt(process.argv[2]);

// The function under test
function sum(x) {
  var sum = 0;
  for (var i = 0; i <= x; i++) {
    sum += i;
  }
  return sum;
}

// Timing the result
var start = new Date().getTime();
var result = sum(NUMBER);
var end = new Date().getTime();

console.log("Result: ", result);
console.log("Elapsed: %dms", end-start);
