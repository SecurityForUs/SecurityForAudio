#ifndef __SFA_WAVE_FMT_H
#define __SFA_WAVE_FMT_H

struct __WAVEFMT {
	char RIFF[4];
	unsigned long RChunkSize;
	char WAVE[4];
	char FMT[4];
	unsigned long FChunkSize;
	unsigned short FFormat;
	unsigned short FChanNum;
	unsigned long FSamplesSec;
	unsigned long FBytesSec;
	unsigned short FBlockAlign;
	unsigned short FBitsSample;
	char DATA[4];
	unsigned long DChunkSize;
	char *DBUFF;
} audiofmt;

#endif
