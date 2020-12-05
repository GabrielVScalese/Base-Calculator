#ifndef BASE_CALCULATOR_AUXILIADORA_H
#define BASE_CALCULATOR_AUXILIADORA_H

#include <string>

using namespace std;

// Classe estatica que auxilia as classes operacionais
class Auxiliadora
{
private:
    static string completarParteInteira (string, int);
    static int getQtdInteiros (string);
public:
    static int getValorEmInteiro (string);
    static string getValorEmLetra (int);
    static int converterDigitoEmInteiro (string);
    static void prepararValores (string *, string *);
    static string getMaiorValor (string, string);
    static string getMenorValor (string, string);
    static string inserirVirgula (string, int);
    static int getQtdDecimais (string);
    static string completarParteDecimal (string, int);
    static string removerCaracter (char, string);
    static string removerZeros (string);
    static int apenasZeros (string);
    static string removerCasasDecimais (string, int);
};

#endif

