#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    int edition;
    int copies;
};
//Dynamic Array
void resize(Book *&books, int &capacity) {
    int newCapacity = capacity * 2;
    Book* temp = new Book[newCapacity];

    for (int i = 0; i < capacity; i++)
        temp[i] = books[i];

    delete[] books;
    books = temp;
    capacity = newCapacity;

    cout << "Array resized → new capacity = " << capacity << endl;
}
//Writing File Function
void writeToFile(Book* books, int count) {
    ofstream fout("Books1.txt");

    if (!fout) {
        cout << "Error saving file!\n";
        return;
    }
    for (int i = 0; i < count; i++) {
        fout << books[i].title << endl;
        fout << books[i].author << endl;
        fout << books[i].ISBN << endl;
        fout << books[i].edition << endl;
        fout << books[i].copies << endl;
        fout << "---" << endl;   // separator
    }

    fout.close();
    cout << "Books saved to file.\n";
}
//Reading from File Function
void readFromFile(Book *&books, int &count, int &capacity) {
    ifstream fin("Books1.txt");

    if (!fin) {
        cout << "No saved file found. Starting fresh.\n";
        return;
    }

    count = 0;
    string line;

    while (true) {
        Book temp;

        if (!getline(fin, temp.title)) break; 
        getline(fin, temp.author);
        getline(fin, temp.ISBN);
        fin >> temp.edition;
        fin >> temp.copies;
        fin.ignore(); // clear newline

        getline(fin, line); // read the "---" separator

        if (count == capacity)
            resize(books, capacity);

        books[count] = temp;
        count++;
    }

    fin.close();
    cout << "Books loaded from file.\n";
}

//Adding a Book Function
void addBook(Book *&books, int &count, int &capacity) {
    if (count == capacity)
        resize(books, capacity);

    cout << "Title: ";
    cin >> ws; //clear the new line in the buffer
    getline(cin, books[count].title);

    cout << "Author: ";
    getline(cin, books[count].author);

    cout << "ISBN: ";
    getline(cin, books[count].ISBN);

    cout << "Edition: ";
    cin >> books[count].edition;

    cout << "Copies: ";
    cin >> books[count].copies;

    count++;
    cout << "Book added.\n";
}

//Deleting Book Function
void deleteBook(Book* books, int &count) {
    string isbn;
    cout << "ISBN to delete: ";
    cin >> ws;
    getline(cin, isbn);

    for (int i = 0; i < count; i++) {
        if (books[i].ISBN == isbn) {
            for (int j = i; j < count - 1; j++)
                books[j] = books[j + 1]; //skipping the index and shifts the elements one forward

            count--;
            cout << "Book deleted.\n";
            return;
        }
    }
    cout << "Not found.\n";
}

//Modify Book details function
void modifyBook(Book* books, int count) {
    string isbn;
    cout << "ISBN to modify: ";
    cin >> ws;
    getline(cin, isbn);

    for (int i = 0; i < count; i++) {
        if (books[i].ISBN == isbn) {
            cout << "New title: ";
            getline(cin, books[i].title);

            cout << "New author: ";
            getline(cin, books[i].author);

            cout << "New edition: ";
            cin >> books[i].edition;

            cout << "New copies: ";
            cin >> books[i].copies;

            cout << "Updated.\n";
            return;
        }
    }
    cout << "Not found.\n";
}

//Searching Book by ISBN
void searchBookByISBN(Book* books, int count) {
    string isbn;
    cout << "ISBN: ";
    cin >> ws;
    getline(cin, isbn);

    for (int i = 0; i < count; i++) {
        if (books[i].ISBN == isbn) {
            cout << books[i].title << " (" << books[i].copies << " copies)\n";
            return;
        }
    }
    cout << "Not found.\n";
}

//Searching Book by Title Function
void searchBookByTitle(Book* books, int count) {
    string title;
    cout << "Title: ";
    cin >> ws;
    getline(cin, title);

    for (int i = 0; i < count; i++) {
        if (books[i].title == title) {
            cout << "ISBN: " << books[i].ISBN << endl;
            return;
        }
    }
    cout << "Not found.\n";
}

//Sorting Book by Title
void sortByTitle(Book* books, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (books[i].title > books[j].title) {
                Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }
    cout << "Sorted by title.\n";
}

//Sorting Book by Edition when same Title
void sortByEdition(Book* books, int count) {
    string title;
    cout << "Enter title: ";
    cin >> ws;
    getline(cin, title);

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (books[i].title == title && books[j].title == title) {
                if (books[i].edition > books[j].edition) {
                    Book temp = books[i];
                    books[i] = books[j];
                    books[j] = temp;
                }
            }
        }
    }
    cout << "Sorted editions.\n";
}
//Borrowing Book Function
void borrowBook(Book* books, int count) {
    string isbn;
    cout << "Enter ISBN to borrow: ";
    cin >> ws;
    getline(cin, isbn);

    for (int i = 0; i < count; i++) {
        if (books[i].ISBN == isbn) {
            if (books[i].copies > 0) {
                books[i].copies--;
                cout << "Borrowed.\n";
            } else {
                cout << "No copies available.\n";
            }
            return;
        }
    }
    cout << "Not found.\n";
}
//Returning Book function
void returnBook(Book* books, int count) {
    string isbn;
    cout << "Enter ISBN to return: ";
    cin >> ws;
    getline(cin, isbn);

    for (int i = 0; i < count; i++) {
        if (books[i].ISBN == isbn) {
            books[i].copies++;
            cout << "Returned.\n";
            return;
        }
    }
    cout << "Not found.\n";
}
//Displaying Books Function
void displayBooks(Book* books, int count) {
    if (count == 0) {
        cout << "No books.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        cout << "\nTitle: " << books[i].title;
        cout << "\nAuthor: " << books[i].author;
        cout << "\nISBN: " << books[i].ISBN;
        cout << "\nEdition: " << books[i].edition;
        cout << "\nCopies: " << books[i].copies << "\n";
    }
}

//Main
int main() {
    int capacity = 5;
    int count = 0;

    Book* books = new Book[capacity];

    readFromFile(books, count, capacity);

    int choice;

    do {
        cout << "\n===== LIBRARY MENU =====\n";
        cout << "1. Add Book\n2. Delete Book\n3. Modify Book\n4. Search ISBN\n5. Search Title\n";
        cout << "6. Sort by Title\n7. Sort by Edition\n8. Borrow Book\n9. Return Book\n";
        cout << "10. Display Books\n11. Save to File\n0. Exit.\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(books, count, capacity); break;
            case 2: deleteBook(books, count); break;
            case 3: modifyBook(books, count); break;
            case 4: searchBookByISBN(books, count); break;
            case 5: searchBookByTitle(books, count); break;
            case 6: sortByTitle(books, count); break;
            case 7: sortByEdition(books, count); break;
            case 8: borrowBook(books, count); break;
            case 9: returnBook(books, count); break;
            case 10: displayBooks(books, count); break;
            case 11: writeToFile(books, count); break;
        }
    } while (choice != 0);

    writeToFile(books, count); // auto-save on exit

    delete[] books;
    return 0;
}