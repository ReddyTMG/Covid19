//include necessary library
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <conio.h>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <limits>
#include <vector>
using namespace std;

//Function prototype
void LoginMenu(void);
void Login(void);
void MenuUpdateStatus(string user_ID);
void DisplayCat(string user_ID);
void Register_User(void);

void UpdateStatus(string user_ID, int status, string VaccinationDoses);
int covidQuestions();
int categorise(int count);



// Function to validate if a string only contains digits
bool is_digit(string str)
{
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }

    return true;
}

// Function to validate user ID
bool is_valid_user_ID(string user_ID)
{
    for (char c : user_ID)
    {
        if (!isalnum(c))
        {
            return false;
        }
    }
    return true;
}

//Validation in display categorise
bool is_valid_confirm(string confirm)
{
    for (char c : confirm)
    {
        if (!isalnum(c))
        {
            return false;
        }
    }
    return true;
}

// Function to validate Covid-19 Status
bool is_valid_covid_status(string CovidStatus)
{
    for (char cs : CovidStatus)
    {
        if (cs == '1')
            return true;
        else if (cs == '2')
            return true;
        else if (cs == '3')
            return true;
        else if (cs == '4')
            return true;
        else
            return false;
    }
    return false;
}

// Function to validate Covid-19 Status
bool is_valid_vaccination_status(string VaccineDose)
{
    for (char vs : VaccineDose)
    {
        if (vs == '0')
            return true;
        else if (vs == '1')
            return true;
        else if (vs == '2')
            return true;
        else if (vs == '3')
            return true;
        else
            return false;
    }
    return false;
}

// Define a struct for user information
typedef struct {
    string name;
    string contact_num;
    string age;
    string home_address;
    string user_ID;
    string password;
    string CovidStatus;
    string VaccineDose;

}USER_DETAILS;

//main function
int main(void)
{
    LoginMenu();
    return 0;
}

//Ask the user to choose to login, register or exit
void LoginMenu(void)
{

    int choice;
    do
    {
        system("CLS");
        cout << "____________________________________________\n";
	    cout << "\tCOVID-19 MANAGEMENT SYSTEM\t\n";
	    cout << "============================================\n\n";
	
	    cout << "Please choose an option:\n";
	    cout << "<1> Login\n";
	    cout << "<2> Register\n";
	    cout << "<3> Exit\n";
	    
	    cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 3) {
            cin.clear();
            cin.ignore(1000, '\n');
            system("CLS");
            cout << "Invalid input, please enter a number between 1 and 3.\n";
        }
        else if (choice == 1)
            Login();
        else if (choice == 2)
            Register_User();
        else if (choice == 3)
        {
            //Display Thank you message.
        	system("CLS");
        	cout << "Thanks for using our Covid-19 Management System (>.<;)" << endl;
            choice = 3;
        }
        else
            cout << "\nInvalid number entered, please try again.\n";
    } while (choice != 3);
    fflush(stdin);
    return;
}

