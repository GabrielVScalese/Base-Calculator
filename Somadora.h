#ifndef BASE_CALCULATOR_SOMADORA_H
#define BASE_CALCULATOR_SOMADORA_H

#include <string>

using namespace std;

// Classe que realiza soma entre dois valores
class Somadora
{
private:
    string valor1;
    string valor2;
    int base;
    string somarDoisDigitos(string, string, string, int);
public:
    Somadora(string, string, int);
    void setValor1 (string);
    void setValor2 (string);
    void setBase (int);
    bool operator!= (Somadora);
    bool operator== (Somadora);
    void print(ostream *os);
    string somarValores();
};

ostream &operator<< (ostream &os, Somadora &d);

#endif
