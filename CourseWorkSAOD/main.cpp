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

void GetIndexArr(record** index, record* list)
{
    for (int i = 0; i < 4000; i++)
    {
        index[i] = &list[i];
    }
}

char* GetSurname(record** index, int i)
{
    char currentWord[32]{};

    for (int j = 0, wordCount = 0; j < 32; j++) 
    {
        if ((int)index[i]->title[j] == 32) 
        {
            ++wordCount;
        }
        if (wordCount == 2) 
        {
            for (int k = j + 1, count = 0; k < 32; k++, count++) 
            {
                currentWord[count] = index[i]->title[k];
            }
            break;
        }
    }

    return currentWord;
}

void quickSort(record** index, int size, int left, int right)
{
    int i = left;
    int j = right;
    char pivot[32]{};
    strcpy(pivot, GetSurname(index, (left + right) / 2));
    while (i <= j)
    {
        while (strcmp(GetSurname(index, i), pivot) < 0) 
        {
            i++;
        }

        while (strcmp(GetSurname(index, j), pivot) > 0) 
        {
            j--;
        }
        if (i <= j)
        {
            swap(index[i], index[j]);
            i++;
            j--;
        }
    }

    if (i < right)
        quickSort(index, size, i, right);
    if (j > left)
        quickSort(index, size, left, j);
}

int display(int i, int sum, record** index)
{
    cout << " Num\t" << "||" << " Author" << "\t     "
        << "||" << " Title\t\t\t\t"
        << "||" << " Publisher\t\t"
        << "||" << " Year "
        << "||  Num ||\n";
    cout << "========||===================||=================================||======================||======||======||\n";
    for (int i = sum - 20; i < sum; i++)
    {
        cout << " " << i + 1 << "\t|| " << index[i]->author << "\t     ||\t" << index[i]->title << "\t|| "
            << index[i]->publisher << "\t|| "
            << index[i]->year << "\t||  "
            << index[i]->num_of_page << "\t|| " << std::endl;
        //cout << "========||===================||=================================||======================||======||======||\n";
    }
    cout << "========||===================||=================================||======================||======||======||\n";
    cout << "'<-' Previous page" << "\t\t\t      " << "Exit 'ESC'" << "      \t\t\t" << "Next page '->'\n";
    cout << "'A' First page" << "\t\t\t\t " << "Sort and unsort 'S'" << "      \t\t" << "Last page 'D'\n";
    return 0;
}

int main()
{
    FILE* fp;
    fp = fopen("testBase1.dat", "rb");
    int i = 0, sum = 20;
    int currentStatus = 0;
    record* list = new record[4000];
    record** index = new record * [4000];
    i = fread((record*)list, sizeof(record), 4000, fp);
    GetIndexArr(index, list);
    display(i, sum, index);
    while (1)
    {
        switch (_getch())
        {
        case 75:
            if (sum > 20) {
                system("cls");
                i = i - 20;
                sum = sum - 20;
                display(i, sum, index);
            }
            break;
        case 77:
            if (sum < 4000) {
                system("cls");
                i += 20;
                sum += 20;
                display(i, sum, index);
            }
            break;
        case 97:
            system("cls");
            i = 20;
            sum = 20;
            display(i, sum, index);
            break;
        case 100:
            system("cls");
            i = 4000;
            sum = 4000;
            display(i, sum, index);
            break;
        case 115:
            if (currentStatus == 0) {
                system("cls");
                quickSort(index, 4000, 0, 3999);
                display(i, sum, index);
                currentStatus = 1;
                break;
            }
            if (currentStatus == 1) {
                system("cls");
                GetIndexArr(index, list);
                display(i, sum, index);
                currentStatus = 0;
                break;
            }
        case 27:
            return 0;
        }

    }
}