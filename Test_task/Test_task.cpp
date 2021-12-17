// Test_task.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<sstream>
#include<fstream>
#include <string>
#include <utility>
#include <map>
#include <ctime>
using namespace std;

int main()
{
    
    string File;
    cout << "Enter the name of csv file: " << endl;
    getline(cin, File);
    cout << "Enter the csv separator " << endl;
    char separator;
    cin >> separator;
    fstream MyFile(File);
    unsigned int time1 = clock();
    string months[12]{ "January", "February","March", "April","May", "June","July","August","September","October","November","December" };
    map<string, map<pair<int,int>,int>> workers;
    string s, name;
    int i = 0,hours=0,month=0,year=0;
    int name_id, month_id, hours_id;
    getline(MyFile, s);
    stringstream ss(s);
    string check;
    while (getline(ss, check, separator)) {
        if (check == "Name")
            name_id = i;
        if (check == "date")
            month_id = i;
        if (check == "logged hours")
            hours_id = i;
        i++;
    };
    
    while (getline(MyFile, s)) {
        i = 0;
        stringstream ss(s);
        while (getline(ss, check, separator)) {
            if (i == name_id) {
                name = check;
            }
            if (i == hours_id) {
                hours = stoi(check);
                if (hours > 24) {
                    cout << "Error.There is only 24 hours in a day" << endl;
                    exit(1);
                }
            }
            if (i == month_id) {
                month = stoi(check.substr(5, 2));
                if (month > 12) {
                    cout << "Error.There is only 12 months" << endl;
                    exit(1);
                }
                year = stoi(check.substr(0, 4));
                
            }
            if (i >= max(max(name_id, month_id), hours_id)) {
                map<string, map<pair<int, int>, int>>::iterator j;
                j = workers.find(name);
                pair<int, int> date = make_pair(year, month);
                if (j != workers.end()) {
                    //u = j->second.find((date));
                    if (j->second.find((date)) != j->second.end())
                        j->second[date] += hours;
                    else
                    {
                        j->second[date] = hours;
                    }
                }

                else
                {
                    map<pair<int, int>, int> curr_hrs;
                    curr_hrs[date] = hours;
                    workers[name] = curr_hrs;
                }
                hours = 0;
            }
            
            i++;
        }
    }
    unsigned  int time2 = clock();
    cout << "Parsing time: " << time2 - time1 <<" milliseconds"<< endl;
    ofstream res("Output.csv");
    res << "Name;Month;Total hours\n";
    map<string, map<pair<int, int>, int>>::iterator j = workers.begin();
    while (j != workers.end()) {
        map<pair<int, int>, int>::iterator k = j->second.begin();
        while (k != j->second.end()) {
            res << j->first << ";" << k->first.first<<" "<<months[(k->first.second)-1]<<";"<<k->second<<endl;
            k++;
        }
        j++;
    }
    res.close();
    MyFile.close();
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
