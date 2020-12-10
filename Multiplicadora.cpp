#include <string>
#include "Multiplicadora.h"
#include "Auxiliadora.h"
#include "Somadora.h"
#include "Conversor.h"
#include "Validadora.h"
#include <iostream>

/* Arquivo de implementacao da classe Multiplicadora */

using namespace std;

// Variavel que representa um vetor de valores obtidos durante uma multiplicacao
string valoresObtidos [1000];
// Variavel que representa que indica o indice atual do vetor de valores obtidos
int cont = 0;

// Construtor da classe
Multiplicadora::Multiplicadora(string valor1, string valor2, int base)
{
    setValor1(valor1);
    setValor2(valor2);
    setBase(base);
}

// Metodo setter do atributo valor1
void Multiplicadora::setValor1(string valor1)
{
    if (valor1.empty())
        throw "Valor invalido";

    Multiplicadora::valor1 = valor1;
}

// Metodo setter do atributo valor2
void Multiplicadora::setValor2(string valor2)
{
    if (valor2.empty())
        throw "Valor invalido";

    Multiplicadora::valor2 = valor2;
}

// Metodo setter do atributo base
void Multiplicadora::setBase(int base)
{
    if (!Validadora::existsBase(base))
        throw "Base invalida";

    Multiplicadora::base = base;
}

// Metodo de comparacao (igual) entre dois objetos do tipo Multiplicadora
bool Multiplicadora::operator== (Multiplicadora mul)
{
    if (this->operator!=(mul))
        return false;
    else
        return true;
}

// Metodo de comparacao (diferente) entre dois objetos do tipo Multiplicadora
bool Multiplicadora::operator!= (Multiplicadora mul)
{
    if (this->valor1 != mul.valor1)
        return true;

    if (this->valor2 != mul.valor2)
        return true;

    if (this->base != mul.base)
        return true;

    return false;
}

// Metodo que printa os atributos do objeto
void Multiplicadora::print(ostream *os)
{
    *os << "Valor1: "  << valor1 << " | Valor2: " << valor2 << " | Base: " << base;
}

// Metodo que permite o uso do metodo print da classe
ostream &operator<< (ostream &os, Multiplicadora &div)
{
    div.print(&os);
    return os;
}

// Metodo que insere um valor no fim do vetor valoresObtidos
void inserirNoFim (string valor)
{
    valoresObtidos[cont++] = valor;
}

// Metodo que realiza uma multiplicacao entre dois digitos
string Multiplicadora::multiplicarDoisDigitos(string digito1, string digito2, string passaUm)
{
    int valor1 = Auxiliadora::converterDigitoEmInteiro(digito1);
    int valor2 = Auxiliadora::converterDigitoEmInteiro(digito2);
    int adicional = 0;

    if (!passaUm.empty()) // Existe um "passaUm"
        adicional = Auxiliadora::converterDigitoEmInteiro(passaUm);

    return Conversor::dezParaOutra((valor1 * valor2) + adicional, base);
}

// Metodo que soma os valores obtidos durante a multiplicacao
string Multiplicadora::somarValoresObtidos()
{
    string ret = valoresObtidos[0];
    for (int i = 0; i < valoresObtidos->length() - 1; i++)
    {
        if (valoresObtidos[i + 1].empty())
            break;

        Somadora som (ret, valoresObtidos[i + 1], base);
        ret = som.somarValores();
    }

    ret = Auxiliadora::removerZerosAntesVirgula(Auxiliadora::inserirVirgula(ret, ret.length() -
    (Auxiliadora::getQtdDecimais(valor1) * 2))); // Retira impurezas do produto final

    return ret;
}

// Metodo que realiza a multiplicacao entre dois valores
string Multiplicadora::multiplicarValores()
{
    string ret;
    string passaUm;

    Auxiliadora::prepararValores(&valor1, &valor2); // Prepara os valores para iniciar a multiplicacao
    string maiorValor = Auxiliadora::getMaiorValor(valor1, valor2);
    string menorValor = Auxiliadora::getMenorValor(valor1, valor2);

    int qtdZeros = -1; // Para saber quantos zeros descemos ao comecar cada multiplicacao de um digito
    for (int i = valor1.length() - 1; i >= 0; i--)
    {
        for (int j = valor1.length() - 1; j >= 0; j--)
        {
            if (string(1, maiorValor[j]) == "," || string(1, menorValor[i]) == "," || string(1, maiorValor[j]) == "")
                continue;

            string produtoDeDoisDigitos = multiplicarDoisDigitos(string(1, menorValor[i]),
                                                                 string(1, maiorValor[j]), passaUm);

            if (produtoDeDoisDigitos.length() > 1)
            {
                passaUm = produtoDeDoisDigitos.substr(0, produtoDeDoisDigitos.length() - 1);
                ret.insert(0, produtoDeDoisDigitos.substr(produtoDeDoisDigitos.length() - 1, 1));

                if (j == 0)
                    ret.insert(0, passaUm);
            }
            else
            {
                ret.insert(0, produtoDeDoisDigitos);
                passaUm = "";
            }
        }

        if (!ret.empty()) // Quando o digito atual e virgula, ignoramos o seu "produto"
        {
            qtdZeros++;
            ret.insert(ret.length(), qtdZeros, '0');
            inserirNoFim(ret);
        }

        ret = "";
        passaUm = "";
    }

    string resultadoFinal = somarValoresObtidos();
    valoresObtidos->erase();
    cont = 0;
    return resultadoFinal;
}


