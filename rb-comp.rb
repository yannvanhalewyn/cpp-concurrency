#! /usr/bin/env ruby

NUM = 100000000

def sum(from, to)
  sum = 0
  for i in from..to
    sum += i
  end
  sum
end

# Splits given a load and returns a hash with :from and :to as if the
# $load had been split into $chunks equal chunks
def splitLoad load, chunk, chunks
  return {
    from: (load * (chunk - 1) / chunks) + 1,
    to: load * (chunk) / chunks
  }
end

def splitLoadIntoWorkersAndWait(load, numWorkers)
  # Split load into multiple work chunks and hand those to threads
  workers = []
  (1..numWorkers).each do |i|
    chunk = splitLoad load, i, numWorkers
    workers << Thread.new { Thread.current[:output] = sum(chunk[:from], chunk[:to]) }
  end

  # Join each thread and store the output
  ret = 0
  workers.each do |w|
    ret += w.join[:output]
  end

  ret
end

def splitLoadIntoProcessesAndWait(load, numProcesses)
  (0..numProcesses-1).each do |i|
    chunk = splitLoad load, i, numProcesses
    fork do
      sum(chunk[:from], chunk[:to])
    end
  end
  Process.waitall
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
