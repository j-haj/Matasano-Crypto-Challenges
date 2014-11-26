#include <stdio.h>
#include <stdlib.h>

/**
 * Jeff Hajewski - 11/15/2014
 *
 * This file contains my solutions to the first set of Matasano
 * Crypto challenges. This code is presented as is and I make
 * no guarantees to it's completeness or correctness.
 */

//////////////////////////////
//  FUNCITON DECLARATIONS
//////////////////////////////
#pragma mark - Function Definitions

char* getBase64(char*, int);
char* getHex(char*, int);

//////////////////////////////
//  MAIN
//////////////////////////////
#pragma mark - Main

int main(){

    // Test - keep the number of bits evenly divisible by 3
    char testWord[] = "Man is distinguished, not only by his reason,\
    but by this singular passion from in the continued and indefatigable\
    generation of knowledge, exceeds the short vehemence of any carnal pleasur";
    int length = sizeof(testWord) - 1;

    char *outputArray = getBase64(testWord, length);

    // Print the output
    for (int i = 0; i < length * 4/3; i++)
    {
        printf("%c", outputArray[i]);
    }
    printf("\n");

    return 0;
} // End main()

//////////////////////////////
//  FUNCTION IMPLEMENTATIONS
//////////////////////////////
#pragma mark - Funciton Implementations

char *getBase64(char* inputArray, int inputArrayLength){
    // Lookup table for the base64 characters
    char base64Table[] = {
                    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };

    char *outputArray = malloc(inputArrayLength * 4 / 3 * sizeof(char));
    int bufferBits;
    int loopCounter = 0;
    int newWord;
    int firstChar, secondChar, thirdChar;
    int firstSixBitGroup, secondSixBitGroup, thirdSixBitGroup, fourthSixBitGroup;

    for (int i = 0; i < inputArrayLength; i = i + 3)
    {
        // Shift initial chars to prep for creating a
        // 24 bit word
        firstChar = inputArray[i] << 16;
        secondChar = inputArray[i + 1] << 8;
        thirdChar = inputArray[i + 2];

        // Create a 24 bit word
        newWord = firstChar | secondChar | thirdChar;

        // Pick up bits 24 through 19
        firstSixBitGroup = newWord >> 18;

        // Pick up bits 18 through 13
        secondSixBitGroup = newWord >> 12 & ~(firstSixBitGroup << 6);

        // Pick up bits 12 through 7
        bufferBits = firstSixBitGroup << 12 | secondSixBitGroup << 6;
        thirdSixBitGroup = newWord >> 6 & ~(bufferBits);

        // Pick up bits 6 through 1
        bufferBits = firstSixBitGroup << 18 | secondSixBitGroup << 12 |
         thirdSixBitGroup << 6;
        fourthSixBitGroup = newWord & ~(bufferBits);

        // Create output
        outputArray[loopCounter] = base64Table[firstSixBitGroup];
        outputArray[loopCounter + 1] = base64Table[secondSixBitGroup];
        outputArray[loopCounter + 2] = base64Table[thirdSixBitGroup];
        outputArray[loopCounter + 3] = base64Table[fourthSixBitGroup];
        loopCounter += 4;

    }

    return outputArray;
}

// Incomplete
char *getHex(char* inputArray, int inputArrayLength){
    // Lookup table for the hex characters
    char * hexTable = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                        'a', 'b', 'c', 'd', 'e', 'f'};
    int index;
    char c;
    for (int i = 0; i < inputArrayLength; i++) {
        /* code */
        index = 0;
        c = inputArray[i];
        while (c != hexTable[index]) {
            index ++;
        }
    }
}









// File end