#include <stdio.h>
#include <stdlib.h>

#define FILENAME_SIZE 13

int main(int argc, char **argv)
{
	short numfiles = (short) argc - 1;
	long *filelocation;
	long *filesize;
	long sizeoffile;
	int i;
	FILE *infile;
	FILE *outfile;
	char buffer[5000000]; //buffers: malloc is for wimps

	filelocation = (long *) malloc(sizeof(long) * argc);
	filesize = (long *) malloc(sizeof(long) * argc);

	filelocation[0] = 0;
	if (!(outfile = fopen("outfile.001", "w"))) return 1;
	fwrite("GladPack", 8, 1, outfile);
	fwrite(&numfiles, sizeof(short), 1, outfile);

	for (i = 0; i < numfiles; i++)
	{
		if (!(infile = fopen(argv[i + 1], "rb"))) exit(0);
		fseek(infile, 0, SEEK_END);
		filesize[i] = ftell(infile);
		filelocation[i + 1] = filelocation[i] + filesize[i];

		fclose(infile);
	}

	sizeoffile = filelocation[numfiles] + filesize[numfiles - 1];
	fwrite(&sizeoffile, sizeof(long), 1, outfile);

	for (i = 0; i < numfiles; i++)
	{
		fwrite(argv[i+1], sizeof(char) * 13, 1, outfile);
		fwrite(&filelocation[i], sizeof(long), 1, outfile);
	}

	for (i = 0; i < numfiles; i++)
	{
		if (!(infile = fopen(argv[i + 1], "rb"))) exit(0);
		printf("adding %s ",argv[i+1]);
		printf("-- size %d\n",filesize[i]);

		fread(buffer,filesize[i],1,infile);
		fwrite(buffer, filesize[i], 1, outfile);

		fclose(infile);
	}


	fclose(outfile);
}