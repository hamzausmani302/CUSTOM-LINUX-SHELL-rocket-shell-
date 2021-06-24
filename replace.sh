#!/bin/bash

args1=$1	#filename
args2=$2	#word to replace
args3=$3	#final word
if [[ -f $args1 ]]
then
	sed -i "s/$args2/$args3/g"  $args1;
	
else
	echo "file donot exist"; 
	
fi






