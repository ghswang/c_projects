/*
This program determines whether or not
the user should choose to pay off all
their loans first and then invest or
pay off their loans and invest at the
same time until retirement
*/

#include <stdio.h>
#include <stdbool.h>

double Calc_Money_Loan_Investment_Together(double annual_loan_interest, double annual_ROR, double loan_amount, int curr_age, int retirement_age, double min_monthly_loan_payment, double total_monthly_money);
double Calc_Money_Loan_First(double annual_loan_interest, double annual_ROR, double loan_amount, int curr_age, int retirement_age, double total_monthly_money);
bool isMoneyLoanInvestmentTogether(double annual_loan_interest, double annual_ROR, double loan_amount, int curr_age, int retirement_age, double min_monthly_loan_payment, double total_monthly_money);
void Print_Outcome(bool decision, double annual_loan_interest, double annual_ROR, double loan_amount, int curr_age, int retirement_age, double min_monthly_loan_payment, double total_monthly_money);

/*
This function tells the user they should either pay off their
loans and invest at the same time or pay off their loans first
and then invest until retirement based on which method nets the
user the most amount of money
@bool decision: bool value of true if the user should pay off their loans and invest at the same time and if otherwise, bool value of false
@double annual_loan_interest: yearly loan interest rate
@double annual_ROR: yearly rate of return on investment
@double loan_amount: starting loan cost
@int curr_age: current age of user
@int retirement_age: age the user plans to retire at
@double min_monthly_loan_payment: the minimum monthly payments for the loan
@double total_monthly_money: max amount of monthly money for loans/investment
@return: N/A
*/
void Print_Outcome(bool decision, double annual_loan_interest, double annual_ROR, double loan_amount, int curr_age, int retirement_age, double min_monthly_loan_payment, double total_monthly_money) {
    if (decision) {
        printf("You should only make the minimum payments on your loan and apply the rest towards retirement.\n\n");
        printf("If you do you will have $%.2lf when you retire as opposed to ", Calc_Money_Loan_Investment_Together(annual_loan_interest, annual_ROR, loan_amount, curr_age, retirement_age, min_monthly_loan_payment, total_monthly_money)); 
        printf("$%.2lf if you paid off your loan before investing.\n\n", Calc_Money_Loan_First(annual_loan_interest, annual_ROR, loan_amount, curr_age, retirement_age, total_monthly_money));
    }
    else {
        printf("You should apply all $%.2lf towards your loan before making any investments.\n\n", total_monthly_money);
        printf("If you do you will have $%.2lf when you retire as opposed to ", Calc_Money_Loan_First(annual_loan_interest, annual_ROR, loan_amount, curr_age, retirement_age, total_monthly_money));
        printf("$%.2lf if you only made minimum payments.\n\n", Calc_Money_Loan_Investment_Together(annual_loan_interest, annual_ROR, loan_amount, curr_age, retirement_age, min_monthly_loan_payment, total_monthly_money));
    }
}

/*
This function determines whether or not the user should
pay off their loans and invest at the same time until
retirement
@double annual_loan_interest: yearly loan interest rate
@double annual_ROR: yearly rate of return on investment
@double loan_amount: starting loan cost
@int curr_age: current age of user
@int retirement_age: age the user plans to retire at
@double min_monthly_loan_payment: the minimum monthly payments for the loan
@double total_monthly_money: max amount of monthly money for loans/investment
@return: bool value of true if the user should pay off their loans and invest at the same time and if otherwise, bool value of false
*/
bool isMoneyLoanInvestmentTogether(double annual_loan_interest, double annual_ROR, double loan_amount, int curr_age, int retirement_age, double min_monthly_loan_payment, double total_monthly_money) {
    bool is_money_loan_investment_together = false;
    
    if (Calc_Money_Loan_Investment_Together(annual_loan_interest, annual_ROR, loan_amount, curr_age, retirement_age, min_monthly_loan_payment, total_monthly_money) - Calc_Money_Loan_First(annual_loan_interest, annual_ROR, loan_amount, curr_age, retirement_age, total_monthly_money) >= 0) {
        is_money_loan_investment_together = true;
    }
   
   return is_money_loan_investment_together;
}

