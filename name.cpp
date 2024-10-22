#include "main.h"
Imagematrix::Imagematrix(int w, int h) : width(w), height(h) { matrix.resize(height, vector<int>(width, 0)); }
Imagematrix::Imagematrix() : width(0), height(0) {matrix.resize(0, vector<int>(0, 0));}
bool Imagematrix::isEmpty()
{
    return width == 0 || height == 0;
}
void Imagematrix::display()
{
    for (auto &row : matrix)
    {
        for (int num : row)
        {
            cout << left << setw(7) << num << " ";
        }
        cout << endl;
    }
}
void Imagematrix::binarydisplay()
{

    for (auto &row : matrix)
    {
        for (int num : row)
        {
            if (num == 0)
            {
                cout << "." << " ";
            }
            else
            {
                cout << "O" << " ";
            }
        }
        cout << endl;
    }
}
void Imagematrix::changepoint(int x, int y, int value)
{
    matrix[y][x] = value;
}
void Imagematrix::pointrectangle(int x, int y, int w, int h, int value)
{
    for (int i = y; i < y + h; i++)
    {
        for (int j = x; j < x + w; j++)
        {
            if (i == y || i == y + h - 1 || j == x || j == x + w - 1)
            {
                matrix[i][j] = value;
            }
        }
    }
}
void Imagematrix::threshold(int thr)
{
    for (auto &temp : matrix)
    {
        for (int &num : temp)
        {
            if (num <= thr)
            {
                num = 0;
            }
        }
    }
}
void Imagematrix::overturn()
{
    vector<vector<int>> temp = matrix;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] = temp[i][width - j - 1];
        }
    }
}
void Imagematrix::rotate()
{
    vector<vector<int>> temp(width, vector<int>(height));
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                temp[i][j] = matrix[height - j - 1][i];
            }
        }
    }
    matrix = temp;
    swap(width, height);
}
void Imagematrix::read(string &filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "读取错误 " << filename << endl;
        return;
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file >> matrix[i][j];
        }
    }
    file.close();
}
void Imagematrix::save(string &filename)  {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cerr << "打开错误 " << filename << endl;
        return;
    }
    file << width << " " << height << std::endl;
    for (auto &row : matrix) {
        for (int pixel : row) {
            file << pixel << " ";
        }
        file << endl; 
    }

    file.close();
}
