#ifndef __SFA_WAVE_FMT_H
#define __SFA_WAVE_FMT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __WAVEFMT {
	char fn[255];
	char *RIFF;
	unsigned long RChunkSize;
	char *WAVE;
	char *FMT;
	unsigned long FChunkSize;
	unsigned long FExtraBytes;
	unsigned short FFormat;
	unsigned short FChanNum;
	unsigned long FSamplesSec;
	unsigned long FBytesSec;
	unsigned short FBlockAlign;
	unsigned short FBitsSample;
	char *DATA;
	unsigned long DChunkSize;
	char *DBUFF;
} audiofmt;

/**
 * ParseAudioFile
 * fmt - Structure where audio data will be stored.
 *
 * Parses fmt->fn and stores relevant information where needed.
 **/
static void ParseAudioFile(audiofmt *fmt){
	FILE *fp = fopen(fmt->fn, "rb");

	if(!fp){
		printf("Unable to open %s for reading in binary mode!\n", fmt->fn);
		return;
	}

	fmt->RIFF = (char*)malloc(sizeof(char) * 5);
	memset(fmt->RIFF, '\0', sizeof(fmt->RIFF));

	fread(fmt->RIFF, 1, 4, fp);

	fread(&fmt->RChunkSize, sizeof(fmt->RChunkSize), 1, fp);

	fmt->WAVE = (char*)malloc(sizeof(char) * 5);
	memset(fmt->WAVE, '\0', sizeof(fmt->WAVE));

	fread(fmt->WAVE, 1, 4, fp);

	fmt->FMT = (char*)malloc(sizeof(char) * 5);
	memset(fmt->FMT, '\0', sizeof(fmt->FMT));

	fread(fmt->FMT, 1, 4, fp);

	fread(&fmt->FChunkSize, sizeof(fmt->FChunkSize), 1, fp);
	fmt->FExtraBytes = fmt->FChunkSize - 16;

	fread(&fmt->FFormat, sizeof(fmt->FFormat), 1, fp);

	fread(&fmt->FChanNum, sizeof(fmt->FChanNum), 1, fp);

	fread(&fmt->FSamplesSec, sizeof(fmt->FSamplesSec), 1, fp);

	fread(&fmt->FBytesSec, sizeof(fmt->FBytesSec), 1, fp);

	fread(&fmt->FBlockAlign, sizeof(fmt->FBlockAlign), 1, fp);

	fread(&fmt->FBitsSample, sizeof(fmt->FBitsSample), 1, fp);

	if(fmt->FExtraBytes != 0){
//		printf("Found an additional %ld bytes in \"fmt \" that we will disregard.\n", fmt->FExtraBytes);
		fseek(fp, fmt->FExtraBytes, SEEK_CUR);
	}

	fmt->DATA = (char*)malloc(sizeof(char) * 5);
	memset(fmt->DATA, '\0', sizeof(fmt->DATA));

	unsigned long hdr_len = 0;

	fread(fmt->DATA, 1, 4, fp);

	/**
	 * WAVE files can have multiple headers before the DATA chunk (where the audio is stored).
	 * We don't care about these extra chunks, and thankfully every chunk ID is followed by the
	 * size it is.  So we just need to fetch that value and jump ahead in the FILE buffer to
	 * the new location.  Then we keep checking for the DATA header/chunk.
	 **/
	while(strcmp(fmt->DATA, "data") != 0){
		fread(&hdr_len, sizeof(hdr_len), 1, fp);

		fseek(fp, hdr_len, SEEK_CUR);

		fread(fmt->DATA, 1, 4, fp);
	}

	// Finally reached the length of the data chunk!
	fread(&fmt->DChunkSize, sizeof(fmt->DChunkSize), 1, fp);

	// Allocate enough memory to handle the buffer
	fmt->DBUFF = (char*)malloc(sizeof(char) * fmt->DChunkSize);
	memset(fmt->DBUFF, '\0', sizeof(fmt->DBUFF));

	// Read it
	int i = 0;
	int c = 0;

	for(i = 0; i <= fmt->DChunkSize; i++){
		c = fgetc(fp);

		// If we don't want fake data, don't include it
		if((SFA_NONULL && (c != 0)) && (SFA_NOFF && (c != 255)))
			sprintf(fmt->DBUFF, "%s%c", fmt->DBUFF, c);
	}

	fclose(fp);
}

/**
 * FreeAudioFile
 * fmt - Structure to free memory of
 *
 * Frees memory allocated during process.
 **/
