#include <sstream>
#include "Auxiliadora.h"

/* Arquivo de implementacao da classe Auxiliadora */

// Metodo que retorna um valor (int) equivalente a uma letra
int Auxiliadora::getValorEmInteiro (string digito)
{
    string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (!isalpha(*digito.c_str()))
        return -1;

    return alfabeto.find(toupper(*digito.c_str())) + 10;
}

// Metodo que retorna o valor (string) equivalente de um inteiro
string Auxiliadora::getValorEmLetra (int valor)
{
    string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    return string (1, alfabeto[valor - 10]);
}

// Metodo que converte um digito (string) para um valor inteiro
int Auxiliadora::converterDigitoEmInteiro(string digito)
{
    int ret;

    if (isalpha(*digito.c_str()))
        ret = Auxiliadora::getValorEmInteiro(digito);
    else
    {
        stringstream st (digito);
        st >> ret;
    }

    return ret;
}

// Metodo que completa a parte inteira com zeros a esquerda
string Auxiliadora::completarParteInteira (string str, int qtd)
{
    for (int i = 0; i < qtd; i++)
        if (str[i] == ',')
            break;
        else
            str.insert(0, "0");

    return str;
}

// Metodo que complementa a parte decimal com zeros a direita
string Auxiliadora::completarParteDecimal (string str, int qtd)
{
    for (int i = 0; i < qtd; i++)
        str.append("0");

    return str;
}

// Metodo que retorna a quantidade de casas decimais de um valor
int Auxiliadora::getQtdDecimais (string valor)
{
    int index = valor.find(",");

    if (index == -1)
        return 0;

    int ret = -1;
    for (; index < valor.length(); index++)
        ret++;

    return ret;
}

// Metodo que retorna a quantidade de valores a direita da virgula
int Auxiliadora::getQtdInteiros (string valor)
{
   return valor.length() - getQtdDecimais(valor) - 1;
}

// Metodo que complementa os valores (parte inteira e/ou parte decimal com zeros) se for necessario
void Auxiliadora::prepararValores (string *valor1, string *valor2)
{
    if (getQtdInteiros(*valor1) > getQtdInteiros(*valor2))
        *valor2 = completarParteInteira (*valor2, getQtdInteiros(*valor1) - getQtdInteiros(*valor2));
    else
        *valor1 = completarParteInteira (*valor1, getQtdInteiros(*valor2) - getQtdInteiros(*valor1));

    if (getQtdDecimais(*valor1) > getQtdDecimais(*valor2))
        *valor2 = completarParteDecimal(*valor2, getQtdDecimais(*valor1) - getQtdDecimais(*valor2));
    else
        *valor1 = completarParteDecimal(*valor1, getQtdDecimais(*valor2) - getQtdDecimais(*valor1));
}

// Metodo que retorna o maior valor entre dois valores
string Auxiliadora::getMaiorValor(string valor1, string valor2)
{
    if (valor1.length() > valor2.length())
        return valor1;
    else
        if (valor2.length() > valor1.length())
            return valor2;
        else
        {
            for (int i = 0; i < valor1.length(); i++)
            {
                if (string(1, valor1[i]) == ",")
                    continue;

                int digitoValor1 = converterDigitoEmInteiro(string(1, valor1[i]));
                int digitoValor2 = converterDigitoEmInteiro(string(1, valor2[i]));

                if (digitoValor1 == digitoValor2)
                    continue;
                else
                {
                    if (digitoValor1 > digitoValor2)
                        return valor1;
                    else
                        return valor2;
                }
            }
        }

    return valor1;
}

// Metodo que retorna o menor valor entre dois valores
string Auxiliadora::getMenorValor(string valor1, string valor2)
{
    if (getMaiorValor(valor1, valor2) == valor1)
        return valor2;
    else
        return valor1;
}

// Metodo que insere virgula em uma determinada posicao
string Auxiliadora::inserirVirgula(string valor, int posicao)
{
    string ret;

    int j = 0;
    for (int i = 0; valor[j]; i++)
    {
        if (i == posicao)
            ret += ",";

        ret += valor[j];
        j++;
    }

    return ret;
}

// Metodo que remove de uma string um determinado caractere
string Auxiliadora::removerCaracter(char carac, string valor)
{
    unsigned int i = 0, j = 0;

    while (i < valor.length())
    {
        if (valor.at(i) != carac)
            valor.at(j++) = valor.at(i);

        i++;
    }

    return valor.substr(0, valor.size() - 1);
}

// Metodo boolean que verifica se o valor tem apenas zeros
int Auxiliadora::apenasZeros (string valor)
{
    for (char c : valor)
        if (c == ',')
            continue;
        else
            if (c != '0')
                return 0;

    return 1;
}

// Metodo que remove zeros a esquerda da virgula
string Auxiliadora::removerZerosAntesVirgula (string valor)
{
    if (apenasZeros(valor))
        return valor;

    while (valor.at(0) == '0')
           if (valor.at(1) == ',')
               break;
           else
               valor.erase(0, 1);

    return valor;
}

// Metodo que remove um certo numero de casas decimais
string Auxiliadora::removerCasasDecimais(string valor, int numCasasDecimais)
{
    int index = valor.find(",");

    if (index == -1)
        return valor;

    for (int i = valor.length() - 1, j = 0; j != numCasasDecimais; i = valor.length() - 1, j++)
         if (valor[i] == ',')
             break;
         else
            valor.erase(i, 1);

    return valor;
}