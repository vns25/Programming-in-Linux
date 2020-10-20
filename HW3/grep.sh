#!/bin/sh

function exprTitle() {
    cat clips.txt | 
    while read info; do 
        echo `expr "$info" : "\(.*\) by.*"`
    done > expr-title.txt
}

function exprUser() {
    cat clips.txt | 
    while read info; do 
        echo `expr "$info" : ".*by \(.*\) [0-9].* ago .*"`
    done > expr-user.txt
}

function exprUpload() {
    cat clips.txt | 
    while read info; do 
        echo `expr "$info" : ".* \([0-9].*\) ago.*"`
    done > expr-upload.txt
}
    
function exprDur() {
    cat clips.txt | 
    while read info; do 
        echo `expr "$info" : ".*ago \(.*\).* [0-9].* views.*"`
    done > expr-dur.txt
}

function exprViews() {
    cat clips.txt | 
    while read info; do 
        echo `expr "$info" : ".* \([0-9].*\) views.*"`
    done > expr-views.txt
}

function exprGrep() {
    exprTitle
    exprUser
    exprUpload
    exprDur
    exprViews
    paste expr-title.txt expr-user.txt expr-upload.txt expr-dur.txt expr-views.txt > expr.csv
}

function sedGrep() {
    cat clips.txt | sed -n 's/\(.*\) by \(.*\) \([0-9].*\) ago \(.*\) \([0-9,].*\) views$/\"\1\",\"\2",\"\3\",\"\4\",\"\5\"/p' > sed.csv
}

function grepExtract() {
    cat clips.txt | ggrep -oP '.*(?= by)' > grep-title.txt
    cat clips.txt | ggrep -oP '(?<=by ).*(?= [0-9].* ago)' > grep-user.txt
    cat clips.txt | ggrep -oP '.*(\K[0-9].*)(?= ago)'> grep-upload.txt
    cat clips.txt | ggrep -oP '(?<= ago)\K.*(?= [0-9].* views)' > grep-dur.txt
    cat clips.txt | ggrep -oP '.*(seconds | minutes )\K.*(?=views)' > grep-views.txt
    paste grep-title.txt grep-user.txt grep-upload.txt grep-dur.txt grep-views.txt > grep.csv
}
    
function main() {

    grep '</ytd-thumbnail><div' index.html | 
    while read thumbnail;
    do 
        info=`expr "$thumbnail" : ".*aria-label=\"\(.*\)\" title=\".*"`;
        echo $info
    done > clips.txt

    exprGrep
    sedGrep
    grepExtract
    
}


main