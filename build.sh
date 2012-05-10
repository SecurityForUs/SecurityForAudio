#!/bin/bash

if [ -f "sfa" ]; then
	echo -n "Removing Security For Audio binary file..."
	rm -rf sfa
	echo "done."
fi

IS_64=$(uname -m)

if [ "$IS_64" == "x86_64" ]; then
	GCC_M="-m32"
else
	GCC_M=""
fi

echo -n "Compiling Security For Audio..."
gcc $GCC_M main.c -o sfa
echo "done."

echo -n "Compiling wave_check..."
gcc $GCC_M wave_check.c -o wave_check
echo "done."

echo ""

exit 0
