#include "Somadora.h"
#include "Conversor.h"
#include "Auxiliadora.h"
#include <string>
#include <sstream>

/* Arquivo de implementacao da classe Somadora */

using namespace std;

// Construtor da classe Somadora
Somadora::Somadora(string valor1, string valor2, int base) {
    Somadora::valor1 = valor1;
    Somadora::valor2 = valor2;
    Somadora::base = base;
}

// Metodo que soma dos digitos
string Somadora::somarDoisDigitos (string digito1, string digito2, string passaUm, int base) {
    int valor1;
    int valor2;
    int adicional = 0;

    valor1 = Auxiliadora::converterDigitoEmInteiro(digito1);
    valor2 = Auxiliadora::converterDigitoEmInteiro(digito2);
    
    if (!passaUm.empty()) // Existe um "passa um"
    {
        stringstream st (passaUm);
        st >> adicional;
    }
    
    return Conversor::dezParaOutra(valor1 + valor2 + adicional, base);
}

// Metodo que soma dois valores
string Somadora::somarValores() {
    string ret = "";
    string passaUm = "";

    Auxiliadora::prepararValores(&valor1, &valor2); // Prepara os valores para iniciar a soma

    for (int i = valor1.length() - 1; i >= 0; i--)
    {
        string digito1(1, valor1[i]);
        string digito2(1, valor2[i]);

        if (digito1 == ",")
        {
            ret.insert(0, ",");
            continue;
        }

        string somaDosDoisDigitos = somarDoisDigitos(digito1, digito2, passaUm, base);
        if (somaDosDoisDigitos.length() > 1) // Existe um "passaUm"
        {
            passaUm = somaDosDoisDigitos.substr(0, somaDosDoisDigitos.length() - 1);
            ret.insert(0, somaDosDoisDigitos.substr(somaDosDoisDigitos.length() - 1, 1));

            if (i == 0)
                ret.insert(0, passaUm);
        }
        else
        {
            ret.insert(0, somaDosDoisDigitos);
            passaUm = "";
        }
    }

    return ret;
}



