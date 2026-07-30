#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

const string FileName = "Clients.text";

enum ePageContent {
    Show = 1,
    Add = 2,
    Delete = 3,
    Update = 4,
    Find = 5,
    Transactions = 6,
    Exit = 7
};
enum ePageTransactions {
    Deposit = 1,
    Withdraw = 2,
    TotalBalances = 3,
    MainMenu = 4
};

struct sClient {
    string AccNum, PinCode, Name, Phone;
    double AccBalance;
    bool IsDeleted = false;
};

void start();
void TransactionsMenuScreen();

vector<string> SplitString(string S1, string delim) {
    vector<string> vstring;
    short pos = 0;
    string sWord;
    while ((pos = S1.find(delim)) != std::string::npos) {
        sWord = S1.substr(0, pos);
        if (sWord != "") {
            vstring.push_back(sWord);
        }
        S1.erase(0, pos + delim.length());
    }

    if (S1 != "") {
        vstring.push_back(S1);
    }

    return vstring;
}

sClient ConvertLineToRecord(string S1) {
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(S1, "#//#");

    Client.AccNum = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccBalance = stod(vClientData[4]);

    return Client;
}

vector<sClient> LoadDataFromFile(string FileName) {
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open()) {
        string Line;
        sClient Client;
        while (getline(MyFile, Line)) {
                Client = ConvertLineToRecord(Line);
                vClients.push_back(Client);
        }
        MyFile.close();
    }
    else {
        cout << "Error: Could not open file " << FileName << endl;
    }
    return vClients;
}



