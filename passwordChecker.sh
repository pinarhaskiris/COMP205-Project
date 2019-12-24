#!/bin/bash
#password safety checker
#for password to be considered safe, it should have the following features;
# - at least 8 characters long
# - has at least one lowecase character
# - has at least one uppercase character
# - has at least one number
# - has at least one special character such as *, -, !, < etc.
#
#according to the given password, this program tells the user whether the password is safe to use or not


tput setaf 5 #setting a color
echo "You entered: $1"
tput sgr0 #resetting the color

lowercase=`echo $1 | grep '.*[a-z].*'` #checking if there are any lowercase letters
uppercase=`echo $1 | grep '.*[A-Z].*'` #checking if there are any uppercase letters
number=`echo $1 | grep '.*[0-9].*'` #checking if there are any numbers
special_characters=`echo $1 | grep '[* | - | ! | < | > | _ | & | % | ^ | # | +]'` #checking if there are any special characters

#for the variables below
#if variable = 0 -> condition is not provided
#if variable = 1 -> condition is provided
isLowercase=0
isUppercase=0
isNumber=0
isLong=0
isSpecial=0

#to check whether there is a lowercase letter
if [ `echo $lowercase | wc -m` -gt 1 ]
then
  let isLowercase++
  let strongness++
fi

#to check whether there is an uppercase letter
if [ `echo $uppercase | wc -m` -gt 1 ]
then
  let isUppercase++
  let strongness++
fi

#to check whether there is a number
if [ `echo $number | wc -m` -gt 1 ]
then
  let isNumber++
  let strongness++
fi

#to check whether there is a special character
if [ `echo $special_characters | wc -m` -gt 1 ]
then
  let isSpecial++
  let strongness++
fi

#to check whether the password is long enough
if [ `echo $1 | wc -m` -gt 8 ]
then
  let isLong++
  let strongness++
fi

#if statements to determine the strongness of the password
if [ $strongness -eq 5 ]
then
  tput setaf 2 #setting the text color to green
  echo "Password strongness : Strong."
  echo "Using this password is recommended. 👍🏻"
  tput sgr0 #resetting colors

elif [ $strongness -eq 4 ]
then
  tput setaf 3
  echo "Password strongness : Upper Medium."
  tput sgr0
elif [ $strongness -eq 3 ]
then
  tput setaf 4
  echo "Password strongness : Medium. 😕"
  tput sgr0
elif  [ $strongness -eq 2 ]
then
  tput setaf 6
  echo "Password strongness : Lower Medium."
  tput sgr0
elif [ $strongness -eq 1 ]
then
  tput setaf 1
  echo "Password strongness : Weak. 👎🏻"
  echo "Using this password is not recommended."
  tput sgr0
else
  tput setaf 1
  echo "Please enter a stronger password."
  tput sgr0
fi

#if statements to determine the features the password has
if [ $isLong -eq 0 ]
then
  echo "The password is not long enough."
fi
if [ $isUppercase -eq 0 ]
then
  echo "The password does not contain any uppercase letter."
fi
if [ $isSpecial -eq 0 ]
then
  echo "The password does not contain any special characters."
fi
if [ $isLowercase -eq 0 ]
then
  echo "The password does not contain any lowercase letter."
fi
if [ $isNumber -eq 0 ]
then
  echo "The password does not contain any numbers."
fi
exit 0 
