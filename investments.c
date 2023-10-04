#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

bool isValidFormat(const int numArgsRead, const int numArgsNeed);
double getValidDouble1(const char* prompt);
void validpayments(double endmonthmoney, double minpayment);
int getValidInt1(const char* prompt);
int getValidInt2(const char* prompt, int currentage);
double minloanretirevalue(double loans, double monthlyinterest, double minpayment, double monthlyreturn, int monthsworking, double leftover);
double maxloanretirevalue(double loans, double monthlyinterest, double endmonthmoney, double monthlyreturn, int monthsworking);
double minloanretirevalue1(double loans, double monthlyinterest, double minpayment, double monthlyreturn, int monthsworking, double leftover);
double maxloanretirevalue1(double loans, double monthlyinterest, double endmonthmoney, double monthlyreturn, int monthsworking);
void loanremaining(double valueminloans1, double valuemaxloans1);
void finalstatement(double valueminloans, double valuemaxloans, double endmonthmoney);

int main() {
  double endmonthmoney = getValidDouble1("Enter how much money you will be putting towards loans/retirement each month: ");
  double loans = getValidDouble1("Enter how much you owe in loans: ");
  double monthlyinterest = (getValidDouble1("Enter the annual interest rate of the loans: ") / 12.0);
  double minpayment = getValidDouble1("Enter your minimum monthly loan payment: ");
  validpayments(endmonthmoney, minpayment);
  int currentage = getValidInt1("Enter your current age: ");
  int retireage = getValidInt2("Enter the age you plan to retire at: ", currentage);
  double monthlyreturn = (getValidDouble1("Enter the annual rate of return you predict for your investments: ") / 12.0);
  int monthsworking = ((retireage - currentage) * 12);
  double leftover = endmonthmoney - minpayment;
  double valueminloans = minloanretirevalue(loans, monthlyinterest, minpayment, monthlyreturn, monthsworking, leftover);
  double valuemaxloans = maxloanretirevalue(loans, monthlyinterest, endmonthmoney, monthlyreturn, monthsworking);
  double valueminloans1 = minloanretirevalue1(loans, monthlyinterest, minpayment, monthlyreturn, monthsworking, leftover);
  double valuemaxloans1 = maxloanretirevalue1(loans, monthlyinterest, endmonthmoney, monthlyreturn, monthsworking);
  loanremaining(valueminloans1, valuemaxloans1);
  finalstatement(valueminloans, valuemaxloans, endmonthmoney);
  return 0;
}


//taken from google drive
int getValidInt2(const char* prompt, int currentage) {
  int num;
  const int numArgsNeeded = 1;
  int numArgsRead;
  do{
    printf("%s", prompt);
    numArgsRead = scanf(" %d", &num); // waffles 45\n
  }while(!isValidFormat(numArgsRead, numArgsNeeded) || (num < currentage));

  return num;
}

//taken from google drive
int getValidInt1(const char* prompt){
  int num;
  const int numArgsNeeded = 1;
  int numArgsRead;
  do{
    printf("%s", prompt);
    numArgsRead = scanf(" %d", &num); // waffles 45\n
  }while(!isValidFormat(numArgsRead, numArgsNeeded) || (num < 0));

  return num;
}

//taken from google drive
bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
  bool formatIsGood = numArgsRead == numArgsNeed;
  char character;
  do{
    scanf("%c", &character); //45  bob  \n
		if(!isspace(character)){ //found a non whitespace character on the way to the end of the line
			formatIsGood = false;
		}
	}while(character != '\n'); //read characters until the end of the line
  return formatIsGood;
}



// partially taken from google drive
double getValidDouble1(const char* prompt){
  double num;
  const int numArgsNeeded = 1;
  int numArgsRead;
  do{
    printf("%s", prompt);
    numArgsRead = scanf(" %lf", &num); //waffles\n
  }while((!isValidFormat(numArgsRead, numArgsNeeded)) || (!(num >= 0)));

  return num;
}

void validpayments(double endmonthmoney, double minpayment) {
  if (endmonthmoney - minpayment < 0) {
    printf("You didn't set aside enough money to pay off our loans. Ending program.\n");
    exit(0);
  }
}

