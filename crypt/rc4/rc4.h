#ifndef __RC4
#define __RC4

#define STREAM_LENGTH 256

typedef struct __CRYPT_STRUCT {
	unsigned char state[STREAM_LENGTH];
	unsigned char key[STREAM_LENGTH];
	unsigned char stream[STREAM_LENGTH];
} crypt_struct;

// Key Scheduling Algorithm
// Input: state - the state used to generate the keystream
//        key - Key to use to initialize the state
//        len - length of key in bytes
void ksa(crypt_struct *cs)
{
   int i,j=0,t;
  int len = strlen(cs->key);

   for (i=0; i < STREAM_LENGTH; ++i)
      cs->state[i] = i;
   for (i=0; i < STREAM_LENGTH; ++i) {
      j = (j + cs->state[i] + cs->key[i % len]) % STREAM_LENGTH;
      t = cs->state[i];
      cs->state[i] = cs->state[j];
      cs->state[j] = t;
   }
}

// Pseudo-Random Generator Algorithm
// Input: state - the state used to generate the keystream
//        out - Must be of at least "len" length
//        len - number of bytes to generate
void prga(crypt_struct *cs, int len)
{
   int i=0,j=0,x,t;
   unsigned char key;
   len *= 2;

   for (x=0; x < len; ++x)  {
      i = (i + 1) % STREAM_LENGTH;
      j = (j + cs->state[i]) % STREAM_LENGTH;
      t = cs->state[i];
      cs->state[i] = cs->state[j];
      cs->state[j] = t;
      cs->stream[x] = cs->state[(cs->state[i] + cs->state[j]) % STREAM_LENGTH];
   }
}

void CipherKey(crypt_struct *cs, unsigned char key[]){
	int i = strlen(key);
	int j = strlen(cs->key);
	int k = 0;

	if(i < j)
		return;

	for(; k < STREAM_LENGTH; k++){
		cs->key[k] = key[k];
	}
}

void CipherCrypt(crypt_struct *cs, unsigned char in[], unsigned char out[]){
	if(sizeof(out) != 0)
		memset(out, '\0', sizeof(out));

	int i = sizeof(in);
	int j = 0;

	for(j = 0; j < i; j++){
		out[j] = in[j] ^ cs->stream[j];
	}
}

#endif
