/* This program determines the least amount of bills needed to be
withdrawn for a certain amount of money */

#include <stdio.h>

const int HUNDREDS = 100, FIFTYS = 50, TWENTYS = 20, TENS = 10, FIVES = 5, ONES = 1;
int moneyAmount;

int FewestBillsCalc(int money, int bill_value);
int RemainingMoneyCalc(int money, int bill_value);

int main() {
    printf("Please enter the amount of money you wish to withdraw: ");
    scanf("%d", &moneyAmount);

    printf("You received %d hundred(s)\n", FewestBillsCalc(moneyAmount, HUNDREDS));
    moneyAmount = RemainingMoneyCalc(moneyAmount, HUNDREDS);
    printf("You received %d fifty(s)\n", FewestBillsCalc(moneyAmount, FIFTYS));
    moneyAmount = RemainingMoneyCalc(moneyAmount, FIFTYS);
    printf("You received %d twenty(s)\n", FewestBillsCalc(moneyAmount, TWENTYS));
    moneyAmount = RemainingMoneyCalc(moneyAmount, TWENTYS);       
    printf("You received %d ten(s)\n", FewestBillsCalc(moneyAmount, TENS));
    moneyAmount = RemainingMoneyCalc(moneyAmount, TENS);
    printf("You received %d five(s)\n", FewestBillsCalc(moneyAmount, FIVES));
    moneyAmount = RemainingMoneyCalc(moneyAmount, FIVES);
    printf("You received %d one(s)\n", FewestBillsCalc(moneyAmount, ONES));
    moneyAmount = RemainingMoneyCalc(moneyAmount, ONES);

    return 0;
}

/* This function determines how many bills to
give the user for a certain bill denomination */
int FewestBillsCalc(int money, int bill_value) {
    int numBills;
    
    numBills = money / bill_value;

    return numBills;
}

/* This function determines how much remaining money
there is left to withdraw after fully considering a
certain bill denomination*/
int RemainingMoneyCalc(int money, int bill_value) {
    int remainingMoney;
    
    remainingMoney = money % bill_value;

    return remainingMoney;
}