/*
This function calculates the total money
earned if the user chooses to pay off their
loans first and then invest until retirement
@double annual_loan_interest: yearly loan interest rate
@double annual_ROR: yearly rate of return on investment
@double loan_amount: starting loan cost
@int curr_age: current age of user
@int retirement_age: age the user plans to retire at
@double total_monthly_money: max amount of monthly money for loans/investment
@return: the total money earned starting from current age until retirement age
*/
double Calc_Money_Loan_First(double annual_loan_interest, double annual_ROR, double loan_amount, int curr_age, int retirement_age, double total_monthly_money) {
    double monthly_loan_interest = annual_loan_interest / 12;
    double monthly_ROR = annual_ROR / 12;
    int num_month_until_retire = (retirement_age - curr_age) * 12;   
    int running_month = 1;
    double running_investment_total = 0;

    while (running_month <= num_month_until_retire) {
        loan_amount += loan_amount * monthly_loan_interest;

        if (total_monthly_money > loan_amount) {
           running_investment_total += running_investment_total * monthly_ROR;
           running_investment_total += (total_monthly_money - loan_amount);
           loan_amount = 0; 
        }
        
        else if (total_monthly_money <= loan_amount) {
            loan_amount -= total_monthly_money;
        }    

        ++running_month;
    }

    if (loan_amount > 0) {
        running_investment_total -= loan_amount;
    }

    return running_investment_total;
}

/*
This function calculates the total money
earned if the user chooses to pay off their
loans and invest at the same time until
retirement
@double annual_loan_interest: yearly loan interest rate
@double annual_ROR: yearly rate of return on investment
@double loan_amount: starting loan cost
@int curr_age: current age of user
@int retirement_age: age the user plans to retire at
@double min_monthly_loan_payment: the minimum monthly payments for the loan
@double total_monthly_money: max amount of monthly money for loans/investment
@return: the total money earned starting from current age until retirement age
*/
double Calc_Money_Loan_Investment_Together(double annual_loan_interest, double annual_ROR, double loan_amount, int curr_age, int retirement_age, double min_monthly_loan_payment, double total_monthly_money) {
    double monthly_loan_interest = annual_loan_interest / 12;
    double monthly_ROR = annual_ROR / 12;
    int num_month_until_retire = (retirement_age - curr_age) * 12;
    int running_month = 1;
    double running_investment_total = 0;

    while (running_month <= num_month_until_retire) {
        loan_amount += loan_amount * monthly_loan_interest;

        if (min_monthly_loan_payment > loan_amount) {
           running_investment_total += running_investment_total * monthly_ROR;
           running_investment_total += (total_monthly_money - loan_amount);
           loan_amount = 0;
        }

        else if (min_monthly_loan_payment <= loan_amount) {
            loan_amount -= min_monthly_loan_payment;
            running_investment_total += running_investment_total * monthly_ROR;
            running_investment_total += (total_monthly_money - min_monthly_loan_payment);
        }

        ++running_month;
    }

    if (loan_amount > 0) {
        running_investment_total -= loan_amount;
    }

    return running_investment_total;
}

int main(void) {
    int currAge, retirementAge;
    double loanAmount, annualLoanInterest, minMonthlyLoanPayment, totalMonthlyMoney, annualROR;

    do {
    printf("Enter how much you owe in loans: ");
    scanf("%lf", &loanAmount);
    printf("\n");
    } while (loanAmount < 0);

    do {
    printf("Enter the annual interest rate of the loans: ");
    scanf("%lf", &annualLoanInterest);
    printf("\n");
    } while (annualLoanInterest < 0);

    do {
    printf("Enter your minimum monthly loan payment: ");
    scanf("%lf", &minMonthlyLoanPayment);
    printf("\n");
    } while (minMonthlyLoanPayment < 0);

    do {
    printf("Enter how much money you will be putting towards loans/retirement each month: ");
    scanf("%lf", &totalMonthlyMoney);
    printf("\n");
    } while (totalMonthlyMoney < minMonthlyLoanPayment);

    do {
    printf("Enter your current age: ");
    scanf("%d", &currAge);
    printf("\n");
    } while (currAge < 0);

    do {
    printf("Enter the age you plan to retire at: ");
    scanf("%d", &retirementAge);
    printf("\n");
    } while (retirementAge < currAge);

    do {
    printf("Enter your predicted annual rate of return: ");
    scanf("%lf", &annualROR);
    printf("\n");
    } while (annualROR < 0);

    Print_Outcome(isMoneyLoanInvestmentTogether(annualLoanInterest, annualROR, loanAmount, currAge, retirementAge, minMonthlyLoanPayment, totalMonthlyMoney), annualLoanInterest, annualROR, loanAmount, currAge, retirementAge, minMonthlyLoanPayment, totalMonthlyMoney);

    return 0;
}
