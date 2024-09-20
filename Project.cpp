#include <iostream>
#include <string>
#include <windows.h>


using namespace std;

enum KeyCodes { NUMBER = 0, ADRESS = 1, CUSTOMER = 2, EXECUTOR = 3, TOTAL = 4, INCOME = 5, DELIVERY = 6, BONUS = 7 };

string today_date();
void deadlines(string today, int HEIGHT, int WIDTH, string array_list[][8]);
int bonus_plus(int HEIGHT, string array_list[][8], double bonus);
int income(int HEIGHT, string array_list[][8]);
int bonus_plus_income(int HEIGHT, string array_list[][8], double bonus);
int worker_earn(int HEIGHT, string array_list[][8], string worker);
void add_bonus(int HEIGHT, string array_list[][8], double bonus);
int worker_payment(int HEIGHT, string array_list[][8], string worker);
int total_payment(int HEIGHT, string array_list[][8]);
int total_profit(int HEIGHT, string array_list[][8], double bonus);


//запрашиваем дату и возвращаем ее в виде строки
string today_date()                                    
{
    string today;
    cout << "Введите дату для отображения списка: ";
    cin >> today;
    return today;
}

//если запрошенная дата совпадает с датой выдачи выводим всю строку в консоль
void deadlines(string today, int HEIGHT, int WIDTH, string array_list[][8]) 
{
    for (int j = 0; j < WIDTH; j++)
    {
    cout << array_list[0][j] << "\t\t";
    }
    cout << "\n";
    for (int i = 0, j = 0; i < HEIGHT; i++)
    {

        if (array_list[i][DELIVERY] == today)
        {

            for (j = 0; j < WIDTH; j++)
            {
                cout << array_list[i][j] << "\t\t";
            }
        cout << "\n";        
        }

    }
}

// суммируем надбавки за выполнение работы в день ее поступления, надбавка равна 20% (все надбавки для сотрудников и подрядной фирмы)
int bonus_plus (int HEIGHT, string array_list[][8], double bonus) 
{
    int bonus_count = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        if (array_list[i][INCOME] == array_list[i][DELIVERY])
        {
            int x = stoi(array_list[i][TOTAL]) * bonus;
            bonus_count += x;
        }
    }
    //cout << bonus_count << "\n";
    return bonus_count;
}

// сумарные поступления, без бонусов (все поступления для сотрудников и подрядной фирмы)
int income (int HEIGHT, string array_list[][8]) 
{
    int sum = 0;
    for (int i = 1; i < HEIGHT; i++)
    {
        int x = stoi(array_list[i][TOTAL]);
        sum += x;
    }
    //cout << sum <<"\n";
    return sum;
}

//считаем сумарные поступления вместе с бонусами 
int bonus_plus_income(int HEIGHT, string array_list[][8], double bonus)
{
    int total_incom = 0;
    total_incom = income (HEIGHT, array_list) + bonus_plus (HEIGHT, array_list, bonus);
    //cout << total_incom << "\n";
    return total_incom;
}

//заполняем массив в случае наличия бонусами
void add_bonus (int HEIGHT, string array_list[][8], double bonus)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        if (array_list[i][INCOME] == array_list[i][DELIVERY])
        {
            int x = stoi(array_list[i][4]) * bonus;
            string y = to_string(x);
            array_list[i][BONUS] = y;
        }
        else
        {
            int x = 0;
            string y = to_string(x);
            array_list[i][BONUS] = y;
        }
    }
    //cout << bonus_count;
}

//cчитаем заработаные деньги наемной фирмой или сотрудником (подсчет доходов отдельно по каждому сотруднику или подрядной фирме на выбор)
int worker_earn (int HEIGHT, string array_list[][8], string worker)
{
    int payment = 0;
    for (int i = 0, j = 3; i < HEIGHT; i++)
    {
        if (array_list[i][j] == worker)
        {
            int x = stoi(array_list[i][TOTAL]) + stoi(array_list[i][BONUS]);
            payment += x;
        }
    }
    //payment *= 0.25;
    cout << payment;
    return payment;
}

//cчитаем сколько нужно заплатить отдельному сотруднику или подрядной фирме
int worker_payment(int HEIGHT, string array_list[][8], string worker)
{
    int payment = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        if (array_list[i][EXECUTOR] == worker)
        {
            if (worker == "сотрудник 1" || worker == "сотрудник 2")
            {
                int x = (stoi(array_list[i][TOTAL]) + stoi(array_list[i][BONUS]))*0.25;
                payment += x;
            }
            else if (worker == "подрядная фирма")
            {
                int x = (stoi(array_list[i][TOTAL]) + stoi(array_list[i][BONUS])) * 0.5;
                payment += x;
            }

        }
    }
    cout << payment;
    return payment;
}

