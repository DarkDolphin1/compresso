#!/usr/bin/env bash
set -e

FILE="random.bin"
RESULTS="results.txt"

TIME_CMD=$(command -v time)

rm -f comp.bin "$FILE.gz" "$FILE.xz" "$FILE.zst" "$FILE.lz4" \
  random.bin linear.bin \
  compresso \
  "$RESULTS" tmp_time.txt

echo "=== Building compresso (MAX OPT) ==="
clang++ -O3 -march=native -flto -DNDEBUG -Iinclude *.cpp src/*.cpp -o compresso

echo "=== Building test generator (MAX OPT) ==="
clang++ -O3 -march=native -flto -DNDEBUG test/test.cpp -o test.exe

echo "=== Generating test files ==="
./test.exe 0 16 # this must create random.bin and linear.bin

if [ ! -f "$FILE" ]; then
  echo "Error: $FILE not generated."
  exit 1
fi

run_test() {
  NAME=$1
  CMD=$2
  OUTFILE=$3

  echo "Running $NAME..."

  $TIME_CMD -f "%e %M" -o tmp_time.txt bash -c "$CMD"

  SIZE=$(stat -c%s "$OUTFILE")
  read WALL MEM <tmp_time.txt

  echo "$NAME|$SIZE|$WALL|$MEM" >>"$RESULTS"
}

echo
echo "=== Benchmarking $FILE ==="

run_test "compresso" "./compresso $FILE comp.bin" "comp.bin"
run_test "gzip -9" "gzip -9 -k -f $FILE" "$FILE.gz"
run_test "xz -9e -T0" "xz -9e -T0 -k -f $FILE" "$FILE.xz"
run_test "zstd -22 --ultra -T0" "zstd -22 --ultra -T0 -k -f $FILE" "$FILE.zst"
run_test "lz4 -9" "lz4 -9 -f $FILE $FILE.lz4" "$FILE.lz4"

echo
printf "%-25s %-15s %-12s %-12s\n" "Algorithm" "Size (MB)" "Time (s)" "Max RSS (MB)"
printf "%-25s %-15s %-12s %-12s\n" "---------" "---------" "--------" "------------"

while IFS="|" read -r NAME SIZE WALL MEM; do
  SIZE_MB=$(awk "BEGIN {printf \"%.2f\", $SIZE/1024/1024}")
  MEM_MB=$(awk "BEGIN {printf \"%.2f\", $MEM/1024}")
  printf "%-25s %-15s %-12s %-12s\n" "$NAME" "$SIZE_MB" "$WALL" "$MEM_MB"
done <"$RESULTS"