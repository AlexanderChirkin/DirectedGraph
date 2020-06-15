#include <iostream>
#include <string>
#include <iomanip>
#include "DirectedGraph.h"
#include <Windows.h>


void help()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 6);
    std::cout << "\
******** Help ********     \n\
.        \n\
.        \n\
.        \n\
        \n\
        \n\
        \n\
    Commands:\n\
h   - print help      \n\
po  - print all users objects \n\
no  - create new object       \n\
\n\
.   - print graph            \n\
+v  - add vertex in graph     \n\
-v  - remove vertex from graph  \n\
?v  - check vertex on contains in graph  \n\
+e  - add edge in graph          \n\
-e  - remove edge from graph          \n\
?e  - check edge on contains in graph     \n\
df  - get path depth-first crawl        \n\
\n\
exit- exit                   \n\
";
    SetConsoleTextAttribute(handle, 7);
}

void addIntObject(vector<int>* vector)
{
    try 
    {
        cout << "Enter new value: ";
        string input_str;
        getline(cin, input_str);
        int var = stoi(input_str);
        (*vector).push_back(var);
        cout << "Object added succesfully\n";
    }
    catch (...)
    {
        cout << "Error: invalid value\n";
    }
}

void addIntObject(vector<string>* vector)
{
    try
    {
        cout << "Enter new value: ";
        string input_str;
        getline(cin, input_str);
        (*vector).push_back(input_str);
        cout << "Object added succesfully\n";
    }
    catch (...)
    {
        cout << "Error: invalid value\n";
    }
}


void printVector(vector<int>* vector)
{
    const int CELL_WIDTH = 5;
    for (int i = 0; i < (*vector).size()*(CELL_WIDTH + 1) + 1 + 6; i++)
        cout << '-';
    cout << "\n|index|";
    for (int i = 0; i < (*vector).size(); i++)
        cout << right << setw(CELL_WIDTH) << setfill(' ') << i << "|";
    cout << "\n";
    for (int i = 0; i < (*vector).size() * (CELL_WIDTH + 1) + 1 + 6; i++)
        cout << '-';
    cout << "\n|value|";
    for (int i = 0; i < (*vector).size(); i++)
        cout << right << setw(CELL_WIDTH) << setfill(' ') << (*vector)[i] << "|";
    cout << "\n";
    for (int i = 0; i < (*vector).size() * (CELL_WIDTH + 1) + 1 + 6; i++)
        cout << '-';
    cout << "\nTotal " << (*vector).size() << " objects\n";
}


int readIndex(vector<int>* vector)
{
    cout << "Enter index of object in vector: ";
    string input_str;
    getline(cin, input_str);
    int index = stoi(input_str);
    if (index >= 0 && index < (*vector).size())
        return index;
    else
        throw "index abroad vector";
}


void addInGraph(vector<int>* vector, DirectedGraph<int>* g)
{
    if (g->addVertex(&(*vector)[readIndex(vector)]))
        cout << "Object added\n";
    else
        cout << "Object contains in graph already\n";
}


void removeFromGraph(vector<int>* vector, DirectedGraph<int>* g)
{
    g->removeVertex(&(*vector)[readIndex(vector)]);
    cout << "Object removed\n";
}


void checkContains(vector<int>* vector, DirectedGraph<int>* g)
{
    if (g->contains(&(*vector)[readIndex(vector)]))
        cout << "Object contains in graph\n";
    else
        cout << "Object not contains in graph\n";
}


void addEdge(vector<int>* vector, DirectedGraph<int>* g)
{
    cout << "From: ";
    int index_from = readIndex(vector);
    cout << "To: ";
    int index_to = readIndex(vector);
    if (g->addEdge(&(*vector)[index_from], &(*vector)[index_to]))
        cout << "Edge added in graph\n";
    else
        cout << "Edge already contains in graph\n";
}


void removeEdge(vector<int>* vector, DirectedGraph<int>* g)
{
    cout << "From: ";
    int index_from = readIndex(vector);
    cout << "To: ";
    int index_to = readIndex(vector);
    g->removeEdge(&(*vector)[index_from], &(*vector)[index_to]);
    cout << "Edge removed from graph\n";
}


void checkContainsEdge(vector<int>* vector, DirectedGraph<int>* g)
{

    cout << "From: ";
    int index_from = readIndex(vector);
    cout << "To: ";
    int index_to = readIndex(vector);
    if (g->adjacent(&(*vector)[index_from], &(*vector)[index_to]))
        cout << "Edge contains in graph\n";
    else
        cout << "Edge not contains in graph\n";
}


void depth(vector<int>* v, DirectedGraph<int>* g)
{
    int index_first = readIndex(v);
    vector<int*> array = g->depth_first(&(*v)[index_first]);
    cout << "Depth-crawl sequence: ";
    for (int* item : array) {
        cout << *item << "---";
    }
    cout << '\n';
}


