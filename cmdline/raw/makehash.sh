#!/bin/sh

~/Downloads/gperf-3.1/src/gperf --multiple-iterations=1 \
  --compare-strncmp --compare-lengths --includes \
  --includes --ignore-case --readonly-tables \
  --struct-type --slot-name=word words.txt > hash.h

cp hash.h hash.h_bak

#sed -i -e 's/(int)(long)/(intptr_t)/g' hash.h
#sed -i -e 's/{-1},/{(int)(size_t)&((struct stringpool_t *)0), -1}/g' hash.h
