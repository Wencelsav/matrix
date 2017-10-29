#include <iostream>
#include <sstream>
using namespace std;
typedef unsigned int uint;

float **create_matrix(uint columns,
                      uint rows)
{
    float **matrix;	
    matrix = new float *[ rows];
    for( uint i = 0; i < rows; ++i ) {
        matrix[ i ] = new float[ columns];
        for(uint j = 0; j < columns; ++j ) {
               matrix[ i ][ j ] = 0.0f;
        }
    }
    return matrix;
}
	

float det(float **matrix,
          uint columns,
          uint rows)
{
	if(columns!=rows)
	{
		return 0;
	}
	float result;
      
    if(columns==1)
    {
    	result=matrix[0][0];
    	
    }
	else if(columns==2)
	{
        result=matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];			
	}
	else
	{
		for(uint j=0;j<columns;j++){
			float **minor;
			minor=create_matrix(columns-1,rows-1);
			for(uint y = 0; y < rows-1; ++y )
			{
				int k=0;
                for(uint x = 0; x < columns-1; ++x ) 
                {
                    if(x==j){
                    	k=1;
                    }
                    minor[y][x]=matrix[y+1][x+k];
                }
				
			}
            switch(j%2){
                case 0:
                   result+=matrix[0][j]*det(minor,columns-1,rows-1);
                   break;
                case 1:
                   result+=(-matrix[0][j])*det(minor,columns-1,rows-1);
                   break;
            }      
                                  
		}
	}
	return result;
}
float **algebraic_matrix(float **matrix,
	                     uint columns,
                         uint rows)
{
	float** result;
	result=create_matrix(columns,rows);
		for(uint j=0;j<rows;j++){
		    for(uint i=0;i<columns;i++){
		    float ** minor;
		    minor=create_matrix(columns-1,rows-1);
			int k1=0;
			for(uint y = 0; y < rows-1; ++y ) 
			{
				int k=0;
                for(uint x = 0; x < columns-1; ++x )
                {
                    if(x==i)
                    {
                    	k=1;
                    }
                    if(y==j)
                    {
                    	k1=1;
                    }
                        
                    matrix[y][x]=matrix[y+k1][x+k];
                }
			}
            switch((j+i)%2){
                case 0:
                   result[j][i]=det(minor,columns-1,rows-1); 
                   break;
                case 1:
                   result[j][i]=(-det(minor,columns-1,rows-1));
                   break;
            }      
		}
	}
	return result;
}
float **sum(float **matrix1,
            uint columns1,
            uint rows1,
            float **matrix2,
            uint columns2,
            uint rows2)
{
	float **result;
	if(columns1!=columns2||rows1!=rows2)
	{
	
		return result;
		
	}
	result=create_matrix(columns1,rows1);
    for(uint j=0;j<rows1;j++){
     	for(uint i=0;i<columns1;i++){
     			result[j][i]=matrix1[j][i]+matrix2[j][i];
     	}
    } 
    return result;
   
}
float **sub(float **matrix1,
            uint columns1,
            uint rows1,
            float **matrix2,
            uint columns2,
            uint rows2)
{
	float **result;
	if(columns1!=columns2||rows1!=rows2)
	{
	
		return result;
		
	}
	result=create_matrix(columns1,rows1);
    for(uint j=0;j<rows1;j++){
     	for(uint i=0;i<columns1;i++){
     			result[j][i]=matrix1[j][i]+matrix2[j][i];
     	}
    } 
    return result;
   
}
float **mul(float **matrix1,
            uint columns1,
            uint rows1,
            float **matrix2,
            uint columns2,
            uint rows2)
{
    float **result;
    if(columns1!=rows2)
    {
	      
	      return result;
    }
    result=create_matrix(columns2,rows1);
    for(uint j=0;j<rows1;j++)
    {
          for(uint i=0;i<columns2;i++)
          {
     			float y=0;
     			for(uint z=0;z<columns1;z++)
     			{
     			    y+=matrix1[j][z]*matrix2[z][i];	
     			}
     			result[j][i]=y;
          }
	} 
    return result;    
}
float **transplate(float **matrix,
                   uint columns,
                   uint rows)
{
     float **result;
     result=create_matrix(rows,columns);
     
     for(uint j=0;j<columns;j++)
     {
     		for(uint i=0;i<rows;i++)
     		{
     			result[j][i]=matrix[i][j];
     		}
     } 
     
     return result;
}
float **reverse(float **matrix,
                uint columns,
                uint rows)
{
     float **result;
     if (det(matrix,columns,rows)==0)
     {
     	
     	return result;
     }	
     result=create_matrix(columns,rows);
     float **a=algebraic_matrix(matrix,columns,rows);
     a=transplate(a,columns,rows);
     for(uint j=0;j<columns;j++)
     {
     		    for(uint i=0;i<rows;i++)
     		    {
     			    result[j][i]=a[j][i]*(1/(det(matrix,columns,rows)));
     		    }
     } 
     
     return result;
}
bool get_matrix(float **&matrix,
               uint ncolumns,
               uint nrows)
{
  matrix=create_matrix(ncolumns,nrows);

   for(uint j=0;j<nrows;j++)
   {
           string new_row;	
	       getline(cin,new_row);
	       istringstream stream(new_row);
	       for(uint i=0;i<ncolumns;i++)
	       {
	       	  if(!(stream>>matrix[j][i]))
	       	  {
	       		     return false;
	       	  }
	       }
	}
	return true;
	
}

void cout_matrix(float **matrix,
                 uint ncolumns,
                 uint nrows)
{

	for(uint j=0;j<nrows;j++)
	{
	       for(uint i=0;i<ncolumns;i++)
	       {
	       	   if(matrix[j][i]==-0)
	       	   {
	       		matrix[j][i]=0;
	       	   }  
	       	   cout<<matrix[j][i]<<"\t";
	       }
	cout<<"\n";
	}
}
bool get_size(uint &columns,
              uint  &rows)
{
     string header;

     char razdel;
     getline(cin,header);
     istringstream str(header);
     if((str>>rows)&&(str>>razdel)&&(str>>columns)&&(razdel==','))
     {
     	return true;
     }
     return false;
}
int main()
{float **matrix1;
unsigned int columns,rows;
bool c=get_size(rows,columns);
get_matrix(matrix1,columns,rows);
cout_matrix(matrix1,columns,rows);
}
