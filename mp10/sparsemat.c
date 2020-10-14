/*
	We open and read a file and then we use addition and multiplication of matrices. 		We then save all the matrices in the Linked list. We also reorder the tuples and 		insert tuples where needed. We then finally free all the allocated memory.
*/
#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

sp_tuples * load_tuples(char* input_file)
{
	FILE *f;
	f = fopen(input_file, "r");
	

	int i_max,j_max;
	int i,j;					
	double value;	
				
	fscanf(f,"%d %d",&i_max,&j_max);					// get height and width
	fgetc(f);											// get next stream in file

	sp_tuples* matrix = malloc(sizeof(sp_tuples));			// initialize new sp_tuples
	matrix->m = i_max;									// initalize all variables in sp_tuples
	matrix->n = j_max;	
	matrix->nz = 0;
	matrix->tuples_head = NULL;							

	while(!feof(f))
	{
		fscanf(f,"%d %d %lf\n", &i,&j,&value);
		set_tuples(matrix,i,j,value);	

	}
	fclose(f);
    return matrix;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)
{
	sp_tuples_node * current = mat_t->tuples_head; //make current node the header
	
	while (current != NULL) //While the current node exists
	{
		if (current->row == row && current->col == col) //compares node with row and col
			return current->value;
		else
			current = current->next;
	}
	
	return 0; //if node doesn't exist, just return 0.
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
	sp_tuples_node* temp1 = malloc(sizeof(sp_tuples_node));

	
	if(mat_t->tuples_head == NULL)	
	{
		if(value == 0) //if value is zero, end function
			return;


		temp1->next = NULL; //next = null
		mat_t->tuples_head = temp1;
		temp1->row = row;
		temp1->col = col;
		temp1->value = value;
		mat_t->nz++; 	
		return;
	}

	sp_tuples_node* temp2 = malloc(sizeof(sp_tuples_node));

	temp1 = mat_t->tuples_head; 


	while(temp1 != NULL)
	{
		if(temp1->row == row && temp1->col == col)
		{
			if(value == 0)
			{
				temp2->next = temp1->next;
				free(temp1);
				mat_t->nz--;
				return;				
			}
			else
			{
				temp1->value = value;
				return;
			}
		}
		temp2 = temp1;
		temp1 = temp1->next;
	}

	if(value == 0)
		return;

	sp_tuples_node* ptr = mat_t->tuples_head;
	sp_tuples_node* current;

	if((ptr->row > row) || 
		(ptr->row == row && ptr->col > col))
	{
		current = mat_t->tuples_head;
		mat_t->tuples_head = malloc(sizeof(sp_tuples_node));
		mat_t->tuples_head->row = row;
		mat_t->tuples_head->col = col;
		mat_t->tuples_head->value = value;
		mat_t->tuples_head->next = current;
		mat_t->nz++;
		return;
	}

	ptr = mat_t->tuples_head; //ptr goes to node
	
	while(ptr->next != NULL)
	{
		if((ptr->next->row > row) || 
			(ptr->next->row == row && ptr->next->col > col))
		{
			current = ptr->next;
			ptr->next = malloc(sizeof(sp_tuples_node));
			ptr->next->row = row;
			ptr->next->col = col;
			ptr->next->value = value;
			ptr->next->next = current;
			mat_t->nz++;
			return;
		}
		ptr = ptr->next;
	}

	ptr->next = malloc(sizeof(sp_tuples_node));
	ptr->next->row = row;
	ptr->next->col = col;
	ptr->next->value = value;
	ptr->next->next = NULL;
	mat_t->nz++;
	return;
}





