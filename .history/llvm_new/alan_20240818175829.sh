#!/bin/bash

./alanc < $1 > a.ll
llc -mtriple=aarch64-apple-macosx11.0.0 -o a.s a.ll
clang -o a.out a.s lib/lib.a -no-pie
