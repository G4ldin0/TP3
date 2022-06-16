#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

struct produto
{
	char nome[16];
	float preco;
	float quantidade;
};


istream& operator>>(istream&, produto&);

void linha(ostream& = cout, char = '=', unsigned char = 24);
produto* AumentarTamanhodeVetor(produto[], char*);
void menu();

void Pedir(produto*, char*);
void Adicionar(produto*, char*);
void Listar(produto*, char);
void Excluir(produto*, char*);