void printGraph(DirectedGraph<int>* g)
{
    int row = g->get_num_vertices();
    int col = 0;
    vector<int*> vertices = g->get_vertices();
    vector<int> col_of_begin;
    col_of_begin.push_back(0);
    for (int* p : vertices) {
        col += to_string(*p).length();
        col_of_begin.push_back(col);
    }
    vector<vector<char>> buf(row, vector<char>(col, ' '));
    int col_cur = 0;
    for (int r = 0; r < vertices.size(); r++)
    {
        for (char c : to_string(*(vertices.at(r))))
        {
            buf[r][col_cur++] = c;
        }
    }
    for (int r = 0; r < vertices.size(); r++)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (g->adjacent(vertices.at(r), vertices.at(i)))
            {
                int cur_col = col_of_begin[r];

                if (r < i)
                {
                    int cur_row = r + 1;
                    while (cur_row != i) {
                        buf[cur_row++][cur_col] = '|';
                    }
                    //buf[cur_row][cur_col++] = '+';
                    while (cur_col < col_of_begin[cur_row] - 1)
                    {
                        buf[cur_row][cur_col++] = '-';
                    }
                    buf[cur_row][cur_col] = '>';
                }
                else
                {
                    int cur_row = r - 1;
                    while (cur_row != i) {
                        buf[cur_row--][cur_col] = '|';
                    }
                    //buf[cur_row][cur_col--] = '+';
                    while (buf[cur_row][cur_col - 1] == ' ')
                    {
                        buf[cur_row][cur_col--] = '-';
                    }
                    buf[cur_row][cur_col] = '<';
                }

            }
        }
    }
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 6);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (buf[i][j] == '|' || buf[i][j] == '+' || buf[i][j] == '-' || buf[i][j] == '<' || buf[i][j] == '>')
                SetConsoleTextAttribute(handle, 11);
            cout << buf[i][j];
            SetConsoleTextAttribute(handle, 6);
        }
        cout << '\n';
    }
    SetConsoleTextAttribute(handle, 7);
    cout << "Total " << g->get_num_vertices() << " vertices, " << g->get_num_edges() << " edges\n";
}

void printGraph(DirectedGraph<string>* g)
{
    int row = g->get_num_vertices();
    int col = 0;
    vector<string*> vertices = g->get_vertices();
    vector<int> col_of_begin;
    col_of_begin.push_back(0);
    for (string* p : vertices) {
        col += (*p).length();
        col_of_begin.push_back(col);
    }
    vector<vector<char>> buf(row, vector<char>(col, ' '));
    int col_cur = 0;
    for (int r = 0; r < vertices.size(); r++)
    {
        for (char c : (*(vertices.at(r))))
        {
            buf[r][col_cur++] = c;
        }
    }
    for (int r = 0; r < vertices.size(); r++)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (g->adjacent(vertices.at(r), vertices.at(i)))
            {
                int cur_col = col_of_begin[r];

                if (r < i)
                {
                    int cur_row = r + 1;
                    while (cur_row != i) {
                        buf[cur_row++][cur_col] = '|';
                    }
                    //buf[cur_row][cur_col++] = '+';
                    while (cur_col < col_of_begin[cur_row] - 1)
                    {
                        buf[cur_row][cur_col++] = '-';
                    }
                    buf[cur_row][cur_col] = '>';
                }
                else
                {
                    int cur_row = r - 1;
                    while (cur_row != i) {
                        buf[cur_row--][cur_col] = '|';
                    }
                    //buf[cur_row][cur_col--] = '+';
                    while (buf[cur_row][cur_col - 1] == ' ')
                    {
                        buf[cur_row][cur_col--] = '-';
                    }
                    buf[cur_row][cur_col] = '<';
                }

            }
        }
    }
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 6);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (buf[i][j] == '|' || buf[i][j] == '+' || buf[i][j] == '-' || buf[i][j] == '<' || buf[i][j] == '>')
                SetConsoleTextAttribute(handle, 11);
            cout << buf[i][j];
            SetConsoleTextAttribute(handle, 6);
        }
        cout << '\n';
    }
    SetConsoleTextAttribute(handle, 7);
    cout << "Total " << g->get_num_vertices() << " vertices, " << g->get_num_edges() << " edges\n";
}


void graphIntInterface(vector<int>* vector, DirectedGraph<int>* g)
{
    help();
    string input_str;
    do
    {
        try
        {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(handle, 5);
            cout << "> ";
            SetConsoleTextAttribute(handle, 7);
            
            getline(cin, input_str);
            if (input_str == "h" || input_str == "help")
                help();
            else if (input_str == "po")
                printVector(vector);
            else if (input_str == "no")
            {
                addIntObject(vector);
                printVector(vector);
            }
            else if (input_str == ".")
                printGraph(g);
            else if (input_str == "+v")
                addInGraph(vector, g);
            else if (input_str == "-v")
                removeFromGraph(vector, g);
            else if (input_str == "?v")
                checkContains(vector, g);
            else if (input_str == "+e")
                addEdge(vector, g);
            else if (input_str == "-e")
                removeEdge(vector, g);
            else if (input_str == "?e")
                checkContainsEdge(vector, g);
            else if (input_str == "df")
                depth(vector, g);
            else if (input_str != "exit")
                cout << "Unknown command: " << input_str << "\n";
        }
        catch (const char* err)
        {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(handle, FOREGROUND_RED);
            cout << "Error: " << err << '\n';
            SetConsoleTextAttribute(handle, 7);
        }
        catch (...)
        {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(handle, FOREGROUND_RED);
            cout << "Error: invalid value\n";
            SetConsoleTextAttribute(handle, 7);
        }
    } while (input_str != "exit");
    delete g;
}


int main()
{
    using namespace std;
    string input_str;
    do
    {
        cout << "Enter data type\n1 - int\n2 - string\n";
        getline(cin, input_str);
        if (input_str == "1")
        {
            DirectedGraph<int>* g = new DirectedGraph<int>();
            vector<int> vector;
            graphIntInterface(&vector, g);
        }
        else if (input_str == "2")
        {
           // DirectedGraph<string>* g = new DirectedGraph<string>();
           // vector<string> vector;
           // graphIntInterface(&vector, g);
        }
    } while (true);
}
