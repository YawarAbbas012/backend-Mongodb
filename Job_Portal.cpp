#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<cctype> 
#include<iomanip>
#include<conio.h>
using namespace std;

class User {
	protected:
		string name;
		string password;

	public:
		User() {}

		User(string name, string password) {
			this->name = name;
			this->password = password;
		}

		string getName()  {
			return name;
		}

		string getPassword()  {
			return password;
		}

		void signUp(string name, string password) {
			this->name = name;
			this->password = password;
            
			//ofstream--> write data in file ^ios::app for keeps previous file data
			ofstream file("users.txt", ios::app);
			if (!file) {
				cout << "Error opening file!" << endl;
				return;
			}

			file << name << "," << password << endl;
			file.close();
			cout << "Your account has been created successfully!" << endl;
		}

		bool login(string name, string password) {
			this->name = name;
			this->password = password;
			
			//ofstream--> read data from file
			ifstream file("users.txt");
			string line;
			while (getline(file, line)) {
				size_t pos = line.find(",");
				string storedName = line.substr(0, pos);
				string storedPassword = line.substr(pos + 1);

				if (name == storedName && password == storedPassword) {
					file.close();
					return true;
				}
			}

			file.close();
			cout << "Account not found against this Username and Password!" << endl;
			return false;
		}
};

class Job_applicant : public User {
	private:
		string fatherName;
		int age;
		char gender;
		string cnic;
		string phoneNumber;
		string email;
		int matricObtainedMarks;
		int intermediateObtainedMarks;
		string bachelorSubject;
		float bachelorCGPA;

	public:
		Job_applicant() {}

		Job_applicant(string name, string password, string fatherName = "", int age = 0, char gender = '\0',
		              string cnic = "", string phoneNumber = "", string email = "", string jobSubject = "",
		              int matricObtainedMarks = 0,int intermediateObtainedMarks = 0,
		              string bachelorSubject = "", float bachelorCGPA = 0.0)	: User(name, password) {
			this->fatherName = fatherName;
			this->age = age;
			this->gender = gender;
			this->cnic = cnic;
			this->phoneNumber = phoneNumber;
			this->email = email;
			this->matricObtainedMarks = matricObtainedMarks;
			this->intermediateObtainedMarks = intermediateObtainedMarks;
			this->bachelorSubject = bachelorSubject;
			this->bachelorCGPA = bachelorCGPA;
		}

		string getFatherName()  {
			return fatherName;
		}

		int getAge()  {
			return age;
		}

		char getGender()  {
			return gender;
		}

		string getCNIC() {
			return cnic;
		}

		string getPhoneNumber()  {
			return phoneNumber;
		}

		string getEmail()  {
			return email;
		}

		int getMatricObtainedMarks()  {
			return matricObtainedMarks;
		}

		int getIntermediateObtainedMarks()  {
			return intermediateObtainedMarks;
		}

		string getBachelorSubject()  {
			return bachelorSubject;
		}

		float getBachelorCGPA()  {
			return bachelorCGPA;
		}

		void enter_personal_information() {
			cout << "Enter Father's Name: ";
		//for removing buffer(otherwise it may skip steps) 
			cin.ignore();
			getline(cin, fatherName);
			while (!for_correct_names(fatherName)) {
				cout << "Name should  contains Alphabetic characters. "<<endl;
				cout<<"Please enter again: ";
				getline(cin, fatherName);
			}

			do {
				cout << "Enter Age: ";
				age=for_int_value(1,100);;

				if (age >30 || age <18) {
					cout << "Invalid input. Age should be between 18 and 30."<<endl;
				}
			} while (age >30 || age <18);

			do {
				cout << "Enter Gender (M/f): ";
				cin >> gender;
				gender=tolower(gender);

				if (gender != 'f' && gender != 'm') {
					cout << "Invalid input. Please try again." << endl;
				}
			} while (gender != 'f' && gender != 'm');
			cout << "Enter CNIC: ";
			cin>>cnic;
			
			//Algorithm header file used here
			while(cnic.length()!=13||!all_of(cnic.begin(),cnic.end(),::isdigit)) {
				cout<<"Invalid CNIC.The CNIC should be of 13 digits and contains only number. "<<endl;
				cout << "Enter CNIC : ";
				cin >> cnic;
			}

			cout << "Enter Phone Number: ";
			cin>>phoneNumber;
			while(phoneNumber.length()!=11||!all_of(phoneNumber.begin(),phoneNumber.end(),::isdigit)) {
				cout<<"Invalid Number.The number should be of 11 digits and contains only number. "<<endl;
				cout << "Enter Phone Number: ";
				cin >> phoneNumber;
			}

			cout << "Enter Email: ";
			
			//to remove input buffers
			cin.clear();
			cin.ignore();
			getline(cin, email);
		}


