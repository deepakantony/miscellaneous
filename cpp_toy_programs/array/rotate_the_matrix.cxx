#include <iostream>
#include <algorithm>

using namespace std;

void rotate( int **img, int N )
{
	for( int i = 0; i < N; ++i )
		for( int j = i+1; j < N; ++j )
			swap(img[i][j], img[j][i]);
}

int main()
{
	int buf[100*100];
	int *img[100];
	for( int i = 0; i < 100; ++i )
		img[i] = &buf[i*100];

	int N;
	cout << "Enter square matrix's dim: ";
	cin >> N;
	cout << "Enter a square matrix" << endl;
	for( int i = 0; i < N; ++i )
		for( int j = 0; j < N; ++j )
			cin >> img[i][j];

	rotate( img, N );

	cout << "Rotated matrix" << endl;
	for( int i = 0; i < N; ++i ) {
		for( int j = 0; j < N; ++j )
			cout << img[i][j] << " ";
		cout << endl;
	}

	return 0;
}
