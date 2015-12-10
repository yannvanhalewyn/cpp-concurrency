#! /usr/bin/env ruby

NUM = 100000000

def sum(from,x)
  sum = 0
  for i in from..x
    sum += i
  end
  sum
end

def splitLoadIntoWorkersAndWait(load, numWorkers)
  # Split load into multiple work chunks and hand those to threads
  workers = []
  (0..numWorkers-1).each do |i|
    from = (i * load / numWorkers) + 1;
    to = (i + 1) * load / numWorkers;
    workers << Thread.new { Thread.current[:output] = sum(from, to) }
  end

  # Join each thread and store the output
  ret = 0
  workers.each do |w|
    puts "Joining worker"
    ret += w.join[:output]
  end

  ret
end

def test(load, numWorkers)
  puts "Running a test with #{numWorkers} thread(s)."
  start = Time.now
  result = splitLoadIntoWorkersAndWait(load, numWorkers)
  stop = Time.now
  puts "Solution: #{result}"
  puts "Elapsed: #{(stop - start) * 1000}ms"
end

test(NUM, 1)
test(NUM, 2)
test(NUM, 4)
