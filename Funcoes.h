#include <iostream>
#include <fstream>
using namespace std;

struct produto
{
	char nome[16];
	float preco;
};


istream& operator>>(istream&, produto);

void linha(char = '=', unsigned char = 24);
void menu();

void Adicionar(produto[], char*);
