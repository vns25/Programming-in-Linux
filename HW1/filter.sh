#!/bin/sh

function average () {
    total=0
    list=( `ls -l $dir | tr -s ' ' | cut -d ' ' -f 5` )
    for size in ${list[@]}; do 
        let total+=$size
    done 
    
    numFiles=`ls  $dir | wc -l`
    avg=$(( total / numFiles))
}

function filter () {
    filterFiles=""
    i=0
    for file in "${files[@]}"; do
        if [ "${list[i]}" -gt "$avg" ]; then 
            filterFiles+="$file "
        fi
        let i++
    done
    echo $filterFiles
}

function main () {
    IFS=$'\n'
    cd ~
    dir=$1
    files=(`ls ~/$dir`)
    if [ -d "$1" ]; then
        average $dir
        filter
    fi

}   

main $1