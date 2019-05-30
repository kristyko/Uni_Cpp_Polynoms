//
//  MPoly.hpp
//  MPoly_C++_Trotsko
//
//  Realization of class MPoly
//  which describes operations with Polynomes over Field with prime base m
//  and inherits fields and methods of class Poly
//  Done by Kristina Trotsko (Computer mathematics group 2)
//  email: christrod17@gmail.com
//
//  Created by mac on 5/19/19.
//  Copyright © 2019 mac. All rights reserved.
//

#ifndef MPoly_hpp
#define MPoly_hpp

//#include <stdio.h>
#include "Poly.hpp"

class MPoly: public Poly
{
public:
    MPoly ();
    MPoly ( unsigned base );
    MPoly ( std::vector<int> &koeff );
    MPoly ( unsigned base, std::vector<int> &koeff );
    MPoly ( std::vector<Field> &koeff );
    MPoly ( unsigned base, std::vector<Field> &koeff );
    ~MPoly ();
    MPoly& operator= ( const MPoly &other );
   
    void print () const;
    void putToFile (std::string filename) const;
    void setBase( unsigned base );
    void setCoef( size_t n, Field value );
    void pushBackCoeff( int value );
    void pushBackCoeff( Field value );
    virtual void setCoef( size_t n, int value );
    virtual float value( float x );

    MPoly& operator+= ( const MPoly &other );
    const MPoly operator+ ( const MPoly &other );
    MPoly& operator-= ( const MPoly &other );
    const MPoly operator- ( const MPoly &other );
    MPoly& operator*= ( const MPoly &other );
    const MPoly operator* ( const MPoly &other );
    MPoly& operator/= ( const MPoly &other );
    const MPoly operator/ ( const MPoly &other );
    MPoly& operator%= ( const MPoly &other );
    const MPoly operator% ( const MPoly &other );
    MPoly derivative();
    MPoly integral();
    float integral(float a, float b);
    
private:
    std::vector<Field> _p;
};

#endif /* MPoly_hpp */
