#include "defs.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	audiofmt fmt;

	sprintf(fmt.fn, "samples/rd.wav");

	ParseAudioFile(&fmt);
printf("Data size: %ld\nData buffer: %d\nDifference: %ld\n", fmt.DChunkSize, strlen(fmt.DBUFF), fmt.DChunkSize - strlen(fmt.DBUFF));
	FreeAudioFile(&fmt);

	return 0;
}
