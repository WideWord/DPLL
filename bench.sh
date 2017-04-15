#!/usr/bin/env bash

for f in fixtures/aim-{200,100,50}*.cnf
do
	if [[ $f == *"yes"* ]]; then
		if [[ $(./dpll $f) == *"UNSATISFIABLE"* ]]; then
			echo "NOOOOOOOOOOOOOOOO"
		else
			echo "YES"
		fi
	else
		if [[ $(./dpll $f) == *"UNSATISFIABLE"* ]]; then
			echo "YES"
		else
			echo "NOOOOOOOOOOOOOOOO"
		fi
	fi

done