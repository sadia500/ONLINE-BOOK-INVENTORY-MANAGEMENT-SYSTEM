#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
using namespace std;

struct book
{
    int Id;
    string Title;
    string Author;
    int publicationYear;
    float Price;
    int Stock;
};

struct Supplier
{
    int Id;
    string Name;
    string Contact;
};

struct customer
{
    string CustomerName;
    long long CustomerContact;
    int CustomerID;
};

struct Bill
{
    int BillID;
    string CustomerName;
    string BookTitle;
    int Quantity;
    float PricePerBook;
    float TotalCost;
    string PaymentMethod;
};

vector<book> books;
vector<Supplier> suppliers;
vector<customer> customers;
vector<Bill> bill;

void saveBooks()
{
    ofstream myfile("Booksdata.txt");
    if (myfile.is_open())
    {
        for (int i = 0; i < books.size(); i++) 
        {
            myfile << books[i].Id << "\n";
            myfile << books[i].Title << "\n";
            myfile << books[i].Author << "\n";
            myfile << books[i].publicationYear << "\n";
            myfile << books[i].Price << "\n";
            myfile << books[i].Stock << "\n";
        }
        myfile.close();
    }
    else
    {
        cout << "Error saving data to file.\n";
    }
}
void loadBooks()
{
    ifstream myfile("Booksdata.txt");
    if (myfile.is_open())
    {
        book newBook;
        while (myfile >> newBook.Id)
        {
            myfile.ignore(); 
            getline(myfile, newBook.Title);
            getline(myfile, newBook.Author);
            myfile >> newBook.publicationYear;
            myfile >> newBook.Price;
            myfile >> newBook.Stock;
            myfile.ignore(); 
            books.push_back(newBook);
        }
        myfile.close();
    }
    else
    {
        cout << "No book data found. Starting with an empty inventory.\n";
    }
}
void addBook() 
{
    book newBook;
    cout << "Enter Book ID: ";
    cin >> newBook.Id;
    cin.ignore();
    cout << "Enter Book Title: ";
    getline(cin, newBook.Title);
    cout << "Enter Book Author: ";
    getline(cin, newBook.Author);
    cout << "Enter Publication Year: ";
    cin >> newBook.publicationYear;
    cout << "Enter Book Price: ";
    cin >> newBook.Price;
    cout << "Enter Book Stock: ";
    cin >> newBook.Stock;

    books.push_back(newBook);
    saveBooks();

    cout << "Book added successfully!\n";
}

void displayBooks()
{
    if (books.empty())
    {
        cout << "No books available.\n";
        return;
    }

    cout << "Books in the system:\n";
    for (int i = 0; i < books.size(); i++) {
        cout << "ID: " << books[i].Id << "\n";
        cout << "Title: " << books[i].Title << "\n";
        cout << "Author: " << books[i].Author << "\n";
        cout << "Publication Year: " << books[i].publicationYear << "\n";
        cout << "Price: $" << books[i].Price << "\n";
        cout << "Stock: " << books[i].Stock << "\n";
        cout << "-----------------------------\n";
    }
}
void deleteBook()
{
    int id;
    cout << "Enter Book ID to delete: ";
    cin >> id;

    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].Id == id) 
        {
            books.erase(books.begin() + i);
            saveBooks();
            cout << "Book deleted successfully!\n";
            return;
        }
    }
    cout << "Book not found!\n";
}

