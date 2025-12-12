#include <iostream>
#include "Library.h"


void clearInput()
{
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

void printMenu() {
    std::cout << "\n=== БИБЛИОТЕКА ===" << std::endl;
    std::cout << "1. Просмотреть все книги" << std::endl;
    std::cout << "2. Просмотреть всех пользователей" << std::endl;
    std::cout << "3. Добавить новую книгу" << std::endl;
    std::cout << "4. Зарегистрировать пользователя" << std::endl;
    std::cout << "5. Выдать книгу пользователю" << std::endl;
    std::cout << "6. Принять книгу от пользователя" << std::endl;
    std::cout << "7. Поиск книги по ISBN" << std::endl;
    std::cout << "8. Просмотреть профиль пользователя" << std::endl;
    std::cout << "9. Сохранить данные в файл" << std::endl;
    std::cout << "10. Выход" << std::endl;
    std::cout << "Ваш выбор: ";
}

int main()
{
    Library file("../data/library_data.txt");
    int choice = 0;

    while (true)
    {
        printMenu();
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cout << "Ошибка: введите число!" << std::endl;
            clearInput();
            continue;
        }

        clearInput();

        try
        {
            if (choice == 10) {
                file.saveToFile(); 
                break;
            }

            switch (choice)
            {
                case 1:
                    file.displayAllBooks();
                    break;

                case 2:
                    file.displayAllUsers();
                    break;

                case 3:
                {
                    std::string title, author, isbn;
                    int year;

                    std::cout << "Введите Название: ";
                    std::getline(std::cin, title);

                    std::cout << "Введите автора: ";
                    std::getline(std::cin, author);

                    std::cout << "Введите год: ";
                    if (!(std::cin >> year))
                    {
                        throw std::invalid_argument("Год должен быть числом");
                    }

                    clearInput();

                    std::cout << "Введите ISBN: ";
                    std::getline(std::cin, isbn);

                    file.addBook(Book(title, author, year, isbn));
                    std::cout << "Книга успешно добавлена." << std::endl;
                    break;
                }

                case 4:
                {
                    std::string name, id;

                    std::cout << "Введите Имя: ";
                    std::getline(std::cin, name);

                    std::cout << "Введите ID: ";
                    std::getline(std::cin, id);
                    
                    file.addUser(User(name, id));
                    
                    std::cout << "Пользователь зарегистрирован.\n";
                    break;
                }

                case 5:
                {
                    std::string name, isbn;

                    std::cout << "Введите Имя пользователя: ";
                    std::getline(std::cin, name);

                    std::cout << "Введите ISBN книги: ";
                    std::getline(std::cin, isbn);

                    file.borrowBook(name, isbn);
                    break;
                }

                case 6:
                {
                    std::string isbn;

                    std::cout << "Введите ISBN для возврата: ";
                    std::getline(std::cin, isbn);

                    file.returnBook(isbn);
                    break;
                }

                case 7:
                {
                    std::string isbn;
                    std::cout << "Введите ISBN: ";
                    std::getline(std::cin, isbn);

                    Book* book = file.findBookByISBN(isbn);
                    if (book != nullptr)
                    {
                        book->displayInfo();
                    }
                    else
                    {
                        std::cout << "Книга с таким ISBN не найдена." << std::endl;
                    }
                    break;
                }

                case 8:
                {
                    std::string name;
                    std::cout << "Введите имя пользователя: ";
                    std::getline(std::cin, name);

                    User* user = file.findUserByName(name);
                    if (user != nullptr)
                    {
                        user->displayProfile();
                    }
                    else
                    {
                        std::cout << "Пользователь не найден." << std::endl;
                    }
                    break;
                }

                case 9:
                    file.saveToFile();
                    break;

                default:
                    std::cout << "Неверная команда. Попробуйте 1-10." << std::endl;
            }
        }
        catch (const std::exception& er)
        {
            std::cerr << "ОШИБКА: " << er.what() << std::endl;
        }
    }

    return 0;
}