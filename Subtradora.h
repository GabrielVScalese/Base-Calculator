#ifndef BASE_CALCULATOR_SUBTRADORA_H
#define BASE_CALCULATOR_SUBTRADORA_H

#include <string>

using namespace std;

// Classe que realiza subtracao entre dois valores
class Subtradora
{
private:
    string valor1;
    string valor2;
    int base;
    string subtrairDoisDigitos(string digito1, string digito2);
    int emprestarUm (int);
public:
    Subtradora(string, string, int);
    void setValor1 (string);
    void setValor2 (string);
    void setBase (int);
    bool operator!= (Subtradora);
    bool operator== (Subtradora);
    void print(ostream *os);
    string subtrairValores();
};

ostream &operator<< (ostream &os, Subtradora &d);

#endif
