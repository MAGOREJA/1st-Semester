#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <iomanip>
#include <cstdlib>

using namespace std;

string signIn(string name, string password, string users[], string passwords[], string roles[], int usersCount);
bool signUp(string name, string password, string role, string users[], string passwords[], string roles[], int &usersCount, int userArrSize);
void header();
void welcome();
void subMenuBeforeMainMenu(string submenu);
void subMenu(string submenu);
int loginMenu();
string getfield(string record, int field);
void savearrays(string customer_names[], long customer_cnic[], long customer_amount[], int &usersDetails);

string manager_menu();
void manager_tasks(string customer_names[], long customer_cnic[], long customer_amount[], string feedback[], int &countfeedback, string customer_email[], int &usersDetails, string cashier_names[], int cashier_hours[], string cashier_status[], int &cashier_count, long &total_money);
void customer_list(string customer_names[], long customer_cnic[], long customer_amount[], string customer_email[], int &usersDetails);
string cashier_hire(string cashier_names[], int cashier_hours[], string cashier_status[], int &cashier_count);
void cashier_list(string cashier_names[], int cashier_hours[], string cashier_status[], int &cashier_count);
bool add_cashier(string cashier_names[], int cashier_hours[], string cashier_status[], string name, int hours, int &cashier_count);
string veiwfeedback(string feedback[], int &countfeedback);
void totalReserves(long &total_money);
void sortingCustomerArray(long customer_amount[], int &usersDetails);
string cashier_tasks();
string open_account(string customer_names[], long customer_cnic[], long customer_amount[], string customer_email[], int &usersDetails);
bool checkAccount(string customer_names[], long customer_cnic[], long customer_amount[], string customer_email[], int &usersDetails, string name, string email, long cnic, float amount);
string close_account(string customer_names[], long customer_cnic[], long customer_amount[], string customer_email[], int &usersDetails);
bool check_forClose(string customer_names[], long customer_cnic[], long customer_amount[], string customer_email[], int &usersDetails, string name, string email, long cnic);
string cash_withdraw(string customer_names[], long customer_cnic[], long customer_amount[], int &usersDetails);
bool can_withdraw(string customer_names[], long customer_cnic[], long customer_amount[], int &usersDetails, string name, long cnic, float amount);
string cash_deposit(string customer_names[], long customer_cnic[], long customer_amount[], int &usersDetails);
bool can_deposit(string customer_names[], long customer_cnic[], long customer_amount[], int &usersDetails, string name, long cnic, float amount);
string loan(string customer_names[], long customer_cnic[], long customer_amount[], int &usersDetails);
bool loan_ok(string customer_names[], long customer_cnic[], long customer_amount[], int &usersDetails, string name, long cnic, float amount, float salary);
string givefeedback(string feedback[], int &countfeedback);
bool donatemoney(string customer_names[], long customer_cnic[], long customer_amount[], string &welfare, string customer_email[], int &usersDetails);
void exchangecurrency();
void cashier_Interface(string customer_names[], long customer_cnic[], string feedback[], string &welfare, int &countfeedback, long customer_amount[], string customer_email[], int &usersDetails);
void clearScreen();

void storeUserData(string users[], string passwords[], string roles[], int userArrSize);
void LoadUserData(string users[], string passwords[], string roles[], int &usersCount);
string parseData(int index, string line);
int convertStoInt(string num); // It validates if the required input are integers

bool containsOnlyIntegers(string integer);
bool containsOnlyAlphabets(string word); // It validates if the required input are alphabets

string setcolor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    return "";
}
int black = 0, blue = 1, green = 2, cyan = 3, red = 4, magenta = 5, brown = 6, lightwhite = 7, darkwhite = 8, lightblue = 9, lightgreen = 10, lightcyan = 11, lightred = 12, lightmagenta = 13, yellow = 14, white = 15;