bool ClientExistsByAccountNumber(string AccountNumber , string FileName) {
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            if (Client.AccNum == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return false;
}

sClient ReadClientData(sClient Client) {
    cout << "-----------------------------------\n";
    cout << "Adding New Client:\n";
    cout << "-----------------------------------\n";

    cout << "Enter Account Number? ";
    // Use ws to consume any remaining whitespace/newlines cleanly
    getline(cin >> ws, Client.AccNum);

    while (ClientExistsByAccountNumber(Client.AccNum,
        FileName)){
        cout << "\nClient with [" << Client.AccNum << "] already exists, Enter another Account Number ? ";
            getline(cin >> ws, Client.AccNum);
    }

    cout << "Enter Pin Code? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone Number? ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance? ";
    cin >> Client.AccBalance;

    return Client;
}


string ConvertRecordToLine(sClient Client, string Separetor = "#//#") {
    string S2 = "";

    S2 += Client.AccNum + Separetor;
    S2 += Client.PinCode + Separetor;
    S2 += Client.Name + Separetor;
    S2 += Client.Phone + Separetor;
    S2 += to_string(Client.AccBalance);

    return S2;
}

void AddClientsToFile(string FileName, string S2) {
    fstream MyFile;
    MyFile.open(FileName, ios::app);
    if (MyFile.is_open()) {
        MyFile << S2 << endl;
    }
    MyFile.close();
}
void SaveClientsToFile(string FileName, vector<sClient> vClients) {

    fstream MyFile;

    MyFile.open(FileName, ios::out );
    string DataLine;
    if (MyFile.is_open()) {
        for (sClient& C : vClients) {
            if (C.IsDeleted == false) {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
    }

    MyFile.close();

}

void PrintAllClients(sClient Client) {

    cout << "| " << setw(17) << Client.AccNum << "| " 
        << setw(12) << Client.PinCode << "| " << setw(35) 
        << Client.Name << "| " << setw(16) << Client.Phone << "| " << setw(11) 
        << Client.AccBalance<<endl;

}





void PrintMainScreen() {
    cout << "=================================\n";
    cout << "\t Main Menu Screen \t\t\n";
    cout << "=================================\n";
    cout << "\t [1] Show Client List. \n"; // Nailed it!
    cout << "\t [2] Add New Client. \n"; // Nailed it!
    cout << "\t [3] Delete Client. \n"; // Nailed it!
    cout << "\t [4] Update Client Info. \n";
    cout << "\t [5] Find Client. \n"; // Nailed it
    cout << "\t [6] Transactions. \n"; // Nailed it
    cout << "\t [7] Exit. \n"; // Nailed it!
    cout << "=================================\n";
    cout << "Choose what do you want to do? [1 to 7]?";

}

void ExitMenu() {
    cout << "\n----------------------------------------\n";
    cout << "\t\t Program Ends :-) \t\t";
    cout << "\n----------------------------------------\n";

}

string GetAccountNumber() {
    string Accnum;
    cout << "Pleade enter AccountNumber? ";
    cin >> Accnum;
    return Accnum;
}

void PrintClientCard(sClient Client) {
    cout << "\nThe following are the client details:";
    cout << "\n----------------------------------------";
    cout << left << setw(16) << "\nAccount Number" << setw(2) << ":" << Client.AccNum;
    cout << left << setw(16) << "\nPin Code" << setw(2) << ":" << Client.PinCode;
    cout << left << setw(16) << "\nName" << setw(2) << ":" << Client.Name;
    cout << left << setw(16) << "\nPhone" << setw(2) << ":" << Client.Phone;
    cout << left << setw(16) << "\nAccount Balance" << setw(2) << ":" << Client.AccBalance;
    cout << left << setw(16) << "\n----------------------------------------\n\n";

}

void FindClient() {

    cout << "\n----------------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n----------------------------------------\n\n";

    string AccountNumber = GetAccountNumber();
    vector<sClient> vClients = LoadDataFromFile(FileName);
    
    for (sClient& C : vClients) {
        if (AccountNumber == C.AccNum) {
            PrintClientCard(C);
        }
    }
    cout << "Press any key to go back to Main Menu...";
    system("pause>0");

}

sClient EditClientCard(sClient &Client , string AccountNumber) {
    Client.AccNum = AccountNumber;
    cout << "Enter Pin Code? ";
    getline(cin >> ws , Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone Number? ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance? ";
    cin >> Client.AccBalance;

    return Client;
}

bool EditClientInfo(vector<sClient>& vClients, string AccountNumber) {
    for (sClient& C : vClients) {
        if (C.AccNum == AccountNumber) {
            C = EditClientCard(C,AccountNumber);
            return true;
        }
    }
    return false;
}
void UpdateClientInfo() {

    cout << "\n----------------------------------------\n";
    cout << "\Update Client Info Screen";
    cout << "\n----------------------------------------\n\n";
    string AccountNumber = GetAccountNumber();
    vector<sClient> vClients = LoadDataFromFile(FileName);

    for (sClient& C : vClients) {
        if (AccountNumber == C.AccNum) {
            PrintClientCard(C);
        }
    }

    char answer;
    cout << "Are you sure you want to Update this client? y/n ?";
    cin >> answer;

    if (toupper(answer) == 'Y') {
        EditClientInfo(vClients, AccountNumber);
        SaveClientsToFile(FileName, vClients);

    }
    cout << "Client Updated successfully.\n";
    cout << "\n\nPress any key to go back to the Main Menu...";
    system("pause>0");

}


bool DeleteClient(vector<sClient>& vClients , string AccountNumber) {
    
    for (sClient& C : vClients) {
        if (AccountNumber == C.AccNum) {
            C.IsDeleted = true;
            return true;
        }
    }
    return false;
}
void DeleteClient() {

    cout << "\n----------------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n----------------------------------------\n\n";
    string AccountNumber = GetAccountNumber();
    vector<sClient> vClients = LoadDataFromFile(FileName);

    for (sClient& C : vClients) {
        if (AccountNumber == C.AccNum) {
            PrintClientCard(C);
        }
    }

    char answer;
    cout << "Are you sure you want to delete this client? y/n ?";
    cin >> answer;

    if (toupper(answer) == 'Y') {
        DeleteClient(vClients , AccountNumber);
        SaveClientsToFile(FileName,vClients);

    }
    cout << "Client Deleted successfully.\n";
    cout << "\n\nPress any key to go back to the Main Menu...";
    system("pause>0");
 
}

void AddClient() {
    string S1;

    char answer = 'Y';

    do {
        system("cls");
        sClient Client;
        Client = ReadClientData(Client);

        S1 = ConvertRecordToLine(Client, "#//#");
        AddClientsToFile(FileName,S1);
        cout << "\nClient Added Successfully. Do you want to add more Clients? Y/N? ";
        cin >> answer;
    } while (toupper(answer) == 'Y');

    cout << "\n\nPress any key to go back to the Main Menu...";
    system("pause>0");

    
}

void ShowClientList() {
    vector<sClient> vClients;
    vClients = LoadDataFromFile(FileName);

    cout << "\n\t\t\t\t\tClients List (" << vClients.size() << ") Client(s)";
    cout << "\n_______________________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(17) << "Account Number" << "| " << left << setw(12) << "Pin Code" << "| " << left << setw(35) << "Client Name" << "| " << left << setw(16) << "Phone" << "| " << left << setw(11) << "Balance";
    cout << "\n_______________________________________________________________________________________________________\n";

    if (vClients.size() == 0){
        cout << "\t\t\t\tNo Clients Available In the System!";
}
else {
        for (sClient& C : vClients) {
            PrintAllClients(C);
        }
    }
    

    cout << "\n_______________________________________________________________________________________________________\n";
    cout << "Press Any key to go back to main menu....";
    system("pause>0");
  

}

bool FindAccountByAccountNumber(string AccountNumber , vector<sClient> vClients) {
    for (sClient& C : vClients) {
        if (AccountNumber == C.AccNum) {
            PrintClientCard(C);
            return true;
        }
    }
    return false;
}

void ShowDeposit() {
    cout << "\n----------------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n----------------------------------------\n\n";
    
    vector<sClient> vClients = LoadDataFromFile(FileName);
    string AccountNumber = GetAccountNumber();

    while (!FindAccountByAccountNumber(AccountNumber, vClients)) {
        cout << "Client with [" << AccountNumber << "] does not Exist.";
        AccountNumber = GetAccountNumber();
    }
    double DepositAmount = 0;
    double Totalbalance = 0;
    for (sClient& C : vClients) {
        if (AccountNumber == C.AccNum) {
            cout << "Please enter The Deposit Amount?";
            cin >> DepositAmount;
            Totalbalance = C.AccBalance + DepositAmount;
            C.AccBalance = Totalbalance;
        }
    }
    
    char answer;
    cout << "Are you sure you want to delete this client? y/n ?";
    cin >> answer;

    if (toupper(answer) == 'Y') {
        SaveClientsToFile(FileName, vClients);
        cout << "Done Successfully. your balance is " << Totalbalance;
    }
    cout << "\n\nPress any key to go back to the Transactions Menu...";
    system("pause>0");
    system("cls");
    
}

void CalculateAllBalances() {
    
}
void ShowTotalBalances() {
    vector<sClient> vClients;
    vClients = LoadDataFromFile(FileName);
    int TotalBalance = 0;
    cout << "\n\t\t\t\t\tClients List (" << vClients.size() << ") Client(s)";
    cout << "\n_______________________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(17) << "Account Number" << "| " << left << setw(12) << "Pin Code" << "| " << left << setw(35) << "Client Name" << "| " << left << setw(16) << "Phone" << "| " << left << setw(11) << "Balance";
    cout << "\n_______________________________________________________________________________________________________\n";

    if (vClients.size() == 0) {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else {
        for (sClient& C : vClients) {
            PrintAllClients(C);
            TotalBalance = C.AccBalance + TotalBalance;
        }
        cout << "Total Balances = " << TotalBalance;
    }

    cout << "\n\nPress any key to go back to the Transactions Menu...";
    system("pause>0");
    system("cls");
 
}

void ChooseTransactionPage(short PageNumber) {
    switch (PageNumber) {
    case ePageTransactions::Deposit:
        system("cls");
        ShowDeposit();
        TransactionsMenuScreen();
        break;
        /*case ePageTransactions::Withdraw:
            system("cls");
            ShowWithdraw();
            start();
            break;*/
        case ePageTransactions::TotalBalances:
            system("cls");
            ShowTotalBalances();
            start();
            break;
       /* case ePageTransactions::MainMenu:
            system("cls");
            start();
            break;*/
    default:
        ShowClientList();
        break;
    }
}
void TransactionsMenuScreen() {
    cout << "=================================\n";
    cout << "\t Transactions Menu Screen \t\t\n";
    cout << "=================================\n";
    cout << "\t [1] Deposit. \n"; // +
    cout << "\t [2] Withdraw. \n"; // -
    cout << "\t [3] Total Balances. \n"; // all clients
    cout << "\t [4] Main Menu. \n";
    cout << "=================================\n";
    cout << "Choose what do you want to do? [1 to 4]?";

    short PageNumber = 0;
    cin >> PageNumber;
    while (PageNumber > 0 && PageNumber > 8) {
        cout << "Failed!. Number is not exist. \n Try again To choose the correct number [1 to 4]? ";
        cin >> PageNumber;
    }
    system("cls");
    ChooseTransactionPage(PageNumber);


}




void WhichPageIsChosen(short PageNumber) {

    switch (PageNumber) {
    case ePageContent::Show:
        system("cls");
        ShowClientList();
        start();
        break;
    case ePageContent::Add:
        system("cls");
        AddClient();
        start();
        break;
    case ePageContent::Delete:
        system("cls");
        DeleteClient();
        start();
        break;
    case ePageContent::Update:
        system("cls");
        UpdateClientInfo();
        start();
        break;
    case ePageContent::Find:
        system("cls");
        FindClient();
        start();
        break;
    case ePageContent::Exit:
        system("cls");
        ExitMenu();
        break;
    case ePageContent::Transactions:
        system("cls");
        TransactionsMenuScreen();
        break;
    default:
        ShowClientList();
        break;
    }



}



void start() {
    short PageNumber = 0;
    PrintMainScreen();
    cin >> PageNumber;
    while (PageNumber > 0 && PageNumber > 8) {
        cout << "Failed!. Number is not exist. \n Try again To choose the correct number [1 to 6]? ";
        cin >> PageNumber;
    }
    system("cls");
    WhichPageIsChosen(PageNumber);


}

int main()
{
    start();

    return 0;
}