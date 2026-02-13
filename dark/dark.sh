#!/bin/zsh

GREEN=$'\e[32m'
RED=$'\e[31m'
RESET=$'\e[0m'

TESTDIR=$1

if [[ -z $TESTDIR ]]; then
  echo "Usage $0 <testdir>"
  exit 1
fi

echo "Compiling dark.cpp..."
g++ -std=c++17 -O2 -o dark dark.cpp && echo "${GREEN}Compilation successful.${RESET}" || { echo "${RED}Compilation failed.${RESET}"; exit 1; }

echo "Compiling dark-checker.cpp..."
g++ -std=c++17 -O2 -o dark-checker dark-checker.cpp && echo "${GREEN}Compilation successful.${RESET}" || { echo "${RED}Compilation failed.${RESET}"; exit 1; }
echo

for input in $TESTDIR/*.in; do
  output=${input%.in}.out
  author_out=$(./dark < $input)
  judge_out=$(cat $output)

  if ! ./dark-checker "$author_out" "$judge_out"; then
    echo "${RED}Test failed for $input${RESET}"
    echo "Author output:"
    echo "$author_out"
    echo "Expected output:"
    echo "$judge_out"
    FAIL=1
  fi

done

if [[ -z $FAIL ]]; then
  echo "${GREEN}All tests passed!${RESET}"
fi