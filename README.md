# Household Expense Tracker

A lightweight **command-line expense tracker written in C**, developed as a programming coursework project. It demonstrates dynamic memory allocation and a **doubly linked list** while providing basic tools for recording and reviewing household expenses.

## Features

- Initialize an empty expense list.
- Add an expense to the beginning or end of the list.
- Delete an expense by its position.
- Display all recorded expenses.
- Calculate total spending and totals per category.
- Filter expenses by category.
- Check whether the list is empty.

Each expense has an **amount**, **category**, **day and month**, and a short **description**. The four categories are Food, Utilities, Entertainment, and Other (displayed in Croatian in the current console interface).

## Built with

- **C** (standard library only)
- Dynamically allocated nodes with `next` and `prev` pointers
- A terminal-based interactive menu

## Usage

This is an interactive console application. Once the C source code has been built and the application is launched, it displays a menu with options **1–9**.

Start by choosing **1** to initialize the expense list. Use **2** or **3** to add expenses, **4** to delete an expense, **5** to display recorded expenses, **7** to view spending totals, and **8** to filter expenses by category. Choose **9** to exit.

When adding an expense, enter its amount, category number (1–4), and date in `DD.MM.` format, followed by a description. The menu and prompts are in Croatian.

## Project structure

```text
.
├── src/
│   └── linked_list.c   # Expense operations, menu and main function
├── include/
│   └── linked_list.h   # Data structures and function declarations
├── .gitignore
└── README.md           # Documentation
```

## How it works

`struct trosak` represents an expense and holds pointers to its previous and next elements. `struct lista_troskova` maintains the list's `head`, `tail`, and item count. New nodes are allocated dynamically; deleted nodes and the remaining list are freed when the program exits.

The project covers fundamental linked-list operations and traversal-based aggregation. It does **not** implement a database or save expenses to disk; entries are stored in memory only for the current session.

## Notes and limitations

- The console prompts and category names are currently in **Croatian**.
- Dates contain a day and month, but no year; calendar-valid dates are not fully checked.
- Expenses are stored using `float`, which is sufficient for this educational example but is not ideal for production financial calculations.
- This version includes small reliability fixes to the original coursework source (head-node back-linking, safer text copying, input checks, and memory cleanup).

## Possible improvements

Persisting expenses to a file, adding monthly summaries, translating the console interface, and using integer minor currency units would be natural next steps.
