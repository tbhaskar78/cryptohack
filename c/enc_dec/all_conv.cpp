/* Author : Bhaskar Tallamraju 
 * Date   : Apr 18, 2020
 * Copyright (c) 2020 Bhaskar Tallamraju. All Rights Reserved
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/bigNumber.h"
#include <string>
#include <iostream>

static const unsigned char base64_table[65] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const int B64index[256] = { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 62, 63, 62, 62, 63, 52, 53, 54, 55,
56, 57, 58, 59, 60, 61,  0,  0,  0,  0,  0,  0,  0,  0,  1,  2,  3,  4,  5,  6,
7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,  0,
0,  0,  0, 63,  0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };

using pr0crustes::BigNumber;

#define HEXATOINT 1
#define NUMTOHEXA 2
#define INT2ASCII 3
#define BASE64ENC 4
#define BASE64DEC 5
#define END 5
#define STOP 0

#define usage() \
    {\
        printf("usage: \n"); \
        printf("\tconv <Input string>\n"); \
    }
        

/**
* base64_decode - Base64 decode
* @data: Data to be encoded
* @len: Length of the data to be encoded
* Returns: Allocated buffer of out_len bytes of encoded data,
* or empty string on failure
*/
std::string base64_decode(const void* data, const size_t len)
{
    unsigned char* p = (unsigned char*)data;
    int pad = len > 0 && (len % 4 || p[len - 1] == '=');
    const size_t L = ((len + 3) / 4 - pad) * 4;
    std::string str(L / 4 * 3 + pad, '\0');

    for (size_t i = 0, j = 0; i < L; i += 4)
    {
        int n = B64index[p[i]] << 18 | B64index[p[i + 1]] << 12 | B64index[p[i + 2]] << 6 | B64index[p[i + 3]];
        str[j++] = n >> 16;
        str[j++] = n >> 8 & 0xFF;
        str[j++] = n & 0xFF;
    }
    if (pad)
    {
        int n = B64index[p[L]] << 18 | B64index[p[L + 1]] << 12;
        str[str.size() - 1] = n >> 16;

        if (len > L + 2 && p[L + 2] != '=')
        {
            n |= B64index[p[L + 2]] << 6;
            str.push_back(n >> 8 & 0xFF);
        }
    }
    return str;
}

/**
* base64_encode - Base64 encode
* @src: Data to be encoded
* @len: Length of the data to be encoded
* @out_len: Pointer to output length variable, or %NULL if not used
* Returns: Allocated buffer of out_len bytes of encoded data,
* or empty string on failure
*/
std::string base64_encode(const unsigned char *src, size_t len)
{
    unsigned char *out, *pos;
    const unsigned char *end, *in;

    size_t olen;

    olen = 4*((len + 2) / 3); /* 3-byte blocks to 4-byte */

    if (olen < len)
        return std::string(); /* integer overflow */

    std::string outStr;
    outStr.resize(olen);
    out = (unsigned char*)&outStr[0];

    end = src + len;
    in = src;
    pos = out;
    while (end - in >= 3) {
        *pos++ = base64_table[in[0] >> 2];
        *pos++ = base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
        *pos++ = base64_table[((in[1] & 0x0f) << 2) | (in[2] >> 6)];
        *pos++ = base64_table[in[2] & 0x3f];
        in += 3;
    }

    if (end - in) {
        *pos++ = base64_table[in[0] >> 2];
        if (end - in == 1) {
            *pos++ = base64_table[(in[0] & 0x03) << 4];
            *pos++ = '=';
        }
        else {
            *pos++ = base64_table[((in[0] & 0x03) << 4) |
                (in[1] >> 4)];
            *pos++ = base64_table[(in[1] & 0x0f) << 2];
        }
        *pos++ = '=';
    }

    return outStr;
}

int getnum(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return (ch - '0');
    }
    else 
    {
        switch(ch)
        {
            case 'a': 
            case 'A': return 10;
            case 'b': 
            case 'B': return 11;
            case 'c': 
            case 'C': return 12;
            case 'd': 
            case 'D': return 13;
            case 'e': 
            case 'E': return 14;
            case 'f': 
            case 'F': return 15;
        }
    }
}

