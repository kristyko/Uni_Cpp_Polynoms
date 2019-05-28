//
//  Poly.cpp
//  IPoly_C++_Trotsko
//
//  Created by mac on 5/25/19.
//  Copyright © 2019 mac. All rights reserved.
//

#include "Poly.hpp"

size_t Poly::getDeg()
{
    return _deg;
}

// reloading of << operatior
std::ostream& operator<< (std::ostream &out, const Poly& element)
{
    // such implementation of the method might seem a little bit weird
    // but it's the only way to do without using templates
    element.print();
    return out;
}