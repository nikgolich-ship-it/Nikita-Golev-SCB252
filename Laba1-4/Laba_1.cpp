#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAX = 1000;

struct Book
{
    char title[100];
    char author[50];
    int year;
    float rating;
};

Book books[MAX];
int k = 0 ;
//k это количество

void loadBooks(const char *filename)
{
    ifstream fin(filename);

    if (!fin)
        return;

    while (fin >> books[k].title 
            >> books[k].author 
            >> books[k].year 
            >> books[k].rating)
    {
        k+=1;
    }
    fin.close();
}

// random это переменная какая-то , когда a,b,c уже надоели
void savebookinfile(const char *filename,Book random)
{
    ofstream fout(filename , ios::app);
    if (!fout)
    {
        cout << "Ошибка при сохранении файла!" << endl;
        return;
    }
    fout << random.title<< " "<< random.author<< " "<< random.year<< " "<< random.rating << endl;

    fout.close();
}
void newbook()
{
    if (k>=MAX)
    {
    cout << "Превышен лимит книг!" << endl;
        return;
    }
    Book random;
    cin.ignore();
    cout << "Введите название книги: ";
    cin.getline(random.title, 100);
    
    cout << "Введите автора: ";
    cin.getline(random.author, 50);

    cout << "Год прочтения: ";
    cin >> random.year;
    while (random.year < 1000 || random.year > 2025) {
        cout << "Ошибка: год должен быть от 1000 до 2025! " << endl << "Введите снова: ";
        cin >> random.year;
    }
    cout << "Ваша оценка (0-10): ";
    cin >> random.rating;
    while (random.rating < 0 || random.rating > 10) {
        cout << "Ошибка: оценка должна быть от 0 до 10!" << endl <<  "Введите снова: ";
        cin >> random.rating;
    }

    if (random.rating < 0 or random.rating > 10)
    {
        cout << "Ошибка: оценка должна быть от 0 до 10!" << endl;
        return;
    }

    books[k++] = random;
    savebookinfile("books.txt", random);

    cout << "Книга добавлена!\n";
}


void showall()
{
    if (k == 0)
    {
        cout << "Нет данных о книгах.\n";
        return;
    }

    cout << "\n--- Все книги ---\n";
    cout << left << setw(40) << "Название"
         << setw(25) << "Автор"
         << setw(10) << "Год"
         << setw(8) << "Оценка" << endl;
    cout << "-----------------------------------------------------------------" << endl;

    for (int i = 0; i < k; i++)
    {
        cout << left << setw(40) << books[i].title
             << setw(25) << books[i].author
             << setw(10) << books[i].year
             << setw(8) << books[i].rating << endl;
    }
}
void showstat()
{
    if (k == 0)
    {
        cout << "Нет книг для анализа.\n";
        return;
    }
    float total =0;
    float maxrating = -1345;
    int best;
    for (int i =0 ; i<k;i++)
    {
        total+=books[i].rating;
        if (books[i].rating>maxrating)
        {
            maxrating = books[i].rating;
            best = i;
        }
    }
    float sr = total / k;
    cout << "\n--- Статистика ---\n";
    cout << "Количество прочитанных книг: " << k << endl;
    cout << "Средняя оценка: "  << sr << endl;
    cout << "Самая высоко оценённая книга: " << books[best].title  << books[best].rating << endl;
}
void showmenu()
{
    cout << "\n=== Трекер книг ===" << endl;
    cout << "1. Добавить книгу" << endl;
    cout << "2. Показать все книги" << endl;
    cout << "3. Показать статистику" << endl;
    cout << "4. Выход" << endl;
    cout << "Выберите пункт: ";
}
int main()
{
    loadBooks("books.txt");

    int choice;
    do
    {
        showmenu();
        cin >> choice;

        switch ( choice)
        {
        case 1:
            newbook();
            break;
        case 2:
            showall();
            break;
        case 3:
            showstat();
            break;
        case 4:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор.\n";
        }

    } while ( choice != 4);

    return 0;
}