main()
{
    const int userArrSize = 10;
    string users[userArrSize];
    string passwords[userArrSize];
    string roles[userArrSize];
    string customer_names[userArrSize];
    string cashier_names[userArrSize];
    long customer_cnic[userArrSize];
    long customer_amount[userArrSize];
    string customer_email[userArrSize];
    int cashier_hours[userArrSize];
    string feedback[userArrSize];
    string cashier_status[userArrSize];
    int usersCount = 0;
    int cashier_count = 3;
    int usersDetails = 0;
    int loginOption = 0;
    int countfeedback = 0;
    string welfare = "";
    long total_money = 106450230;
    LoadUserData(users, passwords, roles, usersCount);

    while (loginOption != 3)
    {
        system("cls");
        welcome();
        header();
        subMenuBeforeMainMenu("Login");
        loginOption = loginMenu();
        if (loginOption == 1)
        {
            system("cls");
            string name;
            string password;
            string role;
            welcome();
            header();
            subMenuBeforeMainMenu("SignIn");
            cout << "\tEnter your Name: \t";
            cin >> name;
            cout << "\tEnter your Password: \t";
            cin >> password;
            role = signIn(name, password, users, passwords, roles, usersCount);
            if (role == "Manager" || role == "manager")
            {
                cout << "You have successfully SignedIn" << endl;
                clearScreen();
                manager_tasks(customer_names, customer_cnic, customer_amount, feedback, countfeedback, customer_email, usersDetails, cashier_names, cashier_hours, cashier_status, cashier_count, total_money);
            }
            else if (role == "Cashier" || role == "cashier")
            {
                cout << "You have successfully SignedIn" << endl;
                clearScreen();
                cashier_Interface(customer_names, customer_cnic, feedback, welfare, countfeedback, customer_amount, customer_email, usersDetails);
            }
            else
            {
                cout << "You have Entered wrong Credentials" << endl;
            }
        }
        else if (loginOption == 2)
        {
            system("cls");
            string name;
            string password;
            string role;
            welcome();
            header();
            subMenuBeforeMainMenu("SignUp");
            cout << "\t*Username should not contain spaces*" << endl;
            cout << "\tEnter your Name: \t";
            cin >> name;
            cout << endl;
            cout << "\t*Password should not contain spaces*" << endl;
            cout << "\tEnter your Password: \t";
            cin >> password;
            cout << endl;
            cout << "\tEnter your Role (Manager or Cashier): \t";
            cin >> role;
            if (role == "manager" || role == "Manager" || role == "cashier" || role == "Cashier")
            {
                bool isValid = signUp(name, password, role, users, passwords, roles, usersCount, userArrSize);
                if (isValid)
                {
                    cout << "You have Successfully SignedUp." << endl;
                }
                if (!isValid)
                {
                    cout << "Signing Up Unsuccessful." << endl;
                }
            }
            else
            {
                cout << "Provide valid role." << endl;
            }
        }
        else if (loginOption != 1 && loginOption != 2)
        {
            storeUserData(users, passwords, roles, userArrSize);
        }
        else
        {
            break;
        }
        clearScreen();
    }
}

int loginMenu()
{
    int option;
    cout << "=> 1. \tSignIn with your Credentials" << endl;
    cout << "=> 2. \tSignUp to get your Credentials" << endl;
    cout << "=>    \tEnter any other Input to Exit the Application" << endl;
    cout << endl;
    cout << "\tEnter the Option Number > ";
    cin >> option;
    return option;
}

string signIn(string name, string password, string users[], string passwords[], string roles[], int usersCount)
{
    for (int index = 0; index < usersCount; index++)
    {
        if (users[index] == name && passwords[index] == password)
        {
            return roles[index];
        }
    }
    return "undefined";
}

bool signUp(string name, string password, string role, string users[], string passwords[], string roles[], int &usersCount, int userArrSize)
{
    bool isPresent = false;

    for (int index = 0; index < usersCount; index++)
    {
        if (users[index] == name && passwords[index] == password)
        {
            isPresent = true;
            break;
        }
    }
    if (isPresent == true)
    {
        return 0;
    }
    else if (usersCount < userArrSize)
    {
        users[usersCount] = name;
        passwords[usersCount] = password;
        roles[usersCount] = role;
        usersCount += 2;
        storeUserData(users, passwords, roles, userArrSize);
        return true;
    }
    else
    {
        return false;
    }
}

void welcome()
{
    setcolor(12);
    cout << endl;
    cout << "\t        d8888 888888b.    .d8888b.       888888b.         d8888 888b    888 888    d8P  " << endl;
    cout << "\t       d88888 888   88b  d88P  Y88b      888   88b       d88888 8888b   888 888   d8P   " << endl;
    cout << "\t      d88P888 888  .88P  888    888      888  .88P      d88P888 88888b  888 888  d8P    " << endl;
    cout << "\t     d88P 888 8888888K.  888             8888888K.     d88P 888 888Y88b 888 888d88K     " << endl;
    cout << "\t    d88P  888 888   Y88b 888             888   Y88b   d88P  888 888 Y88b888 8888888b    " << endl;
    cout << "\t   d88P   888 888    888 888    888      888    888  d88P   888 888  Y88888 888  Y88b   " << endl;
    cout << "\t  d8888888888 888   d88P Y88b  d88P      888   d88P d8888888888 888   Y8888 888   Y88b  " << endl;
    cout << "\t d88P     888 8888888P     Y8888P        8888888P  d88P     888 888    Y888 888    Y88b " << endl;
}

