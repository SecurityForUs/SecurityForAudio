#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]){
	audiofmt fmt;
	crypt_struct cs;
	sfa_opts opts;

	int opt = 0;

	opts.in = NULL;
	opts.out = NULL;

	memset(fmt.fn, '\0', sizeof(fmt.fn));

	while((opt = getopt(argc, argv, "f:s:a:c:i:o:")) != -1){
		switch(opt){
			case 'f':
				sprintf(fmt.fn, "%s", optarg);
			break;
/*
			case 's':
				opts.start = atoi(optarg);
			break;

			case 'a':
				opts.ft = atoi(optarg);
			break;

			case 'c':
				opts.ct = atoi(optarg);
			break;

			case 'i':
				opts.in = fopen(optarg, "r");
			break;

			case 'o':
				opts.out = fopen(optarg, "w");
			break; */
		}
	}

	if(strlen(fmt.fn) < 4){
		printf("No file provided.\n");
		return 1;
	}

	if(opts.in == NULL)
		opts.in = stdin;

	if(opts.out == NULL)
		opts.out = stdout;

	ParseAudioFile(&fmt);

	char buff[1024] = {'\0'};
	char tmp[1024] = {'\0'};

	CipherKey(&cs, fmt.DBUFF);
printf("data buffer length - %d\n", strlen(fmt.DBUFF));
	ksa(&cs);
	prga(&cs, 1024);

	CipherCrypt(&cs, tmp, buff);

	fprintf(opts.out, "%s", buff);
	FreeAudioFile(&fmt);

	fclose(opts.in);
	fclose(opts.out);

	return 0;
}
