/*
This program checks if a first word (can be up to 20 letters long) is
an anagram of a second word (can also be up to 20 letters long), where
the check being done is case-insensitive
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool Is_Same_Word_Length(char first_word[], char second_word[]);
void Alphabetize_Words(char first_word[], char second_word[]);
bool Is_Anagram(char first_word[], char second_word[]);

/*
This function checks to see if two words are anagrams of one another,
being case-insensitive
@char first_word[]: first word (can be up to 20 letters long)
@char second_word[]: second word (can be up to 20 letters long)
@return: bool value of true if the two words are anagrams of one another, bool value of false otherwise
*/
bool Is_Anagram(char first_word[], char second_word[]) {    
    bool is_anagram;

    if (!Is_Same_Word_Length(first_word, second_word)){
        is_anagram = false;
    }
    else {
        Alphabetize_Words(first_word, second_word);
        
        for (unsigned int i = 0; i < strlen(first_word); ++i) {
            if (tolower(first_word[i]) == tolower(second_word[i])) {
                is_anagram = true;
            }
            else {
                is_anagram = false;
                break;
            }
        }
    }

    return is_anagram;
}

/*
This function alphabetizes two words, being case-insensitive and
assuming the length of both words are the same (both words have the
same number of letters in them)
@char first_word[]: first word (can be up to 20 letters long)
@char second_word[]: second word (can be up to 20 letters long)
@return: N/A
*/
void Alphabetize_Words(char first_word[], char second_word[]) {
    char placeholder;
    unsigned int i, j;

    for (i = 0; i < strlen(first_word); ++i) {
        for (j = i + 1; j < strlen(first_word); ++j) {
            if ((tolower(first_word[i])) > tolower(first_word[j])) {
                placeholder = first_word[i];
                first_word[i] = first_word[j];
                first_word[j] = placeholder;
            }

            if ((tolower(second_word[i])) > tolower(second_word[j])) {
                placeholder = second_word[i];
                second_word[i] = second_word[j];
                second_word[j] = placeholder;
            }
        }
    }

}

/*
This function checks to see if two words are the same length (i.e.
have the same number of letters)
@char first_word[]: first word (can be up to 20 letters long)
@char second_word[]: second word (can be up to 20 letters long)
@return: bool value of true if the two words are the same length, bool value of false otherwise
*/
bool Is_Same_Word_Length(char first_word[], char second_word[]) {
    bool is_same_word_length = false;

    if (strlen(first_word) == strlen(second_word)) {
        is_same_word_length = true;
    }

    return is_same_word_length;
}

int main(void) {
    char firstWord[21], secondWord[21], orig_first_word[21], orig_second_word[21];
    
    printf("Please enter the first word: ");
    scanf("%s", firstWord);
    printf("\n");

    printf("Please enter the second word: ");
    scanf("%s", secondWord);
    printf("\n");

    strcpy(orig_first_word, firstWord);
    strcpy(orig_second_word, secondWord);

    (Is_Anagram(firstWord, secondWord)) ? printf("%s is an anagram of %s\n\n", orig_first_word, orig_second_word) : printf("%s is NOT an anagram of %s\n\n", orig_first_word, orig_second_word);

    return 0;
}
