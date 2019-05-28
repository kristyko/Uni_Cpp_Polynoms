//
//  MPoly.cpp
//  MPoly_C++_Trotsko
//
//  Created by mac on 5/19/19.
//  Copyright © 2019 mac. All rights reserved.
//

#include "MPoly.hpp"

// constructors
MPoly::MPoly ()
{
    _p.clear();
    _p.push_back( Field(0) );
    _deg = 0;
}

// basically does all the same as the previous method but we also can change base of the field
MPoly::MPoly ( unsigned base ): MPoly::MPoly()
{
    Field::set_base( base );
}

// now we can either pass vector of Field elements to constructor
// or a vector of integers which will be rewritten as the Field elements
MPoly::MPoly ( std::vector<int> &koeff )
{
    _p.clear();
    for ( std::vector<int>::iterator itr=koeff.begin(), end=koeff.end(); itr < end; ++itr )
    {
        _p.push_back( Field( *itr ) );
    }
    _deg = koeff.size() - 1;
}

MPoly::MPoly ( unsigned base, std::vector<int> &koeff ): MPoly::MPoly(koeff)
{
    Field::set_base( base );
}


MPoly::MPoly ( std::vector<Field> &koeff )
{
    _p = koeff;
    _deg = koeff.size() - 1;
}

MPoly::MPoly ( unsigned base, std::vector<Field> &koeff ): MPoly::MPoly(koeff)
{
    Field::set_base( base );
}

// destructor
MPoly::~MPoly()
{
}

// assignment operator
MPoly& MPoly::operator= ( const MPoly &other )
{
    if ( this == & other )
    {
        return *this;
    }
    
    this->_deg = other._deg;
    this->_p = other._p;
    return *this;
}

void MPoly::setBase( unsigned base )
{
    Field::set_base( base );
}

void MPoly::setCoef(unsigned long n, int value)
{
    if ( n <= _deg)
    {
        _p[n] = value;
    }
    else
    {
        for ( size_t i=_deg + 1; i < n; ++i) { _p.push_back(0); }
        _p.push_back( Field( value ) );
        _deg = n;
    }
}

void MPoly::setCoef(unsigned long n, Field value)
{
    if ( n <= _deg)
    {
        _p[n] = value;
    }
    else
    {
        for ( size_t i=_deg + 1; i < n; ++i)
        {
            _p.push_back(0);
        }
        _p.push_back( value );
        _deg = n;
    }
}

void MPoly::print () const
{
    for ( size_t i=0; i <= _deg; ++i)
    {
        if ( _p[i].get_value() ) { std::cout << _p[i] << "x^" << i; }
        if ( i < _deg && _p[i+1].get_value() ) { std::cout << " + "; }
    }
    std::cout << std::endl;
}

// calculating value of MPoly
float MPoly::value( float x )
{
    float result = 0;
    for ( std::vector<Field>::iterator el=_p.end()-1, end=_p.begin(); el >= end; --el )
    {
        result = *el + result * x;
    }
    return result;
}

// overloading standart arithmetical operations such as +, -, *, /, %
// (most of them quite similar to the corresponding methods of class IPoly )
MPoly& MPoly::operator+= ( const MPoly &other )
{
    if ( this->_deg >= other._deg )
    {
        for ( unsigned long i = 0; i <= other._deg; i++ )
        {
            this->_p[i] += other._p[i];
        }
    }
    else
    {
        for ( unsigned long i = 0; i <= this->_deg; i++ )
        {
            this->_p[i] += other._p[i];
        }
        for ( unsigned long i = this->_deg + 1; i <= other._deg; i++)
        {
            this->setCoef(i, other._p[i]);
        }
    }
    return *this;
}

const MPoly MPoly::operator+ (const MPoly &other)
{
    MPoly res;
    if ( this->_deg >= other._deg )
    {
        res = *this;
        for ( unsigned long i = 0; i <= other._deg; i++)
        {
            res.setCoef(i, this->_p[i] + other._p[i]);
        }
    }
    else
    {
        res = other;
        for ( unsigned long i = 0; i <= this->_deg; i++)
        {
            res.setCoef(i, this->_p[i] + other._p[i]);
        }
        
    }
    return res;
}

MPoly& MPoly::operator-= (const MPoly &other)
{
    if ( this->_deg >= other._deg )
    {
        for ( unsigned long i = 0; i <= other._deg; i++)
        {
            this->_p[i] -= other._p[i];
        }
    }

    else
    {
        for ( unsigned long i = 0; i <= this->_deg; i++)
        {
            this->_p[i] -= other._p[i];
        }
        for ( unsigned long i = this->_deg + 1; i <= other._deg; i++)
        {
            this->setCoef(i, Field(0) - other._p[i]);
        }
    }
    return *this;
}

