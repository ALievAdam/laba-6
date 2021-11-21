#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <windows.h>

float criteria[20][20];
char name_of_criteria[20][20];
int n;
int shift; 
char error[20];
int choice;
float balance;
float maximum = 0;
int index = 0;

using namespace std;

int most(float criteria[20][20], int n, float maximum, int index)
{
    maximum = criteria[n + 1][0];
    for (int g = 1; g < n; g++)
    {
        if (maximum < criteria[n + 1][g])
        {
            maximum = criteria[n + 1][g];
            index = g;
        }
    }
    return 0;
}

int coefficients(float criteria[20][20], int n)
{

    for (int k = 0; k < n; k++)
    {
        criteria[n + 1][k] = criteria[n][k] / criteria[n][n];
        criteria[n + 1][k] = round(criteria[n + 1][k] * 100) / 100; 
    }
    for (int s = 0; s < n; s++)
        criteria[n + 1][n] = criteria[n + 1][n] + criteria[n + 1][s];
    balance = criteria[n + 1][n] - 1;

    if ((balance > 0) || (balance < 0))
    {
        most(criteria, n, maximum, index);
        criteria[n + 1][index] = criteria[n + 1][index] - balance;
    }
    return 0;
}

int sums(float criteria[20][20], int n)
{
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
            criteria[n][j] = criteria[n][j] + criteria[i][j];
    }
    for (int k = 0; k < n; k++)
        criteria[n][n] = criteria[n][n] + criteria[n][k];
    return 0;

}

int input(float criteria[20][20], int n, int shift)
{
    cout << "\nВведите оценку сравнения. От 1-9.\n";
    for (int j = 0; j < n - 1; j++)
    {
        for (int i = 1 + shift; i < n; i++)
        {
            cout << "\nВведите коэфициент отношнения ";
            for (int c = 0; c < 4; c++)
                cout << name_of_criteria[j][c];
            cout << " к ";
            for (int d = 0; d < 5; d++)
                cout << name_of_criteria[i][d];
            cout << ": ";
            for (;;)
            {
                choice = 0;
                cin.getline(error, 20);
                for (int l = 0; l < 20; l++)
                {
                    switch (error[l])
                    {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                    case '.':
                    case '\0':
                        break;

                    default:
                        choice++;
                        break;
                    }
                }
                if (choice == 0)
                {
                    criteria[i][j] = atof(error);
                    choice = 0;
                    if (criteria[i][j] > 0 && criteria[i][j] <= 9)
                        break;
                    else
                    {
                        cout << "   Коэфициент должен находиться в диапазоне от 1-9! " << endl;
                        cout << "Введите коэфициент: ";
                    }
                }
                if (choice != 0)
                {
                    cout << "   Вы можете ввести коэфициенты от 1-9! Помните, что дробные коэфициенты вводятся через запятую!";
                    cout << endl << "Введите коэфициент: ";
                    choice = 0;
                    continue;
                }
            }
            criteria[i][j] = round(criteria[i][j] * 100) / 100;
            criteria[j][i] = 1 / criteria[i][j];
            criteria[j][i] = round(criteria[j][i] * 100) / 100;
        }
        shift++;
    }
    for (int g = 0; g < n; g++)
        criteria[g][g] = 1;
    return 0;
}

int output(float criteria[20][20], int n)
{
    cout << endl << "    ";
    for (int f = 0; f < n; f++)
    {
        cout << "|";
        for (int d = 0; d < 5; d++)
        {
            if (name_of_criteria[f][d] != '\0')
                cout << name_of_criteria[f][d];
            else
                cout << " ";
        }
        cout << "|";
    }
    cout << "|Сумма||Коэффициент|" << endl;
    for (int s = 0; s <= n; s++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (name_of_criteria[s][i] != '\0')
                cout << name_of_criteria[s][i];
            else
                cout << " ";
        }
        for (int k = 0; k <= n + 1; k++)
        {
            cout << "|";
            cout.width(5);
            cout << criteria[k][s];
            cout << "|";
        }
        cout << endl;
    }
    return 0;
}

int title(char name_of_criteria[20][20], int n)
{
    cout << endl << "Введите названия критериев." << endl;
    for (int i = 0; i < n; i++)
    {
        cout << endl << "Критерий №" << i + 1 << ": ";
        cin.getline(name_of_criteria[i], 20);
    }
    return 0;
}

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    for (;;)
    {
        choice = 0;
        cout << "Введите количество критериев: ";
        cin.getline(error, 20);
        for (int i = 0; i < 20; i++)
        {
            switch (error[i])
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '\0':
                break;

            default:
                choice++;
                break;
            }
        }
        if (choice == 0)
        {
            n = atoi(error);
        }
        else
            cout << "Вы ввели недопустимый символ!";

        if (n > 20)
            cout << endl << "   Максимальное количество критериев = 20!" << endl;
        else if ((n < 2) && (n >= 0) && (choice == 0))
            cout << endl << "   Что бы сравнить критерии, их должно быть, как минимум 2!" << endl;
        else if (choice != 0)
            continue;
        else
            break;
    }
    title(name_of_criteria, n);
    input(criteria, n, shift);
    sums(criteria, n);
    coefficients(criteria, n);
    output(criteria, n);
    return 0;
}