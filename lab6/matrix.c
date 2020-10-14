/* Function matrix_multiply
 * matrixA, matrixB, and matrix C are matrices represented as
 * one-dimensional arrays in row-major order. This function must
 * preform matrix multiplication so that C=A*B. 
 * INPUT: matrixA, a one dimensional array of size m*k
 *        matrixB, a one dimensional double array of size k*n
 * OUTPUT: matrixC, a one dimensional double array of size m*n
 */
void matrix_multiply(double *matrixA,double *matrixB,double *matrixC,int m,int k,int n)
{
//YOUR CODE HERE

	int x,y,z;
	
	for (y=0; y < m; y++) //loops row of output matrix. RowA,RowC.
	{
		for (x=0; x < n; x++)//loops column of output matrix. ColumnB, columnC.
		{
			for (z = 0; z < k; z++)//loops columns A or rows B for matrix multiplication.
			{
				int locationA = y*k + z; //m*k + k basically. RowA * colA1 + ColA2
				int locationB = z*n + x; //k*n + n basically. 
				int locationC = y*n + x; //m*n + n basically.

				matrixC[locationC] += matrixA[locationA] * matrixB[locationB]; // C=C+(A*B)
			}
		}
	}
					
}