const MPoly MPoly::operator- (const MPoly &other)
{
    MPoly res;
    if ( this->_deg >= other._deg )
    {
        res = *this;
        for ( unsigned long i = 0; i <= other._deg; i++)
        {
            res.setCoef(i, this->_p[i] - other._p[i]);
        }
    }
    else
    {
        res = other;
        for ( unsigned long i = 0; i <= this->_deg; i++)
        {
            res.setCoef(i, this->_p[i] - other._p[i]);
        }
        for ( unsigned long i = this->_deg+1; i <= other._deg; i++)
        {
            res.setCoef(i, Field(0) - other._p[i]);
        }
        
    }
    return res;
}

MPoly& MPoly::operator *= (const MPoly &other)
{
    std::vector <Field> result(this->_deg + other._deg + 1);
    unsigned long n;
    
    for ( int i=0; i <= this->_deg + other._deg; i++)
    {
        if ( this->_deg <= i ) { n = this->_deg; }
        else { n = i; }
        
        for ( int j=0; j <= n; j++ )
        {
            if ( i - j > other._deg ) { continue; }
            
            result[i] += this->_p[j] * other._p[i-j];
        }
    }
    this->_p = result;
    this->_deg = this->_deg + other._deg;
    return *this;
}

const MPoly MPoly::operator* ( const MPoly &other )
{
    std::vector <Field> result( this->_deg + other._deg + 1 );
    unsigned long n;
    
    for ( int i=0; i <= this->_deg + other._deg; i++ )
    {
        if ( this->_deg <= i ) { n = this->_deg; }
        else { n = i; }
        
        for ( int j=0; j <= n; j++ )
        {
            if ( i - j > other._deg ) { continue; }
            
            result[i] += this->_p[j] * other._p[i-j];
        }
    }
    return MPoly( result );
}

// division of two polynoms
MPoly& MPoly::operator /= (const MPoly &other)
{
    if ( this->_deg >= other._deg )
    {
        unsigned long n = this->_deg - other._deg;
        MPoly result;
        for ( int i=0; i <= n; i++)
        {
            MPoly p;
            p.setCoef(this->_deg - other._deg, _p[_deg] / other._p[other._deg] );
            result += p;
            *this -= p * other;
            this->_deg -= 1;
        }
        *this = result;
    }
    else { *this = MPoly(); }
    return *this;
}

const MPoly MPoly::operator / (const MPoly &other)
{
    MPoly result;
    if ( this->_deg >= other._deg )
    {
        MPoly poly = *this;
        unsigned long n = this->_deg - other._deg;
        for ( int i=0; i <= n; i++)
        {
            MPoly p;
            p.setCoef(poly._deg - other._deg, poly._p[poly._deg] / other._p[other._deg] );
            result += p;
            poly -= p * other;
            poly._deg -= 1;
        }
    }
    return result;
}

// taking the rest of the result of division of two polynoms
MPoly& MPoly::operator%= ( const MPoly &other )
{
    if ( this->_deg >= other._deg )
    {
        unsigned long n = this->_deg - other._deg;
        MPoly result;
        for ( int i=0; i <= n; i++)
        {
            MPoly p;
            p.setCoef(this->_deg - other._deg, _p[_deg] / other._p[other._deg] );
//            result += p;
            *this -= p * other;
            this->_deg -= 1;   // TODO a function that automatically destoys zero coeff
        }
    }
    return *this;
}

const MPoly MPoly::operator% ( const MPoly &other )
{
//    IPoly result;
    MPoly poly = *this;
    if ( this->_deg >= other._deg )
    {
        unsigned long n = this->_deg - other._deg;
        for ( int i=0; i <= n; i++)
        {
            MPoly p;
            p.setCoef(poly._deg - other._deg, poly._p[poly._deg] / other._p[other._deg] );
//            result += p;
            poly -= p * other;
            poly._deg -= 1;
        }
    }
    return poly;
}

MPoly MPoly::derivative()
{
    if (_deg > 0)
    {
        std::vector<Field> result(_deg);
        for ( int i=1; i <= _deg; i++)
        {
            result[i-1] = _p[i] * Field(i);
        }
        return MPoly(result);
    }
    else { return MPoly(); }
}

MPoly MPoly::integral()
{
    std::vector<Field> result(_deg+2);
    result[0] = 0;
    if (_deg > 0)
    {
        for ( int i=0; i <= _deg; i++)
        {
            result[i+1] = _p[i] / Field(i+1);
        }
        return MPoly(result);
    }
    else { return MPoly(); }
}

float MPoly::integral(float a, float b)
{
    MPoly integral = this->integral();
    return integral.value(b) - integral.value(a);
}