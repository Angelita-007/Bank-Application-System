#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class BankAccount {
private:
    int accNo;
    char name[50];
    double balance;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void displayAccount() const {
        cout << "\nAccount No: " << accNo;
        cout << "\nName: " << name;
        cout << "\nBalance: " << balance << endl;
    }

    int getAccNo() const {
        return accNo;
    }

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= balance)
            balance -= amount;
        else
            cout << "Insufficient Balance!" << endl;
    }
};

void writeAccount() {
    BankAccount acc;
    ofstream outFile("bank.dat", ios::binary | ios::app);
    acc.createAccount();
    outFile.write(reinterpret_cast<char*>(&acc), sizeof(acc));
    outFile.close();
}

void displayAll() {
    BankAccount acc;
    ifstream inFile("bank.dat", ios::binary);
    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(acc))) {
        acc.displayAccount();
    }
    inFile.close();
}

void depositWithdraw(int accNo, int option) {
    BankAccount acc;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&acc), sizeof(acc)) && !found) {
        if (acc.getAccNo() == accNo) {
            acc.displayAccount();
            double amount;
            cout << "\nEnter amount: ";
            cin >> amount;

            if (option == 1)
                acc.deposit(amount);
            else
                acc.withdraw(amount);

            int pos = -1 * sizeof(acc);
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&acc), sizeof(acc));
            cout << "Transaction Successful!" << endl;
            found = true;
        }
    }

    file.close();

    if (!found)
        cout << "Account Not Found!" << endl;
}

void checkBalance(int accNo) {
    BankAccount acc;
    ifstream inFile("bank.dat", ios::binary);
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(acc))) {
        if (acc.getAccNo() == accNo) {
            acc.displayAccount();
            found = true;
        }
    }

    inFile.close();

    if (!found)
        cout << "Account Not Found!" << endl;
}

int main() {
    int choice;
    do {
        cout << "\n\n=== Bank Management System ===";
        cout << "\n1. Create Account";
        cout << "\n2. Display All Accounts";
        cout << "\n3. Deposit";
        cout << "\n4. Withdraw";
        cout << "\n5. Check Balance";
        cout << "\n6. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        int accNo;
        switch (choice) {
            case 1:
                writeAccount();
                break;
            case 2:
                displayAll();
                break;
            case 3:
                cout << "Enter Account No: ";
                cin >> accNo;
                depositWithdraw(accNo, 1);
                break;
            case 4:
                cout << "Enter Account No: ";
                cin >> accNo;
                depositWithdraw(accNo, 2);
                break;
            case 5:
                cout << "Enter Account No: ";
                cin >> accNo;
                checkBalance(accNo);
                break;
        }
    } while (choice != 6);

    return 0;
}
