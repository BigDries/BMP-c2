#include <stdio.h>
#include <stdlib.h>

#define __DEBUG

#define BMPINPUTFILE "test.bmp"
#define OUTINPUTFILE "broek.bmp"
#define SecretInputFile "Secret.txt"

void MessageToBit(unsigned char* message, int size, unsigned char* Bin);

int main()
{
    #ifdef __DEBUG
        printf("DEBUG info: BMP transformer\n");
    #endif

	
    FILE* inputFilePointer = fopen(BMPINPUTFILE, "rb"); //maak een file pointer naar de afbeelding
    FILE* SecretFilePointer = fopen(SecretInputFile, "r"); //maak een file pointer naar de afbeelding
    FILE* outputFilePointer = fopen(OUTINPUTFILE, "rb");

	
	if(inputFilePointer == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", BMPINPUTFILE);
        exit(EXIT_FAILURE);
    }
	else if(outputFilePointer == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", OUTINPUTFILE);
        exit(EXIT_FAILURE);
    }
	else if(SecretFilePointer == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", SecretInputFile);
        exit(EXIT_FAILURE);
    }

    #ifdef __DEBUG
        printf("DEBUG info: Opening Files OK: %s %s\n", BMPINPUTFILE, SecretInputFile);
    #endif

    unsigned char bmpHeader[54]; // voorzie een array van 54-bytes voor de BMP Header
    fread(bmpHeader, sizeof(unsigned char), 54, inputFilePointer); // lees de 54-gf header

    //Informatie uit de header (wikipedia)
    // haal de hoogte en breedte uit de header
    int breedte = *(int*)&bmpHeader[18];
    int hoogte = *(int*)&bmpHeader[22];

    
	#ifdef __DEBUG
        printf("DEBUG info: breedte = %d\n", breedte);
        printf("DEBUG info: hoogte = %d\n", hoogte);
    #endif
	
    
	int imageSize = 3 * breedte * hoogte; //ieder pixel heeft 3 byte data: rood, groen en blauw (RGB)
    unsigned char* inputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char)); // allocate een array voor alle pixels
	unsigned char mask = 0b11111110;
	unsigned char* BinMessage = (unsigned char *) calloc(imageSize, sizeof(unsigned char));
	
    fread(inputPixels, sizeof(unsigned char), imageSize, inputFilePointer); // Lees alle pixels (de rest van de file
	fclose(inputFilePointer);


	int messagesize = imageSize/8;
	
	unsigned char* message = (unsigned char *) calloc(imageSize, sizeof(unsigned char));
	
	fread(message, sizeof(unsigned char), messagesize, SecretFilePointer);
	fclose(SecretFilePointer);
	
	
	for(int i =0; i < imageSize-2; i+=3)
	{
		//printf("pixel %d: B= %x, G=%x, R=%x\n", i, inputPixels[i], inputPixels[i+1], inputPixels[i+2]); //neerschrijven van pixelwaardes (hexadecimalen)
		
		inputPixels[i] = inputPixels[i]&mask;     //LSB =0
		inputPixels[i+1] = inputPixels[i+1]&mask; //LSB =0
		inputPixels[i+2] = inputPixels[i+2]&mask; //LSB =0
		
		printf("pixel %d: B= %x, G=%x, R=%x\n", i, inputPixels[i], inputPixels[i+1], inputPixels[i+2]); //neerschrijven van pixels met LSB 0 (hexadecimalen)
	}
    
	for(int i =0; i < messagesize; i++)
	{
		printf("%c \n", message[i]); //neerschrijven van message (hexadecimalen)
	}
	MessageToBit(message, messagesize, BinMessage);
    for(int i =0; i < imageSize; i++)
	{
		printf("%d ", BinMessage[i]); //neerschrijven van message (hexadecimalen)
	}
	for(int i = 0; i <messagesize; i++)
	{
	inputPixels[i]=inputPixels[i]+BinMessage[i];
		
	}
	for(int i =0; i < imageSize-2; i+=3)
	{
		printf("pixel %d: B= %x, G=%x, R=%x\n", i, inputPixels[i], inputPixels[i+1], inputPixels[i+2]); //neerschrijven van pixels met LSB 0 (hexadecimalen)
	}
	fwrite(inputPixels, sizeof(unsigned char), imageSize, outputFilePointer);
	fwrite(bmpHeader, sizeof(unsigned char), 54, outputFilePointer);
	free(inputPixels);
	free(message);

    return 0;
}


void MessageToBit(unsigned char* message, int size, unsigned char* Bin)
{
	//random tekst ==> 01010010 01000001 01001110 01000100 01001111 01001101 00100000 01010100 01000101 01001011 01010011 01010100
	
	for(int f=0; f<size;f++)
	{
		for(int i=0; i<8;i++)
		{
			char mask = 0b00000001;
			Bin[((f*8)+i)] = (message[f]>>i)&mask; //pos =1?
		}
	}
}
