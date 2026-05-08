#include <iostream>
using namespace std;

int main() {
    int pin, attempts = 0;
    int correctPIN = 1234;
    double balance = 1000;   // initial balance
    int choice;
    double amount;
    string lastTransaction = "None";
    double lastAmount = 0;
    int balanceUpdateFlag = 0; // For prefix/postfix demo


    // Welcome Screen

    cout << "==============================" << endl;
    cout << "   Welcome to Simple ATM" << endl;
    cout << "==============================" << endl;

    // PIN Verification (max 3 attempts)
    while (attempts < 3) {
        cout << "Enter your PIN: ";
        cin >> pin;

        if (pin == correctPIN) {
            cout << "PIN verified successfully!" << endl;

            // Main Menu loop
            do {
                cout << "===== Main Menu =====" << endl;
                cout << "1. Check Balance" << endl;
                cout << "2. Deposit Money" << endl;
                cout << "3. Withdraw Money" << endl;
                cout << "4. Mini Statement (Prefix/Postfix Demo)" << endl;
                cout << "5. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                // Operations 

                switch (choice) {
                    case 1:
                        cout << "Current Balance: " << balance << endl;
                        break;

                    case 2:
                        cout << "Enter amount to deposit: ";
                        cin >> amount;
                        if (balance + amount < balance) { // overflow check
                            cout << "Error: Balance overflow!" << endl;
                        } else {
                            balance += amount;
                            cout << "Deposited: " << amount << endl;
                            cout << "New Balance: " << balance << endl;
                            lastTransaction = "Deposit";
                            lastAmount = amount;
                            balanceUpdateFlag = 1;
                        }
                        break;

                    case 3:
                        cout << "Enter amount to withdraw: ";
                        cin >> amount;
                        if (amount > balance) {
                            cout << "Error: Insufficient funds!" << endl;
                        } else {
                            balance -= amount;
                            cout << "Withdrawn: " << amount << endl;
                            cout << "New Balance: " << balance << endl;
                            lastTransaction = "Withdraw";
                            lastAmount = amount;
                            balanceUpdateFlag = 1;
                        }
                        break;

                    case 4:
                        cout << "=== Mini Statement ===" << endl;
                        if (lastTransaction == "Deposit") {
                            cout << "Last Transaction: Deposit of " << lastAmount << endl;
                        } else if (lastTransaction == "Withdraw") {
                            cout << "Last Transaction: Withdrawal of " << lastAmount << endl;
                        } else {
                            cout << "No transactions yet." << endl;
                        }

                        // Demonstrate prefix/postfix
                        cout << "Balance Update Status (Demonstration):" << endl;
                        if (balanceUpdateFlag) {
                            // Postfix: check old value, then update
                            if (balanceUpdateFlag--) {
                                cout << "  - Status was TRUE (1), now set to FALSE (0) using Postfix." << endl;
                            }
                        } else {
                            // Prefix: update first, then check
                            if (++balanceUpdateFlag) {
                                cout << "  - Status was FALSE (0), now set to TRUE (1) using Prefix." << endl;
                            }
                        }
                        break;

                    case 5:
                        cout << "Thank you for using the ATM. Goodbye!" << endl;
                        break;

                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
            } while (choice != 5);

            return 0;
        } else {
            attempts++;
            cout << "Incorrect PIN. Attempts left: " << 3 - attempts << endl;
        }
    }

    cout << "Too many incorrect attempts. ATM locked!" << endl;
    return 0;
}