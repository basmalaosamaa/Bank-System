# Bank Management System (C++)

A C++ Console Application that simulates a full Bank Management System. This project manages client data and banking transactions with persistent storage using text files. Built as a capstone project to demonstrate core C++ concepts and data handling.

## Features

* **Client Management (CRUD Operations):**
  * **Show Clients:** Display a formatted list of all existing bank clients.
  * **Add New Client:** Add new client records with unique account number validation.
  * **Find Client:** Quick search for a client by their account number.
  * **Update Client:** Modify client information (Name, Phone, Pin Code, Balance).
  * **Delete Client:** Remove clients safely with confirmation.
* **Transactions System:**
  * **Deposit:** Deposit money directly into client accounts.
  * **Withdraw:** *(In Progress)* Safe withdrawal operations.
  * **Total Balances:** View total assets held in the bank across all clients.
* **Data Persistence:** Automatically saves and loads client data to/from external text files (`Clients.text`) using a custom delimiter (`#//#`).

## Built With

* **Language:** C++
* **Standard Libraries:** `<vector>`, `<fstream>`, `<iomanip>`, `<string>`, `<iostream>`
* **Paradigm:** Procedural Programming, Structs, and Enums for clean control flow.

##  Status & Future Improvements
* [x] Core Client CRUD operations
* [x] File persistence & custom parsing
* [ ] Complete Withdrawal transaction module
* [ ] Add User/Admin Authentication system
* [ ] Refactor codebase into Object-Oriented Programming (OOP)
