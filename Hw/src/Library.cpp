#include "Library.h"
#include <iostream>
#include <algorithm>
#include <fstream>



Library::Library (const std::string& filename)
    : dataFile(filename)
    {
        loadFromFile();
    }

void Library::addBook(const Book& book)
{
    if (findBookByISBN(book.getISBN()) != 0)
    {
        throw std::invalid_argument("Такая книга уже существует");
    }
    books.push_back(book);
}
void Library::addUser(const User& user)
{
    users.push_back(user);
}
Book* Library::findBookByISBN(const std::string& isbn)
{
    for (int i = 0; i < books.size();i++)
    {
        if (books[i].getISBN()==isbn)
        {
            return &books[i];
        }
    }
    return nullptr;
}

User* Library::findUserByName(const std::string& name)
{
    for (int i = 0; i< users.size(); i++)
    {
        if (users[i].getName() == name)
        {
            return &users[i];
        }
    }
    return nullptr;
}

void Library::borrowBook(const std::string& userName , const std::string& isnb)
{
    User* user = findUserByName(userName);
    Book* book = findBookByISBN(isnb);

    if (user == nullptr){
        throw std::runtime_error("Пользователь не найден");
    }
    if (book == nullptr){
        throw std::runtime_error("Книга не найдена");
    }
    if ((book->getIsAvailable())==false)
    {
        throw std::runtime_error("Книга занята");
    }
    if ((user->canBorrowMore())==false)
    {
        throw std::runtime_error("Больше взять книг нельзя");
    }

    /*Если всё чётко*/

    book->borrowBook(user->getName());
    user->addBook(book->getISBN());
    std::cout << "Книга взята" << std::endl;
}
void Library::returnBook(const std::string& isbn)
{
    Book* book = findBookByISBN(isbn);
    if (book==nullptr)
    {
       throw std::runtime_error("Книаг не найдена"); 
    }
     if (book->getIsAvailable()) {
        throw std::runtime_error("Книгу можно взять");
    }
    std::string userName = book ->getBorrowedBy();
    User* user = findUserByName(userName);

    book ->returnBook();

    if (user!=nullptr)
    {
        user->removeBook(isbn);
    }
    std::cout << "Книга возвращена" <<std::endl;
}   
void Library::displayAllBooks() 
{
    if (books.size()==0) 
    {
        std::cout << "Список книг пуст." << std::endl;
        return; 
    }
    for (int i = 0; i < books.size();i++)
    books[i].displayInfo();
}
void Library::displayAllUsers() 
{
    if (users.size()==0) 
    {
        std::cout << "Список пользователей пуст." << std::endl;
        return;
    }
    for (int i = 0; i < users.size();i++)
    users[i].displayProfile();
}

void Library::loadFromFile()
{
    std::ifstream file(dataFile);
    if (file.is_open()==false)
    {
        return;
    }
    books.clear();
    users.clear();

    int booksCount = 0;
    file >> booksCount;
    file.ignore();
    for (int i = 0; i < booksCount; i++) 
    {
        std::string title, author, isbn, borrowedBy;
        int year;
        bool isAvailable;
        std::getline(file, title);
        std::getline(file, author);
        file >> year;
        file.ignore();
        std::getline(file, isbn);
        file >> isAvailable;
        file.ignore();
        std::getline(file, borrowedBy);
        
        Book k(title, author, year , isbn);
        k.setAvailable(isAvailable);
        k.setBorrowedBy(borrowedBy);

        books.push_back(k);
    }
    int usersCount;
    file >> usersCount;
    file.ignore();

    for (int i = 0; i < usersCount; i++) 
    {
        std::string name, userId;
        int maxBooks;
        std::getline(file, name);
        std::getline(file, userId);
        file >> maxBooks;
        file.ignore();

        User k(name,userId,maxBooks);

        int borrowedCount = 0;
        file >> borrowedCount;
        file.ignore();

        for (int j =0; j < borrowedCount; j++) 
        {
            std::string isbn;
            std::getline(file, isbn);
            k.addBook(isbn);
        }

        users.push_back(k);
    }
    file.close();
    std::cout << "Данные загружены";
}
void Library::saveToFile()
{
    std::ofstream file(dataFile);
    if (file.is_open() == false)
    {
        std::cout << "Невозможно открыть файл для записи" << std::endl;
        return;
    }

    file << books.size() << std::endl;

    for (int i = 0; i < books.size(); i++) 
    {
        file << books[i].getTitle() << std::endl;
        file << books[i].getAuthor() << std::endl;
        file << books[i].getYear() << std::endl;
        file << books[i].getISBN() << std::endl;
        file << books[i].getIsAvailable() << std::endl;
        file << books[i].getBorrowedBy() << std::endl;
    }

    file << users.size() << std::endl;

    for (int i = 0; i < users.size(); i++) 
    {
        file << users[i].getName() << std::endl;
        file << users[i].getUserId() << std::endl;
        file << users[i].getMaxBooksAllowed() << std::endl;
        
        std::vector<std::string> borrow = users[i].getBorrowedBooks();
        file << borrow.size() << std::endl;

        for (int j = 0; j < borrow.size(); j++)
        {
            file << borrow[j] << std::endl;
        }
    }

    file.close();
    std::cout << "Данные успешно сохранены в файл!" << std::endl;
}

