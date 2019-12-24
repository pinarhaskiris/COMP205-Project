#!/bin/bash

# Getting all the data form the internet for the first argument.
URL='https://www.onelook.com/?w=$1&ls=a'
URL=${URL%$'\r'}
curl --progress-bar $URL -o word.txt

isThere=$(grep -woi "Sorry, no dictionaries indexed in the selected category contain the word" word.txt) # If the website doesn't have the word
isThere2=$(grep -woi "Example searches" word.txt)   # If the given input is nothing ('') it tries to search nothing and the website shows examples.

# If the website doesn't have the word
if [[ "$isThere" == "Sorry, no dictionaries indexed in the selected category contain the word" ]]
then
	echo 1 > isthere.txt #There is no such a word. Coded as '1'
	echo "NOT FOUND $1" >> ./Log/log.txt # Writes the result into log file
elif [[ "$isThere2" == "Example searches" ]]
then
	echo 2 > isthere.txt #The all word parts are not in the internet. Coded as '2'
	echo "NO ANY MATCH $1" >> ./Log/log.txt # Writes the result into log file
else
	echo 0 > isthere.txt #The word is in the internet or dictionary. Coded as '0'
	echo "FOUND $1" >> ./Log/log.txt # Writes the result into log file
fi
exit 0