double minloanretirevalue(double loans, double monthlyinterest, double minpayment, double monthlyreturn, int monthsworking, double leftover){
  int i;
  double moneyinvested = 0;
  double value3;
  for (i=0;i < monthsworking; ++i) {
    if (loans > minpayment) {
      loans += (loans * monthlyinterest);
      loans -= minpayment;
      moneyinvested += (moneyinvested * monthlyreturn);
      moneyinvested += leftover;
      continue;
    } else if ((loans < minpayment) && (loans != 0)) {
      loans += (loans * monthlyinterest);
      value3 = minpayment - loans;
      loans = 0;
      moneyinvested += (moneyinvested * monthlyreturn);
      moneyinvested += (leftover + value3);
      continue;
    } else if (loans == 0) {
      moneyinvested += (moneyinvested * monthlyreturn);
      moneyinvested += (minpayment + leftover);
      continue;
    }
  }
  return moneyinvested;
}


double minloanretirevalue1(double loans, double monthlyinterest, double minpayment, double monthlyreturn, int monthsworking, double leftover){
  int i;
  double moneyinvested = 0;
  double value3;
  for (i=0;i < monthsworking; ++i) {
    if (loans > minpayment) {
      loans += (loans * monthlyinterest);
      loans -= minpayment;
      moneyinvested += (moneyinvested * monthlyreturn);
      moneyinvested += leftover;
      continue;
    } else if ((loans < minpayment) && (loans != 0)) {
      loans += (loans * monthlyinterest);
      value3 = minpayment - loans;
      loans = 0;
      moneyinvested += (moneyinvested * monthlyreturn);
      moneyinvested += (leftover + value3);
      continue;
    } else if (loans == 0) {
      moneyinvested += (moneyinvested * monthlyreturn);
      moneyinvested += (minpayment + leftover);
      continue;
    }
  }
  return loans;
}


double maxloanretirevalue(double loans, double monthlyinterest, double endmonthmoney, double monthlyreturn, int monthsworking) {
  int i;
  double moneyinvested = 0;
  double value3;
  for (i=0; i < monthsworking; ++i) {
    if (loans > endmonthmoney) {
      loans += (loans * monthlyinterest);
      loans -= endmonthmoney;
      continue;
    } else if ((loans < endmonthmoney) && (loans != 0)) {
      loans += (loans * monthlyinterest);
      value3 = (endmonthmoney - loans);
      loans = 0;
      moneyinvested += value3;
      continue;
    } else if (loans == 0) {
      moneyinvested += (moneyinvested * monthlyreturn);
      moneyinvested += endmonthmoney;
      continue;
    }
  }
  return moneyinvested;
}

double maxloanretirevalue1(double loans, double monthlyinterest, double endmonthmoney, double monthlyreturn, int monthsworking) {
  int i;
  double moneyinvested = 0;
  double value3;
  for (i=0; i<monthsworking; ++i) {
    if (loans > endmonthmoney) {
      loans += (loans * monthlyinterest);
      loans -= endmonthmoney;
      continue;
    } else if ((loans < endmonthmoney) && (loans != 0)) {
      loans += (loans * monthlyinterest);
      value3 = (endmonthmoney - loans);
      loans = 0;
      moneyinvested += value3;
      continue;
    } else if (loans == 0) {
      moneyinvested += (moneyinvested * monthlyreturn);
      moneyinvested += endmonthmoney;
      continue;
    }
  }
  return loans;
}

void loanremaining(double valueminloans1, double valuemaxloans1) {
  if ((valueminloans1 > 0) || (valuemaxloans1 > 0)) {
    if (valueminloans1 > valuemaxloans1) {
      printf("Warning! After you retire you will still have $%.2f in loans left.\n", valueminloans1);
    } else if (valuemaxloans1 > valueminloans1) {
      printf("Warning! After you retire you will still have $%.2f in loans left.\n", valuemaxloans1);
    }
  }
}

void finalstatement(double valueminloans, double valuemaxloans, double endmonthmoney) {
  if (valueminloans > valuemaxloans) {
    printf("You should only make the minimum payments on your loan and apply the rest towards retirement.\n");
    printf("If you do you will have $%.2f when you retire as opposed to $%.2f if you payed off your loan before investing.\n", valueminloans, valuemaxloans);
  } else if (valuemaxloans > valueminloans) {
    printf("You should apply all $%.2f towards your loan before making any investments.\n", endmonthmoney);
    printf("If you do you will have $%.2f when you retire as opposed to $%.2f if you only made minimum payments.\n", valuemaxloans, valueminloans);
  }
}
