#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <omp.h>


void filling_array(int *arr, int N){
	int i;
	for (i=0; i<N; i++)
		arr[i] = rand();
}


// Быстрая сортировка
void quick_sort(int *arr, int low, int high){

	int pivot, i, j, temp;

	if(low < high){
		pivot = low;
		i = low;
		j = high;

		while(i < j){
			while ((arr[i] <= arr[pivot]) && (i <= high))
				i++;

			while((arr[j] > arr[pivot]) && (j >= low))
				j--;

			if(i < j){
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}

		temp = arr[j];
		arr[j] = arr[pivot];
		arr[pivot] = temp;
		quick_sort(arr, low, j-1);
		quick_sort(arr, j+1, high);
	}
}

// Метод пузырька
void bubble_sort(int *arr, int N)
{
	int i, j, temp;

	for(i=0; i<N; i++)
		for(j=0; j<(N-i-1); j++)
			if(arr[j] > arr[j+1]){
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
}

void verification(int N, int *error, int *arr, int *arr2){
	int i;

	*error = 1;

	for (i=0; i < N; i++){
		if ((arr[i] != arr2[i]))
			*error = 0;
	}

}


void main(){
	int *arr, *arr2;
	int i, N, error;
	double start, end;

	setlocale(LC_ALL, "Russian");

	printf("Введите размер массива: ");
	scanf("%d", &N);

	arr = (int *) malloc(N * sizeof(int));
	arr2 = (int *) malloc(N * sizeof(int));

	filling_array(arr, N);
	memcpy(arr2, arr, N * sizeof(arr));


	printf("Исходный массив: ");
	for (i=0; i<N; i++)
		printf("%d ", arr[i]);
	printf("\n\n");

	printf("Быстрая сортировка:\n");
	start = omp_get_wtime();
	quick_sort(arr, 0, N-1);
	end = omp_get_wtime();
	printf("\nНа сортировку ушло %lf времени.", end-start);
	printf("\n\n");

	printf("Сортировка пузырьковым методом:\n");
	start = omp_get_wtime();
	bubble_sort(arr2, N);
	end = omp_get_wtime();
	printf("\nНа сортировку ушло %lf времени.", end-start);


	printf("\n\nПроверка данных: ");
	verification(N, &error, arr, arr2);

	if (error == 1)
		printf("массивы идентичны.\n");
	else
		printf("массивы не идентичны.\n");


	getch();
}
