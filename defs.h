#ifndef __SFA_DEFS_H
#define __SFA_DEFS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct __SFA_OPTS {
	unsigned int start;
	unsigned short ft;
	unsigned short ct;
	FILE *in;
	FILE *out;
} sfa_opts;

/** What type of audio are we going to be working with?
  * Options:
  * 1 - WAVE file (use wave_check to ensure wave file is compatible)
  * 2 - MP3
  **/
#define SFA_FT 1

/** Cipher to use (see folders in crypt/)
 * 1 - RC4
 **/
#define SFA_CRYPT 1

/** Remove null data?
  * Audio files contain a lot of 0 bytes.  Set to 1 for these to removed from encryption pool.
  **/
#define SFA_NONULL 1

/** Remove full data?
  * Similar to SFA_NONULL.  Audio files contain a lot of FF (255) bytes too.  Set to 1 to remove these too.
  **/
#define SFA_NOFF 1

#if SFA_FT==1
	#include "audio/wave/format.h"
#elif SFA_FT==2
	#include "audio/mp3/format.h"
#endif

#if SFA_CRYPT==1
	#include "crypt/rc4/rc4.h"
#endif

/** Verbal explanation of what SFA_FT values are. **/
static char *SFA_FT_NAME[SFA_FT] = {
					"wave"
				};

static char *GetSFAFTName(const int FT_TYPE){
	return SFA_FT_NAME[FT_TYPE-1];
}

#endif
