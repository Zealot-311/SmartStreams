//
//  matrix.h
//  hackathon
//
//  Created by Ali Ishaque on 7/12/18.
//  Copyright © 2018 IBM. All rights reserved.
//

#include <vector>
#include <cmath>
#ifndef matrixMultiplication_h
#define matrixMultiplication_h

//multiplies two matrices
template <typename T>
class matrix
{
    int rows = 0;
    int columns = 0;
public:
    std::vector<std::vector<T>> data;
    
    matrix()
    {
        //useless default contstuctor
    }
    matrix(int r, int c)
    {
        std::vector<T> dummyVal(r,0);
        for(int i=0; i<c; i++)
        {
            addRow(dummyVal);
        }
        columns = c;
    }
    int getRows()
    {
        return rows;
    }
    void setRows(int r)
    {
        rows = r;
    }
    void setColumns(int c)
    {
        columns = c;
    }
    int getColumns()
    {
        return columns;
    }
    void addRow(std::vector<T> rowData)
    {
        data.push_back(rowData);
        rows++;
        columns = int(rowData.size());
    }

    //contructor that creates a matrix by multiplying 2 others
    matrix(matrix a, matrix b)
    {
        rows = a.getRows();
        columns = b.getColumns();
        //first make sure you can multiply them
        if (a.columns != b.rows)
        {
            std::cout<< "can't multiply/n";
            return;
        }
        //fill data with dummy values
        std::vector<T> dummyVal(rows,0);
        for (int i=0; i<columns; i++)
        {
            data.push_back(dummyVal);
        }
        
        for (int i=0; i<rows; i++)
        {
            for(int j=0; j<columns; j++)
            {
                for (int k =0; k<a.getColumns(); k++)
                {
                    data[i][j] += a.data[i][k] + b.data[k][j];
                }
            }
        }
        
    }
};

template <typename T>
matrix<T> matrixMultiplication(matrix<T> a, matrix<T> b)
{
    matrix<T> c;
    int rows = a.getRows();
    int columns = b.getColumns();
    //first make sure you can multiply them
    if (a.getColumns() != b.getRows())
    {
        std::cout<< "can't multiply/n";
        return c;
    }
    //fill data with dummy values
    std::vector<T> dummyVal(rows,0);
    for (int i=0; i<columns; i++)
    {
        c.data.push_back(dummyVal);
    }
    
    for (int i=0; i<rows; i++)
    {
        for(int j=0; j<columns; j++)
        {
            for (int k =0; k<a.getColumns(); k++)
            {
                c.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return c;
}

template <typename T>
matrix<T> pairwiseAddition(matrix<T> a, matrix<T> b)
{
    matrix<T> c(a.getRows(), a.getColumns());
    if ( (a.getRows() != b.getRows()) || (a.getColumns() != b.getColumns()) )
    {
        std::cout<<"matrix rows and column counts not equal/n";
        return c;
    }
    for (int i=0; i<c.getRows(); i++)
    {
        for (int j=0; j<c.getColumns(); j++)
        {
            c.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return c;
}

template <typename T>
matrix<T> pairwiseSubtraction(matrix<T> a, matrix<T> b)
{
    matrix<T> c(a.getRows(), a.getColumns());
    if ( (a.getRows() != b.getRows()) || (a.getColumns() != b.getColumns()) )
    {
        std::cout<<"matrix rows and column counts not equal/n";
        return c;
    }
    for (int i=0; i<c.getRows(); i++)
    {
        for (int j=0; j<c.getColumns(); j++)
        {
            c.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return c;
}

template <typename T>
matrix<T> scalarMultiplication(matrix<T> a, T scalar)
{
    for(int i=0; i<a.getRows(); i++)
    {
        for(int j=0;j<a.getColumns();j++)
        {
            a.data[i][j] = a.data[i][j] * scalar;
        }
    }
    return a;
}

template <typename T>
matrix<T> matrixMax(matrix<T> a, T max)
{
    for (int i=0; i<a.getRows(); i++)
    {
        for (int j=0; j<a.getColumns(); j++)
        {
            if (a.data[i][j] < max)
            {
                a.data[i][j] = max;
            }
        }
    }
    return a;
}

template <typename T>
matrix<T> matrixPower(matrix<T> a, T power)
{

    for (int i=0; i<a.getRows(); i++)
    {
        for (int j=0; j<a.getColumns(); j++)
        {
            a.data[i][j] = std::pow(a.data[i][j], power);
        }
    }
    return a;
}

template <typename T>
matrix<T> pairwiseDivision(matrix<T> a, matrix<T> b)
{
    matrix<T> c(a.getRows(), a.getColumns());
    if ( (a.getRows() != b.getRows()) || (a.getColumns() != b.getColumns()) )
    {
        std::cout<<"matrix rows and column counts not equal/n";
        return c;
    }
    for (int i=0; i<c.getRows(); i++)
    {
        for (int j=0; j<c.getColumns(); j++)
        {
            c.data[i][j] = a.data[i][j] / b.data[i][j];
        }
    }
    return c;
}

template <typename T>
matrix<T> pairwiseMultiplication(matrix<T> a, matrix<T> b)
{
    matrix<T> c(a.getRows(), a.getColumns());
    if ( (a.getRows() != b.getRows()) || (a.getColumns() != b.getColumns()) )
    {
        std::cout<<"matrix rows and column counts not equal/n";
        return c;
    }
    for (int i=0; i<c.getRows(); i++)
    {
        for (int j=0; j<c.getColumns(); j++)
        {
            c.data[i][j] = a.data[i][j] * b.data[i][j];
        }
    }
    return c;
}

template <typename T>
matrix<T> matrixSigmoid(matrix<T> a, T power)
{
    //flipping the sign
    power = power - power - power;
    for (int i=0; i<a.getRows(); i++)
    {
        for (int j=0; j<a.getColumns(); j++)
        {
            a.data[i][j] = 1 / (1 + std::exp(power));
        }
    }
}
#endif /* matrixMultiplication_h */
