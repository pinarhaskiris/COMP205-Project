#!/bin/bash


#curlInfoCoin()

#Gets webadress html file as a txt called as given variable.
#Controls whether there is a page according to variable which is given.
#If there is not, the program will be stop.
#If there is, txt file will be created.
#For the log file creation time is taken.

curlInfoCoin(){
	curl --progress-bar https://coinmarketcap.com/currencies/$1/ -o $1.txt
	isThere=$(grep -woi "Sorry" $1.txt) # If the website doesn't have the coin
	
	if [[ "$isThere" == "Sorry" ]] #If there is not
	then
		echo -n "There is no coin called as"
		tput bold
		echo " $1"
		tput sgr0
		exit 0
	else
		filename=$(date +%m-%d-%Y--%T) #file creation and data time
	fi
}


#getOneCoin()

#If user gives only 1 argument, this function will be called.
#Calls curlInfoCoin() and will create a txt file if there is a page in the website.
#Also, derives all the data from the txt file and writes into log txt

getOneCoin(){

	curlInfoCoin $1
{ # Getting all the data form the internet for the first argument.
	first_price=$(getPriceInt $1)
	first_market_rank=$(getMarketRankInt $1)
	first_market_cap=$(getMarketCap $1)
	first_day_volume=$(getDayVolume $1)
	first_circ_supp=$(getCirculationSupplyInt $1)
	first_alltime_high=$(getAllTimeHigh $1)
	getAllTimeHighDate $1
	first_alltime_low=$(getAllTimeLow $1)
	getAllTimeLowDate $1
	first_oneyear_high=$(getOneYearHigh $1)
	first_oneyear_low=$(getOneYearLow $1)
	first_ninetyday_high=$(getNinetyDayHigh $1)
	first_ninetyday_low=$(getNinetyDayLow $1)
	first_thirtyday_high=$(getThirtyDayHigh $1)
	first_thirtyday_low=$(getThirtyDayLow $1)
	first_sevenday_high=$(getSevenDayHigh $1)
	first_sevenday_low=$(getSevenDayLow $1)
	first_oneday_high=$(getOneDayHigh $1)
	first_oneday_low=$(getOneDayLow $1)
	first_yesterday_high=$(getYesterdayHigh $1)
	first_yesterday_low=$(getYesterdayLow $1)
	first_yerterday_open=$(getYesterdayOpen $1)
	first_yesterday_close=$(getYesterdayClose $1)
	first_=yesterday_volume$(getYesterdayVolume $1)
}

}


#getTwoCoin()

#If user gives only 2 argument, this function will be called.
#Calls curlInfoCoin() and will create a txt file if there is a page in the website.

getTwoCoin(){

	curlInfoCoin $1
	curlInfoCoin $2
}

