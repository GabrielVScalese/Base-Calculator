#include <sstream>
#include "Subtradora.h"
#include "Auxiliadora.h"
#include "Conversor.h"
#include "Validadora.h"

/* Arquivo de implementacao da classe Subtradora */

// Variavel que representa o indice atual numa busca de digito para emprestimo
int indiceAtual = 0;
// Variavel que representa o maior valor entre dois valores
string maiorValor;

// Construtor da classe Subtradora
Subtradora::Subtradora(string valor1, string valor2, int base)
{
    setValor1(valor1);
    setValor2(valor2);
    setBase(base);
}

// Metodo setter do atributo valor1
void Subtradora::setValor1(string valor1)
{
    if (valor1.empty())
        throw "Valor invalido";

    Subtradora::valor1 = valor1;
}

// Metodo setter do atributo valor2
void Subtradora::setValor2(string valor2)
{
    if (valor2.empty())
        throw "Valor invalido";

    Subtradora::valor2 = valor2;
}

// Metodo setter do atributo base
void Subtradora::setBase(int base)
{
    if (!Validadora::existsBase(base))
        throw "Base invalida";

    Subtradora::base = base;
}

// Metodo de comparacao (igual) entre dois objetos do tipo Subtradora
bool Subtradora::operator== (Subtradora sub)
{
    if (this->operator!=(sub))
        return false;
    else
        return true;
}

// Metodo de comparacao (diferente) entre dois objetos do tipo Subtradora
bool Subtradora::operator!= (Subtradora sub)
{
    if (this->valor1 != sub.valor1)
        return true;

    if (this->valor2 != sub.valor2)
        return true;

    if (this->base != sub.base)
        return true;

    return false;
}

// Metodo que printa os atributos do objeto
void Subtradora::print(ostream *os)
{
    *os << "Valor1: "  << valor1 << " | Valor2: " << valor2 << " | Base: " << base;
}

// Metodo que permite o uso do metodo print da classe
ostream &operator<< (ostream &os, Subtradora &div)
{
    div.print(&os);
    return os;
}

// Metodo que realiza um emprestimo para um determinado digito
int Subtradora::emprestarUm (int valor1) // Tem falha
{
    int copyIndiceAtual = indiceAtual;
    indiceAtual--;

    // Busca um digito para realizar o emprestimo
    for (;;)
    {
        if (maiorValor[indiceAtual] != '0' && maiorValor[indiceAtual] != ',')
            break;

        indiceAtual--;
    }

    if (isalpha(maiorValor[indiceAtual]))
    {
        int valorNumericoDigito = Conversor::outraParaDez(string(1, maiorValor[indiceAtual]), base);
        string novoValorDigito = Conversor::dezParaOutra(valorNumericoDigito - 1, base);
        maiorValor[indiceAtual] = *novoValorDigito.c_str();
    }
    else
    {
        int digitoEmprestimo = Auxiliadora::converterDigitoEmInteiro(string(1, maiorValor[indiceAtual]));
        maiorValor[indiceAtual] = *std::to_string(digitoEmprestimo - 1).c_str(); // Subtrai 1 do digito
    }

    // Se for necessario, passsa por todos os digitos ate chegar ao digito que precisa do emprestimo
    for (int i = indiceAtual + 1; i != copyIndiceAtual; i++)
    {
        if (maiorValor[i] == ',')
            continue;

        int digito = Auxiliadora::converterDigitoEmInteiro(string(1, maiorValor[i]));
        long double valorProvisorioDigito = Conversor::outraParaDez(to_string(digito + 10), base);
        maiorValor[i] = *Conversor::dezParaOutra(valorProvisorioDigito - 1, base).c_str(); // Subtrai, pois esta passando o emprestimo
    }

    if (valor1 >= 10) // Valor passado era uma letra
    {
        string valor1Convertido = Conversor::dezParaOutra(valor1, base);
        valor1Convertido.insert(0, "1");
        valor1 = Conversor::outraParaDez(valor1Convertido, base);
        return valor1;
    }

    return Conversor::outraParaDez(std::to_string(valor1 + 10), base);
}

// Metodo que subtrai dois digitos
string Subtradora::subtrairDoisDigitos (string digito1, string digito2)
{
    int valor1 = Auxiliadora::converterDigitoEmInteiro(digito1);
    int valor2 = Auxiliadora::converterDigitoEmInteiro(digito2);

    if (valor1 < valor2) // Precisa fazer emprestimo
        valor1 = emprestarUm(valor1);

    return Conversor::dezParaOutra(valor1 - valor2, base);
}

// Metodo que subtrai dois valores
string Subtradora::subtrairValores ()
{
    string ret = "";

    Auxiliadora::prepararValores(&valor1, &valor2);
    maiorValor = Auxiliadora::getMaiorValor(valor1, valor2);
    string menorValor = Auxiliadora::getMenorValor(valor1, valor2);

    for (int i = valor1.length() - 1; i >= 0; i--)
    {
        indiceAtual = i;

        if (string(1, maiorValor[i]) == ",") // Acabaram as contas com digitos apos a virgula
        {
            ret.insert(0, ",");
            continue;
        }

        ret.insert(0, subtrairDoisDigitos(string(1, maiorValor[i]), string(1, menorValor[i])));
    }

    return Auxiliadora::removerZerosAntesVirgula(ret); // Retira impurezas e retorna o resultado
}