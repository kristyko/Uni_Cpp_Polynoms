//
//  Poly.hpp
//  IPoly_C++_Trotsko
//
//  Realization of class Poly which is the superclass of IPoly and Poly
//  Done by Kristina Trotsko (Computer mathematics group 2)
//  email: christrod17@gmail.com
//
//  Created by mac on 5/25/19.
//  Copyright © 2019 mac. All rights reserved.
//

#ifndef Poly_hpp
#define Poly_hpp

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Field.hpp"


class Poly
{
protected:
    size_t _deg;
    
public:
    friend std::ostream& operator<< (std::ostream &out, const Poly& element);
    virtual void print() const =0;
    size_t getDeg();
    virtual void setCoef( unsigned long n, int value ) =0;
    virtual float value( float x ) =0;
};

#endif /* Poly_hpp */
