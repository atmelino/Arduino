#!/bin/bash
# Read temperature and humidity from Arduino with SHT21 sensor and format for flot plotting

first_line=true
tz_correct=-21600000  # milliseconds for Chicage timezone



echo "reading temperature and humidity"


#create empty data files
echo '{' > temperature.dat
echo -n 'label: ' >> temperature.dat
echo  \'Temperature [Fahrenheit]\', >> temperature.dat
echo  '    data: [' >> temperature.dat
echo  ']}' >> temperature.dat
echo '{' > humidity.dat
echo -n 'label: ' >> humidity.dat
echo  \'Relative Humidity [%]\', >> humidity.dat
echo  '    data: [' >> humidity.dat
echo  ']}' >> humidity.dat


while true; do

	# Get current date and time
	var1=$(date +%s)
	var2=$((1000*$var1+$tz_correct))

	# extract measurement value
	mystring=$(tail -1 alldata.dat)
	newcount=$(echo $mystring | awk '{print $1}')
	mytype=$(echo $mystring | awk '{print $2}')
	myvalue=$(echo $mystring | awk '{print $3}')
	myline=$(echo ,[ $var2 , $myvalue ])

	if [ "$newcount" != "$oldcount" ]; then
	        echo "different value";


	firstletter=$(echo ${mytype:0:1} )
	case "$firstletter" in
	T)  	echo $mycount "temp"
		sed -i "/]}/i$myline" temperature.dat
	    	;;
	H)  echo $mycount "hum"
		sed -i "/]}/i$myline" humidity.dat
	    ;;
	*) echo "something different"
	   ;;
	esac

	fi

	oldcount=$newcount
	echo $myline

	
	sleep 1
done


	#echo $mytype
	#echo ${mytype:0:1}
	#echo $firstletter