//Ask the user to input their phone number and password to login to our system
void Login(void)
{
    //Define local variables
    string user_phone, password;
    bool found = false;

    //Ask the user to login again if UserID and Password are incorrect.
    do
    {
        //Clear screen
		system("CLS");
        //Welcome user to the login system
        cout << "=========================================================" << endl;
	    cout << "|\tWelcome to our Covid-19 Management system >_<\t|" << endl;
	    cout << "=========================================================" << endl;

        //Ask the user to key in UserId and Password
        cout << "Please enter your Phone Number: ";
        cin >> user_phone;

        cout << "Please enter your Password  : ";
        cin >> password;


        //Read the content of UserData.txt file
        ifstream userdata_file("UserData.txt");

        //Test the file can open or not
        if (!userdata_file)
            cout << "Error opening file\n";
        else
        {
            string line;

            while (getline(userdata_file, line))
            {
                // find the position of the first comma
                size_t firstComma = line.find_first_of("*");
                // find the position of the second comma
                size_t secondComma = line.find_first_of("*", line.find_first_of("*") + 1);

                string id = line.substr(0, firstComma);
                // find the position of the third comma
                size_t thirdComma = line.find_first_of("*", secondComma + 1);
                // extract the substring between the second and third comma
                string pwd = line.substr(secondComma + 1, thirdComma - secondComma - 1);

                //Make sure the UserId and Password keyin by user is same in the UserData.txt file
                if (id == user_phone && pwd == password)
                {
                    found = true;
                    system("CLS");
                    cout << "User ID and Password match. " << endl;


                    int CovidStatusChoice;
                    do
                    {
                        system("CLS");

                        size_t firstComma = line.find_first_of("*");
                        size_t secondComma = line.find_first_of("*", firstComma + 1);
                        string name1 = line.substr(firstComma + 1, secondComma - firstComma - 1);

                        cout << "___________________________________________________\n";
					    cout << "\tWELCOME TO COVID-19 STATUS, " << name1 << "!\n";
					    cout << "===================================================\n\n";
					
					    cout << "Please choose an option:\n";
					    cout << "[1] Update my status\n";
					    cout << "[2] Show my latest status\n";
					    cout << "[3] Logout\n\n";
                        cout << "Enter: ";
                        cin >> CovidStatusChoice;
                        if (cin.fail() || CovidStatusChoice < 1 || CovidStatusChoice > 3) 
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            system("CLS");
                            cout << "Invalid input, please enter a number between 1 and 3.\n";
                        }
                        else if (CovidStatusChoice == 1)
                            MenuUpdateStatus(user_phone);
                        else if (CovidStatusChoice == 2)
                            DisplayCat(user_phone);
                        else if (CovidStatusChoice == 3)
                            CovidStatusChoice = 3;
                        else
                        {
                            system("CLS");
                            cout << "\nInvalid number entered, please try again.\n";
                        }

                    } while (CovidStatusChoice != 3);

                    break;

                }

            }
            //Close the file
            userdata_file.close();
            //flush any input button
            fflush(stdin);
            //Display an error message to ask the user relogin again.
            if (!found)

            {
                system("CLS");
                cout << "User ID and Password not match" << endl;
                cout << "Invalid login" << endl;
                cout << "Please enter a valid User ID and Password\n" << endl;
                cout << endl;
            }

        }
    } while (!found);


    return;
}