void FreeAudioFile(audiofmt *fmt){
	free(fmt->DBUFF);
	free(fmt->DATA);
	free(fmt->FMT);
	free(fmt->WAVE);
	free(fmt->RIFF);
}

/**
 * WaveCheck
 * fmt - Structure to use to determine if file is properly set up.
 *
 * Checks to see if file is usable with Security For Audio.  1 - yes, 0 - no
 **/
int AudioCheck(audiofmt *fmt){
	printf("Validating WAVE file: %s\n", fmt->fn);

	printf("-------------------------------------------------------------\n");
	printf("| - Filename: %s\n", fmt->fn);

	// Checks for valid headers.  Without these we know the WAVE data is incorrect.
	if(strcmp(fmt->RIFF, "RIFF") != 0)
		return -10;
	else
		printf("| - RIFF Header: Found\n");

	if(strcmp(fmt->WAVE, "WAVE") != 0)
		return -20;
	else
		printf("| - WAVE Header: Found\n");

	if(strcmp(fmt->FMT, "fmt ") != 0){
		printf("FMT header was parsed wrong: %s\n", fmt->FMT);
		return -30;
	} else
		printf("| - FMT Header: Found\n");

	if(strcmp(fmt->DATA, "data") != 0)
		return -40;
	else
		printf("| - DATA Header: Found\n");

	if(fmt->RChunkSize > 0)
		printf("| - File size: %ld bytes\n", fmt->RChunkSize);
	else
		return 101;

	printf("| - Compression Type: ");

	if(fmt->FFormat & 0x0001)
		printf("PCM/Uncompressed");
	else if(fmt->FFormat & 0x0002)
		printf("Microsoft ADPCM");
	else if(fmt->FFormat & 0x0006)
		printf("ITU G.711 A-Law");
	else if(fmt->FFormat & 0x0007)
		printf("ITU G.711 u-Law");
	else if(fmt->FFormat & 0x0011)
		printf("IMA ADPCM");
	else if(fmt->FFormat & 0x0016)
		printf("ITU G.723 ADPCM (Yamaha)");
	else if(fmt->FFormat & 0x0031)
		printf("GSM 6.10");
	else if(fmt->FFormat & 0x0040)
		printf("ITU G.721 ADPCM");
	else if(fmt->FFormat & 0x0050)
		printf("MPEG");
	else if(fmt->FFormat & 0xFFFF)
		printf("Experimental");
	else{
		printf("Unknown [ERROR]\n");
		return 301;
	}

	printf("\n");

	if(fmt->FChunkSize > 0)
		printf("| - FMT Chunk Size: %ld\n", fmt->FChunkSize);
	else{
		printf("Invalid \"fmt \" chunk size.\n");
		return 302;
	}

	if(fmt->FExtraBytes > 0)
		printf("| - FMT Extra Bytes: %ld\n", fmt->FExtraBytes);

	if(fmt->FChanNum > 0 && fmt->FChanNum <= 65535)
		printf("| - Channels: %d\n", fmt->FChanNum);
	else{
		printf("| - Invalid channel number.\n");
		return 303;
	}

	if(fmt->FSamplesSec > 0 && (fmt->FSamplesSec <= 0xFFFFFFFF))
		printf("| - Samples Rate: %ld\n", fmt->FSamplesSec);
	else{
		printf("| - Invalid sample rate.\n");
		return 304;
	}

	if(fmt->FBytesSec > 0 && (fmt->FBytesSec <= 0xFFFFFFFF))
		printf("| - Average Bytes/Second: %ld\n", fmt->FBytesSec);
	else{
		printf("| - Invalid average bytes/second.\n");
		return 305;
	}

	if(fmt->FBlockAlign > 0 && (fmt->FBlockAlign <= 65535))
		printf("| - Block Align: %d\n", fmt->FBlockAlign);
	else{
		printf("| - Invalid block align data.\n");
		return 306;
	}

	if(fmt->FBitsSample > 1 && (fmt->FBitsSample <= 65535))
		printf("| - Significant Bits/Sample: %d\n", fmt->FBitsSample);
	else{
		printf("| - Invalid signifcant bits/sample.\n");
		return 307;
	}

	if(fmt->DChunkSize > 0)
		printf("| - Data size: %ld bytes\n", fmt->DChunkSize);
	else{
		printf("| - No data size.\n");
		return 401;
	}

	printf("-------------------------------------------------------------\n");

	return 1;
}

#endif
