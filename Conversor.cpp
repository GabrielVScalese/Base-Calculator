#include <sstream>
#include <cmath>
#include "Conversor.h"
#include "Auxiliadora.h"

/* Arquivo de implementacao da classe Conversor */

// Metodo que converte um valor na base dez para outra base
string Conversor::dezParaOutra (long double valor, int baseValor)
{
    string ret;
    int quociente = (int) valor;

    do
    {
        int resto = quociente % baseValor;

        if (resto >= 10)
            ret.insert(0, Auxiliadora::getValorEmLetra(resto));
        else
            ret.insert(0, std::to_string(resto));

        quociente = quociente / baseValor;
    }
    while (quociente != 0);

    return ret;
}

// Metodo que converte um valor em uma base para a base dez
long double Conversor::outraParaDez (string valor, int baseValor)
{
    long double resultInteira = 0;
    long double resultDecimal = 0;
    long double result;
    int cont = 0;
    bool negativo = false;

    if(valor.find('-') == 0)
    {
        valor.erase(0, 1);
        negativo = true;
    }

    string parteInteira = valor.substr(0, valor.find(","));
    valor.erase(0, valor.find(",") + 1);
    string parteDecimal = valor.substr(0, valor.find(","));

    // Calculos com parte inteira
    for (int i = parteInteira.length() - 1; i >= 0 ; i--)
    {
        int digito = Auxiliadora::converterDigitoEmInteiro(string(1, parteInteira[i]));
        long double potencia = pow (baseValor, cont);
        resultInteira += digito * potencia;
        cont++;
    }

    // Calculos com parte decimal
    cont = -1;
    for (int i = 0; i < parteDecimal.length(); i++)
    {
        int digito = Auxiliadora::converterDigitoEmInteiro(string(1, parteDecimal[i]));
        long double potencia = pow (baseValor, cont);
        resultDecimal += digito * potencia;
        cont--;
    }

    result = resultInteira + resultDecimal;

     if(negativo)
      result = -result;

    return result;
}


