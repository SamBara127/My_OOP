// task_4.cpp: определяет точку входа для приложения.
//

#include "task_4.h"

using namespace std;

// Функция для преобразования даты в строковом формате в уникальное числовое представление
int DateToInt(const string& date) {
    // Преобразовываем дату YYYY-MM-DD в число YYYYMMDD
    // Функция stoi преобразует строку в int, а substr вырезает подстроку(индекс-позиция, кол-во символов)
    assert(stoi(date.substr(0, 4)) < 2100 && stoi(date.substr(0, 4)) >= 2000);
    return stoi(date.substr(0, 4)) * 10000 + stoi(date.substr(5, 2)) * 100 + stoi(date.substr(8, 2));
}

// Функция для обработки запроса Earn
void Earn(map<int, double>& budget, int from, int to, double value) {
    assert(value < 1000000);
    int days = to - from + 1;
    double daily_earn = value / days;
    for (int day = from; day <= to; ++day) {
        budget[day] += daily_earn;
    }
}

// Функция для обработки запроса ComputeIncome
double ComputeIncome(const map<int, double>& budget, int from, int to) {
    double income = 0.0;
    //установка итератора начала и конца контейнера.
    auto start = budget.lower_bound(from);
    auto end = budget.upper_bound(to);
    for (auto it = start; it != end; ++it) {
        income += it->second;
    }
    return income;
}

int main() {
    map<int, double> budget;
    int q;
    cin >> q;
    assert(q < 50);

    string query_type, from, to;
    for (int i = 0; i < q; ++i) {
        cin >> query_type >> from >> to;
        int from_int = DateToInt(from);
        int to_int = DateToInt(to);

        if (query_type == "Earn") {
            double value;
            cin >> value;
            Earn(budget, from_int, to_int, value);
        }
        //setprecision задает определенное количество цифр, 
        //которое в зависимости от состояния потока, которое устанавливается по fixed,
        //является либо значащими цифрами, либо цифрами после десятичного знака.
        else if (query_type == "ComputeIncome") {
            cout << fixed << setprecision(25) << ComputeIncome(budget, from_int, to_int) << endl;
        }
    }

    return 0;
}