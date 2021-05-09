#include <stdio.h>
#include <stdlib.h>

#define __DEBUG

#define BMPINPUTFILE "test.bmp"
#define SecretInputFile "Secret.txt"

int main()
{
    #ifdef __DEBUG
        printf("DEBUG info: BMP transformer\n");
    #endif

	
    FILE* inputFilePointer = fopen(BMPINPUTFILE, "rb"); //maak een file pointer naar de afbeelding
    FILE* SecretFilePointer = fopen(SecretInputFile, "r");
	
	if(inputFilePointer == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", BMPINPUTFILE);
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
    fread(bmpHeader, sizeof(unsigned char), 54, inputFilePointer); // lees de 54-byte header

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
	
    fread(inputPixels, sizeof(unsigned char), imageSize, inputFilePointer); // Lees alle pixels (de rest van de file
	fclose(inputFilePointer);


	int messagesize = imageSize/8;
	unsigned char* message = (unsigned char *) calloc(imageSize, sizeof(unsigned char));
	
	fread(message, sizeof(unsigned char), messagesize, SecretFilePointer);
	fclose(SecretFilePointer);
	
	
	for(int i =0; i < imageSize-2; i+=3)
	{
		//printf("pixel %d: B= %x, G=%x, R=%x\n", i, inputPixels[i], inputPixels[i+1], inputPixels[i+2]); //neerschrijven van pixelwaardes (hexadecimalen)
		
		inputPixels[i] = inputPixels[i]&mask; //LSB =0
		inputPixels[i+1] = inputPixels[i+1]&mask; //LSB =0
		inputPixels[i+2] = inputPixels[i+2]&mask; //LSB =0
		
		printf("pixel %d: B= %x, G=%x, R=%x\n", i, inputPixels[i], inputPixels[i+1], inputPixels[i+2]); //neerschrijven van pixels met LSB 0 (hexadecimalen)
	}
    
	for(int i =0; i < messagesize; i++)
	{
		printf("%x \n", message[i]); //neerschrijven van pixelwaardes (hexadecimalen)
	}
	
    free(inputPixels);
	free(message);
    
    return 0;
}
