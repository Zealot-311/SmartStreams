//
//  main.cpp
//  hackathon
//
//  Created by Ali Ishaque on 7/11/18.
//  Copyright © 2018 IBM. All rights reserved.
//

#include <iostream>
#include "matrix.h"
#include <cassert>
using namespace std;
int main(int argc, const char * argv[]) {
    std::vector<std::vector<int> > m1;
    vector<int> testvec;
    std::vector<int> x(2,0);
    int k=0;
    for (int j=0; j<2; j++)
    {
        for (int i=0;i<2; i++)
        {
            x[i] = k++;
        }
        m1.push_back(x);
    }
    
    testvec = {0,1};
    assert(m1[0] == testvec);
    testvec = {2,3};
    assert(m1[1] == testvec);
    
    std::vector<std::vector<int> > m3 = matrixMax(m1, int(3));
    testvec = {3,3};
    assert(m3[0] == testvec);
    testvec = {3,3};
    assert(m3[1]==testvec);
    
    
    m3 = matrixPower(m1, int(2));
    testvec = {0,1};
    assert(m3[0] == testvec);
    testvec = {4,9};
    assert(m3[1] == testvec);
    
    m3 = matrixMultiplication(m1, m3);
    testvec = {4,9};
    assert(m3[0] == testvec);
    testvec = {12,29};
    assert(m3[1] == testvec);
    
    m3 = scalarMultiplication(m1, int(3));
    testvec = {0,3};
    assert(m3[0] == testvec);
    testvec = {6,9};
    assert(m3[1] == testvec);
    
    m3 = pairwiseAddition(m1, m3);
    testvec = {0, 4};
    assert(m3[0] == testvec);
    testvec ={8,12};
    assert(m3[1] == testvec);
    
    m3 = pairwiseSubtraction(m1, m1);
    testvec = {0,0};
    assert(m3[0] == testvec);
    assert(m3[1] == testvec);
    
    return 0;
}
