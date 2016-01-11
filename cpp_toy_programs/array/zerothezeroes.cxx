#include <iostream>
#include <set>
#include <cassert>
using namespace std;

void zerothezeroes( int **matrix, int M, int N )
{
	set<int> row, col;

	for( int i = 0; i < M; ++i )
		for( int j = 0; j < N; ++j )
			if( matrix[i][j] == 0 )
			{
				row.insert(i);
				col.insert(j);
			}
	for( int x : row )
		for( int j = 0; j < N; ++j )
			matrix[x][j] = 0;
	for( int y : col )
		for( int i = 0; i < M; ++i )
			matrix[i][y] = 0;
}

int main()
{
	int M, N;
	int buf[100*100];
	int *matrix[100];
	for( int i = 0; i < 100; ++i )
		matrix[i] = &buf[i*100];
	
	cout << "Matrix dimensions:";
	cin >> M >> N;
	assert(M <= 100 && N <= 100);
	cout << "Enter matrix contents" << endl;
	for( int i = 0; i < M; ++i )
		for( int j = 0; j < N; ++j )
			cin >> matrix[i][j];

	zerothezeroes(matrix, M, N);

	cout << "Converted matrix" << endl;
	for( int i = 0; i < M; ++i ) {
		for( int j = 0; j < N; ++j )
			cout << matrix[i][j] << " ";
		cout << endl;
	}
	
	return 0;
}
