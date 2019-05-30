//
//  IPoly.cpp
//  IPoly_C++_Trotsko
//
//  Created by mac on 5/21/19.
//  Copyright © 2019 mac. All rights reserved.
//

#include "IPoly.hpp"

// constructors
IPoly::IPoly ()
{
    _p.push_back( 0 );
    _deg = 0;
    
}

IPoly::IPoly (std::vector<int> koeff)
{
    _p = koeff;
    _deg = _p.size() - 1;
}

// destructor
IPoly::~IPoly()
{
}

// assignmebt operator
IPoly& IPoly::operator= (const IPoly &other)
{
    if ( this == & other )
    {
        return *this;
    }
    
    this->_deg = other._deg;
    this->_p = other._p;
    return *this;
}

// copying
IPoly::IPoly (const IPoly &other)
{
    this->_deg = other._deg;
    this->_p = other._p;
}


void IPoly::print () const
{
    for ( unsigned i=0; i <= _deg; i++)
    {
        if ( _p[i] )
        {
            std::cout << _p[i] << "x^" << i;
        }
        if ( i < _deg && _p[i+1] )
        {
            std::cout << " + ";
        }
        
    }
    std::cout << std::endl;
}

void IPoly::putToFile (std::string filename) const
{
    std::fstream file(filename, std::ios::app );
    for ( unsigned i=0; i <= _deg; i++)
    {
        if ( _p[i] )
        {
            file << _p[i] << "x^" << i;
        }
        if ( i < _deg && _p[i+1] )
        {
            file << " + ";
        }
        
    }
    file << std::endl;
}

// setting coefficient
void IPoly::setCoef(size_t n, int value)
{
    if ( n <= _deg)
    {
        _p[n] = value;
    }
    else
    {
        // if _p is not long enough we just fill elements from _deg + 1 to n with 0
        // and assign _p[n] to value
        for ( unsigned long i=_deg + 1; i < n; i++) { _p.push_back(0); }
        _p.push_back(value);
        _deg = n;
    }
}

void IPoly::pushBackCoeff( int value )
{
    if ( _deg == 0 && _p[0] == 0)
    {
        _p[0] = value;
    }
    else
    {
        _p.push_back(value);
        _deg++ ;
    }
}

// calculating value of the polynom
float IPoly::value(float x)
{
    int result = 0;
    // the formula we use here is
    // poly(x) = a0 + (a1 + (a2 + (... + (a_nx))...)x)x
    for ( std::vector<int>::iterator el = _p.end()-1, end=_p.begin(); el >= end; --el)
    {
        result = result * x + *el;
    }
    return result;
}

// the rest of the methods are just overloading simple arithmetical operations such as +, -, *
IPoly& IPoly::operator+= (const IPoly &other)
{
    if ( this->_deg >= other._deg )
    {
        for ( unsigned long i = 0; i <= other._deg; i++)
        {
            this->_p[i] += other._p[i];
        }
    }
    else
    {
        for ( size_t i = 0; i <= this->_deg; i++)
        {
            this->_p[i] += other._p[i];
        }
        // if _deg of this is less than _deg of other
        // we need to make size of this->_p equal to other._deg + 1
        for ( size_t i = this->_deg + 1; i <= other._deg; i++)
        {
            (this->_p).push_back(other._p[i]);
        }
        this->_deg = other._deg;
    }
    return *this;
}

const IPoly IPoly::operator+ (const IPoly &other)
{
    IPoly res;
    if ( this->_deg >= other._deg )
    {
        res = *this;
        for ( size_t i = 0; i <= other._deg; i++)
        {
            res.setCoef(i, this->_p[i] + other._p[i]);
        }
    }
    else
    {
        res = other;
        for ( size_t i = 0; i <= this->_deg; i++)
        {
            res.setCoef(i, this->_p[i] + other._p[i]);
        }
        
    }
    return res;
}

// similar to operator += and +
IPoly& IPoly::operator-= (const IPoly &other)
{
    if ( this->_deg >= other._deg )
    {
        for ( size_t i = 0; i <= other._deg; i++)
        {
            this->_p[i] -= other._p[i];
        }
    }
    else
    {
        for ( size_t i = 0; i <= this->_deg; i++)
        {
            this->_p[i] -= other._p[i];
        }
        for ( size_t i = this->_deg + 1; i <= other._deg; i++)
        {
            (this->_p).push_back(-other._p[i]);
        }
        this->_deg = other._deg;
    }
    return *this;
}

const IPoly IPoly::operator- (const IPoly &other)
{
    IPoly res;
    if ( this->_deg >= other._deg )
    {
        res = *this;
        for ( size_t i = 0; i <= other._deg; i++)
        {
            res.setCoef(i, this->_p[i] - other._p[i]);
        }
    }
    else
    {
        res = other;
        for ( size_t i = 0; i <= this->_deg; i++)
        {
            res.setCoef(i, this->_p[i] - other._p[i]);
        }
        for ( size_t i = this->_deg+1; i <= other._deg; i++)
        {
            res.setCoef(i, - other._p[i]);
        }
    }
    return res;
}


IPoly& IPoly::operator *= (const IPoly &other)
{
    std::vector <int> result(this->_deg + other._deg + 1);
    unsigned long n;

    for ( size_t i=0; i <= this->_deg + other._deg; i++)
    {
        if ( this->_deg <= i ) { n = this->_deg; }
        else { n = i; }

        for ( size_t j=0; j <= n; j++ )
        {
            // we need to control indexes so that we don't call non-existing coefficients of polynoms
            if ( i - j > other._deg ) { continue; }

            result[i] += this->_p[j] * other._p[i-j];
        }
    }
    this->_p = result;
    this->_deg = this->_deg + other._deg;
    return *this;
}

const IPoly IPoly::operator* ( const IPoly &other )
{
    std::vector <int> result( this->_deg + other._deg + 1 );
    unsigned long n;
    
    for ( size_t i=0; i <= this->_deg + other._deg; i++)
    {
        if ( this->_deg <= i ) { n = this->_deg; }
        else { n = i; }
        
        for ( size_t j=0; j <= n; j++ )
        {
            if ( i - j > other._deg ) { continue; }
            
            result[i] += this->_p[j] * other._p[i-j];
        }
    }
    return IPoly(result);
}

// calculating the derivative of IPoly which is always possible over integers
IPoly IPoly::derivative()
{
    if (_deg > 0)
    {
        std::vector<int> result(_deg);
        for ( int i=1; i <= _deg; i++)
        {
            result[i-1] = _p[i] * i;
        }
    return IPoly(result);
    }
    else { return IPoly(); }
}