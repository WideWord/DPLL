#!/usr/bin/env bash

for f in fixtures/aim-{100,50}*.cnf
do
	if [[ $f == *"yes"* ]]; then
		if [[ $(./dpll $f) == *"UNSATISFIABLE"* ]]; then
			echo "NO"
		else
			echo "YES"
		fi
	else
		if [[ $(./dpll $f) == *"UNSATISFIABLE"* ]]; then
			echo "YES"
		else
			echo "NO"
		fi
	fi

done