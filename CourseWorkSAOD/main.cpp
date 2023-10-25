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

struct node {
    record* data;
    node* next;
};

struct MyQueue {
    node* head;
    node* tail;

    MyQueue() : head(nullptr), tail(nullptr) {}

    void push(record* data) {
        node* newNode = new node;
        newNode->data = data;
        newNode->next = nullptr;

        if (!head) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    bool empty() const {
        return !head;
    }

    record* front() const {
        if (head) {
            return head->data;
        }
        throw runtime_error("Queue is empty");
    }

    void pop() {
        if (head) {
            node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    int size() const {
        int count = 0;
        node* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }
};

struct vertex {
    int balance = 0;
    vertex* left = nullptr;
    vertex* right = nullptr;
    MyQueue data;
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

MyQueue BinarySearch(record** index, const string& targetKey) {
    MyQueue result; 

    int arrSize = 4000;
    int left = 0;
    int right = arrSize - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        string key(GetSurname(index, mid), 3);

        if (key == targetKey) {
            result.push(index[mid]);

            int leftIndex = mid - 1;
            while (leftIndex >= 0 && strncmp(GetSurname(index, leftIndex), targetKey.c_str(), 3) == 0) {
                result.push(index[leftIndex]);
                leftIndex--;
            }

            int rightIndex = mid + 1;
            while (rightIndex < arrSize && strncmp(GetSurname(index, rightIndex), targetKey.c_str(), 3) == 0) {
                result.push(index[rightIndex]);
                rightIndex++;
            }

            return result;
        }
        else if (key < targetKey) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return result;
}

void printQueue(const MyQueue& result, int currentPage)
{
    node* currentNode = result.head;
    int counter = 0;
    int startIndex = currentPage * 20;

    while (counter < startIndex && currentNode) {
        currentNode = currentNode->next;
        counter++;
    }
    cout << " Num\t" << "||" << " Author" << "\t     "
        << "||" << " Title\t\t\t\t"
        << "||" << " Publisher\t\t"
        << "||" << " Year "
        << "||  Num ||\n";
    cout << "========||===================||=================================||======================||======||======||\n";
    while (currentNode && counter < startIndex + 20) {
        record* recordPtr = currentNode->data;

            cout << " " << counter - 19 << "\t|| " << recordPtr->author << "\t     ||\t" << recordPtr->title << "\t|| "
                << recordPtr->publisher << "\t|| "
                << recordPtr->year << "\t||  "
                << recordPtr->num_of_page << "\t|| " << std::endl;

            currentNode = currentNode->next;
            counter++;

    }
    cout << "========||===================||=================================||======================||======||======||\n";
    cout << "'<-' Previous page" << "\t\t\t      " << "Exit 'ESC'" << "      \t\t\t" << "Next page '->'\n";
    cout << "'A' First page" << "\t\t     " << "Sort and unsort 'S'" << "      " << "Binary search 'F'" << "      \t" << "Last page 'D'\n";
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
    }
    cout << "========||===================||=================================||======================||======||======||\n";
    cout << "'<-' Previous page" << "\t\t\t      " << "Exit 'ESC'" << "      \t\t\t" << "Next page '->'\n";
    cout << "'A' First page" << "\t\t     " << "Sort and unsort 'S'" << "      " << "Binary search 'F'" << "      \t" << "Last page 'D'\n";
    return 0;
}

void LL_povorot(vertex*& p) 
{
    vertex* q = p->left;
    q->balance = 0;
    p->balance = 0;
    p->left = q->right;
    q->right = p;
    p = q;
}

void RR_povorot(vertex*& p) 
{
    vertex* q = p->right;
    p->balance = 0;
    q->balance = 0;
    p->right = q->left;
    q->left = p;
    p = q;
}

void LR_povorot(vertex*& p) 
{
    vertex* q = p->left;
    vertex* r = q->right;
    if (r->balance < 0) {
        p->balance = 1;
    }
    else {
        p->balance = 0;
    }
    if (r->balance > 0) {
        q->balance = -1;
    }
    else {
        q->balance = 0;
    }
    r->balance = 0;
    q->right = r->left;
    p->left = r->right;
    r->left = q;
    r->right = p;
    p = r;
}

void RL_povorot(vertex*& p) 
{
    vertex* q = p->right;
    vertex* r = q->left;
    if (r->balance < 0) {
        p->balance = -1;
    }
    else {
        p->balance = 0;
    }
    if (r->balance < 0) {
        q->balance = 1;
    }
    else {
        q->balance = 0;
    }
    r->balance = 0;
    q->left = r->right;
    p->right = r->left;
    r->right = q;
    r->left = p;
    p = r;
}

void insert(vertex*& p, MyQueue newData) {
    if (p == nullptr) {
        p = new vertex;
        p->data = newData;
        p->balance = 0;
    }
    else if (newData.head->data->year < p->data.head->data->year) {
        insert(p->left, newData);
        if (p->left->balance == -2) {
            if (newData.head->data->year < p->data.head->data->year) {
                LL_povorot(p);
            }
            else {
                LR_povorot(p);
            }
        }
    }
    else {
        insert(p->right, newData);
        if (p->right->balance == 2) {
            if (newData.head->data->year > p->data.head->data->year) {
                RR_povorot(p);
            }
            else {
                RL_povorot(p);
            }
        }
    }
}
int dfg = 0;
void LeftToRight(vertex* p) 
{
    if (p != nullptr) {
        LeftToRight(p->left);
        if (dfg == 4000) dfg = 0;
        dfg++;
        cout << " " << dfg << "\t|| " << p->data.head->data->author << "\t     ||\t" << p->data.head->data->title << "\t|| "
            << p->data.head->data->publisher << "\t|| "
            << p->data.head->data->year << "\t||  "
            << p->data.head->data->num_of_page << "\t|| " << std::endl;
        LeftToRight(p->right);
    }
}

int main()
{
    FILE* fp;
    fp = fopen("testBase1.dat", "rb");
    int i = 0, sum = 20;
    vertex* root = nullptr;
    string input;
    int currentStatus = 0;
    record* list = new record[4000];
    record** index = new record * [4000];
    MyQueue result{};
    i = fread((record*)list, sizeof(record), 4000, fp);
    GetIndexArr(index, list);
    display(i, sum, index);
    while (1)
    {
        switch (_getch())
        {
        case 75:
            if (sum > 20 && currentStatus != 2 && currentStatus != 3) {
                system("cls");
                i = i - 20;
                sum = sum - 20;
                display(i, sum, index);
            }
            if (sum > 20 && currentStatus == 2) {
                system("cls");
                i -= 20;
                sum -= 20;
                printQueue(result, sum / 20);
            }
            break;
        case 77:
            if (sum < 4000 && currentStatus != 2 && currentStatus != 3) {
                system("cls");
                i += 20;
                sum += 20;
                display(i, sum, index);
            }
            if (sum < 4000 && currentStatus == 2) {
                system("cls");
                i += 20;
                sum += 20;
                printQueue(result, sum / 20);
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
        case 102:
            if (currentStatus == 1)
            {
                system("cls");
                cout << "Write your letters: ";
                cin >> input;
                result = BinarySearch(index, input);
                if (result.empty())
                {
                    cout << "No record!";
                    Sleep(500);
                    break;
                }
                else
                {
                    system("cls");
                    printQueue(result, sum / 20);
                    currentStatus = 2;
                }
            }
            break;
        case 116:
            if (currentStatus == 2)
            {
                system("cls");
                root = nullptr;
                for (int i = 0; i < 4000; i++)
                {
                    insert(root, result);
                }
                LeftToRight(root);
                currentStatus = 3;
                break;
            }
            if (currentStatus == 3)
            {
                system("cls");
                GetIndexArr(index, list);
                display(i, sum, index);
                currentStatus = 0;
                break;
            }
            break;
        case 27:
            return 0;
        }

    }
}