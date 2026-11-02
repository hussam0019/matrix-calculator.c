#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// simple version : 


/*
void remplir(int rows, int cols, int (*M)[cols])
{
     
    for (int *p  = M[0]; p < M[rows]; p++) 
    scanf("%d", p);
    
}



void multi(int rows, int cols
          ,int rows2, int cols2
          ,int (*M)[cols]
          ,int (*M2)[cols2]
          ,int (*M3)[cols2]){
          
  if( cols != rows2)
  {
    printf("%d ≠ %d; impossible de fair multiplication",cols,rows2);
    exit(1);
  }

  
  for(int i = 0; i < rows; i++)
  for(int j = 0; j < cols2; j++){
  
  int temp = 0;
  
  for(int k =0; k < cols; k++){
  
    temp += M[j][k] * M2[k][i];
    M3[j][i] = temp;
  }
  }
  
  


}
          
          
          

int main()
{ 

   int M[2][2];
   int M2[2][2];
   int M3[2][2];
   remplir(2,2,M);
   remplir(2,2,M2);
   
  multi(2,2,2,2,M,M2,M3);
   
  for(int i = 0; i < 2; i++){
  for(int j = 0; j < 2; j++)
  printf("%d ",M3[i][j]);
  
  printf("\n");
  }


    
  return 0;
}

*/

// advance version : 

void remplir_dyn(int **M, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &M[i][j]);
}



void free_matrix(int **M, int rows)
{
    for (int i = 0; i < rows; i++)
        free(M[i]);
    free(M);
}

void free_matrix_double(double **M, int rows)
{
    for (int i = 0; i < rows; i++)
        free(M[i]);
    free(M);
}



int **alloc_matrix(int rows, int cols)
{
    int **M = malloc(rows * sizeof(int *));
    if (!M) return NULL;

    for (int i = 0; i < rows; i++)
    {
        M[i] = malloc(cols * sizeof(int));
        if (!M[i])
        {
            for (int k = 0; k < i; k++)
                free(M[k]);
            free(M);
            return NULL;
        }
    }
    return M;
}



double **alloc_matrix_double(int rows, int cols)
{
    double **M = malloc(rows * sizeof(double *));
    if (!M) return NULL;

    for (int i = 0; i < rows; i++)
    {
        M[i] = malloc(cols * sizeof(double));
        if (!M[i])
        {
            for (int k = 0; k < i; k++)
                free(M[k]);
            free(M);
            return NULL;
        }
    }
    return M;
}

void print_matrix_int(int **M, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%d ", M[i][j]);
        printf("\n");
    }
}

void print_matrix_double(double **M, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%.2f ", M[i][j]);
        printf("\n");
    }
}


int** multi(int rows1, int cols1
           ,int rows2, int cols2
           ,int **M1, int **M2){
           
   if(cols1 != rows2){
   printf("%d ≠ %d, impossible de fair multiplication"
   ,cols1,rows2);
   
   return NULL;
   }
   
   int** M3 = alloc_matrix(rows1,cols2);
   if(!M3){
   printf("error :( "); 
   return NULL;}
   
   for(int i = 0; i < rows1; i++){
       for(int j = 0; j < cols2; j++){
     
         M3[i][j] = 0;
         for(int k =0; k < cols1; k++){
         
         M3[i][j] += M1[i][k] * M2[k][j];
     
     
         }
   
   
     }
   
   }
           return M3;
}

int** somme(int rows1, int cols1
           ,int rows2, int cols2
           ,int **M1, int **M2){
           
           
  if((rows1 != rows2) || (cols1 != cols2)){
  printf("impossible de fair la somme les tailles sont diff");
  return NULL;
  }
  
  int** M3 = alloc_matrix(rows1,cols1);
  if(!M3){printf("error :( "); 
  return NULL;
  }
  
  
  for(int i = 0; i < rows1; i++)
  for(int j = 0; j < cols1; j++)
  M3[i][j] = M1[i][j] + M2[i][j];
           
           
 return M3;         
           
}


int** transposer(int **M, int rows, int cols)
{
    int **M3 = alloc_matrix(cols, rows);
    if (!M3)
    {
        printf("error allocation\n");
        return NULL;
    }

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            M3[j][i] = M[i][j];

    return M3;
}


