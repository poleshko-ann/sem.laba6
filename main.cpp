#include <QCoreApplication>
#include <iostream>
#include <sstream>
#include <list>
#include <QList>
#include <algorithm>
#include <utility>
#include <random>
#include <QtGlobal>
#include <clocale>
#include <Windows.h>
using namespace std;
using namespace Qt;

// Функция для преобразования QList в list
template<typename T>
list<T> qlistToStdList(const QList<T>& qlist) {
    list<T> stdList;
    for (const T& element : qlist) {
        stdList.push_back(element);
    }
    return stdList;
}

// Функция для преобразования list в QList
template<typename T>
QList<T> stdListToQList(const list<T>& stdList) {
    QList<T> qlist;
    for (const T& element : stdList) {
        qlist.push_back(element);
    }
    return qlist;
}

// Функция для показа содержимого QList
void show(const QList<int> &a) {
    if (a.size() == 0) {
        cout << "Список пуст!" << endl;
    } else {
        copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
}

/*template <typename ForwardIterator>
void qDeleteAll(ForwardIterator begin, ForwardIterator end) {
    while (begin != end) {
        delete *begin;
        ++begin;
    }
}*/

template <typename ForwardIterator, typename T>
ForwardIterator qLowerBound(ForwardIterator begin, ForwardIterator end, const T& value) {
    ForwardIterator it = lower_bound(begin, end, value);
    return it;
}


int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    setlocale(LC_ALL, "PL_pl.UTF-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    QTextStream in(stdin);
    QList<int> myList;
    cout << "Введите свой лист:" << endl;
    QString input = in.readLine();
    QTextStream ss(&input);
    while (!ss.atEnd()) {
        int i;
        ss >> i;
        myList.push_back(i);
    }

    int choice;
    do {
        //QTextStream out(stdout);
        cout << "Меню:" << endl;
        cout << "1. Добавить несколько элементов в заданную позицию c другого list" << endl;
        cout << "1. Добавить несколько элементов в заданную позицию c другого list" << endl;
        cout << "2. Удалить элемент равный заданному" << endl;
        cout << "3. Переместить часть элементов(диапазон) в заданную позицию" << endl;
        cout << "4. Перемешивает элементы на заданном диапазоне случайным образом" << endl;
        cout << "5. Изменяет порядок расположения элементов на противоположный" << endl;
        cout << "6. Удаляет все элементы" << endl;
        cout << "7. Выход из программы" << endl;
        cout << "Введите команду (1-7): ";
        cin >> choice;
        switch (choice) {
    case 1: {
        cout << "Введите свой лист вставки:" << endl;
        string ianput;
        cin.ignore();
        getline(cin, ianput);
        stringstream sa(ianput);
        list<int> otherList;
        while (sa.good()) {
            int i;
            sa >> i;
            otherList.push_back(i);
        }
        int pos, numElements;
        cout << "Введите позицию для добавления элементов: ";
        cin >> pos;
        cout << "Введите количество элементов для добавления: ";
        cin >> numElements;
        auto it = myList.begin();
        auto it2 = otherList.begin();
        advance(it, pos);
        advance(it2, numElements);
        otherList.erase(it2, otherList.end());
        //myList.insert(it, otherList.begin(), otherList.end());
        myList.insert(it,QAtomicInteger);
        show(myList);
        break;
    }

    case 2: {
        int value;
        cout << "Введите значение для удаления: ";
        cin >> value;
        myList.remove(value);
        show(myList);
        break;}

    case 3: {
        int start, end, newPos;
        cout << "Введите начальный индекс диапазона: ";
        cin >> start;
        cout << "Введите конечный индекс диапазона: ";
        cin >> end;
        cout << "Введите новую позицию, чтобы переместить диапазон: ";
        cin >> newPos;

        auto startIt = myList.begin();
        auto endIt = myList.begin();
        auto newPosIt = myList.begin();
        advance(startIt, start);
        advance(endIt, ++end);
        advance(newPosIt, newPos);
        myList.splice(newPosIt, myList, startIt, endIt);
        show(myList);
        break;
    }

    case 4: {
        int start, end;
        cout << "Введите начальный индекс диапазона для перемешивания: ";
        cin >> start;
        cout << "Введите конечный индекс диапазона для перемешивания: ";
        cin >> end;

        vector<int> temp(myList.begin(), myList.end());

        auto startIt = temp.begin();
        auto endIt = temp.begin();
        advance(startIt, start);
        advance(endIt, end);

        shuffle(startIt, endIt, default_random_engine{});
        copy(temp.begin(), temp.end(), myList.begin());
        show(myList);
        break;
    }

    case 5: {
        myList.reverse();
        show(myList);
        break;
    }

    case 6: {
        qDeleteAll(myList.begin(), myList.end());
        myList.clear();
        show(myList);
        break;
    }
    case 7: {
        cout << "Выход из программы" << endl;
        break;

    default:
        cout << "Неверный выбор, попробуйте еще раз." << endl;
    }
    } while (choice != 7);
    return app.exec();
}





























