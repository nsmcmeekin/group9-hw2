#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdlib>
#include <stdexcept>


using namespace std;

std::string const labels[3] = {"Invalid loan", "Invalid interest rate", "Invalid payment"};

void fail(int i, char* argv[]) {
	std::cout << "(" << labels[i-1] << "): ";
	for (int j = 1; j <= i; j++) {
		cout << argv[j];
		if (j < i) {
			cout << " ";
		}
	}
	cout << std::endl;
    exit(-2);
}

string const BANNER = "*****************************************************************";

void print_header() {
	std::cout << BANNER << "\n"
		<< "\tAmortization Table\n"
		<< BANNER << "\n"
		<< "Month\tBalance\t\tPayment\t\tRate\tInterest\tPrincipal\n";
}

void print_row0(double loan_amount) {
	std::cout << 0 << "\t$" << loan_amount;
	if (loan_amount < 1000) {
		std::cout << "\t";
	}
	std::cout << "\t" << "N/A\t\tN/A\tN/A\t\tN/A\n";
}

void print_row(int month, double balance, double payment, double rate, double interest, double principal) {
	std::cout << month << "\t"
		<< "$" << balance;
	if (balance < 1000) {
		std::cout << "\t";
	}
	std::cout << "\t";
	std::cout << "$" << payment;
	if (payment < 1000) {
		std::cout << "\t";
	}
	std::cout << "\t";
	std::cout << rate << "\t"
		<< "$" << interest << "\t\t"
		<< "$" << principal << "\n";
}

void print_footer(int months, double interest_total) {
	string m;
	if (months == 1) {
		m = "month";
	}
	else {
		m = "months";
	}
	std::cout << BANNER << "\n"
		<< "\nIt takes " << months << " " << m << " to pay off the loan.\n"
		<< "Total interest paid is: $" << interest_total
		<< "\n\n";
}

bool validLoan(double loan_amount, double monthlyInterestRate, double monthly_payment) {
	double interestPayment = loan_amount * monthlyInterestRate;

	if (monthly_payment <= interestPayment) {
		return false;
	}

	return true;
}

double calculatePayment (double loan_amount, double monthlyInterestRate, double monthly_payment) {
	double interestPayment = loan_amount * monthlyInterestRate;
	double principle = monthly_payment - interestPayment;

	return principle;
}

double calcFinalPayment (double loan_amount, double monthlyInterestRate) {
	double interestPayment = loan_amount * monthlyInterestRate;
	double finalPayment = loan_amount + interestPayment;

	return finalPayment;
}

//pass in space-delimited arguments when you call the executable
//Example: ./a.out 1 2 3.3
int main( int argc, char * argv[] )
{
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	double values[3] = {0.0, 0.0, 0.0};

	if (argc - 1 > 3) {
		std::cout << "Too many arguments" << std::endl;
		return -1;
	}

	for (int i = 1; i < argc; i++) {
		// Check 1 - is it a number?
		size_t pos = 0;
		double v = 0.0;
		string arg = argv[i];
		try {
			v = stod(arg, &pos);
		}
		catch (const invalid_argument&) {
			fail(i, argv);
		}
		catch (const out_of_range&) {
			fail(i, argv);
		}
		
		//Check 2 - did we consume the whole string?
		if (pos != arg.length()) {
			fail(i, argv);
		}
		
		//Check 3 - is it in range?
		if (i == 1 && v <= 0) {
			fail(i, argv);
		}
		else if (i == 2 && v < 0) {
			fail(i, argv);
		}
		else if (i == 3 && v <= 0) {
			fail(i, argv);
		}
		values[i-1] = v;
	}
	
	if (argc - 1 < 3) {
		std::cout << "Not Enough" << std::endl;
		return -1;
	}
	double loan_amount = values[0];
	double yearly_interest_rate = values[1];
	double monthly_payment = values[2];

	double principle, monthlyInterestRate, interestPayment, totalInterest;
    int month = 0;

	
    
    totalInterest = 0;
    

    monthlyInterestRate = yearly_interest_rate / 12;
    monthlyInterestRate /= 100;

	if (!validLoan(loan_amount, monthlyInterestRate, monthly_payment)) {
		cout << "Insufficient payment" << endl;
		return -1;
	}

    


    while (loan_amount > monthly_payment) { //while loop calculating payments month by month
        month++;
		principle = calculatePayment(loan_amount, monthlyInterestRate, monthly_payment);
		interestPayment = loan_amount * monthlyInterestRate;

		totalInterest += interestPayment;
		loan_amount -= principle;
        
		//format output
        
	}

	// final payment made
	month++;
    interestPayment = loan_amount * monthlyInterestRate; //calculate final payment
	double finalPayment = calcFinalPayment(loan_amount, monthlyInterestRate);

    totalInterest += interestPayment;
    principle = loan_amount;
    loan_amount = 0;
    
	//print final payment

	
	return 0;
}
