#!/bin/bash
time=0
for ((i=0; i<60; i++ ))
do
    current_date=`date +"%Y_%m_%d_%H_%M_%S"`
    file="yahoo_${current_date}.html"
    page="https://finance.yahoo.com/most-active/"
    wget -O $file $page
    python3 web.py $file
    sleep 60
done 