{ # Get Functions. They all derive the data from the text file. All of them writes into log file.

getPriceString(){ 	# Gets Price as a string and returns
	#price string
		price_string=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "$1 Price</div><div>.*ROI" | grep -woi "$.*USD")
		echo $price_string
}
getPriceInt(){		# Gets Price as a floating but it is a string and returns
		# PRICE INTEGER
		price_int=$(egrep -woi "About $1.*USD</div>" $1.txt | grep -woi "$1 Price</div><div>.*ROI" | grep -woi "$.*USD" | sed -E 's/,|\$| USD//g') # | grep -o ".*[.]" | sed 's/[.]//')
		echo "All information about $1 in $filename" >> ./Log/$1-$filename.txt
		echo "Price int: `getPriceString $1`" >> ./Log/$1-$filename.txt
		echo $price_int
}
getMarketRank(){	# Gets market rank as a string and returns
	#market rank
		market_rank=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "Market.*Market" | grep -woi "#[0-9]")
		#echo "Market Rank: $market_rank" >> ./Log/$1-$filename.txt
		echo $market_rank
}
getMarketRankInt(){ # Gets market rank as an integer and returns
	#market rank integer
		market_rank_int=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "Market.*Market" | grep -woi "#[0-9]"| sed 's/#//')
		echo "Market Rank int: `getMarketRank $1`" >> ./Log/$1-$filename.txt
		echo $market_rank_int
}
getMarketCap(){		# Gets market cap as an integer and returns

		#market cap int
		market_cap_int=$(grep -woi "About $1.*USD</div>" $1.txt  | grep -woi "Market.*24 Hour Volume" | grep -woi -m 1 "$.*USD" | sed -E 's/,|\$| USD//g')
		echo "Market cap: $market_cap_int" >> ./Log/$1-$filename.txt
		echo $market_cap_int
}
getDayVolume(){		# Gets 24 Hour Volume as an integer and returns
		#24 HOUR VOLUME
		day_volume_int=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "24 Hour Volume.*Circulating" | grep -woi "$.*USD" |  sed -E 's/,|\$| USD//g')
		echo "Day volume int: $day_volume_int" >> ./Log/$1-$filename.txt
		echo $day_volume_int
}
getCirculationSupplyString(){	# Gets Circulation Supply as a string and returns
		#CIRCULATION SUPPLY
		circulation_supply=$(grep -woi "About $1.*USD</div>"  $1.txt | grep -woi "Circulating Supply.*Total Supply"  | grep -woi "<div>.*<\/div>" | sed 's/<div>//g' | sed 's/<\/div>//g' )
		#echo "Ciculation Supply: $circulation_supply" >> ./Log/$1-$filename.txt
		echo $circulation_supply
}
getCirculationSupplyInt(){		# Gets Circulation Supply as an integer and returns

		#Circulation supply integer
		circulation_supply_int=$(grep -woi "About $1.*USD</div>"  $1.txt | grep -woi "Circulating Supply.*Total Supply"  |\
		 grep -woi "<div>.*<\/div>" | sed 's/<div>//g' | sed 's/<\/div>//g' | grep -wo "[0-9].*[0-9]" | sed 's/,//g')
		echo "Circulation Supply int: `getCirculationSupplyString $1`" >> ./Log/$1-$filename.txt
		echo $circulation_supply_int
}
getAllTimeHigh(){	# Gets All time high as a floating but it is a string and returns
		#ALL TIME HIGH
		all_time_high=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "All Time High.*All Time Low" | grep -woi "[0-9].*USD" | sed -E 's/,|\$| USD//g' ) #| grep -o ".*[.]" |sed 's/[.]//')
		echo "All Time high: $all_time_high" >> ./Log/$1-$filename.txt
		echo $all_time_high
}
getAllTimeHighDate(){ # Gets All Time High Date as a string
		#ALL TIME HIGH
		all_time_high_date=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "All Time High.*All Time Low" | grep -woi "(.*)" | grep -woi "[a-z].*[0-9]")
		echo "All Time high date: $all_time_high_date" >> ./Log/$1-$filename.txt
}
getAllTimeLow(){	# Gets All time low as a floating but it is a string and returns

		#ALL TIME LOW
		all_time_low=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "All Time Low<.*Week High" | grep -woi "[0-9].*USD" | sed -E 's/,|\$| USD//g') # | grep -o ".*[.]" |sed 's/[.]//')
		echo "All time low: $all_time_low" >> ./Log/$1-$filename.txt
		echo $all_time_low

}
getAllTimeLowDate(){ # Gets All Time Low Date as a string
 		#ALL TIME LOW
		all_time_low_date=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "All Time High.*All Time Low" | grep -woi "(.*)" | grep -woi "[a-z].*[0-9]")
		echo "All time low: $all_time_low_date" >> ./Log/$1-$filename.txt
}
getOneYearHigh(){	# Gets 1 Year high as a floating but it is a string and returns
		#1 Year high
		one_year_high=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "52 Week High / Low.*90 Day High / Low" |\
		grep -woi ".*USD [/]" | grep -woi "$.*USD" | sed -E 's/,|\$| USD//g') #|  grep -o ".*[.]" | sed 's/[.]//')
		echo "One year high: $one_year_high" >> ./Log/$1-$filename.txt
		echo $one_year_high
}
getOneYearLow(){	# Gets 1 Year low as a floating but it is a string and returns

		#1 Year low
		one_year_low=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "52 Week High / Low.*90 Day High / Low"  |\
		 grep -woi "$.*USD" | grep -oi ">$.*USD" | grep -woi "$.*USD" | sed -E 's/,|\$| USD//g') #|  grep -o ".*[.]" | sed 's/[.]//')
		echo "One year low: $one_year_low" >> ./Log/$1-$filename.txt
		echo $one_year_low
}
getNinetyDayHigh(){	# Gets 90 Day high as a floating but it is a string and returns

		#90 Day H
		ninety_day_high=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "90 Day High / Low.*30 Day High / Low" |\
		grep -woi ".*USD [/]" | grep -woi "$.*USD" | sed -E 's/,|\$| USD//g') #|  grep -o ".*[.]" | sed 's/[.]//')
		echo "90 day high: $ninety_day_high"  >> ./Log/$1-$filename.txt
		echo $ninety_day_high
}
getNinetyDayLow(){	# Gets 90 Day low as a floating but it is a string and returns

		#90 Day L
		ninety_day_low=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "90 Day High / Low.*30 Day High / Low"  |\
		 grep -woi "$.*USD" | grep -oi ">$.*USD" | grep -woi "$.*USD" | sed -E 's/,|\$| USD//g') #|  grep -o ".*[.]" | sed 's/[.]//')
		echo "90 day low: $ninety_day_low" >> ./Log/$1-$filename.txt
		echo $ninety_day_low
}
getThirtyDayHigh(){	# Gets 30 Day high as a floating but it is a string and returns

		#30 Day H

		thirty_day_high=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "30 Day High / Low.*7 Day High / Low" |\
		grep -woi ".*USD [/]" | grep -woi "$.*USD" | sed -E 's/,|\$| USD//g') #|  grep -o ".*[.]" | sed 's/[.]//')
		echo "30 day high: $thirty_day_high" >> ./Log/$1-$filename.txt
		echo $thirty_day_high

}
getThirtyDayLow(){	# Gets 30 Day low as a floating but it is a string and returns
		#30 Day L
		thirty_day_low=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "30 Day High / Low.*7 Day High / Low"  |\
		 grep -woi "$.*USD" | grep -oi ">$.*USD" | grep -woi "$.*USD" | sed -E 's/,|\$| USD//g') #|  grep -o ".*[.]" | sed 's/[.]//')
		echo "30 day low: $thirty_day_low" >> ./Log/$1-$filename.txt
		echo $thirty_day_low
}
getSevenDayHigh(){	# Gets 7 Day high as a floating but it is a string and returns

		#7 Day H
		seven_day_high=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "7 Day High / Low.*24 Hour High / Low" |\
		grep -woi ".*USD [/]" | grep -woi "$.*USD" | sed -E 's/,|\$| USD//g') #|  grep -o ".*[.]" | sed 's/[.]//')
		echo "7 day high: $seven_day_high" >> ./Log/$1-$filename.txt
		echo $seven_day_high
}
getSevenDayLow(){	# Gets 7 Day low as a floating but it is a string and returns

		#7 Day L
		seven_day_low=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "7 Day High / Low.*24 Hour High / Low"  |\
		 grep -woi "$.*USD" | grep -oi ">$.*USD" | grep -woi "$.*USD" | sed -E 's/,|\$| USD//g') #|  grep -o ".*[.]" | sed 's/[.]//')
		echo "7 day low: $seven_day_low" >>./Log/$1-$filename.txt
		echo $seven_day_low
}
getOneDayHigh(){	# Gets 1 Day high as a floating but it is a string and returns

		#1 Day H
		one_day_high=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "24 Hour High / Low.*Yester.*High / Low" |\
		grep -woi ".*USD [/]" | grep -woi "$.*USD" | sed -E 's/,|\$| USD//g') #|  grep -o ".*[.]" | sed 's/[.]//')
		echo "1 day high: $one_day_high" >> ./Log/$1-$filename.txt
		echo $one_day_high

}
getOneDayLow(){	# Gets 1 Day low as a floating but it is a string and returns

		#1 Day L
		one_day_low=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "24 Hour High / Low.*Yester.*High / Low"  |\
		 grep -woi "$.*USD" | grep -oi ">$.*USD" | grep -woi "$.*USD" | sed -E 's/,|\$| USD//g') #|  grep -o ".*[.]" | sed 's/[.]//')
		echo "1 day low: $one_day_low" >> ./Log/$1-$filename.txt
		echo $one_day_low

}
getYesterdayHigh(){	# Gets Yesteray high as a floating but it is a string and returns
		#Yesterday H
		yesterday_high=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "Yester.*High / Low.*Yester.*Open / Close" |\
		grep -woi ".*USD [/]" | grep -woi "$.*USD" | sed -E 's/,|\$| USD//g') #|  grep -o ".*[.]" | sed 's/[.]//')
		echo "Yesterday high: $yesterday_high" >> ./Log/$1-$filename.txt
		echo $yesterday_high
}
getYesterdayLow(){	# Gets Yesteray low as a floating but it is a string and returns
		#Yesterday L

		yesterday_low=$(grep -woi "About $1.*USD</div>" $1.txt | grep -woi "Yester.*High / Low.*Yester.*Open / Close"  |\
		 grep -woi "$.*USD" | grep -oi ">$.*USD" | grep -woi "$.*USD" | sed -E 's/,|\$| USD//g') #|  grep -o ".*[.]" | sed 's/[.]//')
		echo "Yesterday low: $yesterday_low" >> ./Log/$1-$filename.txt
		echo $yesterday_low
}
getYesterdayOpen(){ # Gets Yesteray open as a floating but it is a string and returns
		#Yesterday open
		yesterday_open=$(grep -woi "About $1.*USD</div>" $1.txt | grep -wo "Open / Close.*Yester.*Change"|grep -woi ".*USD [/]" |\
		 grep -woi "$.*USD" | sed -E 's/,|\$| USD//g') #|  grep -o ".*[.]" | sed 's/[.]//')
		echo "Yesterday open: $yesterday_open" >> ./Log/$1-$filename.txt

		echo $yesterday_open
}
getYesterdayClose(){ # Gets Yesteray close as a floating but it is a string and returns
		#Yesterday close
		yesterday_close=$(grep -woi "About $1.*USD</div>" $1.txt | grep -wo "Open / Close.*Yester.*Change"  | grep -woi "$.*USD" |\
		 grep -oi ">$.*USD" | grep -woi "$.*USD" | sed -E 's/,|\$| USD//g') #|  grep -o ".*[.]" | sed 's/[.]//')
		echo "Yesterday close: $yesterday_close" >> ./Log/$1-$filename.txt
		echo $yesterday_close
}
getYesterdayVolume(){	 # Gets Yesteray Volume as an integer and returns
		#Yesterday VOLUME
		yesterday_volume=$(grep -woi "About $1.*USD</div>" $1.txt | grep -wo "Yester.*Volume.*USD" |\
		 grep -wo "Volume.*USD" | grep -wo "$.*USD" | sed -E 's/,|\$| USD//g')
		echo "Yesterday volume: $yesterday_volume" >> ./Log/$1-$filename.txt
		echo $yesterday_volume

}

}


