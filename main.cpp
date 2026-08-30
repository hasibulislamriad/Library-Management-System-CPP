#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

class Book {
public:
    int id;
    string name, author, category, publication;
    bool issued;

    Book() : id(0), issued(false) {}
    Book(int id, string name, string author, string category, string publication, bool issued = false)
        : id(id), name(name), author(author), category(category), publication(publication), issued(issued) {}
};

class Library {
private:
    vector<Book> books;
    const string filename = "books.txt";

    bool idExists(int id) const {
        for (const auto& book : books) if (book.id == id) return true;
        return false;
    }

public:
    Library() { loadBooks(); }

    void loadBooks() {
        books.clear();
        ifstream file(filename);
        if (!file) return;

        Book book;
        int status;
        while (file >> book.id) {
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(file, book.name);
            getline(file, book.author);
            getline(file, book.category);
            getline(file, book.publication);
            file >> status;
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            book.issued = (status != 0);
            books.push_back(book);
        }
    }

    void saveBooks() const {
        ofstream file(filename);
        for (const auto& book : books) {
            file << book.id << '\n'
                 << book.name << '\n'
                 << book.author << '\n'
                 << book.category << '\n'
                 << book.publication << '\n'
                 << book.issued << '\n';
        }
    }

    void addBook() {
        int id;
        string name, author, category, publication;
        cout << "\n========== ADD BOOK ==========\nBook ID: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (idExists(id)) { cout << "Book ID already exists!\n"; return; }
        cout << "Book Name: "; getline(cin, name);
        cout << "Author Name: "; getline(cin, author);
        cout << "Category: "; getline(cin, category);
        cout << "Publication: "; getline(cin, publication);

        books.emplace_back(id, name, author, category, publication);
        saveBooks();
        cout << "Book added successfully!\n";
    }

    void showBooks() const {
        cout << "\n========================== ALL BOOKS ==========================\n";
        if (books.empty()) { cout << "No books available.\n"; return; }
        cout << left << setw(8) << "ID" << setw(25) << "Book Name" << setw(20) << "Author"
             << setw(18) << "Category" << setw(18) << "Publication" << "Status\n";
        cout << string(105, '-') << '\n';
        for (const auto& book : books) {
            cout << left << setw(8) << book.id << setw(25) << book.name << setw(20) << book.author
                 << setw(18) << book.category << setw(18) << book.publication
                 << (book.issued ? "Issued" : "Available") << '\n';
        }
    }

    void searchBook() const {
        int id;
        cout << "\n========== SEARCH BOOK ==========\nBook ID: ";
        cin >> id;
        for (const auto& book : books) {
            if (book.id == id) {
                cout << "\nBook Found!\n-----------------------------\n"
                     << "Book ID       : " << book.id << '\n'
                     << "Book Name     : " << book.name << '\n'
                     << "Author        : " << book.author << '\n'
                     << "Category      : " << book.category << '\n'
                     << "Publication   : " << book.publication << '\n'
                     << "Status        : " << (book.issued ? "Issued" : "Available") << '\n';
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void issueBook() {
        int id;
        cout << "\n========== ISSUE BOOK ==========\nBook ID: ";
        cin >> id;
        for (auto& book : books) {
            if (book.id == id) {
                if (book.issued) { cout << "This book is already issued!\n"; return; }
                book.issued = true; saveBooks(); cout << "Book issued successfully!\n"; return;
            }
        }
        cout << "Book not found!\n";
    }

    void returnBook() {
        int id;
        cout << "\n========== RETURN BOOK ==========\nBook ID: ";
        cin >> id;
        for (auto& book : books) {
            if (book.id == id) {
                if (!book.issued) { cout << "This book is already available!\n"; return; }
                book.issued = false; saveBooks(); cout << "Book returned successfully!\n"; return;
            }
        }
        cout << "Book not found!\n";
    }

    void updateBook() {
        int id;
        cout << "\n========== UPDATE BOOK ==========\nBook ID: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (auto& book : books) {
            if (book.id == id) {
                cout << "New Book Name: "; getline(cin, book.name);
                cout << "New Author Name: "; getline(cin, book.author);
                cout << "New Category: "; getline(cin, book.category);
                cout << "New Publication: "; getline(cin, book.publication);
                saveBooks(); cout << "Book updated successfully!\n"; return;
            }
        }
        cout << "Book not found!\n";
    }

    void deleteBook() {
        int id;
        cout << "\n========== DELETE BOOK ==========\nBook ID: ";
        cin >> id;
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->id == id) {
                if (it->issued) { cout << "Cannot delete an issued book!\n"; return; }
                books.erase(it); saveBooks(); cout << "Book deleted successfully!\n"; return;
            }
        }
        cout << "Book not found!\n";
    }

    void statistics() const {
        int issued = 0;
        for (const auto& book : books) if (book.issued) ++issued;
        cout << "\n========== LIBRARY STATISTICS ==========\n"
             << "Total Books     : " << books.size() << '\n'
             << "Available Books : " << books.size() - issued << '\n'
             << "Issued Books    : " << issued << '\n';
    }
};

int main() {
    Library library;
    int choice;

    while (true) {
        cout << "\n=============================================\n"
             << "       LIBRARY MANAGEMENT SYSTEM\n"
             << "=============================================\n"
             << "1. Add Book\n2. Show All Books\n3. Search Book\n"
             << "4. Issue Book\n5. Return Book\n6. Update Book\n"
             << "7. Delete Book\n8. Library Statistics\n9. Exit\n"
             << "=============================================\nChoice: ";

        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: library.addBook(); break;
            case 2: library.showBooks(); break;
            case 3: library.searchBook(); break;
            case 4: library.issueBook(); break;
            case 5: library.returnBook(); break;
            case 6: library.updateBook(); break;
            case 7: library.deleteBook(); break;
            case 8: library.statistics(); break;
            case 9: cout << "Thank you for using Library Management System!\n"; return 0;
            default: cout << "Invalid choice! Please try again.\n";
        }
    }
}
