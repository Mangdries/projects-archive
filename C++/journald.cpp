#include <iostream>
#include <limits>
#include <vector>

typedef struct Journal {
public:
    struct Entry {
    std::string title{};
    std::vector<std::string> text{};
    };

    std::vector<Entry> entry{};
    std::string title = "Cli Journal!";
} Journal;

typedef enum Action {
    View = 1,
    Add = 2,
    Search = 3,
    Delete = 4,
    Edit = 5,
    EditTitle = 6,
} Action;

std::string spaces(int amount) {
    return std::string(amount, ' ');
}

//Prints title of a screen
void printTitle(std::string title) {
    std::string bar = "===================================\n";
    int spaceAmount{};
    if((spaceAmount = (int)(((bar.length() - 1) - title.length()) /2)) %2 != 0) {
        spaceAmount++;
    }
    std::cout << bar;
    std::cout << spaces(spaceAmount) << title << "\n";
    std::cout << bar;
}

void printEnd() {
    std::cout << "-----------------------------------\n";
    std::cout << "Type \'b\' to go back to the main menu\n";
    std::cout << "===================================\n";
}

void printEntry(Journal& journal, int entry) {
    entry--;
    std::cout << "-----------------------------------\n";
    std::cout << "Title: " << journal.entry[entry].title << "\n\n";
    for(int line = 0; line < (int)journal.entry[entry].text.size(); ++line) {
        std::cout << line + 1 << ". " << journal.entry[entry].text[line] << "\n";
    }
}

int menu(Journal j) {
    printTitle(j.title);
    std::cout << "1. View Entries\n";
    std::cout << "2. Add New Entry\n";
    std::cout << "3. Search Entries\n";
    std::cout << "4. Delete Entry\n";
    std::cout << "5. Edit Title\n";
    std::cout << "6. Exit\n";
    std::cout << "===================================\n";
    std::cout << "Please select an option (1-6):\n";
    std::cout << "> ";
    
    int userOption{};

    do {
    std::cin >> userOption;
    if(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    } while(userOption <= 0 && userOption >= 6); //Number in range

    return userOption;
}

void viewEntries(Journal& journal) {
    bool ret = false;

    if(journal.entry.empty()) {
        std::cout << "No available entries!\n";
        return;
    }

    while(!ret) {
        printTitle("Journal Entries");
        
        for(int entry = 0; entry < journal.entry.size(); ++entry) {
            std::cout << "[" << entry + 1 << "]: " << journal.entry[entry].title << "\n";
            std::cout << "-------------------------------------------------\n";
        }

        std::cout << "Which entry to view (0 to return)\n ";
        std::cout << "> ";

        int userOption{};

        do {
        std::cin >> userOption;
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if(userOption == 0) {
            return;
        }

        } while(userOption < 0 && userOption > (int)journal.entry.size()); //Number in range

        std::cout << '\n';

        printEntry(journal, userOption);
        std::cout << "-------------------------------------------------\n";
    }
}

void addEntry(Journal& journal) {
    std::cin.ignore();
    printTitle("New Entry");
    //std::cout << "Journal Entry Size: " << journal.entry.size() << '\n';
    std::cout << "Enter title:\n";
    std::cout << "> ";
    journal.entry.push_back({});
    std::getline(std::cin, journal.entry[journal.entry.size() - 1].title);
    //std::cin >> journal.entry[journal.entry.size() - 1].title;
    std::cout << "Set title to: " << journal.entry[journal.entry.size() - 1].title << std::endl;

    std::string input{};
    while(true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if(input == "b" || input == "B") {
            break;
        } else if(input == "u" || input == "U") {
            if(journal.entry[journal.entry.size() - 1].text.size() > 0) {
                journal.entry[journal.entry.size() - 1].text.pop_back();
                std::cout << "Deleted last line!\n";
            }
        } else {
            journal.entry[journal.entry.size() - 1].text.push_back(input);
        }
    };

    printEnd();
}

void searchEntries(Journal& journal) {
    if(journal.entry.empty()) {
        std::cout << "No entries to search!\n";
        return;
    }

    printTitle("Search Entries");
    std::cin.ignore();

    std::cout << "Keywords > ";
    std::string userSearch;
    
    std::getline(std::cin, userSearch);
    
    bool found = false;

    for(int entry = 0; entry < journal.entry.size(); ++entry) {
        for(int line = 0; line < journal.entry.size(); ++line) {
            if(userSearch == journal.entry[entry].text.at(line)) {
                std::cout << "Found Text in entry: " << journal.entry[entry].title << "Line number: " << journal.entry[entry].text[line] << "\n";
                found = true;
            }
        }
    }
    
    if(!found) {
        std::cout << "Couldn't find anything :(\n";
    }

    printEnd();
}

void deleteEntry(Journal& journal) {
    bool ret = false;
    while(!ret) {
        printTitle("Delete Entry");
        if(journal.entry.empty()) {
            std::cout << "No available entries to delete!\n";
            return;
        }

        for(int entry = 0; entry < journal.entry.size(); ++entry) {
            std::cout << "[" << entry + 1 << "]: " << journal.entry[entry].title << "\n";
            std::cout << "-------------------------------------------------\n";
        }

        std::cout << "Which entry would you like to delete (0 to return)\n";
        std::cout << "> ";
        
        int userOption{};

        do {
        std::cin >> userOption;
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if(userOption == 0) {
            return;
        }
        } while(userOption < 0 && userOption > (int)journal.entry.size()); //Number in range

        userOption--; //To set the user option to the actual location
        journal.entry.erase(journal.entry.begin() + userOption);
        std::cout << "Deleted entry: " << userOption;

        printEnd();
    }
}

void editTitle(Journal& journal) {
    printTitle("Edit Title");
    std::cout << "Enter the title you want to change the title to (2- 10 characters):\n";
    std::cout << ">";

    std::string userInput{};
    Start:
    do {
    std::cin >> userInput;
    } while(userInput.length() < 2);

    //Idk why this was needed insted of an easier solution lmao
    if(userInput.length() > 10) 
        goto Start;

    journal.title = userInput;
}

int main(int argc, char** argv) {
    Journal journal{};
    bool running = true;
    while(running) {
        switch(menu(journal)) {
            case View:
                viewEntries(journal);
                break;
            case Add:
                addEntry(journal);
                break;
            case Search:
                searchEntries(journal);
                break;
            case Delete:
                deleteEntry(journal);
                break;
            case Edit:
                editTitle(journal);
                break;
            case EditTitle:
                running = false;
                break;
            default:
                break;
        }
    }
}