//Ask the user to input their NRIC, contact number, age, home addresses, covid-19 status and vaccination does(s)
void Register_User(void)
{
    // Open the data file for appending
    ofstream write_file("UserData.txt", ios::app);

    // Display user registration interface
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "\t\t\tHello New User!\n";
    cout << "\tPlease register to our application before you use it .\n";
    cout << "\t  Please provide us your information as shown below: \n";
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;

    // Read user information
    USER_DETAILS user;

    cout << "Name as per NRIC : ";
    cin.ignore();
    getline(cin, user.name);

    cout << "Contact Number (Digit Only) *Will be use for login : ";
    getline(cin, user.contact_num);
    //validate contact number contain only digits
    while (!is_digit(user.contact_num))
    {
        cout << "Sorry, Contact number must be digits only\n";
        cout << "Contact Number (Digit Only) : ";
        getline(cin, user.contact_num);
    }

    cout << "Age: ";
    cin >> user.age;
    //validate age contain only digit
    while (!is_digit(user.age))
    {
        cout << "Sorry, Age must be digits only\n";
        cout << endl;
        cout << "Age (Digit Only) : ";
        getline(cin, user.age);
    }
    cin.ignore(); // Ignore the newline character left by cin

    cout << endl;
    cout << "Home Address : \n";
    cout << "The address should follow the following format :\n";
    cout << "(NO 123, TAMAN TERUS, JALAN TUN HUSSIEN ONN, 97000, BINTULU, SARAWAK)\n";
    getline(cin, user.home_address);



    // Validate user information
    bool isValid = true;
    ifstream userdata_file("UserData.txt");
    string line;
    while (getline(userdata_file, line))
    {
        USER_DETAILS existingUser;
        istringstream lineStream(line);

        lineStream >> existingUser.contact_num >> existingUser.name >> existingUser.password >> existingUser.VaccineDose >> existingUser.age >> existingUser.home_address >> existingUser.user_ID >> existingUser.CovidStatus;
        if (user.contact_num == existingUser.contact_num)
        {
            system("CLS");
            isValid = false;
            cout << "Error: User already registered\n";
            break;
        }
    }

    userdata_file.close();

    // If user information is valid, write to file and display success message
    if (isValid)
    {
        // Read user ID and password
        cout << "|--------------------------------[*]----------------------------------|" << endl;
    	cout << "\nUser ID (As your Student/Staff ID) : ";
        getline(cin, user.user_ID);

        //Validate User ID contain digits and alphabets only
        while (!is_valid_user_ID(user.user_ID))
        {
            cout << "\nSorry, User ID must be digits and alphabets only\n";
            cout << "User ID : ";
            cin >> user.user_ID;
        }

        cout << "Password: ";
        getline(cin, user.password);

        while (user.password.find('*') != string::npos)
        {
            cout << "Sorry, password cannot contain asterisks. Please enter a new password: ";
            getline(cin, user.password);
        }

        cout << "\n[What is your Latest Covid-19 Status?]" <<endl;
        cout << "[1] Positive\n";
        cout << "[2] Close Contact\n";
        cout << "[3] Casual Contact\n";
        cout << "[4] Negative\n";
        cout << "Enter: ";
        getline(cin, user.CovidStatus);

        //Validate Covid-19 Status contain digits only
        while (!is_valid_covid_status(user.CovidStatus))
        {
            cout << "Sorry, Covid-19 Status must be digits only [1/2/3/4]\n";
            cout << "Covid-19 Status: ";
            cin >> user.CovidStatus;
        }

        cout << "How many Vaccination dose(s) you had?\n";
        cout << "[1] 0\n";
        cout << "[2] 1\n";
        cout << "[3] 2\n";
        cout << "[4] 3\n";
        cout << "Enter: ";
        getline(cin, user.VaccineDose);

        //Validate Covid-19 Status contain digits only
        while (!is_valid_covid_status(user.VaccineDose))
        {
            cout << "Sorry, Vaccination Status must be digits only <0/2/2/3>\n";
            cout << "Vaccination Status: ";
            cin >> user.VaccineDose;
        }

        ofstream userdata_file("UserData.txt", ios::app);
        if (!userdata_file)
        {
            cout << "Error: Cannot open file for writing.\n";
            return;
        }

        // Write the User Details to file
        userdata_file << user.contact_num << "*" << user.name << "*" << user.password << "*" << user.VaccineDose << "*" << user.age << "*" << user.home_address << "*" << user.user_ID << "*" << user.CovidStatus << endl;

        userdata_file.close();

        // Display a message to tell User Register successful
        system("CLS");
        cout << "Register Successfully.\n"
            << "Dear user(" << user.name << "),\n"
            << "Thank you for register to our Covid-19 Management System.\n"
            << "You can now proceed to login and Kindly update you Covid-19 Status.\n";
    }

}

