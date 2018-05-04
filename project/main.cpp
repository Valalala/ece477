// Base provided by Sergei Bugrov
// https://cognitivedemons.wordpress.com/2017/07/06/a-neural-network-in-10-lines-of-c-code/
// Walter Rasmussen - Boom Johnson - Spring 2018
// Three layer neural network
// main.cpp

#include <iostream>
#include <vector>
#include <math.h>
#include <numeric>
#include <algorithm>
#include <random>
#include "main.h"

using std::vector;
using std::cout;
using std::endl;

// # of iterations
#define EPOCHS 100

vector<float> indexer(Y.size()/3); //Indexing throught training data in random order. 

vector <float> sigmoid_d (const vector <float>& m1) {
    
    /*  Returns the value of the sigmoid function derivative f'(x) = f(x)(1 - f(x)), 
        where f(x) is sigmoid function.
        Input: m1, a vector.
        Output: x(1 - x) for every element of the input matrix m1.
    */
    
    const unsigned long VECTOR_SIZE = m1.size();
    vector <float> output (VECTOR_SIZE);
    
    
    for( unsigned i = 0; i != VECTOR_SIZE; ++i ) {
        output[ i ] = m1[ i ] * (1 - m1[ i ]);
    }
    
    return output;
}

vector <float> sigmoid (const vector <float>& m1) {
    
    /*  Returns the value of the sigmoid function f(x) = 1/(1 + e^-x).
        Input: m1, a vector.
        Output: 1/(1 + e^-x) for every element of the input matrix m1.
    */
    
    const unsigned long VECTOR_SIZE = m1.size();
    vector <float> output (VECTOR_SIZE);
    
    
    for( unsigned i = 0; i != VECTOR_SIZE; ++i ) {
        output[ i ] = 1 / (1 + exp(-m1[ i ]));
    }
    
    return output;
}

vector <float> operator+(const vector <float>& m1, const vector <float>& m2){
    
    /*  Returns the elementwise sum of two vectors.
        Inputs: 
            m1: a vector
            m2: a vector
        Output: a vector, sum of the vectors m1 and m2.
    */
    
    const unsigned long VECTOR_SIZE = m1.size();
    vector <float> sum (VECTOR_SIZE);
    
    for (unsigned i = 0; i != VECTOR_SIZE; ++i){
        sum[i] = m1[i] + m2[i];
    };
    
    return sum;
}

vector <float> operator-(const vector <float>& m1, const vector <float>& m2){
    
    /*  Returns the difference between two vectors.
        Inputs:
            m1: vector
            m2: vector
        Output: vector, m1 - m2, difference between two vectors m1 and m2.
    */
    
    const unsigned long VECTOR_SIZE = m1.size();
    vector <float> difference (VECTOR_SIZE);
    
    for (unsigned i = 0; i != VECTOR_SIZE; ++i){
        difference[i] = m1[i] - m2[i];
        //difference[i] = m1[indexer[i]] - m2[i];
    };
    
    return difference;
}

vector <float> operator*(const vector <float>& m1, const vector <float>& m2){
    
    /*  Returns the product of two vectors (elementwise multiplication).
        Inputs:
            m1: vector
            m2: vector
        Output: vector, m1 * m2, product of two vectors m1 and m2
    */
    
    const unsigned long VECTOR_SIZE = m1.size();
    vector <float> product (VECTOR_SIZE);
    
    for (unsigned i = 0; i != VECTOR_SIZE; ++i){
        product[i] = m1[i] * m2[i];
    };
    
    return product;
}

vector <float> transpose (float *m, const int C, const int R) {
    
    /*  Returns a transpose matrix of input matrix.
        Inputs:
            m: vector, input matrix
            C: int, number of columns in the input matrix
            R: int, number of rows in the input matrix
        Output: vector, transpose matrix mT of input matrix m
    */
    
    vector <float> mT (C*R);
    
    for(int n = 0; n != C*R; n++) {
        unsigned i = n/C;
        unsigned j = n%C;
        mT[n] = m[R*j + i];
        //mT[n] = m[R*j + indexer[i]];
    }
    
    return mT;
}

vector <float> dot (const vector <float>& m1, const vector <float>& m2, const int m1_rows, const int m1_columns, const int m2_columns) {
    
    /*  Returns the product of two matrices: m1 x m2.
        Inputs:
            m1: vector, left matrix of size m1_rows x m1_columns
            m2: vector, right matrix of size m1_columns x m2_columns (the number of rows in the right matrix 
                must be equal to the number of the columns in the left one)
            m1_rows: int, number of rows in the left matrix m1
            m1_columns: int, number of columns in the left matrix m1
            m2_columns: int, number of columns in the right matrix m2
        Output: vector, m1 * m2, product of two vectors m1 and m2, a matrix of size m1_rows x m2_columns
    */
    
    vector <float> output (m1_rows*m2_columns);
    
    for( int row = 0; row != m1_rows; ++row ) {
        for( int col = 0; col != m2_columns; ++col ) {
            output[ row * m2_columns + col ] = 0.f;
            for( int k = 0; k != m1_columns; ++k ) {
                output[ row * m2_columns + col ] += m1[ row * m1_columns + k ] * m2[ k * m2_columns + col ];
                //output[ row * m2_columns + col ] += m1[ indexer[row] * m1_columns + k ] * m2[ k * m2_columns + col ];
            }
        }
    }
    
    return output;
}

