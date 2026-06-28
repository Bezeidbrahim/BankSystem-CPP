#pragma once
#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Name of the file used to store client records
const string ClientsFileName = "Clients.txt";

// ============================================================
// Enums
// ============================================================

// Options shown in the main menu
enum enMainMenueOptions
{
    eShowClientsList = 1, eAddNewClient = 2,
    eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, eTransactions = 6, eExit = 7
};

// Options shown in the transactions sub-menu
enum enTransactionType
{
    eDeposit = 1, eWithdraw = 2, eTotalBalance = 3, eMainMenue = 4
};

// ============================================================
// Data structure
// ============================================================

// Represents a single bank client record
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false; // used for soft delete before saving
};

// ============================================================
// String helper (used for converting file lines to records)
// ============================================================

// Splits a string into a list of words using a delimiter
vector<string> SplitString(string S1, string delim);

// ============================================================
// Client data helpers (conversion, file storage)
// ============================================================

// Checks if a client with the given account number already exists
bool ClientExistsByAccountNumber(string AccountNumber, string FileName);

// Reads a new client's data from the user
sClient ReadNewClient();

// Converts a client record into a single text line (for saving)
string ConvertRecordToLine(sClient Client, string Seperator = "#//#");

// Converts a text line back into a client record (for loading)
sClient ConvertLinetoRecord(string ClientRecord, string seperator = "#//#");

// Prints all details of one client
void PrintClientCard(sClient client);

// Appends one line of text to the given file
void AddDataLineToFile(string FileName, string stDataLine);

// Adds a single new client and saves it to the file
void AddNewClient();

// Adds one or more new clients in a loop
void AddClients();

// Screen: handles the "Add New Client" menu option
void ShowAddNewClientsScreen();

// Loads all client records from the file into a vector
vector<sClient> LoadCleintsDataFromFile(string FileName);

// Prints one client as a single table row
void PrintClientRecordLine(sClient Client);

// Screen: shows the full client list in a table
void ShowAllClientsScreen();

// Reads an account number from the user
string ReadClientAccountNumber();

// Searches the client list for a given account number
bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client);

// Marks a client as deleted (soft delete, does not remove it yet)
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClients);

// Saves all clients (except those marked for delete) back to the file
vector<sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients);

// Deletes a client after confirmation from the user
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients);

// Screen: handles the "Delete Client" menu option
void ShowDeleteClientScreen();

// Reads updated data for an existing client
sClient ChangeClientRecord(string AccountNumber);

// Updates a client's data after confirmation from the user
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients);

// Screen: handles the "Update Client Info" menu option
void ShowUpdateClientScreen();

// Screen: handles the "Find Client" menu option
void ShowFindClientScreen();

// Screen: shown when the program ends
void ShowEndScreen();

// ============================================================
// Main menu
// ============================================================

// Runs the action chosen from the main menu
void PerfromMainMenueOption(enMainMenueOptions MainMenueOption);

// Displays the main menu and reads the user's choice
void ShowMainMenue();

// Waits for a key press, then returns to the main menu
void GoBackToMainMenue();

// Reads the user's choice from the main menu
short ReadMainMenueOption();

// ============================================================
// Transactions menu
// ============================================================

// Displays the transactions menu and reads the user's choice
void ShowTransactionsMenue();

// Runs the action chosen from the transactions menu
void PerformTransactionsMenueOption(enTransactionType TransactionType);

// Reads the user's choice from the transactions menu
short ReadTransactionMenue();

// Screen: handles the "Deposit" transaction
void ShowDepositScreen();

// Adds (or subtracts, for withdraw) an amount from a client's balance
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient>& vClients);

// Waits for a key press, then returns to the transactions menu
void GoBackToTransactionsMenue();

// Screen: handles the "Withdraw" transaction
void ShowWithdrawScreen();

// Screen: shows the total balance across all clients
void ShowTotalBalanceScreen();

#endif
