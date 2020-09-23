#!/bin/sh
function count {
    declare -a array=( $(ls /usr/bin) )  

    for letter in {a..z}; do 
        counter=0

        for command in "${array[@]}"; do 
            firstletter=${command:0:1}

            if [ $firstletter = $letter ] ; then 
                counter=$((counter+1))
            fi
        done 

        echo $letter $counter
    done 

}

count 