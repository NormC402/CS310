#include <iostream>
using namespace std;

int main()
{
    int matrix[2][5];
    int sum = 0;

    for (int row = 0; row <= 2; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            cout << "Enter value for matrix[" << row << "][" << col << "]: ";
            cin >> matrix[row][col];
        }
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            sum += matrix[i][j];
        }
    }

    cout << "The total sum of all elements is: " << sum << endl;

    for (int i = 0; i <= 2; i++)
    {
        cout << "Row " << i << ": ";
        for (int j = 0; j <= 5; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
