#!/bin/sh

# Zach Wibbenmeyer
# Professor Norman
# CS 232 - Project 2

#file that contains all the lab computer names
filename='csmachines.txt'

# read the out the lines
filelines=`cat $filename` 

# determine if the machine is running windows
windows="Connection timed out" 

# determine if the machine is shut off
shutdown="No route to host"

# loop through the lab computer names
for line in $filelines ; do 
	echo  

	#output the machine name
	echo $line 

	# output errors to a text file
	output=$(ssh -o StrictHostKeyChecking=no -o ConnectTimeout=5 $line "users && exit") 2> error.txt 

	# read error messages to a text file
	read error < error.txt 

	#if the 'No route to host' message is in the error messaage
	if echo "$error" | grep -q "$shutdown" 
	then
		#then the machine is turned off
		echo "Machine is turned OFF" 
	else
		#if the 'Connection timed out' message is in the error message
		if echo "$error" | grep -q "$windows" 
		then
			# the machine is running Windows
			echo "Machine is running WINDOWS" 
		else
			# the machine is running Linux
			echo "Machine is running GNU/LINUX"
			#if the error message is empty and the output is empty,
			if [ -z "$output" -a -z "$error" ]; then 
				echo "No users are logged on"
		    else
				ECHO=$( echo | ssh $line who --count)
				echo The users on $line are $ECHO
			fi
		fi
	fi

done
