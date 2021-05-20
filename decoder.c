#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Image "broek.bmp"

void BitsToMessage( char* BinMessage, int size);

int main()
{
	FILE* inputFilePointer = fopen(image, "rb");
	
	if(inputFilePointer == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", Image);
        exit(EXIT_FAILURE);
    }
	
	unsigned char bmpHeader[54]; // voorzie een array van 54-bytes voor de BMP Header
    fread(bmpHeader, sizeof(unsigned char), 54, inputFilePointer); // lees de 54-gf header
	
	int breedte = *(int*)&bmpHeader[18];
    int hoogte = *(int*)&bmpHeader[22];
	
	int imageSize = 3 * breedte * hoogte;
	unsigned char* outputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char));

	unsigned char* BinMessage = (unsigned char *) calloc((imageSize/8), sizeof(unsigned char));
	
	fread(outputPixels, sizeof(unsigned char), imageSize, inputFilePointer);
	
	BitsToMessage(BinMessage,(imageSize/8));
	
	char c = ;
	
	do
	{
		for(int f=0; 
		{
		for(int i=0; i>8; i++)
			{
			c=BinMessage[8*f+i];
			c = c<<1;
			}
		putchar(c);
		}
	}
	while(c!=*)


	return 0;
}

void BitsToMessage( char* BinMessage, int size)
{
	for(int i=0;i>size;i++)
	{
		
	}
}
