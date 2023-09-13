#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#pragma warning(disable : 4996)

using namespace std;

struct record
{
    char author[12];
    char title[32];
    char publisher[16];
    short int year;
    short int num_of_page;
};

int display(int i, int sum)
{
    FILE* fp;
    fp = fopen("testBase1.dat", "rb");
    record arr[4000] = { 0 };
    i = fread((record*)arr, sizeof(record), 4000, fp);
    cout << "\t\tAuthor" << "     \t"
        << "||" << "\t\tTitle\t\t\t"
        << "||" << "\tPublisher\t"
        << "||" << " Year "
        << "||  Num ||\n";
    cout << "=============================||=================================||======================||======||======||\n";
    for (int i = 0; i < sum; i++)
    {
        cout << i+1 << "\t||\t" << arr[i].author << "  ||\t" << arr[i].title << "\t|| "
            << arr[i].publisher << "\t|| "
            << arr[i].year << "\t||  "
            << arr[i].num_of_page << "\t|| " << std::endl;
        cout << "=============================||=================================||======================||======||======||\n";
    }
    cout << "'<-' Previous page" << "\t\t\t      " << "Exit 'ESC'" << "      \t\t\t" << "Next page '->'";
    return 0;
}

int main()
{
    FILE* fp;
    fp = fopen("testBase1.dat", "rb");
    int i = 0, sum = 20;
    display(i, sum);
    while (1)
    {
        switch (_getch())
        {
        case 75:
            if (i > 0) {
                system("cls");
                i = i - 20;
                sum = sum - 20;
                display(i, sum);
            }
            break;
        case 77:
            system("cls");
            i += 20;
            sum += 20;
            display(i, sum);
            break;
        case 27:
            return 0;
        }

    }
}