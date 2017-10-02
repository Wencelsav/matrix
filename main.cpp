#include <iostream>

#include <sstream>

using namespace std;


bool getmatrix(int matrx[3][3]) {

	bool res = false;

	for (int j = 0; j < 3; j++) {

		for (string string; getline(cin, string);) {

			istringstream stream(string);

			for (int i = 0; i < 3; ++i) {

				if (!(stream >> matrx[i][j])) {

					res = true;

				}

			}

		}

	}

	return res;

}

int main() {

	int matrix[3][3];

	int matrix1[3][3];

	bool failure = false;

	char com;

	for (string string; getline(cin, string);) {

		istringstream stream(string);

		if (!(stream >> com)) {

			failure = true;
		}
	}

	failure = getmatrix(matrix1);

	if (!failure) {

		switch (com) {

		case '+':

			for (int j = 0; j < 3; ++j) {

				for (int i = 0; i < 3; ++i) {

					matrix[i][j] = matrix[i][j] + matrix1[i][j];

				}
			}

			break;

		case '-':

			for (int j = 0; j < 3; ++j) {

				for (int i = 0; i < 3; ++i) {

					matrix[i][j] = matrix[i][j] - matrix1[i][j];

				}
			}

			break;

		case '*':

			int mat[3][3];

			for (int j = 0; j < 3; ++j) {

				for (int i = 0; i < 3; ++i) {

					mat[i][j] = matrix[i][j];

				}
			}

			for (int j = 0; j < 3; ++j) {

				for (int i = 0; i < 3; ++i) {

					matrix[i][j] = mat[i][0] * matrix1[0][j] + mat[i][1] * matrix1[1][j] + mat[i][2] * matrix1[2][j];

				}
			}
			
		}



		for (int j = 0; j < 3; ++j) {

			for (int i = 0; i < 3; ++i) {

				cout << matrix[i][j] << " ";

			}cout << "\n";
		}

	}

	else {

		cout << "An error has occured while reading numbers from line" ;

	}

	return 0;
}
