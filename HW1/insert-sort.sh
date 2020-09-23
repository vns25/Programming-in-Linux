#!/bin/bash

function sort () {
    arr=( "$@" )
    
    i=0
    idxMin=0
    for val in ${arr[@]}; do 
        idxMin=$i

        for (( j=i+1; j < ${#arr[@]}; j++ )); do 
            if [ ${arr[j]} -lt ${arr[idxMin]} ]; then 
                idxMin=$j
            fi
            let j++
        done 

        temp=${arr[idxMin]}
        arr[$idxMin]=${arr[i]}
        arr[$i]=$temp

        let i++
    done 

    echo "${arr[@]}"

}

sort $@