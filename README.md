# Cpp-Health-Tracker

A command-line C++ application for tracking daily health habits such as water intake, gym activity, and blood pressure.  
Entries are stored in a local SQLite database and can be viewed in reverse chronological order.

## Features

- Add daily health entries with:
  - Date
  - Water intake (oz)
  - Gym attendance (yes/no)
  - Blood pressure (optional)
  - Notes (optional)
- View all logged entries with clean formatting
- Data stored persistently in a local SQLite database (`health_tracker.db`)
- Simple menu-driven CLI interface

## Technologies Used

- C++
- SQLite (`sqlite3` C API)

## Getting Started

### Prerequisites

- `g++` compiler
- SQLite development libraries (`libsqlite3-dev` or equivalent)

### Compilation

```bash
g++ main.cpp -o health_tracker -lsqlite3
```

### Running the App

```bash
./health_tracker
```

### Example Usage

```
1. Add Entry
2. View Entries
3. Exit
Choose an option: 1
Enter date (YYYY-MM-DD): 2025-06-23
Water intake (oz): 80
Went to gym? (1 = yes, 0 = no): 1
Blood pressure (optional): 120/80
Notes (optional): Upper body workout

Entry added successfully.
```

```
--- Health Habit Entries ---
Date: 2025-06-23
  Water: 80 oz
  Gym: Yes
  BP: 120/80
  Notes: Upper body workout
```