void header()
{
    setcolor(5);
    cout << "\t\t                  " << endl;
    cout << "\t\t************************************************************" << endl;
    cout << "\t\t*              EMPLOYEE MANAGEMENT SYSTEM                  *" << endl;
    cout << "\t\t************************************************************" << endl;
    cout << "" << endl;
}

void subMenuBeforeMainMenu(string submenu)
{
    setcolor(14);
    string message = "\t\t" + submenu + " Menu";
    cout << message << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
}

void subMenu(string submenu)
{
    string message = "\tMain Menu > " + submenu;
    cout << message << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
}

void clearScreen()
{
    cout << "Press Any Key to Continue.." << endl;
    getch();
    system("cls");
}

string manager_menu()
{
    cout << "" << endl;
    string anyNum;
    cout << "Select any one of the following options" << endl;
    cout << "1.\tList of today's customers" << endl;
    cout << "2.\tList of Cashiers" << endl;
    cout << "3.\tHire a Cashier" << endl;
    cout << "4.\tFire a Cashier" << endl;
    cout << "5.\tPreview Feedback" << endl;
    cout << "6.\tTotal Bank Reserves" << endl;
    cout << "7.\tSorting Customer amount" << endl;
    cout << "8.\tLoan Approval" << endl;
    cout << "9.\tExit" << endl;
    cout << "Choose one option to continue... ";
    cin >> anyNum;
    return anyNum;
}

void manager_tasks(string customer_names[], long customer_cnic[], long customer_amount[], string feedback[], int &countfeedback, string customer_email[], int &usersDetails, string cashier_names[], int cashier_hours[], string cashier_status[], int &cashier_count, long &total_money)
{
    string manager_Option = "";
    while (manager_Option != "9")
    {
        welcome();
        header();
        subMenu("Manager Tasks");
        manager_Option = manager_menu();
        if (manager_Option == "1")
        {
            system("cls");
            welcome();
            header();
            subMenu("Today's customers list");
            customer_list(customer_names, customer_cnic, customer_amount, customer_email, usersDetails);
        }
        else if (manager_Option == "2")
        {
            system("cls");
            welcome();
            header();
            subMenu("Cashier's list");
            cashier_list(cashier_names, cashier_hours, cashier_status, cashier_count);
        }
        else if (manager_Option == "3")
        {
            system("cls");
            welcome();
            header();
            subMenu("Hiring a new Cashier");
            cout << cashier_hire(cashier_names, cashier_hours, cashier_status, cashier_count) << endl;
        }
        else if (manager_Option == "4")
        {
            system("cls");
            welcome();
            header();
            subMenu("Firing the Cashier");
        }
        else if (manager_Option == "5")
        {
            system("cls");
            welcome();
            header();
            subMenu("Feedbacks Preview");
            cout << veiwfeedback(feedback, countfeedback) << endl;
        }
        else if (manager_Option == "6")
        {
            system("cls");
            welcome();
            header();
            subMenu("Preview Total Bank reserves");
            totalReserves(total_money);
        }
        else if (manager_Option == "7")
        {
            system("cls");
            welcome();
            header();
            subMenu("Sorting in increasing order of Customer Amount");
            sortingCustomerArray(customer_amount, usersDetails);
        }
        else if (manager_Option == "8")
        {
            system("cls");
            welcome();
            header();
            subMenu("Loan Approval");
        }
        else if (manager_Option != "9" && manager_Option != "8" && manager_Option != "7" && manager_Option != "6" && manager_Option != "5" && manager_Option != "4" && manager_Option != "3" && manager_Option != "2" && manager_Option != "1")
        {
            cout << "Invalid option. Try another option." << endl;
        }
        clearScreen();
    }
}

