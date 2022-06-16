#include "Funcoes.h"


int main()
{
	setlocale(LC_ALL, "portuguese");


	//leitura do arquivo de estoque
	ifstream fin;
	fin.open("Estoque.bin", ios_base:: in | ios_base::binary);
	
	//numero de elementos no arquivo
	char TamEstoque{};
	fin.read((char*)&TamEstoque, 1);
	
	//elementos no arquivo
	produto* estoque = new produto[TamEstoque];
	for(int i = 0; i < TamEstoque; i++)
	{
		fin.read(estoque[i].nome, 16);
		fin.read((char*)&estoque[i].preco, 4);
		fin.read((char*)&estoque[i].quantidade, 4);
		}
	
	fin.close();

	char EscolhaMenu{};
	while (EscolhaMenu != 'S')
	{

		//limpa tela do loop
		system("CLS");
		
		//display e navegação do menu
		menu();
		cin >> EscolhaMenu;

		EscolhaMenu = toupper(EscolhaMenu);
		switch (EscolhaMenu)
		{
			case 'A':
				Adicionar(estoque, &TamEstoque);
			break;

			case 'E':
				Excluir(estoque,&TamEstoque);
			break;

			case 'L':
				Listar(estoque, TamEstoque);
			break;
			
			case 'S':
				cout << "Finalizando...\n";
			break;

			default:
				cout << endl << "Opção inválida";
			break;
		}

	}
	
	//sobrescrever o arquivo binário com as novas informações
	ofstream fout;
	fout.open("Estoque.bin", ios_base::binary | ios_base::out | ios_base::trunc);
	
	fout.write((char*)&TamEstoque, 1);

	for (int i = 0; i < TamEstoque; i++)
	{
		fout.write((char*)estoque[i].nome, 16);
		fout.write((char*)&estoque[i].preco, 4);
		fout.write((char*)&estoque[i].quantidade, 4);
	}
	fout.close();
	delete[] estoque;
}