std::string hex2Int(std::string hexStr)
{
    char *hexString = NULL;
    char *decoded = NULL;
    int i = 0, j=0;
    hexString = (char *)calloc(hexStr.length()+1, sizeof(char));
    strncpy(hexString, hexStr.c_str(), hexStr.length());
    decoded = (char *)calloc(strlen(hexString), sizeof(char));
    //printf("Enter the string to convert: ");
    //fgets(hexString, 1000, stdin);

    printf("\t");
    for (i=0, j=0; i< strlen(hexString)-1; i++,j++)
    {
        decoded[j] =  (getnum(hexString[i])*16) + getnum(hexString[i+1]);
        printf("%d ", decoded[j]);
        i++;
    }
    printf("\n");
    std::string decodedStr(decoded);
    free (hexString);
    free (decoded);

    return decodedStr;

}



std::string number2Hex(std::string str)
{
    BigNumber a(str);
    std::string hexaDeciNum;

    // counter for hexadecimal number array 
    int i = 0; 

    while(a!=0) 
    {    
        // temporary variable to store remainder 
        BigNumber temp = 0;

        // storing remainder in temp variable. 
        temp = a%16;
        if (temp >= 10)
        {
            temp += 55;
            int hex = std::stoi(temp.asString());
            std::string hexStr(1, hex);
            hexaDeciNum.insert(0, hexStr);
        }
        else
        {
            hexaDeciNum.insert(0, (std::string)temp.asString());
        }

        a = a/16; 
    } 
    printf("\t");
    std::cout << hexaDeciNum << std::endl;
    return hexaDeciNum;

}

int integer2ASCII(void)
{
    int array[100] = {0};
    int i, numElements = 0;

    printf("Enter the number of ints = ");
    scanf("%d", &numElements);
    printf ("Start entering the integers to be converted \n");

    for (i = 0; i < numElements; i++)
    {
        scanf("%d", &array[i]);
    }
    printf ("\t");
    for (i = 0; i < numElements; i++)
    {
        printf("%c, ", array[i]);
    }
    printf("\n");
}


int main(int argc, char *argv[])
{
    int selection[12] = {0};
    int numOfSelections = 0;
    std::string encodedStr;
    int i = 0;
    if (argc < 2 || argc > 2)
    {
        std::cout << "[ERROR]: Incorrect number of arguments" << std::endl;
        usage();
        return -1;
    }
    else 
    {
        encodedStr = argv[1];
        std::cout << "Input String : " << encodedStr << std::endl;
    }


    // CLI
    printf ("Enter the connections for decoding\n");
    printf ("\t [0] Stop \n");
    printf ("\t [1] Hexadecimal to integer \n");
    printf ("\t [2] Integer to Hexadecimal \n");
    printf ("\t [3] Integer to ASCII \n");
    printf ("\t [4] base64 Encoding \n");
    printf ("\t [5] base64 Decoding \n");
    printf ("\t [9] QUIT \n");
    while ( 1 )
    {
        printf("\t Enter your selection: ");
        scanf("%d", &selection[numOfSelections]);
        if (selection[numOfSelections] < STOP || selection[numOfSelections] > END) 
        {
            printf("Chose a wrong option, exiting\n");
            return -1;
        }
        if (selection[numOfSelections] == 0 ) break;
        if (selection[numOfSelections] == 9 ) return 0;
        numOfSelections++;
    }

    printf ("\n\tDECODING STAGES ");
    for (i = 0; i < numOfSelections ; i++)
    {
        printf("%d ", selection[i]);
        if (i+1 != numOfSelections) printf("-> ");
    }
    printf("\n\n");

    std::string str2pass = encodedStr;
    for (i = 0; i < numOfSelections ; i++)
    {
        switch(selection[i])
        {
            case HEXATOINT: 
            {
                printf("1 -> Hexadecimal to Integer ..\n");
                str2pass = hex2Int(str2pass);
                break;
            }
            case NUMTOHEXA:
            {
                printf("2 -> Converting number to hexadecimal ..\n");
                str2pass = number2Hex(str2pass);
                break;
            }
            case INT2ASCII:
            {
                printf("3 -> Integer to ASCII ..\n");
                integer2ASCII();
                break;
            }
            case BASE64ENC:
            {
                printf("4 -> Base64 encoding ..\n");
                str2pass = base64_encode(reinterpret_cast<const unsigned char*>(str2pass.c_str()), str2pass.length());
                break;
            }
            case BASE64DEC:
            {
                printf("5 -> Base64 decoding ..\n");
                str2pass = base64_decode(reinterpret_cast<const unsigned char*>(str2pass.c_str()), str2pass.length());
                break;
            }
            default:
            {
                break;
            }

        }
        if (selection[i] == 0) break;
    }
    std::cout << "Final String: " << str2pass << std::endl;

    return 0;
}
/* End of File */