void customer_list(string customer_names[], long customer_cnic[], long customer_amount[], string customer_email[], int &usersDetails)
{
    cout << "(Following are the lists of the Customers)" << endl;
    cout << "" << endl;
    int *list = &usersDetails;
    cout << "Customer's Name:\t\tCustomer's CNIC:\t\tCustomer Amount:\t\tCustomer Email:" << endl;
    for (int i = 0; i < *list; i++)
    {
        cout << customer_names[i] << "\t\t\t\t" << customer_cnic[i] << "\t\t\t " << customer_amount[i] << "\t\t\t\t" << customer_email[i] << endl;
    }
}

void cashier_list(string cashier_names[], int cashier_hours[], string cashier_status[], int &cashier_count)
{
    cout << "(Following are the lists of the Cashiers)" << endl;
    cout << "" << endl;
    int index = cashier_count;
    cashier_names[0] = "Hamza Chaudhry";
    cashier_names[1] = "Asad Asghar";
    cashier_names[2] = "Irtaza Sheikh";
    cashier_hours[0] = 7;
    cashier_hours[1] = 8;
    cashier_hours[2] = 5;
    cashier_status[0] = "On Duty";
    cashier_status[1] = "Off Duty";
    cashier_status[2] = "On Duty";
    cout << "Cashier Name:\t\t\tCashier's working hour:\t\tCashier's Duty status:" << endl;
    for (int i = 0; i < index; i++)
    {
        cout << cashier_names[i] << "\t\t\t" << cashier_hours[i] << "\t\t\t\t" << cashier_status[i] << endl;
    }
}

string cashier_hire(string cashier_names[], int cashier_hours[], string cashier_status[], int &cashier_count)
{
    string name;
    int hours;
    long cnic;
    string result = "";
    cout << "Name of Candidate: \t";
    cin.clear();
    cin.sync();
    getline(cin, name);
    cout << "Candidate Duty hours: \t";
    cin >> hours;
    cout << "Candidate CNIC: \t";
    cin >> cnic;
    if (add_cashier)
    {
        result = "New Cashier has been added successfully";
    }
    else
    {
        result = "Hiring Unsuccessful";
    }
    return result;
}

bool add_cashier(string cashier_names[], int cashier_hours[], string cashier_status[], string name, int hours, int &cashier_count)
{
    cashier_count++;
    cashier_names[cashier_count] = name;
    cashier_hours[cashier_count] = hours;
    cashier_status[cashier_count] = "On Duty";
    return true;
}

string veiwfeedback(string feedback[], int &countfeedback)
{
    string display = "";
    if (countfeedback != 0)
    {
        cout << "Feedbacks given to the store: " << countfeedback << endl;
        for (int i = 0; i < countfeedback; i++)
        {
            if (feedback[i] != "")
            {
                cout << i + 1 << ": \t" << feedback[i] << endl;
            }
        }
    }
    else
    {
        display = "There is no feedback given yet";
    }
    return display;
}

void totalReserves(long &total_money)
{
    cout << "\t\tBank reserves under your supervision are: " << endl;
    cout << "\t\t\t" << total_money << " Rupees." << endl;
    cout << "\t\tYou are doing a Great Job " << endl;
}

void sortingCustomerArray(long customer_amount[], int &usersDetails)
{
    int temp1;
    for (int i = 0; i < usersDetails; i++)
    {
        for (int j = i + 1; j < usersDetails; j++)
        {
            if (customer_amount[i] > customer_amount[j])
            {
                temp1 = customer_amount[i];
                customer_amount[i] = customer_amount[j];
                customer_amount[j] = temp1;
            }
        }
    }
    for (int i = 0; i < usersDetails; i++)
    {
        cout << customer_amount[i] << endl;
    }
}

