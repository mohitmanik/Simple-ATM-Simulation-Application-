
#include <iostream>
#include <vector>
using namespace std;

class Approval {
    int did;
    int dpin;

public:
    int uid;
    int upin;

    void default_data(int a, int b) {
        did = a;
        dpin = b;
    }

    void udata(void) {
        int id;
        int pin;
        cout << "Enter your id: ";
        cin >> id;
        cout << "Enter your pin: ";
        cin >> pin;

        uid = id;
        upin = pin;
    }

    int check(void) {
        if (did == uid && dpin == upin) {
            return 1;
        } else {
            return 0;
        }
    }
};

class Record {
private:
    string transaction_type;
    double transaction_amount;

public:
    Record(string t, double a) : transaction_type(t), transaction_amount(a) {}

    string GetTransactionType() const {
        return transaction_type;
    }

    double GetTransactionAmount() const {
        return transaction_amount;
    }
};

class Transaction {
    vector<Record> records;

public:
    void AddTransaction(string transaction_type, double transaction_amount) {
        Record record(transaction_type, transaction_amount);
        records.push_back(record);
    }

    void Withdraw(void) {
        double transaction_amount;
        cout << "Enter transaction amount: ";
        cin >> transaction_amount;
        if (transaction_amount > 0) {
            AddTransaction("Withdraw", -transaction_amount);
            cout << " You have successfully withdrew transaction amount: " << transaction_amount << endl;
        } else {
            cout << "Invalid transaction amount" << endl;
        }
    }

    void Deposit(void) {
        double transaction_amount;
        cout << "Enter transaction amount: ";
        cin >> transaction_amount;
        if (transaction_amount > 0) {
            AddTransaction("Deposit", transaction_amount);
            cout << " You have successfully deposited transaction amount: " << transaction_amount << endl;
        } else {
            cout << "Invalid transaction amount" << endl;
        }
    }

    void Transfer(void) {
        double transaction_amount;
        cout << "Enter transaction amount: ";
        cin >> transaction_amount;
        if (transaction_amount > 0) {
            AddTransaction("Transfer", -transaction_amount);
            cout << " You have successfully transferred transaction amount: " << transaction_amount << endl;
        } else {
            cout << "Invalid transaction amount" << endl;
        }
    }

    void Quit() {
        cout << "Thank you for using our services!" << endl;
        exit(0);
    }

    const vector<Record>& GetTransactionRecords() const {
        return records;
    }
};

class TransactionHistory {
public:
    void DisplayTransactionHistory(const vector<Record>& records) const {
        if (records.empty()) {
            cout << "Transaction history is empty." << endl;
        } else {
            cout << "Transaction History:" << endl;
            for (const Record& record : records) {
                cout << "Transaction Type: " << record.GetTransactionType() << ", Transaction Amount: " << record.GetTransactionAmount() << endl;
            }
        }
    }
};

class Option {
public:
    void Menu() {
        int select;
        Transaction transaction;
        TransactionHistory transactionHistory;

        do {
            cout << "Options:"<<endl;
            cout << "1. Deposit"<<endl;
            cout << "2. Withdraw"<<endl;
            cout << "3. Transfer"<<endl;
            cout << "4. Transaction History"<<endl;
            cout << "5. Quit"<<endl;
            cout << "Selec your transaction : ";
            cin >> select;

            switch (select) {
                case 1:
                    transaction.Deposit();
                    break;
                case 2:
                    transaction.Withdraw();
                    break;
                case 3:
                    transaction.Transfer();
                    break;
                case 4:
                    transactionHistory.DisplayTransactionHistory(transaction.GetTransactionRecords());
                    break;
                case 5:
                    transaction.Quit();
                    break;
                default:
                    cout << " Please try again." << endl;
                    break;
            }
        } while (select != 5);
    }
};

int main() {
    int default_id = 8888;
    int default_pin = 2222;

    cout << "--------WELCOME TO ATM INTERFACE------" << endl;
    Approval user;
    user.default_data(default_id, default_pin);
    int count = 1;
    for (int i = 0; i < 3; i++) {
        user.udata();
        if (user.check() == 1) {
            cout << "NOW YOU CAN CONTINUE YOUR TRANSACTIONs!" << endl;
            break;
        } else {
            user.check();
            cout << "WRONG PIN OR ID" << endl;
            count++;
            if (count < 3) {
                cout << "Try again!" << endl;
            }
        }
    }
    if (count == 4) {
        cout << "You have entered a wrong pin too many times." << endl;
        exit(0);
    }

    Option choose;
    choose.Menu();

    return 0;
}