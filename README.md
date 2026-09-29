# Bank & ATM Management System

A modular C++ console solution featuring two fully integrated applications: an **Admin Bank Console** and a **Client ATM Interface**. Both applications operate on a shared persistent database with real-time balance synchronization.

## Key Features

### Bank Management (Admin Panel)
- **Full Client CRUD:** Display, add, search, update, and delete client records with account validation.
- **Transaction Controls:** Perform balance deposits, withdrawals, and monitor total bank assets.

### ATM System (Client Interface)
- **Authentication:** Secure login using Account Number and PIN.
- **Withdrawal Modes:** Quick withdraw (preset amounts) and normal withdraw (multiples of 5).
- **Account Services:** Deposit funds and check real-time account balances.

## Technical Highlights
- **Shared File Database:** Centralized data persistence using `Clients.txt`.
- **Data Synchronization:** Transactions made via the ATM update the central record instantly for the Bank application.
- **Clean Architecture:** Divided into two distinct C++ projects within a single Visual Studio Solution.

## Tech Stack
- **Language:** C++
- **Design:** Procedural Programming, Custom Structs, Enums, and Vector-based data handling
