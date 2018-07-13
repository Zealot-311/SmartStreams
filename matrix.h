//
//  matrix.h
//  hackathon
//
//  Created by Ali Ishaque on 7/12/18.
//  Copyright © 2018 IBM. All rights reserved.
//

#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#ifndef matrixMultiplication_h
#define matrixMultiplication_h

template <typename T>
std::vector<std::vector<T> > matrixNaturalLog(std::vector<std::vector<T> > a)
{
    for (unsigned i =0; i< a.size(); i++)
    {
        for (unsigned j=0; j<a[0].size(); j++)
        {
            a[i][j] = log(a[i][j]);
        }
    }
}

template <typename T>
std::vector<std::vector<T> > randomMatrix(int r, int col)
{
    std::vector<std::vector<T> > randomMatrix;
    double seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::normal_distribution<T> distribution (0,1.0);
    
    std::vector<T> newrow(col, 0);
    
    for (int i=0; i< r; i++)
    {
        for (int j=0; j<col; j++)
        {
            newrow[j] = distribution(generator);
        }
        randomMatrix.push_back(newrow);
    }
    return randomMatrix;
}

template <typename T>
std::vector<std::vector<T> > matrixMultiplication(std::vector<std::vector<T> > a, std::vector<std::vector<T> > b)
{
    std::vector<std::vector<T> > c;
    int columns = int(b[0].size());
    //first make sure you can multiply them
    if (a[0].size() != b.size())
    {
        std::cout<< "can't multiply/n";
        return c;
    }
    //fill data with dummy values
    std::vector<T> dummyVal(a.size(),0);
    for (int i=0; i<columns; i++)
    {
        c.push_back(dummyVal);
    }
    
    for (unsigned i=0; i<a.size(); i++)
    {
        for(unsigned j=0; j<b[0].size(); j++)
        {
            for (unsigned k =0; k<(a[0].size()); k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

template <typename T>
std::vector<std::vector<T> > pairwiseAddition(std::vector<std::vector<T> > a, std::vector<std::vector<T> > b)
{
    
    std::vector<std::vector<T> > c(a.size(), std::vector<int>(a[0].size(), 0));
    if ( (a.size() != b.size()) || (a[0].size() != b[0].size()) )
    {
        std::cout<<"matrix rows and column counts not equal/n";
        return c;
    }
    for (unsigned i=0; i<(c.size()); i++)
    {
        for (unsigned j=0; j<(c[0].size()); j++)
        {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return c;
}

template <typename T>
std::vector<std::vector<T> > pairwiseSubtraction(std::vector<std::vector<T> > a, std::vector<std::vector<T> > b)
{
    std::vector<std::vector<T> > c(a.size(), std::vector<int>(a[0].size(), 0));
    if ( (a.size() != b.size()) || (a[0].size() != b[0].size()) )
    {
        std::cout<<"matrix rows and column counts not equal/n";
        return c;
    }
    for (unsigned i=0; i<(c.size()); i++)
    {
        for (unsigned j=0; j<(c[0].size()); j++)
        {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
    return c;
}

template <typename T>
std::vector<std::vector<T> > scalarMultiplication(std::vector<std::vector<T> > a, T scalar)
{
    for(unsigned i=0; i<(a.size()); i++)
    {
        for(unsigned j=0;j<a[0].size();j++)
        {
            a[i][j] = a[i][j] * scalar;
        }
    }
    return a;
}

template <typename T>
std::vector<std::vector<T> > matrixMax(std::vector<std::vector<T> > a, T max)
{
    for (unsigned i=0; i< (a.size()); i++)
    {
        for (unsigned j=0; j<(a[0].size()); j++)
        {
            if (a[i][j] < max)
            {
                a[i][j] = max;
            }
        }
    }
    return a;
}

template <typename T>
std::vector<std::vector<T> > matrixPower(std::vector<std::vector<T> > a, T power)
{

    for (unsigned i=0; i<(a.size()); i++)
    {
        for (unsigned j=0; j<(a[0].size()); j++)
        {
            a[i][j] = T(std::pow(a[i][j], power));
        }
    }
    return a;
}

template <typename T>
std::vector<std::vector<T> > pairwiseDivision(std::vector<std::vector<T> > a, std::vector<std::vector<T> > b)
{
    std::vector<std::vector<T> > c(int(a.size()), std::vector<int>(int(a[0].size()), 0));
    if ( (a.size() != b.size()) || (a[0].size() != b[0].size()) )
    {
        std::cout<<"matrix rows and column counts not equal/n";
        return c;
    }
    for (unsigned i=0; i<(c.size()); i++)
    {
        for (unsigned j=0; j<(c[0].size()); j++)
        {
            c[i][j] = a[i][j] / b[i][j];
        }
    }
    return c;
}

template <typename T>
std::vector<std::vector<T> > pairwiseMultiplication(std::vector<std::vector<T> > a, std::vector<std::vector<T> > b)
{
    std::vector<std::vector<T> > c(int(a.size()), std::vector<int>(int(a[0].size()), 0));
    if ( (a.size() != b.size()) || (a[0].size() != b[0].size()) )
    {
        std::cout<<"matrix rows and column counts not equal/n";
        return c;
    }
    for (unsigned i=0; i<(c.size()); i++)
    {
        for (unsigned j=0; j<(c[0].size()); j++)
        {
            c[i][j] = a[i][j] * b[i][j];
        }
    }
    return c;
}

template <typename T>
std::vector<std::vector<T> > matrixSigmoid(std::vector<std::vector<T> > a)
{
    //flipping the sign
    for (int i=0; i<a.getRows(); i++)
    {
        for (int j=0; j<a.getColumns(); j++)
        {
            T x = a.data[i][j];
            x = x - x -x;
            a.data[i][j] = 1 / (1 + std::exp(x));
        }
    }
}
template <typename T>
std::vector<std::vector<T> > reshapeVector(std::vector<std::vector<T> > a, int r, int c)
{
    std::vector<T> flattenedVector;
    std::vector<std::vector<T> > reshaped(r, std::vector<T>(c,0));
    for (unsigned i = 0; i < a.size(); i++)
    {
        for (unsigned j =0; j<a[0].size(); j++)
        {
            flattenedVector.push_back(a[i][j]);
        }
    }
    int z = 0;
    for (unsigned i=0; i<reshaped.size(); i++)
    {
        for (unsigned j =0; j<reshaped[0].size(); j++)
        {
            reshaped[i][j] = flattenedVector[z++];
        }
    }
    return reshaped;
}
template <typename T>
std::vector<T> sumAcrossAxis(std::vector<std::vector<T> > a, int axis)
{
    std::vector<T> summedVector;
    if (axis ==1)
    {
        //rows stay the same
        for (unsigned i=0; i<a.size(); i++)
        {
            T val=0;
            for (unsigned j=0; j<a[0].size(); j++)
            {
                val += a[i][j];
            }
            summedVector.push_back(val);
        }
    }
    else
    {
        //columns stay the same
        for (unsigned j=0; j<a[0].size(); j++)
        {
            T val=0;
            for (unsigned i=0; i<a.size(); i++)
            {
                val += a[i][j];
            }
            summedVector.push_back(val);
        }
        
    }
    return summedVector;
}
template <typename T>
std::vector<std::vector<T> >matrixTranspose(std::vector<std::vector<T> > a)
{
    //rows to columns columns to rows
    
    //create new empty vec
    std::vector<std::vector<T> > transposedVec(a[0].size(), std::vector<T>(a.size(),0));
    for (unsigned i=0; i<a.size(); i++)
    {
        for (unsigned j=0; j<a[0].size(); j++)
        {
            transposedVec[j][i] = a[i][j];
        }
    }
    return transposedVec;
}
template <typename T>
T columnSum(std::vector<std::vector<T> > a, int col)
{
    T sum = 0;
    for (unsigned i=0; i<a.size(); i++)
    {
        sum += a[i][col];
    }
    return sum;
}
template <typename T>
std::vector<T> productAcrossAxis(std::vector<std::vector<T> > a, int axis)
{
    std::vector<T> summedVector;
    if (axis ==1)
    {
        //rows stay the same
        for (unsigned i=0; i<a.size(); i++)
        {
            T val=0;
            for (unsigned j=0; j<a[0].size(); j++)
            {
                val *= a[i][j];
            }
            summedVector.push_back(val);
        }
    }
    else
    {
        //columns stay the same
        for (unsigned j=0; j<a[0].size(); j++)
        {
            T val=0;
            for (unsigned i=0; i<a.size(); i++)
            {
                val *= a[i][j];
            }
            summedVector.push_back(val);
        }
        
    }
    return summedVector;
}
#endif /* matrixMultiplication_h */
