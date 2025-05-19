#include <iostream>
#include <string>
using namespace std;

// Class for Book Node
class Book {
public:
    int id;
    string title, author;
    bool isIssued;
    Book* next;

    Book(int bookId, string bookTitle, string bookAuthor) {
        id = bookId;
        title = bookTitle;
        author = bookAuthor;
        isIssued = false;
        next = nullptr;
    }
};

// Class for Book Issue Queue Node
class IssueNode {
public:
    int bookId;
    string userName;
    IssueNode* next;

    IssueNode(int id, string user) {
        bookId = id;
        userName = user;
        next = nullptr;
    }
};

// Book Issue Queue using Linked List
class IssueQueue {
    IssueNode* front;
    IssueNode* rear;

public:
    IssueQueue() {
        front = rear = nullptr;
    }

    void enqueue(int bookId, string userName) {
        IssueNode* newNode = new IssueNode(bookId, userName);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Book issued to " << userName << " successfully.\n";
    }

    void displayIssuedBooks() {
        if (!front) {
            cout << "No books currently issued.\n";
            return;
        }
        IssueNode* temp = front;
        cout << "\nIssued Books:\n";
        while (temp) {
            cout << "Book ID: " << temp->bookId << ", Issued to: " << temp->userName << "\n";
            temp = temp->next;
        }
    }
};

// Library class managing book operations
class Library {
public:
    Book* head;
    IssueQueue issueQueue;

    Library() {
        head = nullptr;
    }

    void addBook() {
        int id;
        string title, author;
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);

        Book* newBook = new Book(id, title, author);
        newBook->next = head;
        head = newBook;

        cout << "Book added successfully.\n";
    }

    void displayBooks() {
        if (!head) {
            cout << "Library is empty.\n";
            return;
        }
        Book* temp = head;
        cout << "\nLibrary Books:\n";
        while (temp) {
            cout << "ID: " << temp->id
                 << ", Title: " << temp->title
                 << ", Author: " << temp->author
                 << ", Status: " << (temp->isIssued ? "Issued" : "Available") << "\n";
            temp = temp->next;
        }
    }

    void searchBook() {
        int id;
        cout << "Enter Book ID to search: ";
        cin >> id;
        Book* temp = head;
        while (temp) {
            if (temp->id == id) {
                cout << "Found - Title: " << temp->title
                     << ", Author: " << temp->author
                     << ", Status: " << (temp->isIssued ? "Issued" : "Available") << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Book not found.\n";
    }

    void issueBook() {
        int id;
        string user;
        cout << "Enter Book ID to issue: ";
        cin >> id;
        cin.ignore();
        cout << "Enter User Name: ";
        getline(cin, user);

        Book* temp = head;
        while (temp) {
            if (temp->id == id) {
                if (temp->isIssued) {
                    cout << "Book already issued.\n";
                    return;
                }
                temp->isIssued = true;
                issueQueue.enqueue(id, user);
                return;
            }
            temp = temp->next;
        }
        cout << "Book not found.\n";
    }

    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;

        Book* temp = head;
        while (temp) {
            if (temp->id == id) {
                if (!temp->isIssued) {
                    cout << "Book is already available.\n";
                    return;
                }
                temp->isIssued = false;
                cout << "Book returned successfully.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Book not found.\n";
    }

    void deleteBook() {
        int id;
        cout << "Enter Book ID to delete: ";
        cin >> id;

        Book* temp = head;
        Book* prev = nullptr;

        while (temp && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (!temp) {
            cout << "Book not found.\n";
            return;
        }

        if (!prev)
            head = temp->next;
        else
            prev->next = temp->next;

        delete temp;
        cout << "Book deleted successfully.\n";
    }

    void viewIssuedBooks() {
        issueQueue.displayIssuedBooks();
    }
};

// Main menu
int main() {
    Library lib;

    // Add 10 predefined books
    string titles[10] = {
        "The Great Gatsby", "To Kill a Mockingbird", "1984", "Pride and Prejudice",
        "The Catcher in the Rye", "The Hobbit", "Jane Eyre", "Animal Farm",
        "The Lord of the Rings", "The Alchemist"
    };

    string authors[10] = {
        "F. Scott Fitzgerald", "Harper Lee", "George Orwell", "Jane Austen",
        "J.D. Salinger", "J.R.R. Tolkien", "Charlotte Bronte", "George Orwell",
        "J.R.R. Tolkien", "Paulo Coelho"
    };

    for (int i = 0; i < 10; i++) {
        Book* newBook = new Book(i + 1, titles[i], authors[i]);
        newBook->next = lib.head;
        lib.head = newBook;
    }

    int choice;

    do {
        cout << "\n====== Smart Library Management System ======\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Delete Book\n";
        cout << "7. View Issued Books\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.displayBooks(); break;
            case 3: lib.searchBook(); break;
            case 4: lib.issueBook(); break;
            case 5: lib.returnBook(); break;
            case 6: lib.deleteBook(); break;
            case 7: lib.viewIssuedBooks(); break;
            case 8: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    return 0;
}
