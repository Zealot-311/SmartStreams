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
#include "activations.cpp"
using namespace std;
int main() {
    std::vector<std::vector<int> > m1;
    vector<int> testvec;
    std::vector<int> x(2,0);
    int k=0;
    for (int j=0; j<2; j++)
    {
        for (unsigned i=0;i<2; i++)
        {
            x[i] = k++;
        }
        m1.push_back(x);
    }
    testvec.clear();
    testvec.push_back(0);
    testvec.push_back(1);
    assert(m1[0] == testvec);
    testvec.clear();
    testvec.push_back(2);
    testvec.push_back(3);
    assert(m1[1] == testvec);

    std::vector<std::vector<int> > m3 = matrixMax(m1, int(3));
    testvec.clear();
    testvec.push_back(3);
    testvec.push_back(3);
    assert(m3[0] == testvec);
    assert(m3[1]==testvec);
    
    m3 = matrixPower(m1, int(2));
    testvec.clear();
    testvec.push_back(0);
    testvec.push_back(1);
    assert(m3[0] == testvec);
    testvec.clear();
    testvec.push_back(4);
    testvec.push_back(9);
    assert(m3[1] == testvec);

    m3 = matrixMultiplication(m1, m3);
    testvec.clear();
    testvec.push_back(4);
    testvec.push_back(9);
    assert(m3[0] == testvec);
    testvec.clear();
    testvec.push_back(12);
    testvec.push_back(29);
    assert(m3[1] == testvec);
   
    m3 = scalarMultiplication(m1, int(3));
    testvec.clear();
    testvec.push_back(0);
    testvec.push_back(3);
    assert(m3[0] == testvec);
    testvec.clear();
    testvec.push_back(6);
    testvec.push_back(9);
    assert(m3[1] == testvec);
    
    m3 = pairwiseAddition(m1, m3);
    testvec.clear();
    testvec.push_back(0);
    testvec.push_back(4);
    assert(m3[0] == testvec);
    testvec.clear();
    testvec.push_back(8);
    testvec.push_back(12);
    assert(m3[1] == testvec);

    m3 = pairwiseSubtraction(m1, m1);
    testvec.clear();
    testvec.push_back(0);
    testvec.push_back(0);
    assert(m3[0] == testvec);
    assert(m3[1] == testvec);
    
    //m3 = reshapeVector(m3, 4,1);
    testvec = sumAcrossAxis(m1, 0);
    testvec = sumAcrossAxis(m1, 1);
    
    m3 = matrixTranspose(m1);
    
    randomMatrix<float>(3, 2);
    cout << "works" << endl;
    return 0;
}
