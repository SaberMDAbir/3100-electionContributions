//MD Abir A. Choudhury
//CIS 3100 - Assignment 9
//Election Contributions

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

//function protocols
void displayMessage();
void readFile(Donation donors[], int count);
void writeFile(Donation donors[], int count);
void addNewContribution(Donation donors[], int &count, int &countAnders, int &countValerie, double &totalAnders, double &totalValerie);
void reportPerCandidate(Donation donors[], int count, int countAnders, int countValerie, double totalAnders, double totalValerie);

//class defintions
class Donation {
public: 
	//Data Members
	string name; //holds the last name of the people who contribute
	double amount; //holds the amount contributed by the donars
	string candidate; //holds the name of the candidate the donar is voting for

	//Member Functions
};

int main() {
	//variable definitions
	int choice = 0;//holds the user choice in the list
	const int SIZE = 1000; //program supports up to 1000 donations
	Donation donors[SIZE];
	int count = 0;
	int countAnders = 0;
	int countValerie = 0;
	double totalAnders = 0;
	double totalValerie = 0;

	readFile(&donors, count);

	do {
		displayMessage();
		cin >> choice;
		if (choice == 1) {
			addNewContribution(&donors, count, countAnders, countValerie, totalAnders, totalValerie);
		}
		else if (choice == 2) {
			reportPerCandidate(&donors, count, countAnders, countValerie, totalAnders, totalValerie);
		}
	} while (choice != 0);

	writeFile(&donors, count);

	system("PAUSE");
	return 0;
}

//function definitions
void displayMessage() {
	cout << "===========================\n"
		<< "Election Contributions v1.0\n"
		<< "     Anders vs. Valerie    \n"
		<< "===========================\n"
		<< "1 - Contribute to Campaign\n"
		<< "2 - Report per Candidate\n"
		<< "0 - Exit\n"
		<< "Choose one: ";
}
//displays the menu of choices
void readFile(Donation donors[],int count) {
	ifstream fileIn("ioFile.txt");
	if (!fileIn) {
		//error for not finding file
		cout << "File has failed to open.\n";
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
	while (!fileIn.eof()) {
		fileIn >> donors[count].name;
		fileIn >> donors[count].amount;
		fileIn >> donors[count].candidate;
		count++;
	}
	fileIn.close;
}
//loads the data from an existing file in to the array of donors
void writeFile(Donation donors[], int count) {
	ofstream fileOut("ioFile.txt");
	for (int i = 0; i < count; i++) {
		fileOut << donors[i].name << " " << donors[i].amount << " " << donors[i].candidate;
		if (i < count - 1) {
			fileOut << endl;
		}
	}
	fileOut.close();
}
//writes the data to an existing file from the array of donors
void addNewContribution(Donation donors[], int &count, int &countAnders, int &countValerie, double &totalAnders, double &totalValerie) {
	//get the total for each candidate
	for (int i = 0; i < count; i++) {
		while (donors[i].candidate == "Anders") {
			totalAnders += donors[i].amount;
		}
		while (donors[i].candidate == "Valerie") {
			totalValerie += donors[i].amount;
		}
	}
	cout << "What is your last name?\n";
	cin >> donors[count].name;

	//check the name whether the contribution is above 2700.
	for (int i = 0; i < count; i++) {
		double total = 0;
		if (donors[count].name == donors[i].name) {
			total += donors[i].amount;
		}
		if (total > 2700) {
			cout << "You are not allowed to donate more. Your contribution will not be accepted.\n";
			return;
		}
	}

	cout << "How much do you want to donate?\n";
	cin >> donors[count].amount;

	cout << "Which candidate are you donating to? (Anders OR Valerie)\n";
	cin >> donors[count].candidate;
	if (donors[count].candidate == "Anders") {
		countAnders++;
	}
	if (donors[count].candidate == "Valerie") {
		countValerie++;
	}

	count++;
}
//adds a new donation to the array
void reportPerCandidate(Donation donors[], int count, int countAnders, int countValerie, double totalAnders, double totalValerie) {
	
	double avg = 0;
	avg = totalAnders / countAnders;
	cout << "The number of contributions is: " << countAnders << endl;
	cout << "The total amount collected for Anders is: " << totalAnders << endl;
	cout << "The average amount collected for Anders is: " << avg << endl;

	avg = 0;
	avg = totalValerie / countValerie;
	cout << "The number of contributions is: " << countValerie << endl;
	cout << "The total amount collected for Valerie is: " << totalValerie << endl;
	cout << "The average amount collected for Valerie is: " << avg << endl;
}