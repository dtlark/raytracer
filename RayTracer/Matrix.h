#pragma once

#include "Tuples.h"
#include <algorithm>
#include <ostream>
#include <vector>
#include <cmath>

using namespace std;

class Matrix {

	int row = 0;
	int col = 0;
	vector<vector<float>> data;

public:

	Matrix() {

		//init to identity matrix
		//identity matrix * tuple = tuple
		data = {{1, 0, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 1}};
	}

	Matrix(vector<vector<float>> data) {

		row = data.size();
		col = data[0].size();

		for (int i = 0; i < data.size(); i++) {
			data.push_back(data[i]);
		}
	}

	Matrix(int _row, int _col) {

		row = _row;
		col = _col;
		for (int i = 0; i < row; i++) {
			vector<float> temp;
			for (int j = 0; j < col; j++) {
				temp.push_back(0);
			}
			data.push_back(temp);
		}
	}

	bool operator==(Matrix const& other) const {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (data[i][j] != other.data[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	void operator=(Matrix const& other) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				data[i][j] = other.data[i][j];
			}
		}
	}

	Matrix operator*(Matrix const& other) const { //matrix * matrix //

		Matrix temp(row, other.col);

		if (col != other.row) {
			cout << "Column of first matrix should be equal to row of second matrix" << endl;
		}
		else {
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < other.col; j++) {
					for (int k = 0; k < col; k++) {
						temp.data[i][j] += data[i][k] * other.data[k][j];
					}
				}
			}

		}
		return temp;
	}

	Point operator*(Point const& other) const {  //matrix * tuple is tuple

		vector<float> temp = other.getAll();
		vector<float> final;

		if (row != 4) {
			cout << "Column of first matrix should be equal to row of second matrix" << endl;
		}
		else {
			for (int i = 0; i < row; i++) {
				float num = 0;
				for (int j = 0; j < col; j++) {
					num += data[i][j] * temp[j];
				}
				final.push_back(num);
			}
		}
		return Point(final[0],
					 final[1],
					 final[2]);
	}

	Vector operator*(Vector const& other) const {  //matrix * tuple is tuple //applying transformations

		vector<float> temp = other.getAll();
		vector<float> final;

		if (row != 4) {
			cout << "Column of first matrix should be equal to row of second matrix" << endl;
		}
		else {
			for (int i = 0; i < row; i++) {
				float num = 0;
				for (int j = 0; j < col; j++) {
					num += data[i][j] * temp[j];
				}
				final.push_back(num);
			}
		}
		return Vector(final[0],
			final[1],
			final[2]);
	}


	void Print() {
		cout << "  Matrix <" << row << ", " << col << ">" << endl;
		for (int i = 0; i < row; i++) {
			cout << " | ";
			for (int j = 0; j < col; j++) {
				cout << data[i][j] << " | ";
				//cout << "(" << i << "," << j << ")" << " | ";
			}
			cout << endl;
		}
	}

	int getRow() const {
		return row;
	}
	int getCol() const {
		return col;
	}
	Matrix getMatrix() {
		return data;
	};


	//transpose matrix
	Matrix transpose() {
		Matrix temp(row, col);

		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				temp.data[j][i] = data[i][j];
			}
		}
		return temp;
	}

	Matrix submatrix(int x, int y) { // use on a Matrix 4
		
		Matrix sub = Matrix({{0, 0, 0},
							 {0, 0, 0},
							 {0, 0, 0}});
		int i = 0;

		for (int r = 0; r < row; r++) {
			
			int j = 0;
			if (r == x) {
				continue;
			}

			for (int c = 0; c < col; c++) {
				
				if (c == y) {
					continue;
				}

				sub.data[i][j] = this->data[r][c];
				j++;
			}
			i++;
		}

		return sub;
	}


	/* Recursive function for finding determinant of matrix.
	   n is current dimension of A[][]. */
	float determinant(vector<vector<float>> A, int n) {
		float D = 0; // Initialize result 

		//  Base case : if matrix contains single element 
		if (n == 1) {
			return A[0][0];
		}


		int sign = 1;  // To store sign multiplier 
		vector<vector<float>> temp = nullMat; // To store cofactors 

		 // Iterate for each element of first row 
		for (int f = 0; f < n; f++) {
			// Getting Cofactor of A[0][f] 
			getCofactor(A, temp, 0, f, n);
			D += sign * A[0][f] * determinant(temp, n - 1);
			// terms are to be added with alternate sign 
			sign = -sign;
		}

		//cout << "D:" << D << endl;
		return D;
	}

	vector<vector<float>> nullMat = { {0, 0, 0, 0},
									   {0, 0, 0, 0},
									   {0, 0, 0, 0},
									   {0, 0, 0, 0}};

	void getCofactor(vector<vector<float>> A, vector<vector<float>>& temp, int p, int q, int n) {
		int i = 0, j = 0;

		// Looping for each element of the matrix 
		for (int row = 0; row < n; row++) {

			for (int col = 0; col < n; col++)
			{
				//  Copying into temporary matrix only those element 
				//  which are not in given row and column 

				if (row != p && col != q) {
					temp[i][j] = A[row][col];
					j++;

					// Row is filled, so increase row index and 
					// reset col index 
					if (j == n - 1) {
						j = 0;
						i++;
					}
				}
			}
		}
	}

	// Function to get adjoint of A[N][N] in adj[N][N]. 
	void adjoint(vector<vector<float>> A, vector<vector<float>>& adj) {
		// temp is used to store cofactors of A[][] 
		int sign = 1;
		vector<vector<float>> temp = nullMat;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				// Get cofactor of A[i][j] 
				getCofactor(A, temp, i, j, 4);

				// sign of adj[j][i] positive if sum of row 
				// and column indexes is even. 
				sign = ((i + j) % 2 == 0) ? 1 : -1;

				// Interchanging rows and columns to get the 
				// transpose of the cofactor matrix 
				adj[j][i] = (sign) * (determinant(temp, 4 - 1));
			}
		}
	}

	// Function to calculate and store inverse, returns false if 
	// matrix is singular 
	Matrix inverse() {
		vector<vector<float>> inverse = nullMat;

		vector<vector<float>> identity = { {1, 0, 0, 0},
											{ 0, 1, 0, 0 },
											{ 0, 0, 1, 0 },
											{ 0, 0, 0, 1 } };


		if (data == identity) {
			return identity;
		}


		// Find determinant of A[][] 
		float det = determinant(data, 4);
		if (det == 0) {
			cout << "Singular matrix, can't find its inverse" << endl;
			//return false;
		}

		// Find adjoint 

		vector<vector<float>> adj = nullMat;
		adjoint(data, adj);

		// Find Inverse using formula "inverse(A) = adj(A)/det(A)" 
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				inverse[i][j] = adj[i][j] / float(det);
			}
		}

		return Matrix(inverse);
	}


	//////////////////////////////////////////////////////////////////////////////////////

	//Translation
	//TODO: Multiply inverse of a translation matrix
	//TODO: Multiply translation matrix * point = to apply transofrmations 
	//Vectors are translation independent (origin independent) so there is no point in translating
	void translate(Point p) {
		
		Matrix translationMatrix = vector<vector<float>>{ {1, 0, 0, p.x},
														   {0, 1, 0, p.y},
														   {0, 0, 1, p.z},
														   {0, 0, 0, 1}};
		// | p.x + v.x
		// | p.y + v.y
		// | p.z + v.z
		// | 1 

		data = (translationMatrix * data).data;
	
	}

	
	//Scaling
	//TODO: Multiply scaling * vector
	void scale(float x, float y, float z) {

		Matrix scalingMatrix = vector<vector<float>> {{x, 0, 0, 0},
													   {0, y, 0, 0},
													   {0, 0, z, 0},
													   {0, 0, 0, 1}};

		// | p.x * v.x
		// | p.y * v.y
		// | p.z * v.z
		// | 1 

		data = (scalingMatrix * data).data;
	}

	//TODO: Rotation Points
	Matrix rotationMatrix(float x, float y, float z) {
	
		Matrix X = Matrix().rotationXMatrix(x);
		Matrix Y = Matrix().rotationYMatrix(y);
		Matrix Z = Matrix().rotationZMatrix(z);
		return X * Y * Z;
	}
	void rotate(float x, float y, float z) {

		Matrix temp = rotationMatrix(x, y, z);
		Matrix temp2 = data;
		data = (temp * temp2).data;
	}

	//RotationX
	Matrix rotationXMatrix(float radians) {
		float const c = std::cos(radians);
		float const s = std::sin(radians);
		vector<vector<float>> temp = {{1, 0, 0, 0},
									  {0,  c , -s , 0},
									  {0,  s ,  c , 0},
									  {0, 0, 0, 1}};
		return temp;
	}
	void rotateX(float radians) {

		Matrix temp = rotationXMatrix(radians);
		Matrix temp2 = data;
		data = (temp * temp2).data;
	}

	//RotationY
	Matrix rotationYMatrix(float radians) {
		float const c = std::cos(radians);
		float const s = std::sin(radians);
		vector<vector<float>> temp = {{c, 0, s, 0},
									  {0, 1, 0, 0},
									  {-s, 0,  c, 0},
									  {0, 0, 0, 1}};
		return temp;
	}
	void rotateY(float radians) {

		Matrix temp = rotationYMatrix(radians);
		Matrix temp2 = data;
		data = (temp * temp2).data;
	}

	//RotationZ
	Matrix rotationZMatrix(float radians) {
		float const c = std::cos(radians);
		float const s = std::sin(radians);
		vector<vector<float>> temp = {{c, -s, 0, 0},
									  {s,  c, 0, 0},
									  {0, 0, 1, 0},
									  {0, 0, 0, 1}};

		// | p.x * cosθ + p.y * sinθ
		// | p.x * sinθ + p.y * cosθ
		// | p.z
		// | 1 
		return temp;
	}
	void rotateZ(float radians) {

		Matrix temp = rotationZMatrix(radians);
		Matrix temp2 = data;
		data = (temp * temp2).data;
	}

	//Shearing
	void shear(float xy, float xz, float yx, float yz, float zx, float zy) {

		Matrix shearingMatrix = vector<vector<float>> {{1, xy, xz, 0},
														{yx, 1,  yz, 0},
														{zx, zy, 1, 0},
														{0, 0, 0, 1}};

		data = (shearingMatrix * data).data;
	}

	//TODO: Chaining it Together


};












