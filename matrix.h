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
std::vector<std::vector<T> > matrixSigmoid(std::vector<std::vector<T> > a, T power)
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
#endif /* matrixMultiplication_h */
