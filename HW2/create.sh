#!/bin/sh

function depthfirst {
	local level=$1
	local dir=$2
	
    if [[ $level -lt $depth ]]; then
        level=$((level+1))
	    local i=0
        while [[ $i -lt $breadth ]]; do
            mkdir -p "$dir/$i"
            #echo $dir/$i
            depthfirst $level $dir/$i
            i=$((i+1))
	    done
    fi 
}

function breadthfirst {
    local open=( $dir )

    for (( i=0; i < $depth; i++ )); do 
        #echo "LEVEL: $i"
        local temp2=( )
        for x in "${open[@]}" ; do 
            local temp=()
            #echo "X: $x"
            for (( j=0; j<$breadth; j++ )); do 
                mkdir -p "$x/$j"
                #echo $dir/$i
                temp+=("$x/$j")
            done 
            temp2+=( ${temp[@]} )
        done 
        open=( ${temp2[@]} )
    done 
}


depth=$1
breadth=$2
dir=$3 
traversal=$4

cd ~
if [[ $traversal == "depth" ]]; then 
    depthfirst 0 $dir
elif [[ $traversal == "breadth" ]]; then 
    breadthfirst
fi 

