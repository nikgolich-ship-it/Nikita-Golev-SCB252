#include "User.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <stdexcept>

User::User(std::string n, std::string I,int max)
    : name(n), userId(I), maxBooksAllowed(max)
    {
        if (name == "" or userId == "")
        {
            throw std::invalid_argument("Имя и ID не могу быть пустыми");
        }
    }

std::string User::getName() const 
{ 
    return name; 
}
std::string User::getUserId() const 
{
    return userId; 
}
std::vector<std::string> User::getBorrowedBooks() const 
{
    return borrowedBooks; 
}
int User::getMaxBooksAllowed() const 
{
    return maxBooksAllowed;
}

bool User::canBorrowMore() const
{
    return borrowedBooks.size() < maxBooksAllowed;
}

void User::addBook(const std::string& isbn)
{
    if (canBorrowMore() == false)
    {
        throw std::runtime_error("Взял уже максимум");
    }
    borrowedBooks.push_back(isbn);
}
void User::removeBook(const std::string& isbn)
{
    auto index = std::find(borrowedBooks.begin(),borrowedBooks.end(),isbn);
    if (index != borrowedBooks.end())
    {
        borrowedBooks.erase(index);
    }
    else 
    {
        throw std::runtime_error("У пользователя нет этой книги");
    }
}

void User::displayProfile() const 
{
    std::cout << "User: " << name << ":" << userId << std::endl;
    std::cout << "Borrowed: " << borrowedBooks.size() << "/" << maxBooksAllowed << std::endl;
    if (borrowedBooks.size()>0)
    {
        std::cout <<"Books (ISBN): ";
        for (int i = 0 ; i < borrowedBooks.size();i++)
        {
            std::cout << borrowedBooks[i] << " ";
        }
        std::cout << std::endl;
    }
}