//Prints vectors.
void print ( const vector <float>& m, int n_rows, int n_columns ) {
    
    /*  "Couts" the input vector as n_rows x n_columns matrix.
        Inputs:
            m: vector, matrix of size n_rows x n_columns
            n_rows: int, number of rows in the left matrix m1
            n_columns: int, number of columns in the left matrix m1
    */
    
    for( int i = 0; i != n_rows; ++i ) {
        for( int j = 0; j != n_columns; ++j ) {
            cout << m[ i * n_columns + j ] << ", ";
        }
        //cout << '\n';
    }
    cout << endl;
}

// Randomizes the order of a matrix.
// Used to prevent overfit by mixing up the order of training data.
vector<float> shuffleData(const vector <float>& m, const vector <float>& mix, int m_columns) {
	vector<float> out(m.size(), 0);
	
	for( int i = 0; i != m.size()/m_columns; ++i ) {
		for( int j = 0; j != m_columns; ++j ) {
			out[ i * m_columns + j] = m[ mix[i] * m_columns + j ];
		}
	}

	return out;
}

// The neural network
int main(int argc, const char * argv[]) {
	
	//random_shuffle(indexer.begin(), indexer.end());
	std::default_random_engine generator;
	std::normal_distribution<float> distribution(0,1);
	//float number = distribution(generator);

	//vector<float> indexer(Y.size(), 0);	
	std::iota (std::begin(indexer), std::end(indexer), 0); //Fill with 0,1,...
	//print(indexer, indexer.size(), 1);
	//print(X, X.size()/4, 4);
	
	vector<float> WL0(4*4, 0);
	vector<float> WL1(4*3, 0);
	
	//init weights = normal distribution
	for(unsigned n = 0; n != WL0.size(); ++n){ WL0[n] = distribution(generator); }
	for(unsigned n = 0; n != WL1.size(); ++n){ WL1[n] = distribution(generator); }
	//print(WL1, 4, 3);
	//print(Y, Y.size()/3, 3);

	for (unsigned i = 0; i != EPOCHS; ++i) { 
		// shuffles the order of the data
		random_shuffle(indexer.begin(), indexer.end());
		X = shuffleData( X, indexer, 4);
		Y = shuffleData( Y, indexer, 3);

		//if (i==1) print(Y, Y.size()/3, 3);
		
		// first set of predictions; input => hidden layer
		vector<float> hid = sigmoid(dot(X, WL0, X.size()/4, 4, 4) );
		// second set of predictions; hidden => out predictions
		vector<float> pred = sigmoid(dot(hid, WL1, hid.size()/4, 4, 3) );

		// how far off the guesses are for each row
		vector<float> pred_error = Y - pred;        
		
		//combines how wrong vs how confident
		vector<float> pred_delta = pred_error * sigmoid_d(pred);
		
		vector<float> tL1 = transpose( &hid[0], 4, hid.size()/4 );
		// how much the hidden layer effected the final error
		vector<float> hid_error = dot(tL1, pred_delta, 4, tL1.size()/4, 3);
		
		//combines how wrong vs how confident
		vector<float> hid_delta = hid_error * sigmoid_d(hid);
		
	
		//vector<float> hid_delta = pred_error * sigmoid_d(hid);
		vector<float> tL0 = transpose( &X[0], 4, X.size()/4 );
		vector<float> WL0_delta = dot(tL0, hid_delta, 4, tL0.size()/4, 4);
		WL0 = WL0 + WL0_delta;


		//vector<float> pred_delta = pred_error * sigmoid_d(pred);
		vector<float> tL1 = transpose( &hid[0], 4, hid.size()/4 );
		vector<float> WL1_delta = dot(tL1, pred_delta, 4, tL1.size()/4, 3);
		WL1 = WL1 + WL1_delta;
        	
		//random_shuffle(indexer.begin(), indexer.end());
		
		//if (i == EPOCHS-1){
			//print ( pred, pred.size()/3, 3 );
		//};
		//print(WL1, WL1.size()/3, 3);
		//print(Y, Y.size()/3, 3);
		cout << pred[0] << ", " << pred[1] << ", " << pred[2] << "\n";
		cout << Y[0] << ", " << Y[1] << ", " << Y[2] << "\n";
		
	};

	return 0;
}


