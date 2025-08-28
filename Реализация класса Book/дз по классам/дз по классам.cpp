#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Book
{
    private :
        string title;
        string author;
        int year;

    public :
        // конструктор с параметрами
        Book (string name, string avtor, int god)
        {
        title = name;
        author = avtor;
        year = god;
        }

        // конструктор по умолчанию
        Book()
        {
            title = "";
            author = "";
            year = 0;
        }
        
        // список геттеров

        string get_title()
        {
            return title;
        }

        string get_author()
        {
            return author;
        }

        int get_year()
        {
            return year;
        }

        // список сеттеров

        string set_title(string new_title)
        {
            cout << "Введите название книги :" << endl;
            getline(cin, new_title);
            if ( !new_title.empty() ) {
                title = new_title;
            } else cout << "Название книги не должно быть пустым" << endl;
        }

        string set_author(string new_author)
        {
            cout << "Введите автора книги :" << endl;
            getline(cin, new_author);
            if (!new_author.empty()) {
                author = new_author;
            }
            else cout << "Имя автора не должно быть пустым" << endl;
        }

        string set_year(int new_year)
        {
            cout << "Введите год издания книги :" << endl;
            cin >> new_year;
            if (new_year > 1800 && new_year < 2025) {
                year = new_year;
            }
            else cout << "Год издания книги должен быть в диапазоне 1800 - 2025 годов" << endl;
        }

        void printInfo()
        {
            cout << "Название книги - " << title << endl; 
            cout << "Автор книги - " << author << endl;
            cout << "Год издания - " << year << endl;
        }

        bool isModern()
        {
            if (year > 2000) {
                return true;
            } else return false;
        }

};

void enter()
{
    cout << endl;
}

// функция для чтения книг из файла
vector<Book> readBooks(const string& filename) {
    vector<Book> books;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка открытия файла: " << filename << endl;
        return books;
    }

    string title, author, yearStr;
    int year;

    while (getline(file, title) && getline(file, author) && getline(file, yearStr)) {
        // Пропускаем пустые строки между записями
        if (title.empty() && author.empty() && yearStr.empty()) {
            continue;
        }

        try {
            year = stoi(yearStr); // преобразуем строку в число
            books.push_back(Book(title, author, year));
        }
        catch (const exception& e) {
            cout << "Ошибка преобразования года для книги: " << title << endl;
        }
    }

    file.close();
    return books;
}

int main()
{
    // добавляем кириллицу
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    // вектор для хранения книг
    vector<Book> library;

    // читаем книги из файла
    library = readBooks("books.txt");
    cout << "Загружено книг из файла : " << library.size() << endl;
    enter();

    // вывод современных книг из файла
    cout << "Современные книги :" << endl;
    int modernCount = 0;

    for (size_t i = 0; i < library.size(); i++) {
        if (library[i].isModern()) {
            modernCount++;
            cout << "Современная книга номер - " << modernCount << ":" << endl;
            library[i].printInfo();
            enter();
        }
    }

    // пишем колличество современных книг или об их отсутствие
    if (modernCount == 0) {
        cout << "Современные книги не найдены =(" << endl;
        enter();
    }
    else {
        cout << "Найдено современных книг : " << modernCount << "^-^" << endl;
        enter();
    }
}