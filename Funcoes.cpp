#include "Funcoes.h"

void menu()
{
	cout << "Sistema de controle\n";
	linha('=', 19);
	cout << "(P)edir\n"
			"(A)dicionar\n"
			"(E)xcluir\n"
			"(L)istar\n"
			"(S)air\n";
	linha('=', 19);
	cout << "Opção: [_]\b\b";
}
