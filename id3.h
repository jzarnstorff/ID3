#ifndef ID3_H
#define ID3_H

/* defines */
#define OK         0
#define ERROR      -1

struct ID3Tag
{
    char tag[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[28];
    char zero;
    char track;
    unsigned char genre;
};

enum _mode
{
    NORMAL,
    HEX
};

DIR * changeDir(const char *directory);
int readMp3Id(const char *name, struct ID3Tag *ID3, int size);
void printID3(const char *label, const char *tag, size_t max, enum _mode format);

#endif // ID3_H
