/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "id3.h"


DIR * changeDir(const char *directory)
{
    DIR *handle;
    int ret;

    handle = opendir(directory);
    if(handle == NULL)
    {
        puts("Error opening directory.");
        return handle;
    }

	ret = chdir(directory);
	if(ret != OK)
	{
		puts("Error changing directories.");
		return(NULL);
	}

    return handle;
}


int readMp3Id(const char *name, struct ID3Tag *ID3, int size)
{
    FILE *fp = fopen(name, "rb");

    fseek(fp, -128, SEEK_END);
    fread(ID3, size, sizeof(char), fp);

    if(strncmp(ID3->tag, "TAG", 3) != 0)
        {
            printf("%s ID3 tag != TAG\n", name);
            fclose(fp);
            return ERROR;
        }

    printf("\n");
    printf("Filename: %s\n", name);
    fclose(fp);
    return OK;
}


void printID3(const char *label, const char *tag, size_t max, enum _mode format)
{
     int i;

     printf("\t%s\t", label);

     for(i = 0; i < max && tag[i]; i++)
     {
         if(format == NORMAL)
             printf("%c", tag[i]);
         if(format == HEX)
             printf("%x", tag[i]);
     }
     putchar('\n');
}

