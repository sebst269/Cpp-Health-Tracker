
#include <iostream>
#include <sqlite3.h>
#include <string>

void createTable(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS habits ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "date TEXT NOT NULL,"
                      "water_oz INTEGER,"
                      "gym INTEGER,"
                      "bp TEXT,"
                      "notes TEXT);";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        std::cerr << "Error creating table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void addEntry(sqlite3* db) {
    std::string date, bp, notes;
    int water, gym;

    std::cin.ignore();
    std::cout << "Enter date (YYYY-MM-DD): ";
    getline(std::cin, date);
    std::cout << "Water intake (oz): ";
    std::cin >> water;
    std::cout << "Went to gym? (1 = yes, 0 = no): ";
    std::cin >> gym;
    std::cin.ignore();
    std::cout << "Blood pressure (optional): ";
    getline(std::cin, bp);
    std::cout << "Notes (optional): ";
    getline(std::cin, notes);

    std::string sql = "INSERT INTO habits (date, water_oz, gym, bp, notes) VALUES ('" +
                      date + "', " + std::to_string(water) + ", " + std::to_string(gym) + ", '" +
                      bp + "', '" + notes + "');";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg) != SQLITE_OK) {
        std::cerr << "Error inserting data: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Entry added successfully.\n";
    }
}

void viewEntries(sqlite3* db) {
    const char* sql = "SELECT date, water_oz, gym, bp, notes FROM habits ORDER BY date DESC;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        std::cout << "\n--- Health Habit Entries ---\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            int water = sqlite3_column_int(stmt, 1);
            int gym = sqlite3_column_int(stmt, 2);
            std::string bp = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            std::string notes = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

            std::cout << "Date: " << date << "\n"
                      << "  Water: " << water << " oz\n"
                      << "  Gym: " << (gym ? "Yes" : "No") << "\n"
                      << "  BP: " << (bp.empty() ? "N/A" : bp) << "\n"
                      << "  Notes: " << notes << "\n\n";
        }
        std::cout << "------------------------------\n";
    }
    sqlite3_finalize(stmt);
}

int main() {
    sqlite3* db;
    if (sqlite3_open("health_tracker.db", &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    createTable(db);

    int choice;
    do {
        std::cout << "\n1. Add Entry\n2. View Entries\n3. Exit\nChoose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addEntry(db);
                break;
            case 2:
                viewEntries(db);
                break;
        }
    } while (choice != 3);

    sqlite3_close(db);
    return 0;
}
