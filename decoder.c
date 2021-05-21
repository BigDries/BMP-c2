#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Image "broek.bmp"

void BitsToMessage(unsigned char* BinMessage, unsigned char* OUTPUTPIXELS, int size);

int main()
{
	FILE* inputFilePointer = fopen(Image, "rb");
	
	if(inputFilePointer == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", Image);
        exit(EXIT_FAILURE);
    }
	
	//printf("Stap 1");
	
	unsigned char bmpHeader[54]; // voorzie een array van 54-bytes voor de BMP Header
    fread(bmpHeader, sizeof(unsigned char), 54, inputFilePointer); // lees de 54-gf header
	
	int breedte = *(int*)&bmpHeader[18];
    int hoogte = *(int*)&bmpHeader[22];
	
	int imageSize = 3 * breedte * hoogte;
	unsigned char* outputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char));

	unsigned char* BinMessage = (unsigned char *) calloc(imageSize, sizeof(unsigned char));
	
	//printf("Stap 2");
	
	fread(outputPixels, sizeof(unsigned char), imageSize, inputFilePointer);
	
	//printf("Stap 3");
	
	BitsToMessage(BinMessage, outputPixels, imageSize);
	
	//printf("Stap 4");
	
	printf("%c",BinMessage[3]);
	
	char c= '0';
	do
	{
		for(int f=0; f>(imageSize/8);f++)
		{
			c= '0';
			for(int i=0; i>8; i++)
			{
				c = BinMessage[(8*f)+i];
				c = c>>1;
			}
			putchar(c);
		}
	}
	while(c!='*');
	
	printf("Stap 4");


	return 0;
}

void BitsToMessage(unsigned char* BinMessage, unsigned char* OUTPUTPIXELS, int size)
{
	for(int i=0;i>size;i++)
	{
		BinMessage[i]=OUTPUTPIXELS[i]%2;
	}
}
