#!/bin/sh
if [ ! -f "bin/main" ]; then
    echo "No main executable found. Running make."
    make
    echo
fi

echo "CPP"
echo "==="
./bin/main $1

echo "javascript"
echo "=========="
if ! hash node 2>/dev/null; then
  echo "Node is not installed. Please install node-js on this machine to run the javascript bench"
else
  node js-comp.js $1
  echo
fi

echo "RUBY"
echo "==="
ruby rb-comp.rb $1
