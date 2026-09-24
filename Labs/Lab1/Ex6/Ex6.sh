#!/bin/bash

echo "Nhap so nguyen N:"
read N

if [ $((N % 2)) -eq 0 ]; then
    echo "$N la so chan"
else
    echo "$N la so le"
fi

echo "Cac so tu 1 den $N:"

for ((i=1; i<=N; i++))
do
    if [ $((i % 2)) -eq 0 ]; then
        echo "$i la so chan"
    else
        echo "$i la so le"
    fi
done

echo "Kiem tra cac tep:"

for file in ../Hello.txt ../Ex4_results.txt Ex6.sh
do
    if [ -f "$file" ]; then
        echo "$file exists"
    else
        echo "$file does not exist"
    fi
done