//Ask the user to update their Covid-19 status and vaccination dose(s)
void MenuUpdateStatus(string user_ID)
{
    int count, status;
    char positive;
    string Vaccine;
    int VaccineDose=6;

    cout << "\nPlease Update Your Covid-19 Status" << endl;
    cout << "---------------------------------------------\n";

    do {
        cout << "Are you tested positive for covid-19? (y/n) :";
        cin >> positive;
        if (positive != 'y' && positive != 'Y' && positive != 'n' && positive != 'N') {
            cout << "Invalid input. Please enter y or n." << endl;
        }
    } while (positive != 'y' && positive != 'Y' && positive != 'n' && positive != 'N');

    if (positive != 'y' && positive != 'Y')
    {
        count = covidQuestions();
        status = categorise(count);
    }
    else
        status = 1;
    do
    {
        cout << "\nPlease enter your Vaccination does(s)\n" << endl;
    	cout << "---------------------------------------------\n";
        cout << "How many vaccination dose(s) you had? [0, 1, 2, 3, 4]";
        cout << "\nEnter: ";
        cin >> VaccineDose;
        if (VaccineDose > 4 || VaccineDose < 0)
        {
            system("CLS");
            cout << "Invalid number entered, please try again.\n";
        }
        else if (cin.fail())
        {
            system("CLS");
            cout << "No digit is entered, please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            VaccineDose = 6;
        }
    } while (VaccineDose > 4 || VaccineDose < 0);
    Vaccine = to_string(VaccineDose);


    UpdateStatus(user_ID, status, Vaccine);
}

//Ask the user to answer the Covid-19 question(s) to make sure the status of the user
int covidQuestions()
{
    int count = 0;
    char input;
    char questions[][200] = {
        "Are you experiencing more than one of the covid-19 symptoms such as fever, cough, fatigue, headache, sore throat and runny nose? (y/n) : ",
        "Have you joined any of the social events or gatherings within the past 7 days? (y/n) : ",
        "Have you been travelling for the past 14 days? (y/n) : ",
        "Have you recently had close contact with any known or suspected COVID-19 cases? (y/n) : "
    };

    for (int i = 0; i < 4; i++) {
        do {
        cout << questions[i];
        cin >> input;
            if (input != 'y' && input != 'Y' && input != 'n' && input != 'N') 
            {
                system("CLS");
                cout << "Invalid input. Please enter y or n." << endl;
            }
        } while (input != 'y' && input != 'Y' && input != 'n' && input != 'N');

        if (input == 'y' || input == 'Y') {
            count++;
        }
    }

    return count;
}

//Categorise the user upon their status
int categorise(int count)
{
    int status;
    if (count > 2)
        status = 2;
    else if (count >= 1)
        status = 3;
    else
        status = 4;
    return status;
}

// Function to edit the VaccinationDoses of the given phone number
void UpdateStatus(string user_ID, int status, string VaccineDose)
{
    // Open the file for reading
    ifstream userdata_file("UserData.txt");
    if (!userdata_file) 
    {
        cout << "Error: unable to open file." << endl;
        return;
    }

    // Store the lines in a vector
    vector<string> lines;
    string line;
    while (getline(userdata_file, line)) 
    {
        lines.push_back(line);
    }
    userdata_file.close();

    // Edit the line that matches the given phone number
    string covidStatus = to_string(status);
    bool found = false;
    for (size_t i = 0; i < lines.size(); i++) {
        string currentPhone;
        stringstream ss(lines[i]);
        getline(ss, currentPhone, '*');
        if (currentPhone == user_ID) {
            getline(ss, currentPhone, '*');
            getline(ss, currentPhone, '*');
            getline(ss, currentPhone, '*');
            getline(ss, currentPhone, '*');
            lines[i].replace(lines[i].find('*', lines[i].find('*', lines[i].find('*') + 1) + 1) + 1, 1, VaccineDose);
            size_t lastSlashPos = lines[i].find_last_of('*');
            lines[i].replace(lastSlashPos + 1, string::npos, covidStatus);
            found = true;
            break;
        }
    }

    // Write the modified lines back to the file
    if (found) {
        ofstream userdata_file("UserData.txt");
        if (!userdata_file) {
            cout << "Error: unable to open file." << endl;
            return;
        }
        for (size_t i = 0; i < lines.size(); i++) {
            userdata_file << lines[i] << endl;
        }
        userdata_file.close();
        cout << "Vaccination dose(s) for the User: <" << user_ID << "> has been updated to " << VaccineDose << endl;
        cout << "Covid-19 Status for User: <" << user_ID << "> has been updated to " << status << endl;
    }
    else {
        cout << "Phone number " << user_ID << " not found." << endl;
    }
}


