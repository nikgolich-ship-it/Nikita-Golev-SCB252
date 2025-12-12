#ifndef Library_hfile
#define Library_hfile
    #include <vector>
    #include <iostream>
    #include <string>

    #include "User.h"
    #include "Book.h"

    class Library
    {
        private:
        std::vector<Book> books;
        std::vector<User> users;
        std::string dataFile;

        public: 

        Library(const std::string& filename);

        void addBook(const Book& book);
        void addUser(const User& user);
        
        void borrowBook(const std::string& userName, const std::string& isbn);
        void returnBook(const std::string& isbn);

        Book* findBookByISBN(const std::string& isbn);
        User* findUserByName(const std::string& name);

        void displayAllBooks();
        void displayAllUsers();

        void saveToFile();
        void loadFromFile();

    };
#endif