#include "Validadora.h"
#include "Auxiliadora.h"

/* Arquivo de implementacao da classe Validadora */

// Metodo que verifica a existencia de uma base
int Validadora::existsBase(int base) {
    return base >= 2 && base <= 36;
}

// Metodo que verifica se um valor existe em uma base
int Validadora::existsInBase(string valor, int base) {
    for (char c : valor)
    {
        if (c == ',')
            continue;

        int valorChar = Auxiliadora::converterDigitoEmInteiro(string(1, c));

        if (valorChar >= base)
            return 0;
    }

    return 1;
}