Fun with c++ / concurrency + comparisons
===

Just having fun with multiple threads in cpp. Comparing the same workload to
node-js. Pretty impressed with the javascript/node performances!

However, the ruby results were terrible. I'm wondering if I did something wrong here. On a relatively high workload (5 * 10^8 numbers), cpp would bench at about 1.5s, javascript ditto and ruby would take more than a minute. Also, adding more workers didn't affect anything. Probably because ruby has a GIL. I tried JRuby as well, same story.  I've also tried forking processes, no luck. Or is ruby just not suitable for calculating stuff? Because calculations are of course a niche occupation for programs :).

## Running / Building
---

Build the c++ program:

`$ make`

Run benches (will run make if necessary):

`$ ./bench.sh`

Pass in your own number to run the benches with:

`$ ./bench.sh 20000`

Run any bench with your own number, or not (defaults to 5 * 10^8)

`$ ./bin/main $mynumber`

`$ ruby rb-comp.rb $mynumber`

`$ node js-comp.js $mynumber`

All you need is make and gcc or clang (and node for the js).


## My results
---
*Ran on a core 2 duo (Yes I have an old machine)*

*Sum of all numbers between 1 and 5 x 10^8*

*Threads* | C++ | Javascript(node) | Ruby | JRuby
:--------|:--------:|---------:|---------:|---------:
1 | 1400ms | 1389ms | 32 331ms | 27 773ms
2 | 733ms | N.A.      | 31 435ms | 21 224ms
4 | 723ms   | N.A.      |  29 887ms | 22 326ms
