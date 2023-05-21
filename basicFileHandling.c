#include<stdio.h>
#include<stdlib.h>

// An example code to show file handling

int main(){
	FILE *file_input;
	file_input = fopen("filename.txt", "r");
	if(file_input == NULL){
		printf("The file could not be opened. :( \n");
		exit(0);
	}
	char str1[100];
	for (int i = 0; i <100; i++)
	{
		fscanf(file_input,"%c",&str1[i]);
	}
	printf("%s",str1);
	
	
	return 0;
		  
}

