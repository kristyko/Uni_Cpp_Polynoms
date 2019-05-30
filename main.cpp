//
//  main.cpp
//  IPoly_C++_Trotsko
//
//  Created by mac on 5/19/19.
//  Copyright © 2019 mac. All rights reserved.
//

#include <iterator>
#include "MPoly.hpp"
#include "IPoly.hpp"

using namespace std;

int main(int argc, const char * argv[])
{
    int mode;
    while ( 1 )
    {
        cout << "How would you like to enter Data?\n"
        << "Press 1 - if through console\n\t  2 - if through the file\n\t "
        << " other - if you want to exit: ";
        cin >> mode;
        if (mode != 1 && mode != 2) { return 0; }
        
        cout << "Would you like to have polynoms over integers or Field?\n"
             << "Enter 0 in the first case and a prime number in other: ";
        unsigned int base;
        cin >> base;
        while ( !(Field::isPrime(base) || base == 0))
        {
            cout << "Try once more: ";
            cin >> base;
        }
        Field::set_base(base);
        // reading data from console
        if ( mode == 1)
        {
            // analogical to the second case
        }
        // getting data from file
        if ( mode == 2)
        {
            string filename;
            cout << "Please enter name of the file you want to read from: ";
            cin >> filename;
            fstream file(filename);
            if ( !file.is_open() ) { cout << "Couldn't open file\n"; exit(1); }
            if ( base == 0 )
            {
                // actually getting two polynoms
                IPoly a, b;
                int coeff;
                while ( file.peek() != '\n' )
                {
                    file >> coeff;
                    a.pushBackCoeff(coeff);
                }
                file >> coeff;
                b.pushBackCoeff(coeff);
                while ( file.peek() != '\n' )
                {
                    file >> coeff;
                    b.pushBackCoeff(coeff);
                }
                string out_filename;
                // getting the name of file we the info is supposed to be written to
                cout << "Please enter name of the file you want to write results to: ";
                cin >> out_filename;
                std::fstream ofile(out_filename, std::ios::trunc );
                ofile.clear();
                ofile << "Polynoms over integers" << endl;
                a.putToFile(out_filename);
                b.putToFile(out_filename);
                string operation;
                while ( 1 )
                {
                    cout << "What do you want to do to the polynoms?\n"
                         << "Enter +, +=, -, -=, *, */,\n"
                         << "\td (if you wush to calculate the derivative of polypoms),\n"
                         << "\tand any other symbols if you wish to stop this madness: ";
                    cin >> operation;
                    if ( operation == "+" ) { IPoly c = a + b; c.putToFile(out_filename); }
                    else if ( operation == "+=" ) { a += b; a.putToFile(out_filename); }
                    else if ( operation == "-" ) { IPoly c = a - b; c.putToFile(out_filename); }
                    else if ( operation == "-=" ) { a -= b; a.putToFile(out_filename); }
                    else if ( operation == "*" ) { IPoly c = a * b; c.putToFile(out_filename); }
                    else if ( operation == "*=" ) { a *= b; a.putToFile(out_filename); }
                    else if ( operation == "d")
                    {
                        a.derivative().putToFile(out_filename);
                        b.derivative().putToFile(out_filename);
                    }
                    else { break; }
                }
            }
            else
            {
                // actually getting polynoms
                MPoly a, b;
                int coeff;
                while ( file.peek() != '\n' )
                {
                    file >> coeff;
                    a.pushBackCoeff(coeff);
                }
                file >> coeff;
                b.pushBackCoeff(coeff);
                while ( file.peek() != '\n' )
                {
                    file >> coeff;
                    b.pushBackCoeff(coeff);
                }
                string out_filename;
                // getting the name of file we the info is supposed to be written to
                cout << "Please enter name of the file you want to write results to: ";
                cin >> out_filename;
                std::fstream ofile(out_filename, std::ios::out );
                ofile.clear();
                ofile << "Field(" << Field::get_base() << ")" << endl;
                a.putToFile(out_filename);
                b.putToFile(out_filename);
                string operation;
                while ( 1 )
                {
                    cout << "\nWhat do you want to do to the polynoms?\n"
                    << "Enter +, +=, -, -=, *, */, /, /=, %, %=,\n"
                    << "\td - if you wush to calculate the derivative of polypoms,\n"
                    << "\ti - if you wush to calculate the integral of polypoms,\n"
                    << "\ti_d - if you wush to calculate the definite integral of polypoms,\n"
                    << "\tand any other symbols if you wish to stop this madness: ";
                    cin >> operation;
                    if ( operation == "+" ) { MPoly c = a + b; c.putToFile(out_filename); }
                    else if ( operation == "+=" ) { a += b; a.putToFile(out_filename); }
                    else if ( operation == "-" ) { MPoly c = a - b; c.putToFile(out_filename); }
                    else if ( operation == "-=" ) { a -= b; a.putToFile(out_filename); }
                    else if ( operation == "*" ) { MPoly c = a * b; c.putToFile(out_filename); }
                    else if ( operation == "*=" ) { a *= b; a.putToFile(out_filename); }
                    else if ( operation == "/" ) { MPoly c = a / b; c.putToFile(out_filename); }
                    else if ( operation == "d" ) { a /= b; a.putToFile(out_filename); }
                    else if ( operation == "%" ) { MPoly c = a % b; c.putToFile(out_filename); }
                    else if ( operation == "%=" ) { a %= b; a.putToFile(out_filename); }
                    else if ( operation == "d")
                    {
                        a.derivative().putToFile(out_filename);
                        b.derivative().putToFile(out_filename);
                    }
                    else if ( operation == "i" )
                    {
                        a.integral().putToFile(out_filename);
                        b.integral().putToFile(out_filename);
                    }
                    else { break; }
                }
            }
            
        }
    }

    return 0;
}