# Checks how many arguments are given.
if [[ "$#" -eq 1  && "$r" -eq 0 ]] #If there is only 1 argument
then
	#Gets txt file from the internet
	#Derives the txt file to get information.
	#Fills the log txt file.
	#Prints the log txt file.
	getOneCoin $1
    cat ./Log/$1-$filename.txt
elif [ "$#" -eq 2 ] #If there are 2 argument
then

	#Gets txt file from the internet for each argument
    getTwoCoin $1 $2

	{ # Derives the txt files to get information for each argument

	{  # Getting all the data form the internet for the first argument.
	first_price=$(getPriceInt $1)
	first_market_rank=$(getMarketRankInt $1)
	first_market_cap=$(getMarketCap $1)
	first_day_volume=$(getDayVolume $1)
	first_circ_supp=$(getCirculationSupplyInt $1)
	first_alltime_high=$(getAllTimeHigh $1)
	getAllTimeHighDate $1
	first_alltime_low=$(getAllTimeLow $1)
	getAllTimeLowDate $1
	first_oneyear_high=$(getOneYearHigh $1)
	first_oneyear_low=$(getOneYearLow $1)
	first_ninetyday_high=$(getNinetyDayHigh $1)
	first_ninetyday_low=$(getNinetyDayLow $1)
	first_thirtyday_high=$(getThirtyDayHigh $1)
	first_thirtyday_low=$(getThirtyDayLow $1)
	first_sevenday_high=$(getSevenDayHigh $1)
	first_sevenday_low=$(getSevenDayLow $1)
	first_oneday_high=$(getOneDayHigh $1)
	first_oneday_low=$(getOneDayLow $1)
	first_yesterday_high=$(getYesterdayHigh $1)
	first_yesterday_low=$(getYesterdayLow $1)
	first_yerterday_open=$(getYesterdayOpen $1)
	first_yesterday_close=$(getYesterdayClose $1)
	first=yesterday_volume=$(getYesterdayVolume $1)
	}
	{  # Getting all the data form the internet for the second argument.
	second_price=$(getPriceInt $2)
	second_market_rank=$(getMarketRankInt $2)
	second_market_cap=$(getMarketCap $2)
	second_day_volume=$(getDayVolume $2)
	second_circ_supp=$(getCirculationSupplyInt $2)
	second_alltime_high=$(getAllTimeHigh $2)
	getAllTimeHighDate $2
	second_alltime_low=$(getAllTimeLow $2)
	getAllTimeLowDate $2
	second_oneyear_high=$(getOneYearHigh $2)
	second_oneyear_low=$(getOneYearLow $2)
	second_ninetyday_high=$(getNinetyDayHigh $2)
	second_ninetyday_low=$(getNinetyDayLow $2)
	second_thirtyday_high=$(getThirtyDayHigh $2)
	second_thirtyday_low=$(getThirtyDayLow $2)
	second_sevenday_high=$(getSevenDayHigh $2)
	second_sevenday_low=$(getSevenDayLow $2)
	second_oneday_high=$(getOneDayHigh $2)
	second_oneday_low=$(getOneDayLow $2)
	second_yesterday_high=$(getYesterdayHigh $2)
	second_yesterday_low=$(getYesterdayLow $2)
	second_yerterday_open=$(getYesterdayOpen $2)
	second_yesterday_close=$(getYesterdayClose $2)
	second=yesterday_volume=$(getYesterdayVolume $2)

	}

	}

	{  # Dummy Calculations. Not any real complex financial calculations. These are based on basic math calculations.
    calculation1=$( echo "$first_price / $second_price" | bc -l)
    calculation2=$( echo "$first_alltime_low / $second_alltime_low / $calculation1" | bc -l)
    calculation3=$( echo "$first_oneyear_high / $second_oneyear_high / $calculation1" | bc -l)
    calculation4=$( echo "$first_oneyear_low / $second_oneyear_low / $calculation1" | bc -l)
    calculation5=$( echo "$first_ninetyday_high / $second_ninetyday_high / $calculation1" | bc -l)
    calculation6=$( echo "$first_ninetyday_low / $second_ninetyday_low / $calculation1" | bc -l)
    calculation7=$( echo "$first_thirtyday_high/ $second_thirtyday_high / $calculation1" | bc -l)
    calculation8=$( echo "$first_thirtyday_low / $second_thirtyday_low / $calculation1" | bc -l)
    calculation9=$( echo "$first_sevenday_high / $second_sevenday_high / $calculation1" | bc -l)
    calculation10=$( echo "$first_sevenday_low / $second_sevenday_low / $calculation1" | bc -l)
    calculation11=$( echo "$first_oneday_high / $second_oneday_high / $calculation1" | bc -l)
    calculation12=$( echo "$first_oneday_low / $second_oneday_low / $calculation1" | bc -l)
    calculation13=$( echo "$first_yesterday_high / $second_yesterday_high / $calculation1" | bc -l)
    calculation14=$( echo "$first_yesterday_low / $second_yesterday_low / $calculation1" | bc -l)
    calculation15=$( echo "$first_yerterday_open / $second_yerterday_open / $calculation1" | bc -l)
    calculation16=$( echo "$first_yesterday_close / $second_yesterday_close / $calculation1" | bc -l)
	calculation17=$( echo "$first_alltime_high / $second_alltime_high / $calculation1" | bc -l)

	# Initial points for each coin
	firstCoin=0
	secondCoin=0

{ 	# Comparing 2 coins calculation results and gives points

	if (( $(echo "$calculation1 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

	if (( $(echo "$calculation2 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

	if (( $(echo "$calculation3 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

	if (( $(echo "$calculation4 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

	if (( $(echo "$calculation5 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

	if (( $(echo "$calculation6 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

	if (( $(echo "$calculation7 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

	if (( $(echo "$calculation8 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

	if (( $(echo "$calculation9 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

	if (( $(echo "$calculation10 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

	if (( $(echo "$calculation11 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

	if (( $(echo "$calculation12 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

	if (( $(echo "$calculation13 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

	if (( $(echo "$calculation14 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

	if (( $(echo "$calculation15 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

	if (( $(echo "$calculation16 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

	if (( $(echo "$calculation17 > 1" |bc -l) ));
	then
	((firstCoin++))
	else
	((secondCoin++))
	fi

}

}

warning(){
	tput bold
	tput setaf 1
	echo "This is not a investment recommendation."
	echo "Do not buy or sell any financial product according to this result."
	tput sgr0	
}


	echo
	{  # Calculates difference and prints the result according to calculation.
	key=$(( $firstCoin - secondCoin ))
	if [ $key -gt 10 ]; then
	tput bold
	tput setaf 2
	echo -n "All in"
	tput sgr0
	echo " $1"
	warning
	elif [ $key -gt 5 ]; then
	tput bold
	tput setaf 3
	echo -n "Highly Recommended"
	tput sgr0
	echo " $1"
	warning
	elif [ $key -gt 0 ]; then
	tput bold
	tput setaf 4
	echo -n "Recommended"
	tput sgr0
	echo " $1"
	warning
	elif [ $key -eq 0 ]; then
	tput bold
	tput setaf 7
	echo "Both recommended"
	tput sgr0
	warning
	elif [ $key -gt -5 ]; then
	tput bold
	tput setaf 4
	echo -n "Recommended"
	tput sgr0
	echo " $2"
	warning
	elif [ $key -gt -10 ]; then
	tput bold
	tput setaf 3
	echo -n "Highly Recommended"
	tput sgr0
	echo " $2"
	warning
	else
	tput bold
	tput setaf 2
	echo -n "All in"
	tput sgr0
	echo " $2"
	warning
	fi


}

else # If there are 0 argument or more than 2 arguments
	echo "Something wrong. Please try again with valid arguments"
fi
exit 0
