//gcc -Wall -pedantic main.c -o dec
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define __DEBUG //haal uit comments voor debugging

#define BMPINPUTFILE "test.bmp"
#define OUTINPUTFILE "out.bmp"
#define SecretInputFile "Secret.txt"

void MessageToBit( char* message, int size, unsigned char* Bin);

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

	
    #ifdef __DEBUG
        printf("DEBUG info: BMP transformer\n");
    #endif

	
    FILE* inputFilePointer = fopen(BMPINPUTFILE, "rb"); //maak een file pointer naar de afbeelding
    FILE* SecretFilePointer = fopen(SecretInputFile, "r"); //maak een file pointer naar de afbeelding
    FILE* outputFilePointer = fopen(OUTINPUTFILE, "wb");

	if(inputFilePointer == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", BMPINPUTFILE);
        exit(EXIT_FAILURE);
    }
	
	else if(outputFilePointer == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", OUTINPUTFILE);
		system("pause");
        exit(EXIT_FAILURE);
    }
	
	else if(SecretFilePointer == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", SecretInputFile);
        exit(EXIT_FAILURE);
    }

    #ifdef __DEBUG
        printf("DEBUG info: Opening Files OK: %s %s %s\n", BMPINPUTFILE, OUTINPUTFILE, SecretInputFile);
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
	unsigned char* BinMessage = (unsigned char *) calloc(imageSize, sizeof(unsigned char));
	
	unsigned char mask = 0b11111110; //mask om bits op 0 te zetten
	
    fread(inputPixels, sizeof(unsigned char), imageSize, inputFilePointer); // Lees alle pixels (de rest van de file
	fclose(inputFilePointer);


	int messagesize = imageSize/8; //max messagesize
	
	char* message = ( char *) calloc(imageSize, sizeof( char));
	
	if(!feof (SecretFilePointer))
	{
		fread(message, sizeof(unsigned char), messagesize, SecretFilePointer);
	}
	
	fclose(SecretFilePointer);
	
	messagesize=strlen(message); //messagesize inkorten tot juiste lengte
	
	for(int i =0; i < (messagesize*8); i+=3)
	{
		inputPixels[i] = inputPixels[i]&mask;     //LSB =0
		inputPixels[i+1] = inputPixels[i+1]&mask; //LSB =0
		inputPixels[i+2] = inputPixels[i+2]&mask; //LSB =0
	}
    
	for(int i =0; i < messagesize; i++)
	{
		printf("%c", message[i]); //neerschrijven van message (hexadecimalen)
	}
	
	MessageToBit(message, messagesize, BinMessage);
	
    for(int i =0; i < (messagesize*8); i++)
	{
		inputPixels[i]=inputPixels[i]+BinMessage[i];
	}
	
	fwrite(bmpHeader, sizeof(unsigned char), 54, outputFilePointer);
	fwrite(inputPixels, sizeof(unsigned char), imageSize, outputFilePointer);
	free(inputPixels);
	free(message);

    return 0;
}


void MessageToBit( char* message, int size, unsigned char* Bin)
{
	for(int f=0; f<size;f++)
	{
		for(int i=0; i<8;i++)
		{
			char mask = 0b00000001;
			Bin[((f*8)+i)] = (message[f]>>(7-i))&mask; //pos =1?
		}
	}
}
