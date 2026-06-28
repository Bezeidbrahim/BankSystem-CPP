#include "BankSystem.h"
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// ============================================================
// String helper (used for converting file lines to records)
// ============================================================

// Splits a string into a list of words using a delimiter
vector<string> SplitString(string S1, string delim) {
    vector<string> words;
    size_t pos = 0;
    string sWord;
    while ((pos = S1.find(delim)) != std::string::npos) {
        sWord = S1.substr(0, pos);
        if (!sWord.empty()) {
            words.push_back(sWord);
        }
        S1.erase(0, pos + delim.length());
    }
    if (!S1.empty()) {
        words.push_back(S1);
    }
    return words;
}

// ============================================================
// Client data helpers (conversion, file storage)
// ============================================================

// Checks if a client with the given account number already exists
bool ClientExistsByAccountNumber(string AccountNumber, string FileName) {
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open()) {
        string Line;
        sClient Client;
        while (getline(MyFile, Line)) {
            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber) {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }
        MyFile.close();
    }

    return false;
}

// Reads a new client's data from the user
sClient ReadNewClient()
{
    sClient Client;

    cout << "\nEnter AccountNumber? ";
    getline(cin >> ws, Client.AccountNumber);

    // Keep asking until a unique account number is given
    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName)) {
        cout << "\nClient with Account Number (" << Client.AccountNumber << ") already exists.\n";
        cout << "\nEnter AccountNumber? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "\nEnter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "\nEnter Name? ";
    getline(cin, Client.Name);

    cout << "\nEnter Phone? ";
    getline(cin, Client.Phone);

    cout << "\nEnter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

// Converts a client record into a single text line (for saving)
string ConvertRecordToLine(sClient Client, string Seperator)
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

// Converts a text line back into a client record (for loading)
sClient ConvertLinetoRecord(string ClientRecord, string seperator)
{
    vector<string> vClientRecord = SplitString(ClientRecord, seperator);
    sClient client;
    client.AccountNumber = vClientRecord[0];
    client.PinCode = vClientRecord[1];
    client.Name = vClientRecord[2];
    client.Phone = vClientRecord[3];
    client.AccountBalance = stod(vClientRecord[4]);
    return client;
}

// Prints all details of one client
void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

// Appends one line of text to the given file
void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}

// Adds a single new client and saves it to the file
void AddNewClient()
{
    sClient Client;

    Client = ReadNewClient();

    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

// Adds one or more new clients in a loop
void AddClients()
{
    char AddMore = 'Y';
    do
    {
        system("cls");
        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}

// Screen: handles the "Add New Client" menu option
void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";
    AddClients();
}

// Loads all client records from the file into a vector
vector<sClient> LoadCleintsDataFromFile(string FileName)
{
    vector<sClient> vClients;
    fstream MyFile;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {
            sClient Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

// Prints one client as a single table row
void PrintClientRecordLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

// Screen: shows the full client list in a table
void ShowAllClientsScreen()
{
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (sClient Client : vClients)
        {
            PrintClientRecordLine(Client);
            cout << endl;
        }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

// Reads an account number from the user
string ReadClientAccountNumber() {

    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";

    cin >> AccountNumber;

    return AccountNumber;
}

// Searches the client list for a given account number
bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClient, sClient& Client) {

    for (sClient C : vClient) {
        if (C.AccountNumber == AccountNumber) {
            Client = C;
            return true;
        }
    }
    return false;
}

// Marks a client as deleted (soft delete, does not remove it yet)
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClient) {

    for (sClient& C : vClient) {
        if (C.AccountNumber == AccountNumber) {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

// Saves all clients (except those marked for delete) back to the file
vector<sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClient) {
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string DataLine;
    if (MyFile.is_open()) {
        for (sClient C : vClient) {
            if (C.MarkForDelete == false) {
                // Only write records that are not marked for delete
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClient;
}

// Deletes a client after confirmation from the user
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClient) {

    sClient Client;
    char Answer = 'y';

    if (FindClientByAccountNumber(AccountNumber, vClient, Client)) {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClient);
            SaveCleintsDataToFile(ClientsFileName, vClient);
            vClient = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\n\nClient with Account Number (" << AccountNumber << ") Not Found.";
        return false;
    }

    return false;
}

// Screen: handles the "Delete Client" menu option
void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

// Reads updated data for an existing client
sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}

// Updates a client's data after confirmation from the user
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want to update this client? Y/N? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is not found.\n";
        return false;
    }
    return false;
}

// Screen: handles the "Update Client Info" menu option
void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

// Screen: handles the "Find Client" menu option
void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

// Screen: shown when the program ends
void ShowEndScreen() {
    system("cls");
    cout << "\n=====================================\n";
    cout << "\t\t Program Ends :-) \n";
    cout << "=====================================\n";
}

// ============================================================
// Main menu
// ============================================================

// Runs the action chosen from the main menu
void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eShowClientsList:
    {
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eTransactions:
        system("cls");
        ShowTransactionsMenue();
        break;
    case enMainMenueOptions::eExit:
        system("cls");
        ShowEndScreen();
        break;
    }
}

// Waits for a key press, then returns to the main menu
void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}

