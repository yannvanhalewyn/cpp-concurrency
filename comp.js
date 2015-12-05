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
var result = sum(1000000000);
var end = new Date().getTime();

console.log("Result: ", result);
console.log("Elapsed: %dms", end-start);
