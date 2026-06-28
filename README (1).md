# 🏦 Bank Management System (C++)

A console-based Bank Management System built in C++, developed as part of **Course 7** on the [ProgrammingAdvices](https://programmingadvices.com) platform by **Dr. Mohammad Abu Hadhoud**.

This project applies everything learned through 50+ structured exercises in the course roadmap, combining string utilities, file handling, and structured data management into a single working application.

---

## 📋 Features

- **Client Management**
  - ➕ Add new client(s)
  - 📋 Show full client list (formatted table view)
  - 🔍 Find client by account number
  - ✏️ Update client information
  - 🗑️ Delete client (soft delete — safely marks records before saving)

- **Transactions**
  - 💰 Deposit balance
  - 💸 Withdraw balance
  - 📊 Show total balance across all clients

- **Data Persistence**
  - All client data is saved to and loaded from a local text file (`Clients.txt`)
  - Custom serialization (struct ↔ text line) using a configurable separator

---

## 🧠 Concepts Practiced

- Structures (`struct`) and arrays of structures
- `std::vector` for dynamic data storage
- File streams (`ifstream` / `ofstream` / `fstream`)
- String processing (split, trim, join, replace, case conversion)
- Enums for menu options and transaction types
- Pass-by-reference vs pass-by-value
- Modular function design (Interface vs Logic separation)
- Soft-delete pattern for safe record removal
- Confirmation prompts before destructive actions (delete/update)

---

## 🗂️ Project Structure

```
BankSystem-CPP/
├── BankSystem.h      # Struct, enums, and function declarations
├── BankSystem.cpp    # Function implementations
├── main.cpp          # Entry point — starts the main menu
└── README.md
```

---

## ▶️ How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/<your-username>/BankSystem-CPP.git
   ```
2. Open the project in Visual Studio (or any C++ IDE).
3. Build and run `main.cpp`.
4. On first run, a `Clients.txt` file will be created automatically to store client data.

---

## 📸 Demo

*(Add screenshots of the Main Menu, Add Client, and Transactions screens here)*

---

## 🙏 Acknowledgment

This project was built while following the **Course 7 Roadmap** on ProgrammingAdvices, under the guidance of **Dr. Mohammad Abu Hadhoud**. Special thanks for the structured, problem-by-problem approach that made concepts like file handling and modular design click in practice.

---

## 📬 Contact

Feel free to reach out or check my other projects on GitHub.
