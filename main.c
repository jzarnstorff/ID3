#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "id3.h"

static void print_usage(const char *name)
{
    printf("Usage: ");
    printf("%s [OPTIONS] Path/to/MP3s\n\n", name);
    printf("Options:\n\n"
           "\t-h   View ID3 tags in Hex format\n"
           "\t-v   Verbose\n");
    exit(1);
}


int main(int argc, char *argv[])
{
    DIR *dhandle;
    struct dirent *drecord;
    struct ID3Tag ID3;
    enum _mode mode = NORMAL;
    char cwd[80];
    char *directory;
    int ret, opt;

    while((opt = getopt(argc, argv, "hv:")) != -1)
    {
        switch(opt)
        {
            case 'h' :
                mode = HEX;
        		directory = argv[2];
                break;
            case 'v' :
                #define DEBUG
                break;
            default  :
                print_usage(argv[0]);
        }
    }

    if(argc <= 1)
        print_usage(argv[0]);

    if(argc == 2)
        directory = argv[1];

#ifdef DEBUG
    int x;
    printf("argc: %d\n", argc);
    for(x = 0; x < argc; x++)
        printf("argv[%d]: %s\n", x, argv[x]);
    printf("directory: %s\n", directory);
#endif

    getcwd(cwd, sizeof(cwd));

    if(!(dhandle = changeDir(directory)))
    {
        ret = ERROR;
        goto done;
    }

	while((drecord = readdir(dhandle)) != NULL)
    {
        if((strcmp(drecord->d_name, ".") == 0) ||
           (strcmp(drecord->d_name, "..") == 0))
            continue;

        if((ret = readMp3Id(drecord->d_name, &ID3, sizeof(ID3))) != OK)
        {
            ret = ERROR;
            goto done;
        }

        printID3("Tag",       ID3.tag,       sizeof(ID3.tag),      mode);
        printID3("Title",     ID3.title,     sizeof(ID3.title),    mode);
        printID3("Artist",    ID3.artist,    sizeof(ID3.artist),   mode);
        printID3("Album",     ID3.album,     sizeof(ID3.album),    mode);
        printID3("Year",      ID3.year,      sizeof(ID3.year),     mode);
        printID3("Comment",   ID3.comment,   sizeof(ID3.comment),  mode);
        printf("\tTrack\t%x\n", ID3.track);

    }

    ret = OK;
done:
    chdir(cwd);
	closedir(dhandle);
	return ret;
}