void save_tuples(char * file_name, sp_tuples * mat_t)
{
	FILE *file;
	file = fopen("file_name", "w"); // open the file with write capabilties

	int i_max,j_max; //max row, max col
	int i,j;	//current row, current col		
	double value;	//value in the node

	i_max = mat_t->m; //max row = m
	j_max = mat_t->n; //max col = n
	fprintf(file,"%d,%d\n",i_max,j_max);	//write max vals to file			
	

	while(mat_t->tuples_head != NULL)
	{
		i = mat_t->tuples_head->row; //make i the current row
		j = mat_t->tuples_head->col; //j = current col
		value = mat_t->tuples_head->value; 
		fprintf(file,"%d %d %lf\n", i,j,value); //write to file
		mat_t->tuples_head = mat_t->tuples_head->next;	//go to next node
	}
	fclose(file); //close it.
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
	int locate;
	
	if(matA->n != matB->n || matA->m != matB->m) //check if matA and matB have same row/col
		return NULL;


	sp_tuples* calc = malloc(sizeof(sp_tuples)); //Allocate memory for calc
	calc->m = matA->m;
	calc->n = matA->n;
	calc->tuples_head = NULL;
	calc->nz = 0;
	sp_tuples_node* pointer_a = matA->tuples_head;
	sp_tuples_node* pointer_b = matB->tuples_head;

	while(pointer_a != NULL) //loop until null
	{
		locate = 0;
		while(pointer_b != NULL)
		{
			if(pointer_a->row == pointer_b->row && pointer_a->col == pointer_b->col)
			{
				set_tuples(calc, pointer_a->row, pointer_a->col,(pointer_a->value + pointer_b->value)); //set the tuple
				locate = 1; 
				break;
			}
			pointer_b = pointer_b->next;
		}
		pointer_b = matB->tuples_head;
 		
		
		if(!locate)
			set_tuples(calc, pointer_a->row, pointer_a->col, pointer_a->value);
		pointer_a = pointer_a->next; //go to next node
	}
	pointer_a = matA->tuples_head; //set node for A
	pointer_b = matB->tuples_head;//set node for B

	while(pointer_b != NULL)
	{
		locate = 0;
		while(pointer_a != NULL)
		{
			if(pointer_a->row == pointer_b->row && pointer_a->col == pointer_b->col)
			{
				locate = 1;
				break;
			}
			pointer_a = pointer_a->next; //go to next node pointer
		}
		pointer_a = matA->tuples_head;

		if(!locate)
			set_tuples(calc, pointer_b->row, pointer_b->col, pointer_b->value);
		pointer_b = pointer_b->next;
	}
	return calc;
}

sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB)
{ 

	sp_tuples * return_matrix;
	return_matrix = (sp_tuples*)malloc(sizeof(sp_tuples)); //allocate memory for a new return matrix
	return_matrix->m = matA->m;
	return_matrix->n = matB->n;
	return_matrix->nz = 0;
	return_matrix->tuples_head = NULL;

	sp_tuples_node * matrixA;
	matrixA = matA->tuples_head;
	sp_tuples_node * matrixB;
	matrixB = NULL; //set B to null for now

	while (matrixA != NULL) //loop until matrixA is null
	{
		int rowA = matrixA->row, colA = matrixA->col;
		
		matrixB = matB->tuples_head; //set matrixB to the matB node

		while (matrixB != NULL)
		{
			int rowB = matrixB->row, colB = matrixB->col;

			if (rowB == colA)
			{
				double val = gv_tuples(return_matrix, rowA, colB) + ( gv_tuples(matA, rowA, colA) * gv_tuples(matB, rowB, colB) ); //Get value
				set_tuples(return_matrix, rowA, colB, val);
			}
			
			matrixB = matrixB->next; //next node
		}
		
		matrixA = matrixA->next; //go to next node
	}

	return return_matrix;
}

	
void destroy_tuples(sp_tuples * mat_t){

	sp_tuples_node * temp = mat_t->tuples_head; //make temp node
	free(mat_t);

	if (temp == NULL) //when temp is null, done.
		return;
	while (temp->next != NULL)
	{
		sp_tuples_node * next_temp = temp->next; //make next_temp the next node.
		free(temp);
		temp = next_temp; //go to next node
	}
	free(temp);

}  






