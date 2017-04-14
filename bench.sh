#!/usr/bin/env bash

set -c

for f in fixtures/*.cnf
do
	echo "Testing $f"
	./dpll $f
done