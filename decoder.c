#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Image "out.bmp"

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
	
	for(int i=0; i<imageSize; i++)
	{
		printf("%d \n", outputPixels[i]);
	}
	//printf("Stap 3");
	
	BitsToMessage(BinMessage, outputPixels, imageSize);
	
	for(int i=0; i<imageSize; i++)
	{
		printf("%d", BinMessage[i]);
	}
	
	//printf("Stap 4");
	//gcc -Wall -pedantic decoder.c -o dec
	
	//fout bij N O M X Y
	char letter = 0;
	int f=0;
	printf("\n");
	while(letter!='*' && f!=51)
	{
		letter =0; 
		for(int i=0; i<8; i++)
		{
			letter = letter <<1;
			//printf("%d\t", BinMessage[(f*8)+i]);
			letter = letter | BinMessage[(f*8)+i]; 
		}
		f++;
		//printf("\n%c \n", letter);
		//printf("%d \n", f);
		//system("pause");
		putchar(letter);
	}
	


	return 0;
}

void BitsToMessage(unsigned char* BinMessage, unsigned char* OUTPUTPIXELS, int size)
{
	for(int i=0;i<size;i++)
	{
		BinMessage[i]=(OUTPUTPIXELS[i]%2);
	}
}
