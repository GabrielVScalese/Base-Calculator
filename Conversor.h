#ifndef BASE_CALCULATOR_CONVERSOR_H
#define BASE_CALCULATOR_CONVERSOR_H

using namespace std;

// Classe estatica que realiza conversoes entre bases numericas
class Conversor
{
public:
    static string dezParaOutra (long double, int);
    static long double outraParaDez (string, int);
};

#endif
