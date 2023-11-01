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

/*АВЛ-Дерево*/
struct Vertex
{
    MyQueue Data;
    Vertex* Left = nullptr;
    Vertex* Right = nullptr;
};

/*Вращения*/

Vertex* LLRotation(Vertex* root)
{
    Vertex* newRoot = root->Left;
    root->Left = newRoot->Right;
    newRoot->Right = root;
    return newRoot;
}

Vertex* RRRotation(Vertex* root)
{
    Vertex* newRoot = root->Right;
    root->Right = newRoot->Left;
    newRoot->Left = root;
    return newRoot;
}

Vertex* LRRotation(Vertex* root)
{
    root->Left = RRRotation(root->Left);
    return LLRotation(root);
}

Vertex* RLRotation(Vertex* root)
{
    root->Right = LLRotation(root->Right);
    return RRRotation(root);
}

/*Высота дерева*/
int TreeHeight(Vertex* vertex)
{
    if (vertex == nullptr)
    {
        return 0;
    }
    else
    {
        int LHeight = TreeHeight(vertex->Left);
        int RHeight = TreeHeight(vertex->Right);
        return 1 + max(LHeight, RHeight);
    }
}

/*Построение дерева*/
Vertex* BuildAVLTree(Vertex*& vertex, MyQueue value)
{
    if (vertex == nullptr)
    {
        vertex = new Vertex;
        vertex->Data = value;
    }
    else if (value.head->data->year < vertex->Data.head->data->year)
    {
        vertex->Left = BuildAVLTree(vertex->Left, value);
    }
    else if (value.head->data->year > vertex->Data.head->data->year)
    {
        vertex->Right = BuildAVLTree(vertex->Right, value);
    }

    // Обновление баланса и проверка на нарушение баланса
    int balance = TreeHeight(vertex->Left) - TreeHeight(vertex->Right);

    // Слева перевес (нужно выполнить вращение LL или LR)
    if (balance > 1)
    {
        if (value.head->data->year < vertex->Data.head->data->year)
        {
            // Левое-Левое (LL) вращение
            vertex = LLRotation(vertex);
        }
        else
        {
            // Левое-Правое (LR) вращение
            vertex = LRRotation(vertex);
        }
    }
    // Справа перевес (нужно выполнить вращение RR или RL)
    else if (balance < -1)
    {
        if (value.head->data->year > vertex->Data.head->data->year)
        {
            // Правое-Правое (RR) вращение
            vertex = RRRotation(vertex);
        }
        else
        {
            // Правое-Левое (RL) вращение
            vertex = RLRotation(vertex);
        }
    }

    return vertex;
}
int dfg = 0;

int LeftToRight(Vertex* root, const int sost, short int inputt)
{
    while (!(root == nullptr))
    {

        LeftToRight(root->Left, sost, inputt);

        LeftToRight(root->Right, sost, inputt);

        if (dfg == 4000) dfg = 0;
        dfg++;

        if (sost == 1)
        {
            if (root->Data.head->data->year == inputt)
            {
                std::cout << " " << dfg << "\t|| " << root->Data.head->data->author << "\t||\t" << root->Data.head->data->title << "\t||"
                    << root->Data.head->data->publisher << "\t||"
                    << root->Data.head->data->year << "\t||"
                    << root->Data.head->data->num_of_page << "\t||" << std::endl;
            }
        }
        if (sost == 0)
        {
            std::cout << " " << dfg << "\t|| " << root->Data.head->data->author << "\t||\t" << root->Data.head->data->title << "\t||"
                << root->Data.head->data->publisher << "\t||"
                << root->Data.head->data->year << "\t||"
                << root->Data.head->data->num_of_page << "\t||" << std::endl;
        }
        root->Data.head = root->Data.head->next;
        if (root->Data.head == nullptr || root->Data.head->next == nullptr)
            return 0;
        else {
            return LeftToRight(root, sost, inputt);
        }
    }
}

int main()
{
    FILE* fp;
    fp = fopen("testBase1.dat", "rb");
    int i = 0, sum = 20;
    Vertex* Root_AVL = nullptr;
    MyQueue result{};
    string input;
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
            if (currentStatus == 3)
            {
                system("cls");
                cout << "Write your year: ";
                short int inputt = 0;
                cin >> inputt;
                system("cls");
                for (int i = 0; i < 4000; i++)
                {
                    BuildAVLTree(Root_AVL, result);
                }
                cout << " Num\t" << "||" << " Author" << "\t     "
                    << "||" << " Title\t\t\t\t"
                    << "||" << " Publisher\t\t"
                    << "||" << " Year "
                    << "||  Num ||\n";
                cout << "========||===================||=================================||======================||======||======||\n";
                LeftToRight(Root_AVL, 1, inputt);
                cout << "========||===================||=================================||======================||======||======||\n";
                currentStatus = 4;
                break;
            }
            break;
        case 116:
            if (currentStatus == 2)
            {
                system("cls");
                Root_AVL = nullptr;
                for (int i = 0; i < 4000; i++)
                {
                    BuildAVLTree(Root_AVL, result);
                }
                cout << " Num\t" << "||" << " Author" << "\t     "
                    << "||" << " Title\t\t\t\t"
                    << "||" << " Publisher\t\t"
                    << "||" << " Year "
                    << "||  Num ||\n";
                cout << "========||===================||=================================||======================||======||======||\n";
                LeftToRight(Root_AVL, 0 , 0);
                cout << "========||===================||=================================||======================||======||======||\n";
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