		void enter_educational_information() {
			cout<<"Enter the obtained marks out of 1100\n";

			cout << "Enter Matric Obtained Marks: ";
			matricObtainedMarks=for_int_value(0,1100);;

			cout<<"Enter the obtained marks out of 1100\n";
			cout << "Enter Intermediate Obtained Marks: ";
			intermediateObtainedMarks=for_int_value(0,1100);;

			cout << "Enter Bachelor Subject: ";
			cin.ignore();
			getline(cin, bachelorSubject);
			while (!for_correct_names(bachelorSubject)) {
				cout << "Subject should  contains Alphabetic characters. "<<endl;
				cout<<"Please enter again: ";
				getline(cin, bachelorSubject);
			}

			do {
				cout << "Enter Bachelor CGPA out of 4: ";
				cin >> bachelorCGPA;

				if (bachelorCGPA < 2.0 || bachelorCGPA > 4.0) {
					cout << "Invalid input. CGPA should be between 2 and 4." <<endl;
				}
			} while (bachelorCGPA < 2.0 || bachelorCGPA > 4.0);
		}


		void displayInformation() {
			cout<<"\n*******************\n";
			//flag to allign the information and flags are in--> iomanip
			cout<<left;
			cout<<setw(30)<<"Name: "<<name<<endl;
			cout<<setw(30)<<"Father's Name: "<<fatherName<<endl;
			cout<<setw(30)<<"Age: "<<age<<endl;
			cout<<setw(30)<<"Gender: "<<gender<<endl;
			cout<<setw(30)<<"CNIC: "<<cnic<<endl;
			cout<<setw(30)<<"Phone Number: " <<phoneNumber << std::endl;
			cout<<setw(30)<<"Email: " << email<<endl;
			cout<<setw(30)<<"Matric Total Marks: " << 1100<<endl;
			cout<<setw(30)<<"Matric Obtained Marks: " << matricObtainedMarks<<endl;
			cout<<setw(30)<<"Intermediate Total Marks: " << 1100<<endl;
			cout<<setw(30)<<"Intermediate Obtained Marks: " << intermediateObtainedMarks<<endl;
			cout<<setw(30)<<"Bachelor Subject: " << bachelorSubject<<endl;
			cout<<setw(30)<<"Bachelor CGPA: " << bachelorCGPA<<endl;
			cout<<"\n*******************\n";
		}

		void save_information() {
			ofstream file(name + ".txt", ios::out);
			if (!file) {
				cout << "Error opening file!" << endl;
				return;
			}

			file << "Name: " << name << endl;
			file << "Father's Name: " << fatherName << endl;
			file << "Age: " << age << endl;
			file << "Gender: " << gender << endl;
			file << "CNIC: " << cnic << endl;
			file << "Phone Number: " << phoneNumber << endl;
			file << "Email: " << email << endl;
			file << "Matric Total Marks: " << 1100 << endl;
			file << "Matric Obtained Marks: " << matricObtainedMarks << endl;
			file << "Intermediate Total Marks: " << 1100 << endl;
			file << "Intermediate Obtained Marks: " << intermediateObtainedMarks << endl;
			file << "Bachelor Subject: " << bachelorSubject << endl;
			file << "Bachelor CGPA: " << bachelorCGPA << endl;

			file.close();
		}


		bool applyForJob() {
			cout << "Available Jobs: " << endl;
			cout << "1.Lecturer" << endl;
			cout << "2.Punjab Police" << endl;
			cout << "3.IT Manager" << endl;

			cout << "Enter the Job number you want to apply for: ";
			int jobNumber=for_int_value(1,3);
			
			switch (jobNumber) {
				case 1: {
					cout << "You have selected Lecturer." << endl;

					//Lecturer--> 70%
					if (matricObtainedMarks >= 770 && intermediateObtainedMarks >= 770 && bachelorCGPA >= 3.0) {
						cout << "Congratulations! You are eligible to apply for Lecturer." << endl;

						ofstream file("Lecturer_applications.txt", ios::app);
						file << "candidate information for Job Lecturer:\n";
						file << "Matric Obtained Marks: " << matricObtainedMarks << "\n";
						file << "Intermediate Obtained Marks: " << intermediateObtainedMarks << "\n";
						file << "Bachelor CGPA: " << bachelorCGPA << "\n";
						file.close();

						return true;
					} else {
						cout << "You do not meet the criteria for Lecturer. Application not submitted." << endl;
						return false;
					}
					break;
				}
				case 2: {
					cout << "You have selected Punjab Police." << endl;
					
						//punjab Police--> 65%				
					if (matricObtainedMarks >= 715 && intermediateObtainedMarks >= 715 && bachelorCGPA >= 2.75) {
						cout << "Congratulations! You are eligible to apply for Punjab Police." << endl;
	
						ofstream file("Punjab Police_applications.txt", ios::app);
						file << "candidate information for Punjab Police:\n";
						file << "Matric Obtained Marks: " << matricObtainedMarks << "\n";
						file << "Intermediate Obtained Marks: " << intermediateObtainedMarks << "\n";
						file << "Bachelor CGPA: " << bachelorCGPA << "\n";
						// Add more relevant information
						file.close();
						return true;
					} else {
						cout << "You do not meet the criteria for Punjab Police. Application not submitted." << endl;
						return false;
					}
					break;
				}
				case 3: {
					cout << "You have selected IT Manager." << endl;
					
					//IT Manager--> 60%
					if (matricObtainedMarks >= 660 && intermediateObtainedMarks >= 660 && bachelorCGPA >= 2.5) {
						cout << "Congratulations! You are eligible to apply for IT Manager." << endl;
						ofstream file("IT Manager_applications.txt", ios::app);
						file << "candidate information for IT Manager:\n";
						file << "Matric Obtained Marks: " << matricObtainedMarks << "\n";
						file << "Intermediate Obtained Marks: " << intermediateObtainedMarks << "\n";
						file << "Bachelor CGPA: " << bachelorCGPA << "\n";
						file.close();
						return true;
					} else {
						cout << "You do not meet the criteria for IT Manager. Application not submitted." << endl;
						return false;
					}
					break;
				}
				default:
					cout << "Invalid job number. Application not submitted." << endl;
					return false;
			}
		}
		string getPassword() {
			string password;
			char ch;
			while (true) {
				ch = getch();  

				if (ch == '\r') {  // If the Enter key is pressed, break the loop
					cout << endl;
					break;
				} else if (ch == '\b') {  // If the Backspace key is pressed, remove the last character
					if (!password.empty()) {
						password.pop_back();
						cout << "\b \b";  // Erase the last asterisk or * and move the cursor back
					}
				} else {
					password.push_back(ch);
					cout << '*';  // Display an asterisk for each character
				}
			}
			return password;
		}

