if test -f "$1"; then #do the following operations only if the input file exists

  isEncrypted=`cat $1 |  grep '.*[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9].*'` #if there are 8 numbers back to back the file is very likely to be encrypted

  if [ `echo $isEncrypted | wc -m` -gt 1 ] #if the file is encrypted
  then
    #ask the user if they still want to see the file
    echo "This is a crypted file. Do you still want to see it?"
    echo "Please enter 1 to see."
    read input #get an input from the user
    if [ $input -eq 1 ] #if the input = 1
    then
      cat $1 #print the content of the file on screen
    else
      echo "Stopped dog command." #stop the function if the user doesn't want to see the file
    fi

  else
    cat $1
  fi

else
  tput setaf 1 #to print the following message red
  echo "The input file does not exists."
  tput sgr0 #resetting color
fi
echo
exit 0
