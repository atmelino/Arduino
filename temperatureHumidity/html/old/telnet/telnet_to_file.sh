arduino_ip=192.168.0.177
(
while true; do
	sleep 2
	echo t
	sleep 2
	echo h
done
)|telnet $arduino_ip | tee alldata.dat


