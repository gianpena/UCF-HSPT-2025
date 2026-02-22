#!/bin/zsh
alias diff=/opt/homebrew/Cellar/diffutils/3.12/bin/diff

GREEN=$'\e[32m'
RED=$'\e[31m'
RESET=$'\e[0m'

TESTDIR=$1

if [[ -z $TESTDIR ]]; then
  echo "Usage $0 <testdir>"
  exit 1
fi

echo "Compiling tyler.cpp..."
g++ -std=c++17 -O2 -o tyler tyler.cpp && echo "${GREEN}Compilation successful.${RESET}" || { echo "${RED}Compilation failed.${RESET}"; exit 1; }
echo

for input in $TESTDIR/*.in; do
  output=${input%.in}.out

  if ! diff -Z <(./tyler < $input) <(cat $output) >/dev/null; then
    echo "${RED}Wrong answer on ${input}${RESET}"
    FAIL=1
  fi

done

if [[ -z $FAIL ]]; then
  echo "${GREEN}All tests passed!${RESET}"
fi