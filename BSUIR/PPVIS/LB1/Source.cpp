#include <iostream>
#include <fstream>
#include <iostream>

using namespace std;

ifstream in("input.txt");

class matrix
{
private:
	 
	int** mas; //матрица
public:
	int m, n; //строка столбец, перенес в public потому что нужно сравнивать переменные в int main
	matrix() { m = n = 0; } //конструктор по умолчанию
	matrix(const matrix& main) //конструктор копирования 
	{
		m = main.m;
		n = main.n;

		mas = new int* [m];

		for (int i = 0; i < m; i++)
		{
			mas[i] = new int[n];
		}

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				mas[i][j] = main.mas[i][j];
	}
	void show()   //метод отображения матрицы mas
	{
		if (m == 0 && n == 0) { cout << "Your matrix doesn't exist yet! \n"; return; }
		for (int i = 0; i < m; i++)
		{
			cout << endl;
			for (int j = 0; j < n; j++)
			{
				cout << mas[i][j] << " ";
			}
		}
	}
	matrix(int M, int N) //конструктор для создания матрицы m*n
	{
		m = M;
		n = N;

		mas = new int* [m];

		for (int i = 0; i < m; i++)
		{
			mas[i] = new int[n];
		}

	}

	void set(int M, int N) { //создание матрицы m*n
		m = M;
		n = N;

		mas = new int* [m];

		for (int i = 0; i < m; i++)
		{
			mas[i] = new int[n];
		}

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				mas[i][j] = 1;
	} 

