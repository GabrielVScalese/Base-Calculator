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
    int emprestarUm (int);
    string subtrairDoisDigitos(string digito1, string digito2);
public:
    Subtradora(string, string, int);
    string subtrairValores();
};

#endif
