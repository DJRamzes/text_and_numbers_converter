#include <stdio.h>
#include <stdlib.h>

/*
- command line arguments:
    1) key "-bin" 		- convert decimal to binary;
    2) key "-oct" 		- convert decimal to octal;
    3) key "-hex" 		- convert decimal to hexadecimal;
    4) key "-spr" and file name - spread text(from one file to another file);
    5) key "-enc" and file name	- text encryption;
    6) key "-dec" and file name - text decryption;
    7) key "-help"		- help box.
*/

struct text{
    int data;
    struct text *next;
    struct text *prev;
};

char letters(int value)
{
    switch(value){
        case 10: // letter A
            return 'A';
        case 11: // letter B
            return 'B';
        case 12: // letter C
            return 'C';
        case 13: // letter D
            return 'D';
        case 14: // letter E
            return 'E';
        case 15: // letter F
            return 'F';
        default:
            return value + '0';
    }
}

void numbers_converting(int value, int degree_of_number)
{
    if(value < degree_of_number){
        printf("%c", letters(value));
        return;
    }
    
    numbers_converting(value / degree_of_number, degree_of_number);
    printf("%c", letters(value % degree_of_number));
}

void decimal_to_binary(char **agrv)
{
    int number = atoi(*(agrv + 2));
    numbers_converting(number, 2);
    printf("\n");
}

void decimal_to_octal(char **agrv)
{
    int number = atoi(*(agrv + 2));
    numbers_converting(number, 8);
    printf("\n");
}

void decimal_to_hexadecimal(char **agrv)
{
    int number = atoi(*(agrv + 2));
    numbers_converting(number, 16);
    printf("\n");
}

int spread_text(char **agrv)
{
    struct text *first = NULL, *last = NULL, *tmp;
    int ch;
    FILE *f1, *f2;
    f1 = fopen(*(agrv + 2), "r");
    f2 = fopen(*(agrv + 3), "w");
    
    if (!f1 || !f2){
        printf("Error");
        return 1;
    }
    
    first = malloc(sizeof(struct text)); // push upside-down text
    first->next = NULL;
    first->prev = NULL;
    while((ch = fgetc(f1)) != EOF){
        if (!last){
            last = first;
            first->data = ch;
        }
        else {
            tmp = malloc(sizeof(struct text));
            tmp->data = ch;
            first->prev = tmp;
            tmp->next = first;
            tmp->prev = NULL;
            first = tmp;
        }
    }
    
    while(first){
        fputc(first->data, f2);
        first = first->next;
    }
    
    if (fclose(f1) != 0)
        printf("Error close first file");
    else if (fclose(f2) != 0)
        printf("Error close second file");
    return 0;
}

int text_encryption(char **agrv)
{
    int ch;
    FILE *f1, *f2;
    f1 = fopen(*(agrv + 2), "r");
    f2 = fopen(*(agrv + 3), "w");
    
    if (!f1 || !f2){
        printf("Error");
        return 1;
    }
    
    while((ch = fgetc(f1)) != EOF)
        fputc(ch - 1, f2);
        
    if (fclose(f1) != 0)
        printf("Error close first file");
    else if (fclose(f2) != 0)
        printf("Error close second file");
    return 0;
}

int text_decryption(char **agrv)
{
    int ch;
    FILE *f1, *f2;
    f1 = fopen(*(agrv + 2), "r");
    f2 = fopen(*(agrv + 3), "w");
    
    if (!f1 || !f2){
        printf("Error");
        return 1;
    }
    
    while((ch = fgetc(f1)) != EOF)
        fputc(ch + 1, f2);
        
    if (fclose(f1) != 0)
        printf("Error close first file");
    else if (fclose(f2) != 0)
        printf("Error close second file");
    return 0;
}

void help()
{
    printf("input key -bin to convert decimal to binary\n");
    printf("input key -oct to convert decimal to octal\n");
    printf("input key -hex to convert decimal to hexadecimal\n");
    printf("input key -spr to spread text(from one file to another file). After key you should to input two file name(first - source, second - decinal)\n");
    printf("input key -enc to encryption text(from one file to another file). After key you should to input two file name(first - source, second - decinal)\n");
    printf("input key -dec to decryption text(from one file to another file). After key you should to input two file name(first - source, second - decinal)\n");
}

int strcompare(char *str1, char *str2)
{
    for (int i = 0; str1[i] != '\0' || str2[i] != '\0'; i++){
        if (str1[i] != str2[i])
            return 1;
        if (str1[i] == '\0' && str2[i] != '\0')
            return 1;
        if (str1[i] != '\0' && str2[i] == '\0')
            return 1;
    }
    return 0;
}
 
int main(int agrc, char **agrv)
{
    if (agrc < 2){
        printf("Too few arguments\n");
        return 1;
    }
    
    if (strcompare(*(agrv + 1), "-bin") == 0 && agrc == 3)
        decimal_to_binary(agrv);
    else if(strcompare(*(agrv + 1), "-oct") == 0 && agrc == 3)
        decimal_to_octal(agrv);
    else if(strcompare(*(agrv + 1), "-hex") == 0 && agrc == 3)
        decimal_to_hexadecimal(agrv);
    else if(strcompare(*(agrv + 1), "-spr") == 0 && agrc == 4)
        spread_text(agrv);
    else if(strcompare(*(agrv + 1), "-enc") == 0 && agrc == 4)
        text_encryption(agrv);
    else if(strcompare(*(agrv + 1), "-dec") == 0 && agrc == 4)
        text_decryption(agrv);
    else if(strcompare(*(agrv + 1), "-help") == 0 && agrc == 2)
        help();
    else
        printf("Input error, input key -help to look at help box\n");
    
    return 0;
}