string cashier_tasks()
{
    string work;
    cout << "Select any one of the following options" << endl;
    cout << "1.\tOpen a Bank Account" << endl;
    cout << "2.\tClose a Bank Account" << endl;
    cout << "3.\tWithdraw Cash" << endl;
    cout << "4.\tDeposit Cash" << endl;
    cout << "5.\tFeedbacks of Customers" << endl;
    cout << "6.\tTransfer Donation" << endl;
    cout << "7.\tApply for Loan" << endl;
    cout << "8.\tExchange Currency" << endl;
    cout << "9.\tExit" << endl;
    cout << "Choose one option to continue... ";
    cin >> work;
    return work;
}
void cashier_Interface(string customer_names[], long customer_cnic[], string feedback[], string &welfare, int &countfeedback, long customer_amount[], string customer_email[], int &usersDetails)
{
    string cashier_Option = "";
    while (cashier_Option != "9")
    {
        welcome();
        header();
        subMenu("Cashier Tasks");
        cashier_Option = cashier_tasks();
        if (cashier_Option == "1")
        {
            system("cls");
            welcome();
            header();
            subMenu("Opening of Bank Account");
            cout << open_account(customer_names, customer_cnic, customer_amount, customer_email, usersDetails) << endl;
        }
        if (cashier_Option == "2")
        {
            system("cls");
            welcome();
            header();
            subMenu("Closing of Bank Account");
            cout << close_account(customer_names, customer_cnic, customer_amount, customer_email, usersDetails) << endl;
        }
        if (cashier_Option == "3")
        {
            system("cls");
            welcome();
            header();
            subMenu("Cash Withdrawal");
            cout << cash_withdraw(customer_names, customer_amount, customer_cnic, usersDetails) << endl;
        }
        if (cashier_Option == "4")
        {
            system("cls");
            welcome();
            header();
            subMenu("Cash Deposit");
            cout << cash_deposit(customer_names, customer_amount, customer_cnic, usersDetails) << endl;
        }
        if (cashier_Option == "5")
        {
            system("cls");
            welcome();
            header();
            subMenu("Feedbacks");
            cout << givefeedback(feedback, countfeedback) << endl;
        }
        if (cashier_Option == "6")
        {
            system("cls");
            welcome();
            header();
            subMenu("Money Donation");
            if (donatemoney(customer_names, customer_cnic, customer_amount, welfare, customer_email, usersDetails))
            {
                cout << " Your donations is successfully transfered to " << welfare << ". Now your Current Balance is: " << customer_amount[usersDetails];
            }
            else
                cout << " Sorry! You don't have enough balance.";
        }
        if (cashier_Option == "7")
        {
            system("cls");
            welcome();
            header();
            subMenu("Loan Applying");
            cout << loan(customer_names, customer_amount, customer_cnic, usersDetails) << endl;
        }
        if (cashier_Option == "8")
        {
            system("cls");
            welcome();
            header();
            subMenu("Currency Exchange");
            exchangecurrency();
        }
        else if (cashier_Option != "9" && cashier_Option != "8" && cashier_Option != "7" && cashier_Option != "6" && cashier_Option != "5" && cashier_Option != "4" && cashier_Option != "3" && cashier_Option != "2" && cashier_Option != "1")
        {
            cout << "Invalid option. Try another option." << endl;
        }
        clearScreen();
    }
}

string open_account(string customer_names[], long customer_cnic[], long customer_amount[], string customer_email[], int &usersDetails)
{
    string name, email, cnicInput, amountInput;
    cout << "\t\tEnter the following details to proceed." << endl;
    cout << "Enter your Name: \t";
    cin >> name;
    cout << "Enter your CNIC: \t";
    cin.clear();
    cin.sync();
    getline(cin, cnicInput);
    while (!containsOnlyIntegers(cnicInput))
    {

        cout << "Invalid input! Please enter a valid option." << endl;
        cin.clear();
        cin.sync();
        getline(cin, cnicInput);
    }
    long cnic;
    cnic = stoi(cnicInput);

    cout << "Enter your email address: \t";
    cin.clear();
    cin.sync();
    getline(cin, email);
    cout << "Enter your Salary (in Rupees): \t";
    cin.clear();
    cin.sync();
    getline(cin, amountInput);
    while (!containsOnlyIntegers(amountInput))
    {

        cout << "Invalid amount! Please enter a valid option." << endl;
        cin.clear();
        cin.sync();
        getline(cin, amountInput);
    }
    float amount;
    amount = stoi(amountInput);

    string ans;
    if (checkAccount(customer_names, customer_cnic, customer_amount, customer_email, usersDetails, name, email, cnic, amount))
    {
        ans = "You have Successfully Opened your account.";
    }
    else
    {
        ans = "User already exists";
    }
    return ans;
}
bool checkAccount(string customer_names[], long customer_cnic[], long customer_amount[], string customer_email[], int &usersDetails, string name, string email, long cnic, float amount)
{
    customer_cnic[usersDetails] = cnic;
    customer_email[usersDetails] = email;
    customer_amount[usersDetails] = amount;
    customer_names[usersDetails] = name;
    usersDetails++;
    return true;
    savearrays(customer_names, customer_cnic, customer_amount, usersDetails);
}

