#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""

s21_command=(
    "./s21_grep"
    )
sys_command=(
    "grep"
    )

tests=(
"test_files/lorem.txt"
"test_files/lorem.txt test_files/inter.txt test_files/merol.txt"
)
flags=(
    "o" "i" "v" "c" "l" "n" "s" "h"
)

patterns=(
    "Lorem"
    "i$"
)

regex_files=(
    "regex_files/regex.txt"
)

for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
    for file in "${regex_files[@]}"
    do
    for pat in "${patterns[@]}"
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                param="-$var1 -$var2 -f $file -e $pat $i"                  
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose -q --log-file="${s21_command[@]}".log ./"${s21_command[@]}" $param > /dev/null
    leak=$(grep -ic -A10000 "LEAK SUMMARY:" "${s21_command[@]}".log || true)
    leak2=$(grep -ic -A10000 "ERROR SUMMARY: [^0]" "${s21_command[@]}".log || true)
    let "COUNTER++"
    if [ "$leak" -eq "0" ] && [ "$leak2" -eq "0" ]
    then
        let "SUCCESS++"
        echo "$COUNTER - Success $param"
    else
        let "FAIL++"
        echo "$COUNTER - Fail $param"
    fi
    rm -f "${s21_command[@]}".log "${sys_command[@]}".log

            done
        fi
    done
    done
    done
done


printf "\n"
echo "FAILED: $FAIL"
echo "SUCCESSFUL: $SUCCESS"
echo "ALL: $COUNTER"
printf "\n"
