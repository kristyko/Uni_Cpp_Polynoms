//
//  IPoly.hpp
//  IPoly_C++_Trotsko
//
//  Realization of class IPoly
//  which describes operations with Polynomes over integer coefficients
//  and inherits fields and methods of class Poly
//  Done by Kristina Trotsko (Computer mathematics group 2)
//  email: christrod17@gmail.com
//
//  Created by mac on 5/21/19.
//  Copyright © 2019 mac. All rights reserved.
//

#ifndef IPoly_hpp
#define IPoly_hpp

//#include <stdio.h>
#include "Poly.hpp"

class IPoly: public Poly
{
public:
    IPoly ();
    IPoly (std::vector<int> koeff);
    ~IPoly ();
    IPoly& operator= (const IPoly &other);
    IPoly (const IPoly &other);
    
    virtual void print() const;
    virtual void setCoef(unsigned long n, int value);
    virtual float value(float x);
    
    IPoly& operator+= (const IPoly &other);
    const IPoly operator+ (const IPoly &other);
    IPoly& operator-= (const IPoly &other);
    const IPoly operator- (const IPoly &other);
    IPoly& operator*= (const IPoly &other);
    const IPoly operator* (const IPoly &other);
    IPoly derivative();
    // it is not always possible to divide two polynoms or take integral over integers
    // for example (x ^ 2) / 2x
    // so there are no such methods in this class
    
private:
    std::vector<int> _p;
};

#endif /* IPoly_hpp */
