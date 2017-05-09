#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uchar;
typedef unsigned int uint;

FILE*
fopen_f(const char *path, const char *mode)
{
    FILE *f;
    
    f = fopen(path, mode);
    
    if(f == NULL) {
        fprintf(stderr, "error: couldn't open file (create the directory?) %s\n", path);
        exit(1);
    }
    
    return f;
}

int main(int argc, char *argv[])
{
    uchar *fslp;
    uint beef1337;
    int fsize, i;
    FILE *f;
    
    if(argc < 3) {
        fprintf(stderr, "usage: vooblyslpdecode slp_in.slp slp_out.slp\n");
        return 1;
    }
    
    f = fopen_f(argv[1], "rb");
    fread(&beef1337, 1, 4, f);
    
    if(beef1337 != 0xBEEF1337) {
        fprintf(stderr, "error: not a voobly encoded slp file\n");
        return 1;
    }
    
    fseek(f, 0, SEEK_END);
    fsize = ftell(f) - 4;
    fseek(f, 4, SEEK_SET);
    
    fslp = malloc(fsize);
    fread(fslp, 1, fsize, f);
    fclose(f);
    
    for(i = 0; i < fsize; i++)
        fslp[i] = 0x20 * ((fslp[i] - 17) ^ 0x23) | ((uchar)((fslp[i] - 17) ^ 0x23) >> 3);
    
    f = fopen_f(argv[2], "wb");
    fwrite(fslp, 1, fsize, f);
    fclose(f);
}