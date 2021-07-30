#include <stdio.h>
#include <stdlib.h>
int main() {
	int dim1,dim2,dim3,i,j,k;
	printf("dim1=");
	scanf("%d",&dim1);
	printf("dim2=");
	scanf("%d",&dim2);
	printf("dim3=");
	scanf("%d",&dim3);
	int ***cube = (int ***)malloc(dim1*sizeof(int**));
	for(i=0; i<dim1; i++) {
		cube[i] = (int **)malloc(dim2*sizeof(int*));

		for(j=0; j<dim2; j++)
			cube[i][j] = (int *)malloc(dim3*sizeof(int));
	}
	
	for(i=0;i<dim1;i++)
		for(j=0;j<dim2;j++)
			for(k=0;k<dim3;k++)
				cube[i][j][k] = rand()%10+1;
	
	for(i=0;i<dim1;i++) {
		for(j=0;j<dim2;j++) {
			for(k=0;k<dim3;k++) {
				//printf("%d",cube[i][j][k]);
				//printf(" ");
				printf("Value of cube[%d][%d][%d] = %d",i,j,k,cube[i][j][k]);
				printf("\n");
			}
			//printf("\n");
		}
		//printf("\n");
	}
	
	for(i=0;i<dim1;i++) {
		for(j=0;j<dim2;j++)
			free(cube[i][j]);
	free(cube[i]);
	}
	free(cube);

	return 0;
}