// Reads the user's choice from the main menu
short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 7]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

// ============================================================
// Transactions menu
// ============================================================

// Reads the user's choice from the transactions menu
short ReadTransactionMenue()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

// Runs the action chosen from the transactions menu
void PerformTransactionsMenueOption(enTransactionType TransactionsMenueOption) {
    switch (TransactionsMenueOption)
    {
    case enTransactionType::eDeposit:
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    case enTransactionType::eWithdraw:
        system("cls");
        ShowWithdrawScreen();
        GoBackToTransactionsMenue();
        break;
    case enTransactionType::eTotalBalance:
        system("cls");
        ShowTotalBalanceScreen();
        GoBackToTransactionsMenue();
        break;
    case enTransactionType::eMainMenue:
        system("cls");
        ShowMainMenue();
        break;
    }
}

// Displays the transactions menu and reads the user's choice
void ShowTransactionsMenue() {
    system("cls");
    cout << "\n===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balance.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";

    PerformTransactionsMenueOption((enTransactionType)ReadTransactionMenue());
}

// Adds (or subtracts, for withdraw) an amount from a client's balance
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient>& vClients) {

    char Answer = 'n';

    cout << "\n\nAre you sure you want to deposit to this client? Y/N? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDeposit Successful. New Balance: " << C.AccountBalance;
                return true;
            }
        }
        return false;
    }
    else {
        cout << "\n\nDeposit Cancelled.";
        return false;
    }
}

// Screen: handles the "Deposit" transaction
void ShowDepositScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        cout << "\nClient with Account Number (" << AccountNumber << ") Not Found.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);
    double Amount = 0;
    cout << "\n\nPlease enter the amount to deposit: ";
    cin >> Amount;
    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

// Waits for a key press, then returns to the transactions menu
void GoBackToTransactionsMenue() {
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue();
}

// Screen: handles the "Withdraw" transaction
void ShowWithdrawScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";
    sClient Client;
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        cout << "\nClient with Account Number (" << AccountNumber << ") Not Found.\n";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClientCard(Client);
    double Amount = 0;
    cout << "\n\nPlease enter the amount to withdraw: ";
    cin >> Amount;
    DepositBalanceToClientByAccountNumber(AccountNumber, -Amount, vClients);
}

// Screen: shows the total balance across all clients
void ShowTotalBalanceScreen() {
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalance = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (sClient Client : vClients)
        {
            PrintClientRecordLine(Client);
            TotalBalance += Client.AccountBalance;
            cout << endl;
        }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t Total Balances = " << TotalBalance;
}

// Displays the main menu and reads the user's choice
void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}