	matrix reset(int R, int sw) //добавление рядов/колонок
	{
		int** newmas;
		int X, Y;
		if (sw == 0) 
		{
			X = m + R;
			Y = n;
		}
		if (sw == 1)
		{
			X = m;
			Y = n + R;
		}
		newmas = new int* [X];

		for (int i = 0; i < X; i++)
		{
			newmas[i] = new int[Y];
		}

		for (int i = 0; i < X; i++)
			for (int j = 0; j < Y; j++)
				newmas[i][j] = 0;

		for(int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
			{
				newmas[i][j] = mas[i][j];
			}

		for (int i = 0; i < n; i++)
		{
			delete[] mas[i];
		}
		delete[] mas;


		mas = newmas;
		m = X;
		n = Y;
		matrix p;
		p.m = m;
		p.n = n;
		p.mas = mas;
		return p;
	} 

	matrix remove(int C, int SW) //удаление рядов/колонок
	{	

		int** newmas;
		int X, Y;
		if (SW == 0)
		{
			X = m - C;
			Y = n;
		}
		if (SW == 1)
		{
			X = m;
			Y = n - C;
		}
		newmas = new int* [X];

		for (int i = 0; i < X; i++)
		{
			newmas[i] = new int[Y];
		}

		for (int i = 0; i < X; i++)
			for (int j = 0; j < Y; j++)
			{
				newmas[i][j] = mas[i][j];
			}

		for (int i = 0; i < n; i++)
		{
			delete[] mas[i];
		}
		delete[] mas;


		mas = newmas;
		m = X;
		n = Y;
		matrix p;
		p.m = m;
		p.n = n;
		p.mas = mas;
		return p;
	}


	void load() {
//очистка матрицы
		if (n != m != 0)
		{
			for (int i = 0; i < m; i++)
			{
				delete[] mas[i];
			}
			delete[] mas;
		}
//считаем количество символов в файле
		if (in.is_open())
		{
			int counter = 0; // число чисел в файле
			int temp; //временная переменная, сюда будем считывать числа из файла, для определения их количества

			while (!in.eof())
			{
				in >> temp;
				counter++;
			}


			in.seekg(0, ios::beg);
			in.clear();
 //подсчет количества пробелов
			int pr = 0; //количество пробелов
			char symbol; //переменноая для посимвольного считывания
			while (!in.eof())
			{ 
				in.get(symbol);
				if (symbol == ' ') pr++;
				if (symbol == '\n') break;
			}

			in.seekg(0, ios::beg); //переходим в начало для последующего считывания матрицы
			in.clear();


			m = counter / (pr + 1);
			n = pr + 1;

			mas = new int* [m];
			for (int i = 0; i < m; i++)
			{
				mas[i] = new int[n];
			}


			for (int i = 0; i < m; i++) //считывание
				for (int j = 0; j < n; j++)
					in >> mas[i][j];


			in.close();
		}
		else
		{
			cout << "Whoops, seems that your file doesn't exist or it's already opened\n"; system("pause");
		}
	}

	matrix transpose() { //транспонирование матрицы
		int** trans;
		int tmp;

		trans = new int* [n];
		for (int i = 0; i < n; i++)
			trans[i] = new int[m];

		for(int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
			{
				trans[j][i] = mas[i][j];
			}


		for (int i = 0; i < m; i++)
		{
			delete[] mas[i];
		}
		delete[] mas;

		matrix p;

		p.n = m;
		p.m = n;
		p.mas = trans;

		return p;
	}

	void matrixtype() { 
		int counter = 0;

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				if (mas[i][j] == 0) counter++;
		if (counter == m * n) { cout << " Zero/Null\n"; return; } //нулевая

		if (m == n)
		{
			cout << "Square ";
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			for (int i = 0; i < m; i++)
				for (int j = 0; j < m; j++)
				{
					if (i == j) continue;
					else {
						if (mas[i][j] == 0) counter++;
					}
				}
			if (counter == m * (n - 1)) 
			{
				counter = 0;
			for (int i = 0; i < m; i++)
				{
				if (mas[i][i] == 1) counter++;
				}
			if (counter == m)
			{
				cout << "+ Identity";
				return;
			}
			}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			counter = 0;
			for (int i = 0; i < m; i++)
				for (int j = 0; j < m; j++)
				{
					if (i == j) continue;
					else {
						if (mas[i][j] == 0) counter++;
					}
				}
			if (counter == m * (n - 1)) { cout << "+ Diagonal \n"; return; }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			counter = 0;
			for(int i = 0; i< m; i++)
				for (int j = 0; j < m; j++)
				{
					if (mas[i][j] == mas[j][i]) counter++;
				}
			if (counter == m * n) { cout << "+ Symmetric \n"; counter = 0; return; }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			counter = 0;
			for (int i = 0; i < m; i++)
				for (int j = 0; j < m; j++)
				{
					if (i < j) continue;
					else
					{
						if (mas[i][j] == 0) counter++;
					}
				}
			if (counter == n * (n - 1) / 2)
			{
				cout << " Lower triangular\n";
				return;
			}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			counter = 0;
			for (int i = 0; i < m; i++)
				for (int j = 0; j < m; j++)
				{
					if (i > j) continue;
					else
					{
						if (mas[i][j] == 0) counter++;
					}
				}
			if (counter == n * (n - 1) / 2)
			{
				cout << " Upper triangular\n";
				return;
			}


		}//Все для квадратной матрицы
		cout << "Default rectangular array \n";
		return;
	}

	void submatrix(int size)
	{
		if (size > n)
		{
			cout << "Can't eject submatrix with size more than " << n << "!";
			return;
		}
		cout << "Number of submatrixes with size "<< size <<": "<< (n - size + 1) * (n - size + 1) << endl;
		cout << "All submatrixes with size: " << size << endl;
		for(int x = 0; x <= n - size; x++)
			for (int y = 0; y <= n - size; y++)
			{
				cout << endl;
				for (int i = x; i < size + x; i++)
				{
					cout << endl;
					for (int j = y; j < size + y; j++)
						cout << mas[i][j] << " ";
				}
			}
		cout << endl;
	}

};



matrix arr;

int main()
{
	int z;
	while (true)
	{
		system("cls");
		cout << " 1 - create matrix \n 2 - view matrix \n 3 - edit matrix \n 4 - load matrix \n 5 - transpose matrix\n 6 - eject submatrix \n 7 - identify matrix type\n 0 - exit \n";
		cin >> z;
		switch (z)
		{
		case 1:
		{
			int x, y;
			cout << "Number of rows: \n";
			cin >> x;
			cout << "Number of cols: \n";
			cin >> y;
			arr.set(x, y);
			system("pause");
			break;
		}
		case 2:
		{
			
			if (arr.m == 0 && arr.n != 0) {
				cout << "Look at this matrix.. 0 rows and " << arr.n << "columns! Amazing, good job. \n"; system("pause"); break;
			}
			if (arr.m != 0 && arr.n == 0) {
				cout << "Look what you've done! "<< arr.m <<" rows while 0 columns.. I mean, how would this work exactly? \n"; system("pause"); break;
			}
			arr.show();
			cout << endl;
			system("pause");
			break;
		}
		case 3:
		{
			int f;
			cout << "1 - add certain nuber of rows \n 2 - remove certain number of rows \n 3 - add certain number of cols \n 4 - remove certain number of cols \n";
			cin >> f;
			switch (f)
			{
			case 1:
			{
				int r;
				cout << "How much rows do you want to add: \n";
				cin >> r;
				arr = arr.reset(r, 0);
				system("pause");
				break;
			}
			case 2:
			{
				if (arr.m == 0) { cout << "Matrix is epmty, nothing to remove! \n"; break; }
				int r;
				cout << "How much rows do you want to remove: \n";
				cin >> r;
				if (r > arr.m) { cout << "Number should be less then: " << arr.m; system("pause"); break; }
				arr = arr.remove(r, 0);
				system("pause");
				break;
			}
			case 3:
			{
				int r;
				cout << "How much columns do you want to add: \n";
				cin >> r;
				arr = arr.reset(r, 1);
				system("pause");
				break;
			}
			case 4:
			{
				if (arr.n == 0) { cout << "Matrix is epmty, nothing to remove! \n"; break; }
				int r;
				cout << "How much columns do you want to remove: \n";
				cin >> r;
				
				if (r > arr.m) { cout << "Number should be less then: " << arr.n; system("pause"); break; }
				arr = arr.remove(r, 1);
				system("pause");
				break;
			}
			}
			break;
		}
		case 4:
		{
			arr.load();
			break;
		}
		case 5:
			arr = arr.transpose();
			break;
		case 6:
		{
			int S;
			cout << "Enter the required size of submatrix: ";
			cin >> S;
			system("cls");
			arr.submatrix(S);
			system("pause");
			break;
		}
		case 7:
		{
			arr.matrixtype();
			system("pause");
		}
		case 0:
			exit(0);
		}

	}

	system("pause");
	return 0;
};





