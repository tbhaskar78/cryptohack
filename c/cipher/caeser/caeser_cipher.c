/* Author : Bhaskar Tallamraju 
 * Date   : Apr 18, 2020
 * Copyright (c) 2020 Bhaskar Tallamraju. All Rights Reserved
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cipherShift = 0;
char mapped[26][1] = {0};
char reverse_mapped[26][1] = {0};
#define map() \
    do{ \
        for (j=0,i = cipherShift-1; i >= 0; j++, i--) \
        { \
            mapped[j][0] = 'z' - i; \
        } \
        for (i = 0; i < 26-cipherShift; i++) \
        { \
            mapped[i+cipherShift][0] = 'a' + i; \
        }  \
    }while(0)

#define reverseMap() \
    do{ \
        for (i = 0; i < 26 - cipherShift; i++) \
        { \
            reverse_mapped[i][0] = 'a' + cipherShift + i; \
        } \
        for (j = 0, i = 26 - cipherShift; i < 26; j++, i++) \
        { \
            reverse_mapped[i][0] = 'a' + j; \
        }  \
    }while(0)

#define printReverseMap() \
    { \
        int i = 0; \
        for (i=0;i<26;i++) printf("%c ", reverse_mapped[i][0]); \
    }
#define printMap() \
    { \
        int i = 0; \
        for (i=0;i<26;i++) printf("%c ", mapped[i][0]); \
    }

int decodeString(void);
int createEncodedString(void);

int main(void)
{
    int j, i = 0;
    int choice = 0;
    printf("Enter cipher shift value = ");
    scanf("%d", &cipherShift);
    printf ("Cipher shift is %c -> %c \n", 'a', 'a'+cipherShift);
    map();
    reverseMap();

    printf ("\n\nMenu: \n");
    printf ("\t 1. Decode a string \n");
    printf ("\t 2. Create an encoded string\n");
    printf ("Enter your choice (1/2) = ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1: decodeString();
                break;
        case 2: createEncodedString();
                break;
        default: 
                printf ("Incorrect choice, enter 1 or 2\n");
                return -100;
    }
    return 0;
}

int decodeString(void)
{
    int j, i = 0;
    int stringLength = 0;
    char *encodedString = NULL;
    char *decodedString = NULL;
    printf("Enter string length = ");
    scanf("%d", &stringLength);
    getchar();
    printf ("Enter encoded string = ");
    if((encodedString = (char*) malloc(sizeof(char)*stringLength)) == NULL)
    {
        printf ("malloc failed to allocate \n");
        return -1;
    }
    if((decodedString = (char*) malloc(sizeof(char)*stringLength)) == NULL)
    {
        printf ("malloc failed to allocate \n");
        return -1;
    }
    encodedString = fgets(encodedString, 100, stdin);
    if (encodedString == NULL)
    {
        printf ("fgets returning null\n");
        free(encodedString);
        return -1;
    }
    //scanf("%s", encodedString);

    for (i = 0; encodedString[i] > 0; i++)
    {
        if (encodedString[i] == 32)
        {
            decodedString[i] = 32;
        }
        else 
        {
            decodedString[i] = mapped[encodedString[i] - 'a'][0];
        }
    }

    printf ("Decoded String %s\n", decodedString);

    free(encodedString);


    return 0;
}

int createEncodedString(void)
{
    int j, i = 0;
    int stringLength = 0;
    char *encodedString = NULL;
    char *string = NULL;

    printReverseMap();
    printf("Enter string length = ");
    scanf("%d", &stringLength);
    getchar();
    printf ("Enter string to encode = ");
    if((encodedString = (char*) calloc(stringLength, sizeof(char))) == NULL)
    {
        printf ("malloc failed to allocate \n");
        return -1;
    }
    if((string = (char*) malloc(sizeof(char)*stringLength)) == NULL)
    {
        printf ("malloc failed to allocate \n");
        return -1;
    }
    string = fgets(string, 100, stdin);
    if (string == NULL)
    {
        printf ("fgets returning null\n");
        free(string);
        return -1;
    }

    for (i = 0; i < strlen(string)-1; i++)
    {
        if (string[i] == 32)
        {
            encodedString[i] = 32;
        }
        else 
        {
            encodedString[i] = reverse_mapped[string[i] - 'a'][0];
        }
    }

    printf ("Encoded String is %s\n", encodedString);

    free(encodedString);


    return 0;
}
/* End of File */
