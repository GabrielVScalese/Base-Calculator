#ifndef BASE_CALCULATOR_MULTIPLICADORA_H
#define BASE_CALCULATOR_MULTIPLICADORA_H

#include <string>

using namespace std;

// Classe que realiza multiplicacao entre dois valores
class Multiplicadora
{
private:
    string valor1;
    string valor2;
    int base;
    string multiplicarDoisDigitos(string, string, string);
    string somarValoresObtidos();
public:
    Multiplicadora(string, string, int);
    string multiplicarValores();
};

#endif
