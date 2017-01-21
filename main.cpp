#include <fstream>
#include <iostream>

using namespace std;

bool validate_bf(int** sudoku, size_t n) {
	int sqn = (int)sqrt(n);
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n - 1; j++) {
			for (size_t k = j + 1; k < n; k++) {
				
				if (sudoku[i][j] == sudoku[i][k] || sudoku[j][i] == sudoku[k][i] || sudoku[(i / sqn) * sqn + j / sqn][(i % sqn) * sqn + j % sqn] == sudoku[(i / sqn) * sqn + k / sqn][(i % sqn) * sqn + k % sqn]) {
					return false;
				}
			}
		}
	}
	return true;
}

void bool_array_to_false(bool* a, int n) {
	for (size_t i = 0; i < n; i++) {
		a[i] = false;
	}
}

bool validate_bool(int** sudoku, size_t n) {
	bool* checkRow = new bool[n];
	bool* checkCol = new bool[n];
	bool* checkBl = new bool[n];
	
	int sqn = (int)sqrt(n);
	for (size_t i = 0; i < n; i++) {
		bool_array_to_false(checkRow, n);
		bool_array_to_false(checkCol, n);
		bool_array_to_false(checkBl, n);
		for (size_t j = 0; j < n; j++) {
			if (checkRow[sudoku[i][j]-1] || checkCol[sudoku[j][i]-1] || checkBl[sudoku[(i / sqn) * sqn + j / sqn][(i % sqn) * sqn + j % sqn]-1]) {
				delete[] checkRow;
				delete[] checkCol;
				delete[] checkBl;
				return false;
			}
			checkRow[sudoku[i][j]-1] = true;
			checkCol[sudoku[j][i]-1] = true;
			checkBl[sudoku[(i / sqn) * sqn + j / sqn][(i % sqn) * sqn + j % sqn]-1] = true;
		}
	}
	delete[] checkRow;
	delete[] checkCol;
	delete[] checkBl;
	return true;
}



//read sudoku from file stream
void read_soduko(fstream &fin, int** sudoku, size_t n) {
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			fin >> sudoku[i][j];
		}
	}
}


int main() {

	int** sudoku;
	size_t n;

	//input
	fstream fin("sudoku.in", ios::in);
	fin >> n;
	//alocate memory for sudoku
	sudoku = new int*[n];
	for (size_t i = 0; i < n; i++) {
		sudoku[i] = new int[n];
	}
	//read sudoku
	read_soduko(fin, sudoku, n);
	fin.close();

	//validate sudoku
	bool valid = validate_bf(sudoku, n);
	//bool valid = validate_bool(sudoku, n);

	fstream fout("sudoku.out", ios::out);
	fout << (valid ? "Valid" : "Not valid") << endl;
	fout.close();

	//dealocate memory
	for (size_t i = 0; i < n; i++) {
		delete[] sudoku[i];
	}
	delete[] sudoku;

	return 0;
}