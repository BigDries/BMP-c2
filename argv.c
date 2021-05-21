#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    for(int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }
    if(argc > 1 && strcmp(argv[i], "-s") == 0)
    {
        char * secret.txt = argv[i + 1]; 
    }
    else if(argc > 1 && strcmp(argv[i], "-i") == 0)
    {
        char * test.bmp = argv[i+1];
    }

return 0;
}