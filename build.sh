#!/bin/bash

if [ -f "sfa" ]; then
	echo -n "Removing Security For Audio binary file..."
	rm -rf sfa
	echo "done."
fi

echo -n "Compiling Security For Audio..."
gcc main.c -o sfa
echo "done."

#read -p "Execute Security For Audio now? (Y/n) " CHOICE

#if [ -f "sfa" ]; then
#	if [ -z "$CHOICE" ] || [ "$CHOICE" == "y" ] || [ "$CHOICE" == "Y" ]; then
#		./sfa
#	fi
#fi

read -p "Compile wave_check? (Y/n) " CHOICE

if [ -z "$CHOICE" ] || [ "$CHOICE" == "y" ] || [ "$CHOICE" == "Y" ]; then
	gcc wave_check.c -o wave_check
fi

echo ""

exit 0
