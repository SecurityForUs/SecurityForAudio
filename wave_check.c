#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]){
	audiofmt fmt;

	if(argc == 2)
		sprintf(fmt.fn, "%s", argv[1]);
	else
		sprintf(fmt.fn, "samples/rd.wav");

	printf("--------------- WAVE Check v1.0 ---------------\n");
	printf("| Checks a provided WAVE file to see if it is |\n");
	printf("| usable with Security For Audio.             |\n");
	printf("|                                             |\n");
	printf("| Usage:                                      |\n");
	printf("| %s [filename]                          |\n", argv[0]);
	printf("| filename - optional                         |\n");
	printf("| - The file to verify.  If left empty, uses  |\n");
	printf("| samples/rd.wav for testing purposes.        |\n");
	printf("-----------------------------------------------\n\n");

	ParseAudioFile(&fmt);

	int ret = AudioCheck(&fmt);

	if(ret == 1){
		printf("\n-------------------------------------------------------------\n");
		printf("| - %s\n| - Status: OK\n", fmt.fn);
		printf("-------------------------------------------------------------\n\n");
	} else{
		printf("\n-------------------------------------------------------------\n");
		printf("| - %s\n| - Status: FAIL\n| - Error Result: %d\n", fmt.fn, ret);
		printf("-------------------------------------------------------------\n\n");
	}

	// Call this last to free up memory
	FreeAudioFile(&fmt);

	return 0;
}
