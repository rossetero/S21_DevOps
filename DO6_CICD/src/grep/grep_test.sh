GREP=/usr/bin/grep
MY_GREP=./s21_grep
TEST_FILES=test_files/*.txt
REGEX_FILES=regex_files/*.txt
PATTERNS=(
    "Lorem"
    "D"
    "i$"
)

FLAGS=("o" "i" "v" "c" "l" "n" "s" "h")

SUCCESS=0
FAIL=0
COUNTER=0


for file in $TEST_FILES; do

  for flag in "${FLAGS[@]}"; do
  for pat in "${PATTERNS[@]}"; do


    grep_output=$($GREP -$flag $pat "$file")

    my_grep_output=$($MY_GREP -$flag $pat "$file")
    let "COUNTER++"

    if [ "$grep_output" == "$my_grep_output" ]; then
      echo "Тест пройден: $file (флаги: -$flag паттерны $pat)"
      let "SUCCESS++"
    else
      echo "Тест не пройден: $file (флаги: -$flag паттерны $pat)"
      let "FAIL++"
      echo "$grep_output"
      echo "--------------------"
      echo $MY_GREP -$flag $pat "$file"
      echo "--------------------"

      echo "$my_grep_output"
    fi
  done
  done
done

for file in $TEST_FILES; do

  for flag1 in "${FLAGS[@]}"; do
  for flag2 in "${FLAGS[@]}"; do
  for flag3 in "${FLAGS[@]}"; do
    flgs=$flag1$flag2$flag3
    if [[ "$flgs" != *"i"* || "$flgs" != *"o"* ]]
    then   
  for pat in "${PATTERNS[@]}"; do
    grep_output=$($GREP -$flag1$flag2$flag3 $pat "$file")

    my_grep_output=$($MY_GREP -$flag1$flag2$flag3 $pat "$file")
    let "COUNTER++"

    if [ "$grep_output" == "$my_grep_output" ]; then
      echo "Тест пройден: $file (флаги: -$flag1$flag2$flag3 паттерны $pat)"
      let "SUCCESS++"
    else
      echo "Тест не пройден: $file (флаги: -$flag1$flag2$flag3 паттерны $pat)"
      let "FAIL++"
      echo "$grep_output"
      echo "--------------------"
      echo $MY_GREP --$flag1$flag2$flag3 $pat "$file"
      echo "--------------------"
      echo "$my_grep_output"
    fi
    
  done
  fi
  done
  done
  done
done


for file1 in $TEST_FILES; do
for file2 in $TEST_FILES; do

  for flag1 in "${FLAGS[@]}"; do
  for flag2 in "${FLAGS[@]}"; do
        flgs=$flag1$flag2
    if [[ "$flgs" != *"o"* ]]
    then 
  for pat1 in "${PATTERNS[@]}"; do
  for pat2 in "${PATTERNS[@]}"; do
  for regfile in $REGEX_FILES; do
    if [ $file1 != $file2 ]
    then
    grep_output=$($GREP -$flag1$flag2 -e $pat1 -f $regfile -e $pat2 "$file1" "$file2")

    my_grep_output=$($MY_GREP -$flag1$flag2 -e $pat1 -f $regfile -e $pat2 "$file1" "$file2")
    let "COUNTER++"

    if [ "$grep_output" == "$my_grep_output" ]; then
      echo "Тест пройден: "$file1" "$file2" (флаги: -$flag1$flag2 паттерны $pat1 $pat2 файл $regfile)"
      let "SUCCESS++"
    else
      echo "Тест не пройден: "$file1" "$file2" (флаги: -$flag1$flag2 паттерны $pat1 $pat2 файл $regfile)"
      let "FAIL++"
      echo "$grep_output"
      echo "--------------------"
      echo $MY_GREP -$flag1$flag2 $pat1 $pat2 "$file"
      echo "--------------------"
      echo "$my_grep_output"
    fi

    fi
    done
    done
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