void searchBook()
{
    string keyword;
    cout << "Enter Title or Author to search: ";
    cin.ignore();
    getline(cin, keyword);
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

    bool found = false;
    for (int i = 0; i < books.size(); i++)
    {
        string title = books[i].Title;
        string author = books[i].Author;
        transform(title.begin(), title.end(), title.begin(), ::tolower);
        transform(author.begin(), author.end(), author.begin(), ::tolower);

    
        if (title.find(keyword) != string::npos || author.find(keyword) != string::npos)
        {
            cout << "\nBook Found:\n";
            cout << "ID: " << books[i].Id << "\nTitle: " << books[i].Title
                << "\nAuthor: " << books[i].Author << "\nPrice: $" << books[i].Price
                << "\nPublication Year: " << books[i].publicationYear << "\n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "No book found with the given keyword.\n";
    }
}

void updateBook()
{
    int id;
    cout << "Enter Book ID to update: ";
    cin >> id;

    for (int i = 0; i < books.size(); i++) 
    {
        if (books[i].Id == id)
        {
            cin.ignore();
            cout << "Enter new Title: ";
            getline(cin, books[i].Title);
            cout << "Enter new Author: ";
            getline(cin, books[i].Author);
            cout << "Enter new Price: ";
            cin >> books[i].Price;
            cout << "Enter new Stock: ";
            cin >> books[i].Stock;

            saveBooks();
            cout << "Book updated successfully!\n";
            return;
        }
    }
    cout << "Book not found!\n";
}

void saveSuppliers()
{
    ofstream myfile("Suppliersdata.txt");
    if (myfile.is_open())
    {
        for (int i = 0; i < suppliers.size(); i++)
        {
            myfile << suppliers[i].Id << "\n";
            myfile << suppliers[i].Name << "\n";
            myfile << suppliers[i].Contact << "\n";
        }
        myfile.close();
    }
    else
    {
        cout << "Error saving data to file.\n";
    }
}

void addSupplier()
{
    Supplier s;
    cout << "Enter Supplier ID: ";
    cin >> s.Id;
    cin.ignore();
    cout << "Enter Supplier Name: ";
    getline(cin, s.Name);
    cout << "Enter Supplier Contact: ";
    getline(cin, s.Contact);

    suppliers.push_back(s);
    saveSuppliers();

    cout << "Supplier added successfully!\n";
}

void displaySuppliers() 
{
    if (suppliers.empty())
    {
        cout << "No suppliers available.\n";
        return;
    }

    cout << "Displaying Suppliers:\n";
    cout << setw(10) << "ID" << setw(30) << "Name" << setw(20) << "Contact" << endl;

    for (const auto& supplier : suppliers)
    {
        cout << setw(10) << supplier.Id << setw(30) << supplier.Name << setw(20) << supplier.Contact << endl;
    }
}

void sortBooks()
{
    if (books.empty()) {
        cout << "No books available to sort.\n";
        return;
    }
    sort(books.begin(), books.end(), [](const book& a, const book& b) {
        return a.Title < b.Title;
        });
    cout << "Books sorted by title successfully.\n";
}

void filterBooksByYear()
{
    if (books.empty())
    {
        cout << "No books available to filter.\n";
        return;
    }
    int year;
    cout << "Enter year to filter books: ";
    cin >> year;
    cout << "Books published in " << year << ":\n";
    cout << setw(10) << "ID" << setw(30) << "Title" << setw(20) << "Author" << endl;
    for (const auto& book : books)
    {
        if (book.publicationYear == year)
        {
            cout << setw(10) << book.Id << setw(30) << book.Title << setw(20) << book.Author << endl;
        }
    }
}
int loadBillID()
{
    ifstream myfile("lastBillID.txt");
    int lastBillID = 0; // Default starting ID (if file doesn't exist)
    if (myfile.is_open())
    {
        myfile >> lastBillID;
        myfile.close();
    }
    return lastBillID;
}

void saveBillID(int billID)
{
    ofstream myfile("lastBillID.txt");
    if (myfile.is_open())
    {
        myfile << billID;
        myfile.close();
    }
    else
    {
        cout << "Error saving Bill ID.\n";
    }
}

void generate_bill(string& title, string& customer_name, float& price, int& quantity, string& author)
{
    static int billCounter = loadBillID(); 

    Bill newBill;
    newBill.BillID = billCounter++; 
    float totalCost = quantity * price;
    newBill.CustomerName = customer_name;
    newBill.BookTitle = title;
    newBill.Quantity = quantity;
    newBill.PricePerBook = price;
    newBill.TotalCost = totalCost;

    int paymentChoice;
    string paymentMethod;

    cout << "\n--- Billing Details ---\n";
    cout << "Book Title: " << title << "\n";
    cout << "Author: " << author << "\n";
    cout << "Quantity: " << quantity << "\n";
    cout << "Price per book: $" << price << "\n";
    cout << "Total Cost: $" << totalCost << "\n";
    cout << "-----------------------\n";
    cout << "\nChoose a payment method:\n";
    cout << "1. Credit/Debit Card\n";
    cout << "2. Easy Paisa\n";
    cout << "3. Digital Wallet\n";
    cout << "Enter your choice: ";
    cin >> paymentChoice;

    switch (paymentChoice)
    {
    case 1:
        cout << "Processing payment via Credit/Debit Card...\n";
        cout << "Payment successful!\n";
        paymentMethod = "Credit/Debit Card";
        break;
    case 2:
        cout << "Processing payment via Easy Paisa...\n";
        cout << "Payment successful!\n";
        paymentMethod = "Easy Paisa";
        break;
    case 3:
        cout << "Processing payment via Digital Wallet...\n";
        cout << "Payment successful!\n";
        paymentMethod = "Digital Wallet";
        break;
    default:
        cout << "Invalid payment method selected. Transaction canceled.\n";
        return;
    }

    newBill.PaymentMethod = paymentMethod;
    bill.push_back(newBill);

    saveBillID(billCounter); 
}
void purchaseBook()
{
    bool found = false;
    string Book, customer_name;
    int quantity;
    cout << "Enter full name: " << endl;
    getline(cin, customer_name);
    cout << "Enter the book you want to purchase: " << endl;
    getline(cin, Book);
    cout << "Enter the quantity you want to purchase: ";
    cin >> quantity;
    cin.ignore();  

    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].Title == Book)
        {
            found = true;
            if (books[i].Stock >= quantity)
            {
                cout << "Book purchased successfully: " << books[i].Title << " by " << books[i].Author << "\n";
                books[i].Stock -= quantity;
                generate_bill(books[i].Title, customer_name, books[i].Price, quantity, books[i].Author);
            }
            else if (books[i].Stock == 0)
            {
                cout << "Sorry, the book \"" << books[i].Title << "\" is out of stock.\n";
            }
            else
            {
                cout << "Sorry, only " << books[i].Stock << " copies of \"" << books[i].Title << "\" are available.\n";
            }
            break;
        }
    }
    if (found == false)
    {
        cout << "Sorry, the book \"" << Book << "\" was not found in the library.\n";
    }
}