//cчитаем сколько нужно заплатить всем сотрудникам и подрядной фирме (включая бонусы)
int total_payment(int HEIGHT, string array_list[][8])
{
    int payment = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        if (array_list[i][EXECUTOR] == "сотрудник 1" || array_list[i][EXECUTOR] == "сотрудник 2")
        {
            int x = (stoi(array_list[i][TOTAL]) + stoi(array_list[i][BONUS])) * 0.25;
            payment += x;
        }
        else if (array_list[i][EXECUTOR] == "подрядная фирма")
        {
            int x = (stoi(array_list[i][TOTAL]) + stoi(array_list[i][BONUS])) * 0.5;
            payment += x;
        }
    }
    //cout << payment;
    return payment;
}

//суммарный доход фирмы после вычета зарплаты сотрудникам и подрядной фирме
int total_profit(int HEIGHT, string array_list[][8], double bonus)
{
int profit = bonus_plus_income(HEIGHT, array_list, bonus) - total_payment(HEIGHT, array_list);
cout << profit;
return profit;
}

int main()
{
setlocale(0, "");

double bonus = 0.2;

string worker = "сотрудник 1";

const int WIDTH = 8;
const int HEIGHT = 17;
string array_list [HEIGHT][WIDTH] =
{
    {"№", "Адрес", "Заказчик", "Исполнитель", "Сумма", "Дата поступления", "Дата выдачи", "Надбавка"},
    {"1", "вул. Жемчужна ж/м Дружний, буд. 3, кв. 938", "АН Премьер", "сотрудник 1", "100", "05.09.2024", "07.09.2024"},
    {"2", "6 ст Люстдорфської дороги, буд. 27, кв. 45", "АН Премьер", "подрядная фирма", "100", "07.09.2024", "07.09.2024"},
    {"3", "Грушевського Михайла, буд. 39/1, кв. 10а", "АН Атланта", "сотрудник 2", "100", "05.09.2024", "07.09.2024"},
    {"4", "просп. Глушка академіка, буд. 11/3, кв. 56", "АН Юго-Запад", "сотрудник 1", "100", "09.09.2024", "11.09.2024"},
    {"5", "вул. Лідерсівський, буд. 5, кв. 102", "АН Премьер", "подрядная фирма", "100", "09.09.2024", "09.09.2024"},
    {"6", "Люстдорфська дорога, буд. 27б, кв. 9", "АН Премьер", "подрядная фирма", "100", "09.09.2024", "11.09.2024"},
    {"7", "вул. Балківська, буд. 34, кв. 18", "АН Юго-Запад", "сотрудник 2", "100", "11.09.2024", "13.09.2024"},
    {"8", "бул. Французький, буд. 23/25, кв. 7", "АН Атланта", "сотрудник 1", "100", "13.09.2024", "13.09.2024"},
    {"9", "Корольова академіка, буд. 43/2, кв. 50", "АН Юго-Запад", "подрядная фирма", "100", "11.09.2024", "13.09.2024"},
    {"10", "Старицького, буд. 20/4, кв. 34", "АН Авторитет", "подрядная фирма", "100", "12.09.2024", "14.09.2024"},
    {"11", "Костанді, буд. 104-В", "АН Дом Стар", "сотрудник 1", "100", "12.09.2024", "14.09.2024"},
    {"12", "Садова, буд. 14, кв. 18", "АН Авторитет", "подрядная фирма", "100", "12.09.2024", "14.09.2024"},
    {"13", "Петрова генерала, буд. 46, кв.31", "АН Юго-Запад", "сотрудник 1", "100", "13.09.2024", "15.09.2024"},
    {"14", "Цвєтаєва генерала, буд. 1, кв. 94", "АН Авторитет", "сотрудник 2", "100", "13.09.2024", "15.09.2024"},
    {"15", "Зоопаркова, буд. 8-В, кв. 182", "АН Дом Стар", "сотрудник 1", "100", "13.09.2024", "15.09.2024"},
    {"16", "Каришковського професора, буд. 31", "АН Дом Стар", "сотрудник 2", "100", "13.09.2024", "15.09.2024"}
};

    deadlines(today_date(), HEIGHT, WIDTH, array_list);
    //bonus_plus(HEIGHT, array_list, bonus);
    //income(HEIGHT, array_list);
    //bonus_plus_income(HEIGHT, array_list, bonus);
    add_bonus(HEIGHT, array_list, bonus);
    //worker_earn(HEIGHT, array_list, worker);
    //worker_payment(HEIGHT, array_list, worker);
    //total_payment(HEIGHT, array_list);
    //total_profit(HEIGHT, array_list, bonus);

    Sleep(10000);
}
