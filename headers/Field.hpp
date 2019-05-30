//
//  Field.hpp
//  IPoly_C++_Trotsko
//
//  Realization of class Field and arithmetic operations with elements in it
//  Done by Kristina Trotsko (Computer mathematics group 2)
//  email: christrod17@gmail.com
//
//  Created by mac on 5/19/19.
//  Copyright © 2019 mac. All rights reserved.
//

#ifndef Field_hpp
#define Field_hpp

#include <iostream>

class Field
{
public:
    Field ();
    Field (unsigned int value);
    ~Field ();
    Field& operator= (const Field &other);
    Field& operator= (const int &other);
    Field (const Field &other);
    Field (const int &other);
    
    int get_value() const;
    static unsigned get_base();
    static bool isPrime( unsigned n );
    static void set_base(unsigned base);
    friend std::ostream& operator<< (std::ostream &out, const Field& element);

    Field& operator+= (const Field &other);
    const Field operator+ (const Field &other);
    const int operator+ (const float &other);
    Field& operator-= (const Field &other);
    const Field operator- (const Field &other);
    const int operator- (const float &other);
    Field& operator*= (const Field &other);
    const Field operator* (const Field &other);
    const float operator* (const float &other);
    Field get_reverse() const;
    Field& operator/= (const Field& other);
    const Field operator/ (const Field &other);
 
private:
    static unsigned _base;
    int _value;
};

#endif /* Field_hpp */
