#!/bin/bash
CAT="/bin/cat"
MY_CAT=./s21_cat
TEST_FILES=test_files/*.txt
CAT_FLAGS_LIST=(
  "bestnv"
  "vse"
  "bet"
  "b"
  "e"
  "s"
  "t"
  "n"
  "v"
)
SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""

for file in $TEST_FILES; do

  for flag in "${CAT_FLAGS_LIST[@]}"; do

    $CAT -$flag "$file" > cat.log

    $MY_CAT -$flag "$file" > my_cat.log
    let "COUNTER++"
    DIFF=$(diff cat.log my_cat.log)
    if [ "$DIFF" = "" ]; then
      echo "Тест пройден: $file (флаги: -$flag)"
      let "SUCCESS++"
    else
      echo "Тест не пройден: $file (флаги: -$flag)"
      let "FAIL++"
    fi
    
    
  done
done

for file in $TEST_FILES; do

  for flag1 in "${CAT_FLAGS_LIST[@]}"; do
  for flag2 in "${CAT_FLAGS_LIST[@]}"; do

    let "COUNTER++"

    $CAT -$flag1$flag2 "$file" > cat.log
    $MY_CAT -$flag1$flag2 "$file" > my_cat.log
    DIFF=$(diff cat.log my_cat.log)

    if [ "$DIFF" = "" ]; then
      echo "Тест пройден: $file (флаги: -$flag1$flag2)"
      let "SUCCESS++"
    else
      echo "Тест не пройден: $file (флаги: -$flag1 -$flag2)"
      let "FAIL++"
    fi
    
  done
  done
done

for file in $TEST_FILES; do
  for flag1 in "${CAT_FLAGS_LIST[@]}"; do
  for flag2 in "${CAT_FLAGS_LIST[@]}"; do
  for flag3 in "${CAT_FLAGS_LIST[@]}"; do
  
    if [ $flag1 != $flag2 ] && [ $flag2 != $flag3 ] && [ $flag1 != $flag3 ]
    then
    let "COUNTER++"

    $CAT -$flag1 -$flag2 -$flag3 "$file" > cat.log
    $MY_CAT -$flag1 -$flag2 -$flag3 "$file" > my_cat.log
    DIFF=$(diff cat.log my_cat.log)

    if [ "$DIFF" = "" ]; then
      echo "Тест пройден: $file (флаги: -$flag1 -$flag2 -$flag3)"
      let "SUCCESS++"
    else
      echo "Тест не пройден: $file (флаги: -$flag1 -$flag2 -$flag3)"
      let "FAIL++"
    fi
    
    fi
  done
  done
  done
done
rm cat.log my_cat.log
printf "\n"
echo "FAILED: $FAIL"
echo "SUCCESSFUL: $SUCCESS"
echo "ALL: $COUNTER"
printf "\n"

echo -e "^^^^^^^^^^^^^^^^^^^^^^^^\n"
echo -e "GNU TESTS\n"
echo -e "^^^^^^^^^^^^^^^^^^^^^^^^\n"
    file=test_files/test_1_cat.txt
    cat_output=$($CAT -e "$file")
    my_cat_output=$($MY_CAT -vE "$file")
    if [ "$cat_output" == "$my_cat_output" ]; then
      echo "Тест пройден"
    else
      echo "Тест не пройден"
    fi

    cat_output=$($CAT -t "$file")
    my_cat_output=$($MY_CAT -vT "$file")
    if [ "$cat_output" == "$my_cat_output" ]; then
      echo "Тест пройден"
    else
      echo "Тест не пройден"
    fi

        cat_output=$($CAT -s "$file")
    my_cat_output=$($MY_CAT --squeeze-blank "$file")
    if [ "$cat_output" == "$my_cat_output" ]; then
      echo "Тест пройден"
    else
      echo "Тест не пройден"
    fi

            cat_output=$($CAT -n "$file")
    my_cat_output=$($MY_CAT --number "$file")
    if [ "$cat_output" == "$my_cat_output" ]; then
      echo "Тест пройден"
    else
      echo "Тест не пройден"
    fi

    cat_output=$($CAT -b "$file")
    my_cat_output=$($MY_CAT --number-nonblank "$file")
    if [ "$cat_output" == "$my_cat_output" ]; then
      echo "Тест пройден"
    else
      echo "Тест не пройден"
    fi