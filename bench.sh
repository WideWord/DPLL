#!/usr/bin/env bash

for f in fixtures/aim-100-1-*.cnf
do
	if [[ $f == *"yes"* ]]; then
		if [[ $(./dpllk $f) == *"UNSATISFIABLE"* ]]; then
			echo "NO"
		else
			echo "YES"
		fi
	else
		if [[ $(./dpllk $f) == *"UNSATISFIABLE"* ]]; then
			echo "YES"
		else
			echo "NO"
		fi
	fi

done