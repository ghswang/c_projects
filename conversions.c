/* This program converts either temperature measurements
or distance measurements from one unit to another unit,
respectively. This program also ends whenever the user
enters invalid or unknown input */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
 
void convert_to_Common_Temp_then_Final_Temp();
void convert_to_Common_Dist_then_Final_Dist();
bool isValidFormat(const int numArgsRead, const int numArgsNeed);

int main(void) { 
    char temp_or_dist;  
    
    printf("Pick the type of conversion that you would like to do.\n\n");
    printf("T or t for temperature\n\n");
    printf("D or d for distance\n\n");
    printf("Enter your choice: ");
    scanf(" %c", &temp_or_dist);
    printf("\n");
    
    if (temp_or_dist == 'T' || temp_or_dist == 't') {
        convert_to_Common_Temp_then_Final_Temp();
    }
    else if (temp_or_dist == 'D' || temp_or_dist == 'd') {
        convert_to_Common_Dist_then_Final_Dist();
    }
    else if (!isValidFormat(1, 1)) {
        printf("Invalid formatting. Ending program.\n\n");
    }
    else {
        printf("Unknown conversion type %c chosen. Ending program.\n\n", toupper(temp_or_dist));
    }
    
    return 0; 
}  

/* This function converts the temperature type the user enters
to a common temperature type (i.e. C) and then converts that
temperature type to the one the user desires. This function also
exits the entire program if the user's input is an invalid
temperature type or is formatted incorrectly.
@param: N/A
@return: N/A */
void convert_to_Common_Temp_then_Final_Temp() {
    double init_temp, placeholder_temp, final_temp;
    char init_temp_unit, final_temp_unit;
    
    printf("Enter the temperature followed by its suffix (F, C, or K): ");
    scanf("%lf %c", &init_temp, &init_temp_unit);
    printf("\n");

    placeholder_temp = init_temp; // Converting from initial temp unit to C
    
    if (init_temp_unit == 'F' || init_temp_unit == 'f') {
        placeholder_temp = (init_temp - 32) * (5.0 / 9.0) ;
    }
    else if (init_temp_unit == 'K' || init_temp_unit == 'k') {
        placeholder_temp = init_temp - 273.15;
    }
    else if (init_temp_unit != 'C' && init_temp_unit !='c') {
        printf("%c is not a valid temperature type. Ending program.\n\n", toupper(init_temp_unit));
        exit(0);
    }
    else if (!isValidFormat(1, 1)) {
        printf("Invalid formatting. Ending program.\n\n");
        exit(0);
    }

    printf("Enter the new unit type (F, C, or K): ");
    scanf(" %c", &final_temp_unit);
    printf("\n");

    // Converting from C to final temp unit
    if (final_temp_unit == 'F' || final_temp_unit == 'f') {
        final_temp = (placeholder_temp * (9.0 / 5.0)) + 32;
    }
    else if (final_temp_unit == 'C' || final_temp_unit == 'c') {
        final_temp = placeholder_temp;
    }
    else if (final_temp_unit == 'K' || final_temp_unit == 'k') {
        final_temp = placeholder_temp + 273.15;
    }
    else if (!isValidFormat(1, 1)) {
        printf("Invalid formatting. Ending program.\n\n");
        exit(0);
    }
    else {
        printf("%c is not a valid temperature type. Ending program.\n\n", toupper(final_temp_unit));
        exit(0);
    }

    printf("%.2lf%c is %.2lf%c\n\n", init_temp, toupper(init_temp_unit), final_temp, toupper(final_temp_unit));
 }
    
/* This function converts the distance type the user enters
to a common distance type (i.e. Y) and then converts that
distance type to the one the user desires. This function also
exits the entire program if the user's input is an invalid
distance type or is formatted incorrectly.
@param: N/A
@return: N/A */
void convert_to_Common_Dist_then_Final_Dist() {
    double init_dist, final_dist, placeholder_dist;
    char init_dist_unit, final_dist_unit;
    
    printf("Enter the distance followed by its suffix (I,F,Y,M): ");
    scanf("%lf %c", &init_dist, &init_dist_unit);
    printf("\n");

    placeholder_dist = init_dist; // Converting from initial dist unit to Y

    if (init_dist_unit == 'I' || init_dist_unit == 'i') {
        placeholder_dist = init_dist / 36;
    }
    else if (init_dist_unit == 'F' || init_dist_unit == 'f') {
        placeholder_dist = init_dist / 3;
    }
    else if (init_dist_unit == 'M' || init_dist_unit == 'm') {
        placeholder_dist = init_dist * 1760;
    }
    else if (init_dist_unit != 'Y' && init_dist_unit != 'y') {
        printf("%c is not a valid distance type. Ending program.\n\n", toupper(init_dist_unit));
        exit(0);
    }
    else if (!isValidFormat(1, 1)) {
        printf("Invalid formatting. Ending program.\n\n");
        exit(0);
    }

    printf("Enter the new unit type (I,F,Y,M): ");
    scanf(" %c", &final_dist_unit);
    printf("\n");

    // Converting from Y to final dist unit
    if (final_dist_unit == 'I' || final_dist_unit == 'i') {
        final_dist = placeholder_dist * 36;
    }
    else if (final_dist_unit == 'F' || final_dist_unit == 'f') {
        final_dist = placeholder_dist * 3;
    }
    else if (final_dist_unit == 'Y' || final_dist_unit == 'y') {
        final_dist = placeholder_dist;
    }
    else if (final_dist_unit == 'M' || final_dist_unit == 'm') {
        final_dist = placeholder_dist / 1760;
    }
    else if (!isValidFormat(1, 1)) {
        printf("Invalid formatting. Ending program.\n\n");
        exit(0);
    }
    else {
        printf("%c is not a valid distance type. Ending program.\n\n", toupper(final_dist_unit));
        exit(0);
    }

    printf("%.2lf%c is %.2lf%c\n\n", init_dist, toupper(init_dist_unit), final_dist, toupper(final_dist_unit));
}

/* This function assesses whether or not the user's input is formatted
correctly, specifically making sure that the number of arguments the
user inputs is equivalent to the number of arguments required by the
program
@param: const int numArgsRead = the number of inputs the user enters
@param: const int numArgsNeed = the number of inputs required by the program
@return: formatIsGood = can either be true or false, depending on whether or
or not the number of inputs the user enters equals the number of inputs
required by the program */
bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
    bool formatIsGood = numArgsRead == numArgsNeed;
    char character;
    
    do{ 
        scanf ("%c", &character); //45  bob  \n
		    if(!isspace(character)) { //found a non whitespace character on the way to the end of the line
			formatIsGood = false;
		}
	} while(character != '\n'); //read characters until the end of the line
  
  return formatIsGood;
}
