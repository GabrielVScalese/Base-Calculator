#include "Somadora.h"
#include "Conversor.h"
#include "Auxiliadora.h"
#include <string>
#include <sstream>
#include "Validadora.h"

/* Arquivo de implementacao da classe Somadora */

using namespace std;

// Construtor da classe Somadora
Somadora::Somadora(string valor1, string valor2, int base)
{
    setValor1(valor1);
    setValor2(valor2);
    setBase(base);
}

// Metodo setter do atributo valor1
void Somadora::setValor1(string valor1)
{
    if (valor1.empty())
        throw "Valor invalido";

    Somadora::valor1 = valor1;
}

// Metodo setter do atributo valor2
void Somadora::setValor2(string valor2)
{
    if (valor2.empty())
        throw "Valor invalido";

    Somadora::valor2 = valor2;
}

// Metodo setter do atributo base
void Somadora::setBase(int base)
{
    if (!Validadora::existsBase(base))
        throw "Base invalida";

    Somadora::base = base;
}

// Metodo de comparacao (igual) entre dois objetos do tipo Somadora
bool Somadora::operator== (Somadora som)
{
    if (this->operator!=(som))
        return false;
    else
        return true;
}

// Metodo de comparacao (diferente) entre dois objetos do tipo Somadora
bool Somadora::operator!= (Somadora som)
{
    if (this->valor1 != som.valor1)
        return true;

    if (this->valor2 != som.valor2)
        return true;

    if (this->base != som.base)
        return true;

    return false;
}

// Metodo que printa os atributos do objeto
void Somadora::print(ostream *os)
{
    *os << "Valor1: "  << valor1 << " | Valor2: " << valor2 << " | Base: " << base;
}

// Metodo que permite o uso do metodo print da classe
ostream &operator<< (ostream &os, Somadora &div)
{
    div.print(&os);
    return os;
}

// Metodo que soma dois digitos
string Somadora::somarDoisDigitos (string digito1, string digito2, string passaUm, int base)
{
    int adicional = 0;

    int valor1 = Auxiliadora::converterDigitoEmInteiro(digito1);
    int valor2 = Auxiliadora::converterDigitoEmInteiro(digito2);
    
    if (!passaUm.empty()) // Existe um "passa um"
        adicional = Auxiliadora::converterDigitoEmInteiro(passaUm);
    
    return Conversor::dezParaOutra(valor1 + valor2 + adicional, base);
}

// Metodo que soma dois valores
string Somadora::somarValores()
{
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

    return Auxiliadora::removerZerosAntesVirgula(ret); // Retira impurezas antes de retornar
}



