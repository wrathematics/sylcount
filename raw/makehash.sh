#!/bin/sh

#gperf --includes --ignore-case --readonly-tables --global-table --struct-type --switch=2 --slot-name=word words.txt > hash.h

gperf --includes --ignore-case --readonly-tables --struct-type --slot-name=word words.txt > hash.h


