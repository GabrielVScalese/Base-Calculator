#include <sstream>
#include "Subtradora.h"
#include "Auxiliadora.h"
#include "Conversor.h"

/* Arquivo de implementacao da classe Subtradora */

// Atributo que representa o indice atual numa busca de digito para emprestimo
int indiceAtual = 0;
// Atributo que representa o maior valor entre dois valores
string maiorValor;

// Construtor da classe Subtradora
Subtradora::Subtradora(string valor1, string valor2, int base)
{
    Subtradora::valor1 = valor1;
    Subtradora::valor2 = valor2;
    Subtradora::base = base;
}

// Metodo que realiza emprestimo para um determinado digito
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
        stringstream st (string(1, maiorValor[indiceAtual]));
        int digitoEmprestimo; // Digito que realiza o emprestimo
        st >> digitoEmprestimo; // Guarda-se o valor do digito que realiza o emprestimo
        maiorValor[indiceAtual] = *std::to_string(digitoEmprestimo - 1).c_str(); // Subtrai 1 do digito
    }

    // Se for necessario, passsa por todos os digitos ate chegar ao digito que precisa do emprestimo
    for (int i = indiceAtual + 1; i != copyIndiceAtual; i++)
    {
        if (maiorValor[i] == ',')
            continue;

        stringstream st(string(1, maiorValor[i]));
        int digito;
        st >> digito;

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

// Metodo que subtrai dos digitos
string Subtradora::subtrairDoisDigitos (string digito1, string digito2) {
    int valor1 = Auxiliadora::converterDigitoEmInteiro(digito1);
    int valor2 = Auxiliadora::converterDigitoEmInteiro(digito2);

    if (valor1 < valor2) // Precisa fazer emprestimo
        valor1 = emprestarUm(valor1);

    return Conversor::dezParaOutra(valor1 - valor2, base);
}

// Metodo que subtrai dois valores
string Subtradora::subtrairValores () {
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

    return Auxiliadora::removerZeros(ret); // Retira impurezas e retorna o resultado
}