//Display the category and the actions needed to be followed by the user
void DisplayCat(string user_ID)
{
    ifstream userdata_file("UserData.txt");
    if (!userdata_file)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    string row;
    while (getline(userdata_file, row))
    {
        size_t firstComma = row.find_first_of('*');
        size_t lastComma = row.find_last_of('*');
        string PhonePart = row.substr(0, firstComma);
        string categoryPart = row.substr(lastComma + 1);
        if (PhonePart == user_ID)
        {
            char categoryChar = categoryPart[0];
            string confirm;
            do
            {
                switch (categoryChar)
                {
                case '1':
                    cout << "Action need to be taken:\n" <<
                        "*************************************************************************************************\n";
                    cout << "*" << setw(3) << setw(97) << "*\n";
                    cout << "*" << setw(3) << " Category        : A (COVID - 19 Positive Cases)" << setw(49) << "*\n"
                        << "*" << setw(3) << " Quarantine Days : 7" << setw(77) << "*\n"
                        << "*" << setw(3) << " You can choose  : Hospital Quarantine or Home Surveillance Order(HSO)" << setw(27) << "*\n";
                    cout << "*" << setw(3) << setw(97) << "*\n"
                        << "*" << setw(3) << " However, you can be released earlier if they tested negative on Day 4." << setw(26) << "*\n"
                        << "*" << setw(3) << " The Covid - 19 test on Day 4 of quarantine needs to be supervised by medical practitioner." << setw(6) << "*\n"
                        << "*" << setw(3) << " Remember immediate report to your supervisor/respective lecturer and" << setw(28) << "*\n"
                        << "*" << setw(3) << " report to Bilik Gerakan for close monitoring and sanitisation process." << setw(26) << "*\n";
                    cout << "*" << setw(3) << setw(97) << "*\n"
                        << "*************************************************************************************************" << endl;
                    break;
                case '2':
                    cout << "Action need to be taken:\n" <<
                        "*************************************************************************************************\n";
                    cout << "*" << setw(3) << setw(97) << "*\n"
                        << "*" << setw(3) << " Category        : B(Close contact with individuals from Category A)" << setw(29) << "*\n"
                        << "*" << setw(3) << " Quarantine Days : No quarantine / 3 Days" << setw(56) << "*\n"
                        << "*" << setw(3) << " You can choose  : Home Surveillance Order(HSO)" << setw(50) << "*\n"
                        << "*" << setw(3) << setw(97) << "*\n"
                        << "*" << setw(3) << " Allowed to work/study as usual and access campus when the RTK(AG) self-test results" << setw(13) << "*\n"
                        << "*" << setw(3) << " on the 3rd day were negative and no symptoms or improved." << setw(39) << "*\n"
                        << "*" << setw(3) << " Three days of self-isolation is only applicable for close contact under symptomatic or" << setw(10) << "*\n"
                        << "*" << setw(3) << " asymptomatic." << setw(83) << " *\n"
                        << "*" << setw(3) << " (only to those staying with tested positive Covid - 19 family members and roommates)" << setw(12) << "*\n"
                        << "*" << setw(3) << " You may refer to a doctor if you continue to have symptoms" << setw(38) << "*\n"
                        << "*" << setw(3) << " end the RTK(AG) self-test result on the 3rd day is negative." << setw(36) << "*\n"
                        << "*" << setw(3) << " Remember immediate report to your supervisor/respective lecturer and" << setw(28) << "*\n"
                        << "*" << setw(3) << " report to Bilik Gerakan for close monitoring and sanitisation process." << setw(26) << "*\n"
                        << "*" << setw(3) << setw(97) << "*\n"
                        << "*************************************************************************************************" << endl;
                    break;
                case '3':
                    cout << "Action need to be taken:\n" << "*************************************************************************************************\n"
                        << "*" << setw(3) << setw(97) << "*\n"
                        << "*" << setw(3) << " Catagory        : C (Casual Contact)" << setw(60) << "*\n"
                        << "*" << setw(3) << " Quarantine Days : No quarantine" << setw(65) << "*\n"
                        << "*" << setw(3) << setw(97) << "*\n"
                        << "*" << setw(3) << " You are under monitoring list." << setw(66) << "*\n"
                        << "*" << setw(3) << " If Casual Contact Symptomatic: Allowed access on campus if Covid-19 test result is negative." << setw(4) << "*\n"
                        << "*" << setw(3) << " If Casual Contact No Symptoms: Allowed access campus in accordance with UTAR SOPs/procedures." << setw(3) << "*\n"
                        << "*" << setw(3) << setw(97) << "*\n"
                        << "*************************************************************************************************" << endl;
                    break;
                default:
                    cout << "Action need to be taken:\n" << "*************************************************************************************************\n"
                        << "*" << setw(3) << setw(97) << "*\n"
                        << "*" << setw(3) << " Category: D (Classification in MySejahtera)" << setw(53) << "*\n"
                        << "*" << setw(3) << setw(97) << "*\n"
                        << "*************************************************************************************************\n"
                        << "*" << setw(3) << "                            Classification in MySejahtera" << setw(40) << "*\n"
                        << "*************************************************************************************************\n"
                        << "*" << setw(3) << setw(97) << "*\n"
                        << "*" << setw(3) << " Classification That Allow access on Campus" << setw(54) << "*\n"
                        << "*" << setw(3) << " 1. Risiko Rendah / Low Risk - Individuals with low risk of Covid-19 infection." << setw(18) << "*\n"
                        << "*" << setw(3) << setw(97) << "*\n"
                        << "*" << setw(3) << " Classification That Not Allow access on Campus & Need self-isolate / Hospitalised by KKM." << setw(7) << "*\n"
                        << "*" << setw(3) << " 2. Kontak Rapat / Close Contact - Individuals who have been exposed to other individuals" << setw(8) << "*\n"
                        << "*" << setw(3) << "                                   infected with COVID-19." << setw(39) << "*\n"
                        << "*" << setw(3) << setw(97) << "*\n"
                        << "*" << setw(3) << " 3. Individual dalam Pemantauan /" << setw(64) << "*\n"
                        << "*" << setw(3) << "   Person Under Surveillance(PUS)- Individuals who are at risk of being infected with COVID-19.* \n"
                        << "*" << setw(3) << "                                   For example, individuals with a history of traveling abroad " << setw(1) << "*\n"
                        << "*" << setw(3) << "                                   within the last 14 days." << setw(38) << "*\n"
                        << "*" << setw(3) << setw(97) << "*\n"
                        << "*" << setw(3) << " 4. Kes Suspek / Suspected Case  - Individuals who are at risk of being infected with COVID-19.*\n"
                        << "*" << setw(3) << "                                   For example, individuals with a history of traveling abroad " << setw(1) << "*\n"
                        << "*" << setw(3) << "                                   or have attended mass gatherings within 14 days before the  " << setw(1) << "*\n"
                        << "*" << setw(3) << "                                   onset of symptoms." << setw(44) << "*\n"
                        << "*" << setw(3) << setw(97) << "*\n"
                        << "*" << setw(3) << " 5. Kes Yang Disahkah -Bergejala/" << setw(64) << "*\n"
                        << "*" << setw(3) << "    Confirmed case -Symptomatic  - Individuals tested positive for COVID-19." << setw(21) << "*\n"
                        << "*************************************************************************************************" << endl;
                    break;
                }
                cout << "Press any character(s) or number(s) to exit the Result: ";
                cin >> confirm;

            } while (!is_valid_confirm(confirm));
            fflush(stdin);
            return;
        }
    }

    cout << "No record found for " << user_ID << endl;
    userdata_file.close();
    fflush(stdin);
    return;
}