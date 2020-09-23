#!/bin/sh

function reverse () {
    for (( i=${#arr[@]}-1; i>=0 ; i-- )); do
        echo "${arr[i]}"
    done
        
}

function main() {
    IFS=$'\n'
    dir=$1
    cd ~
    arr=( $(ls $dir) )
    reverse $dir
}

main $1



