#include "Book.h"
#include <ctime>
#include <stdexcept>

const int minYear = 1450;
Book::Book(std::string t, std::string a , int y, std::string i) 
    : title(t),author(a),year(y),isbn(i),isAvailable(true),borrowedBy("")
{

/*для нашего года*/

std::time_t zero = std::time(nullptr);
std::tm* now = std::localtime(&zero);
int Now = now->tm_year + 1900; 

    if (minYear>year or year > Now)
    {
        throw std::invalid_argument("Ошибка:Год должен быть от 1450 и до " + std::to_string(Now));
    }

    if (isbn == "")
    {
        throw std::invalid_argument("Ошибка:ISBN не может быть пустым");
    }
}
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
int Book::getYear() const { return year; }
std::string Book::getISBN() const { return isbn; }
bool Book::getIsAvailable() const { return isAvailable; }
std::string Book::getBorrowedBy() const { return borrowedBy; }

void Book::setAvailable(bool status) { isAvailable = status; }
void Book::setBorrowedBy(const std::string& user) { borrowedBy = user; }

void Book::borrowBook(const std::string& username)
{
    if (isAvailable == false)
    {
        throw std::runtime_error("Книга занята");
    }
    isAvailable = false;
    borrowedBy = username;
}
void Book::returnBook()
{
    isAvailable = true;
    borrowedBy = "";
}

void Book::displayInfo() const 
{
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Year: " << year << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
    std::cout << "Avaible: " << (isAvailable ? "Да" : "Нет") << std::endl;

    if (isAvailable == false)
    {
        std::cout << "Уже забрал(а)" << borrowedBy << std::endl;
    }
    std::cout << std::endl;
}
    