# Bank Management System

This is a simple C++ console application for managing bank accounts. The system allows users to create new accounts, deposit and withdraw money, check balance details, list all account holders, modify account information, and close accounts.

## Features

1. **Create New Account**
   - Users can create a new account by providing the account ID, account holder's name, account type (Savings/Current), and initial deposit amount.

2. **Deposit Amount**
   - Users can deposit money into an existing account by providing the account ID and deposit amount.

3. **Withdraw Amount**
   - Users can withdraw money from an existing account by providing the account ID and withdrawal amount. The system ensures that the minimum balance is maintained.

4. **Balance Enquiry**
   - Users can check the balance and details of an existing account by providing the account ID.

5. **List All Account Holders**
   - Users can view a list of all account holders, including their account ID, name, account type, and balance.

6. **Modify Account**
   - Users can modify the details of an existing account, such as the account holder's name, account type, and balance.

7. **Close Account**
   - Users can close an existing account by providing the account ID. The account will be deleted from the system.

8. **Exit**
   - Users can exit the application.

## File Structure

- `main.cpp`: Contains the main program and all the functions related to account management.
- `account.dat`: Binary file used to store account details.

## Getting Started

### Prerequisites

To run this application, you need to have a C++ compiler installed on your system.

### Running the Application

1. Compile the C++ code using the following command:

   ```bash
   g++ main.cpp -o bank_system
