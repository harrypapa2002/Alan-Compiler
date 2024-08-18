#!/bin/bash

./alanc < $1 > a.ll
llc -o a.s a.ll
clang -o a.out a.s lib/lib.a 
