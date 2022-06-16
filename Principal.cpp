#include "Funcoes.h"


int main()
{
	setlocale(LC_ALL, "portuguese");

	ifstream fin;
	fin.open("Estoque.bin", ios_base:: in | ios_base::binary);

	char TamEstoque{};

	fin.read((char*)&TamEstoque, 1);
	produto* estoque = new produto[TamEstoque];
	for(int i = 0; i < TamEstoque; i++)
	{
		fin.read(estoque[i].nome, 16);
		fin.read((char*)&estoque[i].preco, 4);
	}


	fin.close();
	cout << fixed; cout.precision(2);
	cout << estoque[0].nome << " " << estoque[0].preco;

	char EscolhaMenu{};
	while (EscolhaMenu != 'S')
	{
		//display e navegação do menu

		menu();
		cin >> EscolhaMenu;

		EscolhaMenu = toupper(EscolhaMenu);
		switch (EscolhaMenu)
		{
			case 'A':
			Adicionar(estoque, &TamEstoque);
			break;
			
			case 'S':
				cout << "Finalizando...\n";
				system("Pause");
			break;

			default:
				cout << endl << "Opção inválida";
			break;
		}

		//limpa tela do loop
		system("CLS");
	}
	/*
	ofstream fout;
	fout.open("Estoque.bin", ios_base::binary | ios_base::out);
	int temp = 1;
	float ftemp = 2.5f;
	fout.write((char*)&temp, 1);
	fout.write("Quejo", 16);
	fout.write((char*)&ftemp, 4);
	fout.close();
	*/
}

