#ifndef User_hfile
#define User_hfile

#include <vector>
#include <string>
#include <iostream>

const int enoughBooks = 3;
class User
{
    private : 
    std::string name;
    std::string userId;
    std::vector<std::string> borrowedBooks;
    int maxBooksAllowed;

    public :
        
    User(std::string n, std::string I,int max = enoughBooks);

    std::string getName() const;
    std::string getUserId() const;
    std::vector<std::string> getBorrowedBooks() const;
    int getMaxBooksAllowed() const;

    bool canBorrowMore() const;
    void addBook(const std::string& isbn);
    void removeBook(const std::string& isbn);
    void displayProfile() const;
};

#endif