void addCustomer()
{
    customer Customer;
    cout << "Enter Customer Name: ";
    getline(cin, Customer.CustomerName);
    string contact;
    cout << "Enter Customer Contact (11 digits): ";
    cin.ignore();
    getline(cin, contact); 
    while (contact.length() != 11 || contact.find_first_not_of("0123456789") != string::npos)
    {
        cout << "Invalid contact number. Please enter a 11-digit number: ";
        getline(cin, contact);
    }
    Customer.CustomerContact = stoll(contact);
    bool idExists;
    do
    {
        idExists = false;
        cout << "Enter Customer ID: ";
        cin >> Customer.CustomerID;
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i].CustomerID == Customer.CustomerID)
            {
                cout << "Customer ID already exists. Please enter a unique ID.\n";
                idExists = true;
                break;
            }
        }
    } while (idExists);

    customers.push_back(Customer);
    cout << "Customer added successfully!\n";
}

void display_customers()
{
    if (customers.empty())
    {
        cout << "\nNo customers found.\n";
        return;
    }
    cout << "\nCustomers Information: \n";
    for (int i = 0; i < customers.size(); i++)
    {
        cout << "Id: " << customers[i].CustomerID
            << " Name: " << customers[i].CustomerName
            << " Contact: " << customers[i].CustomerContact
            << "\n";
    }
}
void filter_by_author()
{
    string authorName;
    cout << "enter the name of author: " << endl;
    getline(cin, authorName);
    cout << "\nBooks by \"" << authorName << "\":\n";
    bool found = false;
    for (int i = 0; i < books.size(); i++)
    {
        if (authorName == books[i].Author)
        {
            found = true;
            cout << "Book ID: " << books[i].Id << "\n";
            cout << "Title: " << books[i].Title << "\n";
            cout << "Year of Publication: " << books[i].publicationYear << "\n";
            cout << "Price: $" << books[i].Price << "\n";
            cout << "Stock: " << books[i].Stock << "\n";
            cout << "-----------------------\n";
        }
    }
    if (!found)
    {
        cout << "No books found by author \"" << authorName << "\".\n";
    }
}

int main()
{
    loadBooks();
    int choice;
    do {
        cout << "\n--- Online Book Inventory Management System ---\n";
        cout << "1. Add Book\n";
        cout << "2. Display Book\n";
        cout << "3. Delete Book\n";
        cout << "4. Search Book\n";
        cout << "5. Update Book\n";
        cout << "6. Filter Books by Year\n";
        cout << "7. Filter Book by Author\n";
        cout << "8. Sort Books \n";
        cout << "9. Purcahse Book\n";
        cout << "10.Add Supplier  \n";
        cout << "11.Display Suppliers\n";
        cout << "12.Add Customer\n";
        cout << "13.Display Customer\n";
        cout << "14.Exit \n";

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            displayBooks();
            break;
        case 3:
            deleteBook();
            break;
        case 4:
            searchBook();
            break;
        case 5:
            updateBook();
            break;
        case 6:
            filterBooksByYear();
            break;
        case 7:
            filter_by_author();
            break;
        case 8:
            sortBooks();
            break;
        case 9:
            purchaseBook();
            break;
        case 10:
            addSupplier();
            break;
        case 11:
            displaySuppliers();
            break;
        case 12:
            addCustomer();
            break;
        case 13:
            display_customers();
            break;
        case 14:
            cout << "Exiting the system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 14);
    return 0;
}


