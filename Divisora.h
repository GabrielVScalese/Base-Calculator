#ifndef BASE_CALCULATOR_DIVISORA_H
#define BASE_CALCULATOR_DIVISORA_H

#include <string>

using namespace std;

// Classe que realiza divisao entre dois valores
class Divisora
{
private:
    string valor1;
    string valor2;
    int numCasasDecimais;
    int base;
    string obterQuociente(string, string);
    void colocarVirgula (string *, string *, string *);
public:
    Divisora(string, string, int, int);
    string dividirValores();
    void setValor1 (string);
    void setValor2 (string);
    void setBase (int);
    void setNumCasasDecimais (int);
    bool operator!= (Divisora);
    bool operator== (Divisora);
};

#endif
