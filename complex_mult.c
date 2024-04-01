/* This program calculates the product of two complex numbers 
both in the form ai + b where a is the imaginary part of the number,
b is the real part of the number, and i is the imaginary unit with
value of sqrt(-1). This program will display the final product in the
form ai + b as well. */

#include <stdio.h>

int main(void) {
    int a_first_complex;
    int a_second_complex;
    int b_first_complex;
    int b_second_complex;
    char imaginary_unit;
    char plus_sign;
    int num_imaginary_part;
    int num_real_part;
    
    printf("Enter the first complex number in the form ai + b: ");
    scanf("%d %c %c %d", &a_first_complex, &imaginary_unit, &plus_sign, &b_first_complex);
    printf("Enter the second complex number in the form ai + b: ");
    scanf("%d %c %c %d", &a_second_complex, &imaginary_unit, &plus_sign, &b_second_complex);

    num_imaginary_part = a_first_complex * b_second_complex + a_second_complex * b_first_complex;
    num_real_part = -1 * a_first_complex * a_second_complex + b_first_complex * b_second_complex;

    printf("(%d%c %c %d) * (%d%c %c %d) = ", a_first_complex, imaginary_unit, plus_sign, b_first_complex, a_second_complex, imaginary_unit, plus_sign, b_second_complex);
    printf("%d%c %c %d\n", num_imaginary_part, imaginary_unit, plus_sign, num_real_part);

    return 0;
}
