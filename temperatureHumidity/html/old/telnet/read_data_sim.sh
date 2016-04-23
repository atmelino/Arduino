#!/bin/bash
# Simulate reading temperature and humidity from Arduino with SHT21 sensor and 
# convert the data to JSON format for flot plotting

first_line=true
tz_correct=-21600000  # milliseconds for Chicage timezone

	RANDOM=$$$(date +%s); 


randomHumidity () {
        ranhum=$[ ( $RANDOM % 20  ) + 1 ];
}


randomTemperature () {
        rantemp=$[ ( $RANDOM % 70  ) + 1 ];
}


mv temperature.json temperature.json.bak
mv humidity.json humidity.json.bak

#create empty data files
#echo '{' >> temperature.json
#echo -n '"label": "Temperature (F)",' >> temperature.json
#echo  '"data": [' >> temperature.json
#echo  ']}' >> temperature.json
#echo '{' >> humidity.json
#echo -n '"label": "Relative Humidity (%)",' >> humidity.json
#echo  '"data": [' >> humidity.json
#echo  ']}' >> humidity.json


#create empty data files
echo -n '{"min":' >> humidity.json
# Get current date and time
var1=$(date +%s)
var2=$((1000*$var1+$tz_correct))
echo -n $var2 >> humidity.json
echo -n ',"max":' >> humidity.json
let "var3 = var2 + 10000"
echo -n $var3 >> humidity.json
echo ',"data":[[' >> humidity.json

echo ']]}' >> humidity.json


while true; do
	#	echo "reading temperature and humidity"

	# Get current date and time
	var1=$(date +%s)
	var2=$((1000*$var1+$tz_correct))

	# Add temperature data
	cp temperature.json temperature.json.tmp
	sed '/]}/d' temperature.json.tmp >temperature.json
	if ! $first_line 
	then
		echo -n ',' >> temperature.json
	fi
	echo -n '[' >> temperature.json
	echo -n $var2 >> temperature.json
	echo -n ',' >> temperature.json
	randomTemperature
	echo -n $rantemp >> temperature.json
	echo  ']' >> temperature.json
	echo ']}' >> temperature.json

	# Add humidity data
	cp humidity.json humidity.json.tmp
	sed '/]]/d' humidity.json.tmp >humidity.json
	if ! $first_line 
	then
		echo -n ',' >>humidity.json
	fi
	echo -n '[' >> humidity.json
	echo -n $var2 >> humidity.json
	echo -n ',' >> humidity.json
	randomHumidity
	echo -n $ranhum >> humidity.json
	echo  ']' >> humidity.json
	echo  ']]}' >> humidity.json
	first_line=false
	sleep 1
done


