#include <sstream>
#include <cmath>
#include "Conversor.h"
#include "Auxiliadora.h"

/* Arquivo de implementacao da classe Conversor */

// Metodo que converte um valor na base dez para outra base
string Conversor::dezParaOutra (long double valor, int base) {
    string ret;
    int resto;
    int quociente = (int) valor;

    do
    {
        resto = quociente % base;

        if (resto >= 10)
            ret.insert(0, Auxiliadora::getValorEmLetra(resto));
        else
            ret.insert(0, std::to_string(resto));

        quociente = quociente / base;
    }
    while (quociente != 0);

    return ret;
}

// Metodo que converte um valor em uma base para a base dez
long double Conversor::outraParaDez(string valor, int baseValor)
{
    long double result = 0;
    unsigned int cont = 0;

    for (int i = valor.length() - 1; i >= 0 ; i--)
    {
        if (isalpha(valor[i])) // Se o digito e letra
        {
            unsigned int digito = Auxiliadora::getValorEmInteiro(string(1, valor[i]));
            long double potencia = pow (baseValor, cont);
            result += digito * potencia;
            cont++;
        }
        else
        {
            int digito;
            stringstream st (string(1, valor[i]));
            st >> digito;
            long double potencia = pow (baseValor, cont);
            result += digito * potencia;
            cont++;
        }
    }

    return result;
}


