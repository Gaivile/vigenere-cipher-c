#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv[])
{

    // checks if there is exactly one command line argument
    if (argc != 2)
    {
        printf("Please, enter one valid argument.\n");
        return 1;
    }
    
    // makes a key of command line arg. and checks if it's correct
    char* key = argv[1];
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Please, enter one valid argument.\n");
            return 1;
        }
    }
    
    // encrypt given text by the key
    FILE* file = fopen("test.txt", "r");
    if(file == NULL)
    {
        return 1;
    }
    
    // get file size
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // allocate and read file into memory block
    char* text = malloc(size * sizeof(char) + 1);
    fread(text, 1, size, file);
    
    int keylen = strlen(key);
    int x = 0; // another variable to wrap key around text and shift correctly
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            keylen = x % strlen(key);
            if (islower(text[i])) //for lowercase letters in text
            {
                if(islower(key[keylen])) // for lowecase letters in key
                {
                    int letter = ((text[i] - 97 + key[keylen] - 97) % 26) + 97;
                    printf("%c", letter);
                }
                else // for uppercase letters in key
                {
                        int letter = ((text[i] - 97 + key[keylen] - 65) % 26) + 97;
                        printf("%c", letter);
                }
            }
            if (isupper(text[i])) // for uppercase letters in text
                {
                    if (islower(key[keylen])) // for lowerace letters in key
                    {
                        int letter = ((text[i] - 65 + key[keylen] - 97) % 26) + 65;
                        printf("%c", letter);
                    }
                    else // for uppercase letters in key
                    {
                        int letter = ((text[i] - 65 + key[keylen] - 65) % 26) + 65;
                        printf("%c", letter);
                    }
                }
            x++; // adds +1 to wrap key around text 
        }
        else // leaves non-alphabetical chars unchanged
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}
