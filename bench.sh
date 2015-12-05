#!/bin/sh
if [[ ! -f "bin/main" ]]; then
    echo "No main executable found. Running make"
    make
    echo
fi

echo "javascript"
echo "=========="
node comp.js
echo

echo "CPP"
echo "==="
./bin/main
