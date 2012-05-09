#ifndef __SFA_DEFS_H
#define __SFA_DEFS_H

/** What type of audio are we going to be working with?
  * Options:
  * 1 - WAVE file (use wave_check to ensure wave file is compatible)
  **/
#define SFA_FT 1

/** Remove null data?
  * Audio files contain a lot of 0 bytes.  Set to 1 for these to removed from encryption pool.
  **/
#define SFA_NONULL 1

/** Remove full data?
  * Similar to SFA_NONULL.  Audio files contain a lot of FF (255) bytes too.  Set to 1 to remove these too.
  **/
#define SFA_NOFF 1

#endif
