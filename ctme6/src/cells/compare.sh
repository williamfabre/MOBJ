#! /bin/bash

find $1 > file1 
tail -n +1 file1 > file1
find $2 > file2 
tail -n +1 file2 > file2

result=$(diff file1 file2)

if [ $? -eq 0 ]
then
        echo "$1 == $2 files are the same"
else
        echo "$1 != $2 files are different"
        echo "$result"
fi
rm file1
rm file2
