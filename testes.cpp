#include <iostream>
#include "Divisora.h"
#include "Multiplicadora.h"
#include "Somadora.h"
#include "Subtradora.h"

int main ()
{
    cout << "==== [ Programa de testes ] ==== ";

    // Classe Divisora
    Divisora div ("10", "10", 10, 1);
    Divisora div2 ("5", "10", 10, 1);
    Divisora div3 ("10", "10", 10, 1);

    cout << "\n\n---- Classe Divisora ----";
    cout << "\n\ntoString: " << div;

    if (div != div2)
        cout << "\ndiv eh diferente de div2";
    else
        cout << "\ndiv e div2 sao iguais";

    if (div == div3)
        cout << "\ndiv eh igual a div3";
    else
        cout << "\ndiv eh diferente de div3";

    // Classe Multiplicadora
    Multiplicadora mul ("20", "20", 10);
    Multiplicadora mul2 ("15", "15", 10);
    Multiplicadora mul3 ("20", "20", 10);

    cout << "\n\n---- Classe Multiplicadora ----";
    cout << "\n\ntoString: " << mul;

    if (mul != mul2)
        cout << "\nmul eh diferente de mul2";
    else
        cout << "\nmul e mul2 sao iguais";

    if (mul == mul3)
        cout << "\nmul eh igual a mul3";
    else
        cout << "\nmul eh diferente de mul3";

    // Classe Somadora
    Somadora som ("100", "100", 10);
    Somadora som2 ("45", "45", 10);
    Somadora som3 ("100", "100", 10);

    cout << "\n\n---- Classe Somadora ----";
    cout << "\n\ntoString: " << som;

    if (som != som2)
        cout << "\nsom eh diferente de som2";
    else
        cout << "\nsom e som2 sao iguais";

    if (som == som3)
        cout << "\nsom eh igual a som3";
    else
        cout << "\nsom eh diferente de som3";

    // Classe Subtradora
    Subtradora sub ("98", "98", 10);
    Subtradora sub2 ("32", "32", 10);
    Subtradora sub3 ("98", "98", 10);

    cout << "\n\n---- Classe Subtradora ----";
    cout << "\n\ntoString: " << sub;

    if (sub != sub2)
        cout << "\nsub eh diferente de sub2";
    else
        cout << "\nsub e sub2 sao iguais";

    if (sub == sub3)
        cout << "\nsub eh igual a sub3";
    else
        cout << "\nsub eh diferente de sub3";
}
