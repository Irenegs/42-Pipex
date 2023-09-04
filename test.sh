#!/bin/bash

make && make clean

touch a.txt b.txt

T=1

echo "TEST" $T && T=$((T+1))
./pipex pipex.c "cat" "wc -l" a.txt
< pipex.c cat | wc -l > b.txt
echo "Difference:"
diff a.txt b.txt

echo -n > a.txt > b.txt

echo "TEST" $T && T=$((T+1))
./pipex pipex strings "wc -l" a.txt
<pipex strings | wc -l > b.txt
diff a.txt b.txt

echo -n > a.txt > b.txt

echo "TEST" $T && T=$((T+1))
./pipex pipex.c "ls -l     -a" "wc -l" a.txt
< pipex.c ls -l     -a| wc -l > b.txt
diff a.txt b.txt

echo -n > a.txt > b.txt

echo "TEST" $T && T=$((T+1))
./pipex pipex.c "wc -v" cat a.txt
< pipex.c wc -v | cat > b.txt
diff a.txt b.txt

echo -n > a.txt > b.txt

echo "TEST" $T && T=$((T+1))
./pipex pipex.c cat "wc -v" a.txt
< pipex.c cat | wc -v > b.txt
diff a.txt b.txt

#rm -f a.txt b.txt
