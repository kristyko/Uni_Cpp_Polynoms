//
//  Field.cpp
//  IPoly_C++_Trotsko
//
//  Created by mac on 5/19/19.
//  Copyright © 2019 mac. All rights reserved.
//

#include "Field.hpp"
#include <cmath>

/* helper function
created to control the value of the object so that it is between 0 and m-1 if m is Base
 */
int module( int n, unsigned m )
{
    if ( n < 0 and m > 1 ) { return m + n % int(m); }
    else { return n % m; }
}

// default base is 1
// which means that the only possible member of the Field is 0
unsigned Field::_base = 1;

// constructors
Field::Field()
{
    _value = 0;
}

Field::Field( unsigned int value )
{
    _value = module( value, _base );
}

// destructor
Field::~Field()
{}

// assignment operator
// it is possible to assign another object of the field or an integer
Field& Field::operator= ( const Field &other )
{
    if ( this == & other )
    {
        return *this;
    }
    this->_value = other._value;
    return *this;
}

Field& Field::operator= ( const int &other )
{
    this->_value = module( other, _base );
    return *this;
}

// copying
Field::Field ( const Field &other )
{
    this->_value = other._value;
}

Field::Field ( const int &other )
{
    this->_value = module(other, _base);
}

// static method, returns base of the Field
unsigned Field::get_base()
{
    return _base;
}

// returns value of the object
int Field::get_value() const
{
    return _value;
}

// helper function
// checks whether a number is prime
bool Field::isPrime( unsigned n )
{
    if ( n == 1 or n == 0) { return 0; }
    for ( int i = 2; i <= sqrt(n); i++)
    {
        if ( n % i == 0 ) { return 0; }
    }
    return 1;
}

// a multiplicative group of integers modulo m is Field if and only if m is Prime
// so in this static method we enable the user to change the base of the Field, but only if new base is prime
// in other case base stays the same
void Field::set_base( unsigned base )
{
    if ( (isPrime( base ) ) || (base == 1))
    {
        _base = base;
    }
}

// reloading of operator <<
std::ostream& operator<< (std::ostream &out, const Field& element)
{
    out << element._value;
    return out;
}

// the rest of the functions are quite alike
// basically what they are is reloading standart arithmetic operations such as +, -, *, /
Field& Field::operator+= ( const Field &other )
{
    this->_value = module( this->_value + other._value, _base );
    return *this;
}

const Field Field::operator+ ( const Field &other )
{
    return Field( module( this->_value + other._value, _base ) );
}

// we will need this function when it comes to calculatins the value of polynom
const int Field::operator+ ( const float &other )
{
    return this->_value + other;
}

Field& Field::operator-= ( const Field &other )
{
    
    this->_value = module( this->_value - other._value, _base );
    return *this;
}

const Field Field::operator- ( const Field &other )
{
    return Field( module( this->_value - other._value, _base ) );
}

// we will need this function when it comes to calculatins the value of polynom
const int Field::operator- (const float &other)
{
    return this->_value - other;
}

Field& Field::operator*= ( const Field &other )
{
    this->_value = module( this->_value * other._value, _base );
    return *this;
}

const Field Field::operator* ( const Field &other )
{
    return Field( module( this->_value * other._value, _base ) );
}

// we will need this function when it comes to calculatins the value of polynom
const float Field::operator* ( const float &other )
{
    return this->_value * other;
}

//const int Field::operator* ( const int &other )
//{
//    return this->_value * other;
//}
//

// this method calculates a^(-1) of element a of the Field
Field Field::get_reverse() const
{
    if ( _base > 1)
    {
        int res = 1;
        for ( int i=1; i < _base - 1; i++ )
        {
            res = module( res * _value, _base );
        }
        return res;
    }
    else { return 0; }
}

Field& Field::operator/= ( const Field& other )
{
    Field reverse = other.get_reverse();
    this->_value = module( this->_value * reverse._value, _base );

    return *this;
}

const Field Field::operator/ (const Field &other)
{
    Field reverse = other.get_reverse();
    return Field( module(this->_value * reverse._value, _base) );

}
