#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const string ClientsFileName = "D:\\NewVS\\Course8_AboHadhood\\ATM System\\Clients.txt.txt";

enum enATMMenueOptions { eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCheckBalance = 4, eLogout = 5 };

enum enQuickWithdraw { eTwenty = 1, eFifty = 2, eHundred = 3, eTwoHundred = 4, eFourHundred = 5, eSixHundred = 6, eEightHundred = 7, eThousand = 8, eExit = 9 };

void ShowATMMainMenue();
void ShowQuickWithdrawScreen();
void GoBackToATMMainMenue();
void Login();
void ShowNormalWithdrawScreen();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

sClient Client;

vector <string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; 

    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); 
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  
    }

    if (S1 != "")
    {
        vString.push_back(S1); 
    }

    return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double


    return Client;

}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vClients;

}

bool FindUserByAccountNumberAndPinCode(string AccountNumber, string PinCode, sClient& Client)
{
    vector <sClient>  vClient =  LoadCleintsDataFromFile(ClientsFileName);

    for (sClient& C  : vClient)
    {
        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool IsLoginFaild(string AccountNumber, string PinCode)
{
    if (FindUserByAccountNumberAndPinCode(AccountNumber, PinCode, Client))
        return true;
    else
        return false;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{

    

    char Answer = 'n';


    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;
            }

        }


        return false;
    }
    return false;
}

bool CheckExceedsBalance(double Amount) 
{
    if (Amount > Client.AccountBalance) 
    {
        cout << "\nThe amount exceeds your balance, Enter another amount.";
        cout << "\nPress AnyKey to continue....";
        system("pause>0");
        return true; 
    }
    return false; 
}

void GoBackToATMMainMenue()
{
    cout << "\n\nPress any key to go back to ATM Main Menue...";
    system("pause>0");
    ShowATMMainMenue();
}

double BalanceWithAccountNumber(string AccountNumber)
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient& Client : vClients)
        {

            if (Client.AccountNumber == AccountNumber)
            {
                return Client.AccountBalance;
            }

            cout << endl;
        }

    return Client.AccountBalance;

}

double ReadAmount()
{
    int Amount = 0;

    do
    {
        cout << "\nEnter an amount multiple of 5's ? ";
        cin >> Amount;

    } while (Amount % 5 != 0);

    return (double)Amount;
}

short ReadATMMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

short ReadQuickWithdrawMenueOption()
{
    cout << "Choose what to Withdraw from? [1 to 9]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void CalculateBalanceQuickWithdraw(enQuickWithdraw QuickWithdraw)
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    int Amount = 0;

    switch (QuickWithdraw) 
    {
    case eTwenty:
        Amount = 20;
        break;

    case eFifty:
        Amount = 50; 
        break;
    
    case eHundred: 
        Amount = 100;
        break;
    
    case eTwoHundred:
        Amount = 200;
        break;
    
    case eFourHundred: 
        Amount = 400;
        break;
    
    case eSixHundred: 
        Amount = 600;
        break;
    
    case eEightHundred: 
        Amount = 800;
        break;
    
    case eThousand:
        Amount = 1000;
        break;
    
    case eExit:
        GoBackToATMMainMenue();
        return;
    }

    if (CheckExceedsBalance(Amount))
    {
        ShowQuickWithdrawScreen();
        return;
    }

    DepositBalanceToClientByAccountNumber(Client.AccountNumber, Amount * -1, vClients);

}

void ShowCheckBalanceScreen()
{
    system("cls");
    cout << "\n-----------------------------------\n";
    cout << "\tCheck Balance Screen";
    cout << "\n-----------------------------------\n";

    cout << "Your Balance is " << BalanceWithAccountNumber(Client.AccountNumber) << endl;
}

void ShowQuickWithdrawScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tQuick Withdraw Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] 20  " << " \t[2] 50  \n";
    cout << "\t[3] 100 " << " \t[4] 200 \n";
    cout << "\t[5] 400 " << " \t[6] 600 \n";
    cout << "\t[7] 800 " << " \t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "===========================================\n";
    cout << "Your Balance is " << Client.AccountBalance << endl;
    CalculateBalanceQuickWithdraw(enQuickWithdraw(ReadQuickWithdrawMenueOption()));
}

void ShowNormalWithdrawScreen()
{
    system("cls");
    cout << "\n-----------------------------------\n";
    cout << "\tNormal Withdraw Screen";
    cout << "\n-----------------------------------\n";
    double Amount = ReadAmount();
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);


    if (CheckExceedsBalance(Amount))
    {
        ShowNormalWithdrawScreen();
        return;
    }

    DepositBalanceToClientByAccountNumber(Client.AccountNumber, Amount * -1, vClients);
}

void ShowDepositScreen()
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    double Amount = 0;

    system("cls");
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";

    cout << "\nEnter a Positive deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(Client.AccountNumber, Amount, vClients);

}

void PerfromMainMenueOption(enATMMenueOptions AtmMainMenueOption)
{
    switch (AtmMainMenueOption)
    {
    case eQuickWithdraw:
        ShowQuickWithdrawScreen();
        GoBackToATMMainMenue();
        break;

    case eNormalWithdraw:
        ShowNormalWithdrawScreen();
        GoBackToATMMainMenue();
        break;

    case eDeposit:
        ShowDepositScreen();
        GoBackToATMMainMenue();
        break;

    case eCheckBalance:
        ShowCheckBalanceScreen();
        GoBackToATMMainMenue();
        break;

    case eLogout:
        Login();
        break;
    }

}

void ShowATMMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Log out.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption(enATMMenueOptions(ReadATMMainMenueOption()));
}

void Login()
{

    string AccountNumber;
    string PinCode;

    bool FirstExist = true;

    do
    {
        system("cls");
        cout << "\n-----------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n-----------------------------------\n";

        if (!FirstExist)
        {
            cout << "Invalid Account Number/PinCode!\n";
        }

        cout << "Enter Account Number? ";
        cin >> AccountNumber;
       
        cout << "Enter PinCode? ";
        cin >> PinCode;

        FirstExist = IsLoginFaild(AccountNumber, PinCode);

    } while (!FirstExist);

    ShowATMMainMenue();
}

int main()

{
    Login();

    system("pause>0");
    return 0;
}