string close_account(string customer_names[], long customer_cnic[], long customer_amount[], string customer_email[], int &usersDetails)
{
    string name, email, ans, cnicInput;
    cout << "\t\tEnter the following details to proceed." << endl;
    cout << "Enter your Name: \t";
    cin >> name;
    cout << "Enter your CNIC: \t";
    cin.clear();
    cin.sync();
    getline(cin, cnicInput);
    while (!containsOnlyIntegers(cnicInput))
    {

        cout << "Invalid input! Please enter a valid option." << endl;
        cin.clear();
        cin.sync();
        getline(cin, cnicInput);
    }
    long cnic;
    cnic = stoi(cnicInput);

    cout << "Enter your email address: \t";
    cin.clear();
    cin.sync();
    getline(cin, email);
    cout << "Enter reason of Closing your account: \t";
    cin.clear();
    cin.sync();
    getline(cin, ans);
    string result = "";
    if (check_forClose(customer_names, customer_cnic, customer_amount, customer_email, usersDetails, name, email, cnic))
    {
        result = "Your account has been closed";
    }
    else
    {
        result = "Account closing unsuccessful.";
    }
    return result;
}
bool check_forClose(string customer_names[], long customer_cnic[], long customer_amount[], string customer_email[], int &usersDetails, string name, string email, long cnic)
{
    // This function will assist manager in expelling staff.

    int x = -1;

    for (int i = 0; i <= usersDetails; i++)
    {
        if (customer_names[i] == name && customer_cnic[i] == cnic && customer_email[i] == email)
        {
            x = i;
            break;
        }
        else
        {

            return false;
        }
    }
    if (x != -1)
    {
        customer_names[x] = " ";
        customer_cnic[x] == 0;
        customer_email[x] == " ";
        return true;
    }
    return false;
}
string cash_withdraw(string customer_names[], long customer_cnic[], long customer_amount[], int &usersDetails)
{
    string name, cnicInput, amountInput;
    long cnic;
    float amount;
    cout << "Enter your Name: \t";
    cin.clear();
    cin.sync();
    getline(cin, name);
    cout << "Enter your CNIC: \t";
    cin.clear();
    cin.sync();
    getline(cin, cnicInput);
    while (!containsOnlyIntegers(cnicInput))
    {

        cout << "Invalid input! Please enter a valid option." << endl;
        cin.clear();
        cin.sync();
        getline(cin, cnicInput);
    }
    cnic = stoi(cnicInput);

    cout << "Enter the amount you want to deposit: ";
    cin.clear();
    cin.sync();
    getline(cin, amountInput);
    while (!containsOnlyIntegers(amountInput))
    {

        cout << "Invalid amount! Please enter a valid option." << endl;
        cin.clear();
        cin.sync();
        getline(cin, amountInput);
    }
    amount = stoi(amountInput);

    string result;
    if (can_withdraw(customer_names, customer_cnic, customer_amount, usersDetails, name, cnic, amount))
    {
        customer_amount[usersDetails] = customer_amount[usersDetails] - amount;
        result = "Cash withdrawal successful";
    }
    else
    {
        result = "Withdrawal unsuccessful";
    }
    return result;
}
bool can_withdraw(string customer_names[], long customer_cnic[], long customer_amount[], int &usersDetails, string name, long cnic, float amount)
{
    for (int i = 0; i <= usersDetails; i++)
    {
        if (customer_names[i] == name && customer_cnic[i] == cnic)
        {
            if (amount > customer_amount[i])
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
string cash_deposit(string customer_names[], long customer_cnic[], long customer_amount[], int &usersDetails)
{
    string name, cnicInput, amountInput;
    long cnic;
    float amount;
    cout << "Enter your Name: \t";
    cin.clear();
    cin.sync();
    getline(cin, name);
    cout << "Enter your CNIC: \t";
    cin.clear();
    cin.sync();
    getline(cin, cnicInput);
    while (!containsOnlyIntegers(cnicInput))
    {

        cout << "Invalid input! Please enter a valid option." << endl;
        cin.clear();
        cin.sync();
        getline(cin, cnicInput);
    }
    cnic = stoi(cnicInput);

    cout << "Enter the amount you want to deposit: ";
    cin.clear();
    cin.sync();
    getline(cin, amountInput);
    while (!containsOnlyIntegers(amountInput))
    {

        cout << "Invalid amount! Please enter a valid option." << endl;
        cin.clear();
        cin.sync();
        getline(cin, amountInput);
    }
    amount = stoi(amountInput);

    string result;
    if (can_deposit(customer_names, customer_cnic, customer_amount, usersDetails, name, cnic, amount))
    {
        customer_amount[usersDetails] = customer_amount[usersDetails] + amount;
        result = "Cash Deposit successful";
    }
    else
    {
        result = "You don't have an account yet";
    }
    return result;
}
bool can_deposit(string customer_names[], long customer_cnic[], long customer_amount[], int &usersDetails, string name, long cnic, float amount)
{
    for (int i = 0; i <= usersDetails; i++)
    {
        if (customer_names[i] == name && customer_cnic[i] == cnic)
        {
            return true;
        }
    }
    return false;
}
string loan(string customer_names[], long customer_cnic[], long customer_amount[], int &usersDetails)
{
    string name, cnicInput, amountInput, salaryInput;
    long cnic;
    float amount, salary;
    cout << "Enter your Name: \t";
    cin.clear();
    cin.sync();
    getline(cin, name);
    cout << "Enter your CNIC: \t";
    cin.ignore();
    getline(cin, cnicInput);
    while (!containsOnlyIntegers(cnicInput))
    {

        cout << "Invalid input! Please enter a valid option." << endl;
        cin.ignore();
        getline(cin, cnicInput);
    }
    cnic = stoi(cnicInput);

    cout << "Enter your Salary (in Rupees): \t";
    cin.clear();
    cin.sync();
    getline(cin, salaryInput);
    while (!containsOnlyIntegers(salaryInput))
    {

        cout << "Invalid salary! Please enter a valid option." << endl;
        cin.clear();
        cin.sync();
        getline(cin, salaryInput);
    }
    salary = stoi(salaryInput);

    cout << "Enter the amount you need as a loan: \t";
    cin.clear();
    cin.sync();
    getline(cin, amountInput);
    while (!containsOnlyIntegers(amountInput))
    {

        cout << "Invalid amount! Please enter a valid option." << endl;
        cin.clear();
        cin.sync();
        getline(cin, amountInput);
    }
    amount = stoi(amountInput);

    string result;
    if (loan_ok(customer_names, customer_cnic, customer_amount, usersDetails, name, cnic, salary, amount))
    {
        result = "Application for Loan submitted.";
    }
    else
    {
        result = "Your application did not meet the criteria.";
    }
}
bool loan_ok(string customer_names[], long customer_cnic[], long customer_amount[], int &usersDetails, string name, long cnic, float amount, float salary)
{
    for (int i = 0; i <= usersDetails; i++)
    {
        if (customer_names[i] == name && customer_cnic[i] == cnic)
        {
            if (salary > 25000)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}

string givefeedback(string feedback[], int &countfeedback)
{
    string rev, display;
    cout << "Enter feedback about your experience: ";
    cin.clear();
    cin.sync();
    getline(cin, rev);
    feedback[countfeedback] = rev;
    countfeedback++;
    display = "You have successfuly given a feedback";
    return display;
}

bool donatemoney(string customer_names[], long customer_cnic[], long customer_amount[], string &welfare, string customer_email[], int &usersDetails)
{
    string input;
    int donateamount;
    cout << " Enter the amount you want to transfer: ";
    cin.ignore();
    getline(cin, input);
    while (!containsOnlyIntegers(input))
    {

        cout << "Invalid input! Please enter a valid option." << endl;
        cin.ignore();
        getline(cin, input);
    }
    donateamount = stoi(input);

    cin >> donateamount;
    cout << " Enter the welfare to which yo want to transfer donations: ";
    cin.ignore();
    getline(cin, welfare);
    if (customer_amount[usersDetails] >= donateamount)
    {
        customer_amount[usersDetails] -= donateamount;
        return true;
    }
    else
        return false;
}

void exchangecurrency()
{
    cout << "\t1 Dollar = 300 Rupees" << endl;
    cout << "\t1 Pound = 400 Rupees" << endl;
    float amount, exchange;
    string a, b, amountInput;
    cout << " Enter the amount you want to exchange: ";
    cin.clear();
    cin.sync();
    getline(cin, amountInput);
    while (!containsOnlyIntegers(amountInput))
    {

        cout << "Invalid input! Please enter a valid option." << endl;
        cin.clear();
        cin.sync();
        getline(cin, amountInput);
    }
    amount = stoi(amountInput);

    cout << " Enter your currency (Dollar, Pound, Rupee): ";
    cin >> a;
    cout << " Enter your currency you want to get (Dollar, Pound, Rupee): ";
    cin >> b;
    if (a == "Rupee" && b == "Dollar")
        exchange = amount / 300;
    if (a == "Rupee" && b == "Pound")
        exchange = amount / 400;
    if (a == "Dollar" && b == "Rupee")
        exchange = amount * 300;
    if (a == "Dollar" && b == "Pound")
        exchange = (amount / 300) * 400;
    if (a == "Pound" && b == "Dollar")
        exchange = (amount * 300) / 400;
    if (a == "Pound" && b == "Rupee")
        exchange = amount * 400;
    cout << " Recieve your " << exchange << " " << b << endl;
}

bool containsOnlyAlphabets(string word) // It validates if the required input are alphabets
{
    bool result = false;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int asciiCode = word[i];

        if (asciiCode >= 65 && asciiCode <= 122)
        {
            result = true;
        }
    }

    return result;
}

bool containsOnlyIntegers(string integer) // It validates if the required input are integers
{
    bool result = false;

    for (int i = 0; integer[i] != '\0'; i++)
    {
        int asciiCode = integer[i];

        if (asciiCode >= 48 && asciiCode <= 57)
        {
            result = true;
        }
    }

    return result;
}

void storeUserData(string users[], string passwords[], string roles[], int userArrSize)
{
    fstream fileUsers;
    fileUsers.open("users.txt", ios::out);
    for (int i = 0; i < userArrSize; i++)
    {
        if (users[i] != " ")
        {
            fileUsers << users[i];
            fileUsers << "~";
            fileUsers << passwords[i];
            fileUsers << "~";
            fileUsers << roles[i];
            fileUsers << "~";
            if (i != userArrSize - 1)
            {
                fileUsers << "\n";
            }
        }
    }
    fileUsers.close();
}

void LoadUserData(string users[], string passwords[], string roles[], int &usersCount)
{
    string data;
    usersCount = 0;
    fstream Filein;
    Filein.open("users.txt", ios::in);
    while (!(Filein.eof()))
    {
        getline(Filein, data);
        users[usersCount] = getfield(data, 1);
        passwords[usersCount] = getfield(data, 2);
        roles[usersCount] = getfield(data, 3);
        usersCount++;
    }
    Filein.close();
}

string parseData(int index, string line)
{
    int idx = 0;
    string word = "";
    int wordnum = 0;
    while (line[idx] != '\0')
    {
        if (line[idx] == '~')
        {
            if (wordnum == index)
            {
                return word;
            }
            word = "";
            wordnum++;
        }
        else
        {
            word += line[idx];
        }
        idx++;
    }
}

int convertStoInt(string num)
{
    int number = 0;
    int temp;
    int difference = 1;
    for (int i = num.length() - 1; i >= 0; i--)
    {
        temp = num[i] - '0';
        number += (temp * difference);
        difference *= 10;
    }
    return number;
}

string getfield(string record, int field)
{
    int comma = 1;
    string result = "";
    for (int i = 0; i < record.length(); i++)
    {
        if (record[i] == '~')
        {
            comma = comma + 1;
        }
        else if (comma == field)
        {
            result = result + record[i];
        }
    }
    return result;
}

void savearrays(string customer_names[], long customer_cnic[], long customer_amount[], int &usersDetails)
{
    string some = "";
    long amount, cnic;
    fstream file2;
    file2.open("arrays.txt", ios::out);
    for (int i = 0; i < usersDetails; i++)
    {
        getline(file2, some);
        customer_names[usersDetails] = getfield(some, 1);
        usersDetails++;
    }
    file2.close();
}
void savefeed(string feedback[], int &countfeedback)
{
    string feed = "";
    long amount, cnic;
    fstream file3;
    file3.open("file2.txt", ios::out);
    for (int i = 0; i < countfeedback; i++)
    {
        getline(file3, feed);
        feedback[countfeedback] = getfield(feed, 1);
        countfeedback++;
    }
    file3.close();
}

void Loadfeedback(string feedback[], int &countfeedback)
{
    string data;
    countfeedback = 0;
    fstream Filein;
    Filein.open("users.txt", ios::in);
    while (!(Filein.eof()))
    {
        getline(Filein, data);
        feedback[countfeedback] = getfield(data, 1);
        countfeedback++;
    }
    Filein.close();
}
