#ifndef BASE_CALCULATOR_VALIDADORA_H
#define BASE_CALCULATOR_VALIDADORA_H

#include <string>

using namespace std;

// Classe estatica que valida se uma determinada base existe ou se um determinado valor existe em uma base
class Validadora
{
public:
    static int existsBase (int);
    static int existsInBase (string, int);
};

#endif //BASE_CALCULATOR_VALIDADORA_H