void getCofactor(int **matrix, int **temp, int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
        
            if (row != p && col != q) {
                temp[i][j++] = matrix[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}


int determinant(int **M, int n)
{
    if (n == 1)
        return M[0][0];

    int det = 0;
    int signe = 1;

    int **temp = alloc_matrix(n - 1, n - 1);
    if (!temp)
    {
        printf("error allocation\n");
        return -1;
    }

    for (int i = 0; i < n; i++)
    {
        getCofactor(M, temp, 0, i, n);
        det += signe * M[0][i] * determinant(temp, n - 1);
        signe = -signe;
    }

    free_matrix(temp, n - 1);
    return det;
}




int **comatrice(int **M, int n)
{
    int **Com  = alloc_matrix(n, n);
    if (!Com)
    {
        printf("error d'allocation :( ");
        return NULL;
    }

    int **temp = alloc_matrix(n - 1, n - 1);
    if (!temp)
    {
        free_matrix(Com, n);
        printf("error d'allocation :( ");
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            getCofactor(M, temp, i, j, n);
            Com[i][j] = ((i + j) % 2 == 0 ? 1 : -1)
                        * determinant(temp, n - 1);
        }
    }

    free_matrix(temp, n - 1);
    return Com;
}


double** matrice_inverse(int** M, int n){

  int det = determinant(M, n);
  if(det == 0) return NULL;
  
  int** com = comatrice(M, n);
  if(!com) return NULL;
  
  int** adj = transposer(com, n, n);
  free_matrix(com, n);
  
  
  double** inv = alloc_matrix_double(n, n);
  if(!inv){
  free_matrix(adj, n);
  return NULL;
  }
  
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
    inv[i][j] = (float) adj[i][j] / det;
  
  free_matrix(adj, n);
  return inv;

}













int main(void)
{
    int x;
    int **A = NULL, **B = NULL, **C = NULL;
    double **Inv = NULL;

    printf("-------- MENU --------\n");
    printf("1 : saisir une matrice\n");
    printf("2 : somme des matrices\n");
    printf("3 : multiplication des matrices\n");
    printf("4 : transpose d'une matrice\n");
    printf("5 : determinant\n");
    printf("6 : comatrice\n");
    printf("7 : matrice inverse\n");
    printf("0 : quitter\n");

    while (1)
    {
        printf("\nVotre choix : ");
        scanf("%d", &x);

        switch (x)
        {
        case 1:
        {
            int rows, cols;
            printf("Donner lignes et colonnes : ");
            scanf("%d %d", &rows, &cols);

            A = alloc_matrix(rows, cols);
            remplir_dyn(A, rows, cols);
            print_matrix_int(A, rows, cols);

            free_matrix(A, rows);
            break;
        }

        case 2:
        {
            int rows, cols;
            printf("Donner lignes et colonnes : ");
            scanf("%d %d", &rows, &cols);

            A = alloc_matrix(rows, cols);
            B = alloc_matrix(rows, cols);

            printf("Matrice A:\n");
            remplir_dyn(A, rows, cols);
            printf("Matrice B:\n");
            remplir_dyn(B, rows, cols);

            C = somme(rows, cols, rows, cols, A, B);
            if (C)
                print_matrix_int(C, rows, cols);

            free_matrix(A, rows);
            free_matrix(B, rows);
            if (C) free_matrix(C, rows);
            break;
        }

        case 3:
        {
            int rows, cols, rows1, cols1;
            printf("Donner lignes cols de A : ");
            scanf("%d %d", &rows, &cols);
            printf("Donner lignes cols de B : ");
            scanf("%d %d", &rows1, &cols1);

            A = alloc_matrix(rows, cols);
            B = alloc_matrix(rows1, cols1);

            remplir_dyn(A, rows, cols);
            remplir_dyn(B, rows1, cols1);

            C = multi(rows, cols, rows1, cols1, A, B);
            if (C)
                print_matrix_int(C, rows, cols1);

            free_matrix(A, rows);
            free_matrix(B, rows1);
            if (C) free_matrix(C, rows);
            break;
        }

        case 4:
        {
            int rows, cols;
            printf("Donner lignes et colonnes : ");
            scanf("%d %d", &rows, &cols);

            A = alloc_matrix(rows, cols);
            remplir_dyn(A, rows, cols);

            C = transposer(A, rows, cols);
            print_matrix_int(C, cols, rows);

            free_matrix(A, rows);
            free_matrix(C, cols);
            break;
        }

        case 5:
        {
            int n;
            printf("Donner taille n : ");
            scanf("%d", &n);

            A = alloc_matrix(n, n);
            remplir_dyn(A, n, n);

            printf("Determinant = %d\n", determinant(A, n));

            free_matrix(A, n);
            break;
        }

        case 6:
        {
            int n;
            printf("Donner taille n : ");
            scanf("%d", &n);

            A = alloc_matrix(n, n);
            remplir_dyn(A, n, n);

            C = comatrice(A, n);
            print_matrix_int(C, n, n);

            free_matrix(A, n);
            free_matrix(C, n);
            break;
        }

        case 7:
        {
            int n;
            printf("Donner taille n : ");
            scanf("%d", &n);

            A = alloc_matrix(n, n);
            remplir_dyn(A, n, n);

            Inv = matrice_inverse(A, n);
            if (Inv)
                print_matrix_double(Inv, n, n);

            free_matrix(A, n);
            if (Inv) free_matrix_double(Inv, n);
            break;
        }

        case 0:
            printf("Au revoir \n");
            return 0;

        default:
            printf("Choix invalide \n");
        }
    }
}