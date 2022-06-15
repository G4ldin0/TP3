#include "funcoes.h"
#include "outros.h"

void linha(char ch, unsigned char tam)
{
	for(char i = 0; i < tam; i++)
		cout << ch;
	cout << endl;
}