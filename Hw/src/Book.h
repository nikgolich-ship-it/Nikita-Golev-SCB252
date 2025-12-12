#ifndef Book_hfile
#define Book_hfile

#include <string>
#include <iostream>

class Book 
{
    private: 
        std::string title;
        std::string author;
        int year;
        std::string isbn;
        bool isAvailable;
        std::string borrowedBy;

    public:
        Book(std::string t, std::string a , int y, std::string i);

        std::string getTitle() const;
        std::string getAuthor() const;
        int getYear() const;
        std::string getISBN() const;
        bool getIsAvailable() const;
        std::string getBorrowedBy() const;

        void setAvailable(bool status);
        void setBorrowedBy(const std::string& userName);

        void borrowBook(const std::string& userName);
        void returnBook();
        void displayInfo() const;

};
#endif 