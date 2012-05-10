#!/bin/bash

if [ -f "sfa" ]; then
	echo -n "Removing Security For Audio binary file..."
	rm -rf sfa
	echo "done."
fi

echo -n "Compiling Security For Audio..."
gcc -m32 main.c -o sfa
echo "done."

#read -p "Execute Security For Audio now? (Y/n) " CHOICE

#if [ -f "sfa" ]; then
#	if [ -z "$CHOICE" ] || [ "$CHOICE" == "y" ] || [ "$CHOICE" == "Y" ]; then
#		./sfa
#	fi
#fi

if [ $? -eq 1 ]; then
	read -p "Compile wave_check? (Y/n) " CHOICE

	if [ -z "$CHOICE" ] || [ "$CHOICE" == "y" ] || [ "$CHOICE" == "Y" ]; then
		echo -n "Compiling wave_check..."
		gcc -m32 wave_check.c -o wave_check
		echo "done."
	fi
else
	echo "Please fix compilation errors."
fi

echo ""

exit 0
