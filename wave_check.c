#include "defs.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	audiofmt fmt;
	sprintf(fmt.fn, "samples/rfd.wav");
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