		bool for_correct_names(string& name) {
			bool foundAlpha = false;
			for (int i = 0; i < name.length(); i++) {
				char ch = name[i];
				if (isalpha(ch)) {
					foundAlpha = true;
				} else if (!isspace(ch) && foundAlpha) {
					return false;
				}
			}
			return foundAlpha;
		}
		int for_int_value(int min, int max) {
			int input;
			bool valid_input = false;
			while (!valid_input) {

				if (cin>>input) {
					if (input>=min&&input<= max) {
						valid_input = true;
					} else {
						cout << "Wrong Input.Please enter a valid number!"<<endl;
					}
				} else {
					cout << "Invalid input. Please enter a number." << endl;
					cin.clear();
					cin.ignore();
				}
			}
			return input;
		}
};

int main() {
	string username, password;
	Job_applicant candidate;
	bool isLoggedIn = false;

	while (true) {
		cout << "****** Main Menu ****** " << endl;
		cout << "1. Sign Up" << endl;
		cout << "2. Login" << endl;
		cout << "3. Show Data" << endl;
		cout << "4. Apply for a Job" << endl;
		cout << "5. Exit" << endl;
		cout << "Enter your choice: ";
		int choice=candidate.for_int_value(1,5);

		switch (choice) {
			case 1: {
				cout << "Sign Up" << endl;
				cout << "Enter Username: ";
				cin >> username;
				while (!candidate.for_correct_names(username)) {
					cout << "Name should  contains Alphabetic characters. "<<endl;
					cout<<"Please Enter again: ";
					cin>>username;
				}
				cout << "Enter Password: ";
				password=candidate.getPassword();
				candidate.signUp(username, password);
				cout << "Account created successfully!" << endl;
				break;
			}
			case 2: {
				cout << "Login" << endl;
				cout << "Enter Username: ";
				cin >> username;
				while (!candidate.for_correct_names(username)) {
					cout << "Name should  contains Alphabetic characters. "<<endl;
					cout<<"Please enter again: ";
					getline(cin, username);
				}
				cout << "Enter Password: ";
				password=candidate.getPassword();
				isLoggedIn = candidate.login(username, password);
				if (isLoggedIn) {
					cout << "Login successful!" << endl;
				} else {
					cout << "Invalid username or password." << endl;
				}
				if (isLoggedIn) {

					cout << "Enter Information" << endl;
					cout<<"\nEnter your Personal Information\n";
					candidate.enter_personal_information();
					cout<<endl;
					cout<<"\nEnter your Educational Information\n";
					candidate.enter_educational_information();
					cout<<endl;
					candidate.save_information();
					cout << "Information saved successfully!" << endl;
				} else {
					cout << "You must login first." << endl;
				}
				break;
			}
			case 3: {
				if (isLoggedIn) {
					cout << "Show Data" << endl;
					candidate.displayInformation();
				} else {
					cout << "You must login first." << endl;
				}
				break;
			}
			case 4: {
				if (isLoggedIn) {
					cout << "Apply for a Job" << endl;
					candidate.applyForJob();
					cout<<"Application Received - You will be notified via the provided email and phone number.";

				} else 
				{
					cout << "You must login first." << endl;
				}
				break;
			}
			case 5: {
				cout << "Exiting...\n";
				return 0;
			}
			default: {
				cout<<"Invalid input \n";
			}
		}
		cout << endl;
	}
	return 0;
}