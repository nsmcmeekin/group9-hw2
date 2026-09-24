#include <iostream>


using namespace std;

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
	if (argc > 4) 
	{
		cout << "Too many arguments. Cannot pass in more than three." << endl;
		return -1;
	}

	int i = 1;
	double loan_amount, yearly_interest_rate, monthly_payment;

	double arguments [3];

	if (argc > 1)
	{
		while ( i < argc )
		{

			try
			{
				arguments[i-1] = stod(argv[i]);
			}
			catch(const std::invalid_argument&)
			{
				if(i==1)
					cout << "(Invalid loan amount): " << argv[i] << endl;
				else if (i==2)
					cout << "(Invalid interest rate): " << argv[i-1] << " " << argv[i] << endl;
				else
					cout << "(Invalid payment): " << argv[i-2] << " " << argv[i-1] << " " << argv[i] << endl;
				return -2;
			}
			i++;
		}
	}

	loan_amount = arguments[0];
	yearly_interest_rate = arguments[1];
	monthly_payment = arguments[2];
	cout << loan_amount << " " << yearly_interest_rate << " " << monthly_payment << endl;

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
