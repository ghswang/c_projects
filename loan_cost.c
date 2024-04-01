/* This program determines the amount of money someone pays back per month
when taking a loan. In addition, this program also calculates the total
cost of the loan */

#include <stdio.h>
#include <math.h>

int main(void) {
    double amount_money_borrowed;
    double annual_interest_rate;
    int numMonthlyPayments;
    double monthlyPayments;

    printf("Please enter the amount of money you borrowed: $");
    scanf("%lf", &amount_money_borrowed);
    printf("Please enter the annual interest rate: ");
    scanf("%lf", &annual_interest_rate);
    printf("Please enter the number of payments to be made: ");
    scanf("%d", &numMonthlyPayments);
    
    monthlyPayments = amount_money_borrowed * (annual_interest_rate / 12) / (1 - pow((1 + annual_interest_rate / 12), -numMonthlyPayments));

    printf("A loan of $%.2lf with an annual interest of %.2lf paid off over %d months will have monthly payments of $%.2lf.\n", amount_money_borrowed, annual_interest_rate, numMonthlyPayments, monthlyPayments);
    printf("In total, you will pay $%.2lf, making the cost of your loan $%.2lf.\n", monthlyPayments * numMonthlyPayments, monthlyPayments * numMonthlyPayments - amount_money_borrowed );

    return 0;
}
