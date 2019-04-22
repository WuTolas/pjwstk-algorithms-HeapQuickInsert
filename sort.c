#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertSort(int array[]);
void quickSort(int array[], int p, int r);
int partition(int array[], int p, int r);
int parent(int i);
int left(int i);
int right(int i);
void heapSort(int array[]);
void buildHeap(int array[], int heapSize);
void heapify(int array[], int i, int heapSize);
void swap(int *x, int *y);
int * generateRandomArray();
void viewArray(int array[]);
void reverseArray(int array[]);
void copyArray(int source[], int destination[]);
double getSortTime(clock_t start, clock_t end);
void viewResult(double heapRandomTime, double heapReversedTime, double heapSortedTime,
		double quickRandomTime, double quickReversedTime, double quickSortedTime,
		double insertRandomTime, double insertReversedTime, double insertSortedTime);
void printSortAction(char sortType[], char arrayType[]);

#define arrayLength 100000

int main() {
	clock_t start, end;
	double  heapRandomTime, heapReversedTime, heapSortedTime;
	double  quickRandomTime, quickReversedTime, quickSortedTime;
	double  insertRandomTime, insertReversedTime, insertSortedTime;
	int *tab = generateRandomArray();
	int array1[arrayLength], array2[arrayLength], array3[arrayLength];

	copyArray(tab, array1);
	copyArray(tab, array2);
	copyArray(tab, array3);

	printSortAction("Heap Sort", "random");
	start = clock();
	heapSort(array1);
	end = clock();
	heapRandomTime = getSortTime(start, end);

	printSortAction("Heap Sort", "Max->Min sorted");
	reverseArray(array1);
	start = clock();
	heapSort(array1);
	end = clock();
	heapReversedTime = getSortTime(start, end);

	printSortAction("Heap Sort", "Min->Max sorted");
	start = clock();
	heapSort(array1);
	end = clock();
	heapSortedTime = getSortTime(start, end);

	printSortAction("Quick Sort", "random");
	start = clock();
	quickSort(array2, 0, arrayLength - 1);
	end = clock();
	quickRandomTime = getSortTime(start, end);

	printSortAction("Quick Sort", "Max->Min sorted");
	reverseArray(array2);
	start = clock();
	quickSort(array2, 0, arrayLength - 1);
	end = clock();
	quickReversedTime = getSortTime(start, end);

	printSortAction("Quick Sort", "Min->Max sorted");
	start = clock();
	quickSort(array2, 0, arrayLength - 1);
	end = clock();
	quickSortedTime = getSortTime(start, end);

	printSortAction("Insert Sort", "random");
	start = clock();
	insertSort(array3);
	end = clock();
	insertRandomTime = getSortTime(start, end);

	printSortAction("Insert Sort", "Max->Min sorted");
	reverseArray(array3);
	start = clock();
	insertSort(array3);
	end = clock();
	insertReversedTime = getSortTime(start, end);

	printSortAction("Insert Sort", "Min->Max sorted");
	start = clock();
	insertSort(array3);
	end = clock();
	insertSortedTime = getSortTime(start, end);

	viewResult(heapRandomTime, heapReversedTime, heapSortedTime,
		quickRandomTime, quickReversedTime, quickSortedTime,
		insertRandomTime, insertReversedTime, insertSortedTime);
}

/* Insert sort methods */

void insertSort(int array[]) {
	for (int i = 1; i <= arrayLength - 1; i++) {
		int tmp = array[i];
		int j = i - 1;
		while (j >= 0 && tmp < array[j]) {
			array[j+1] = array[j];
			j--;
		}
		array[j+1] = tmp;
	}
}

/* Quick sort methods */

void quickSort(int array[], int p, int r) {
	if (p < r) {
		int q = partition(array, p, r);
		quickSort(array, p, q-1);
		quickSort(array, q+1, r);
	}
}

int partition(int array[], int p, int r) {
	int x = array[r];
	int i = p-1;
	for (int j = p;  j < r; j++) {
		if (array[j] <= x) {
			i++;
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[i+1], &array[r]);
	return i+1;
}

/* Heap sort methods */

int parent(int i) {
	return (i-1)/2;
}

int left(int i) {
	return 2*i+1;
}

int right(int i) {
	return 2*i+2;
}

void heapSort(int array[]) {
	int heapSize = arrayLength - 1;
	buildHeap(array, heapSize);
	for (int i = arrayLength - 1; i >= 1; i--) {
		swap(&array[i], &array[0]);
		heapSize = heapSize - 1;
		heapify(array, 0, heapSize);
	}
}

void buildHeap(int array[], int heapSize) {
	for (int i = arrayLength/2; i >= 0; i--) {
		heapify(array, i, heapSize);
	}
}

void heapify(int array[], int i, int heapSize) {
	int l = left(i);
	int r = right(i);
	int largest = i;

	if (l <= heapSize && array[l] > array[i]) {
		largest = l;
	}

	if (r <= heapSize && array[r] > array[largest]) {
		largest = r;
	}

	if (largest != i) {
		swap(&array[i], &array[largest]);
		heapify(array, largest, heapSize);
	}

}

/* Mutual methods */

void swap(int *x, int *y) {
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

int * generateRandomArray() {
	static int array[arrayLength];
	srand(time(0));
	for (int i = 1; i <= arrayLength; i++) {
		array[i-1] = rand() % 100 + 1;
	}

	return array;
}

void viewArray(int array[]) {
	printf("\n");
	for (int i = 0; i < arrayLength; i++) {
		printf("%d |", array[i]);
	}
	printf("\n");
}

void reverseArray(int array[]) {
	int start = 0;
	int end = arrayLength - 1;
	while (start < end) {
		swap(&array[start], &array[end]);
		start++;
		end--;
	}
}

void copyArray(int source[], int destination[]) {
	for (int i = 0; i <= arrayLength - 1; i++) {
		destination[i] = source[i];
	}
}

double getSortTime(clock_t start, clock_t end) {
	return ((double)(end - start) / CLOCKS_PER_SEC);
}

void viewResult(double heapRandomTime, double heapReversedTime, double heapSortedTime,
		double quickRandomTime, double quickReversedTime, double quickSortedTime,
		double insertRandomTime, double insertReversedTime, double insertSortedTime) {
	printf("\nSorting result times table (each array contained %d elements):\n\n", arrayLength);
	printf("%39s|%17s|%17s\n", "Heap Sort", "Quick Sort", "Insert Sort");
	printf("%21s|%17f|%17f|%17f\n", "Random array", heapRandomTime, quickRandomTime, insertRandomTime);
	printf("%21s|%17f|%17f|%17f\n", "Max->min sorted array", heapReversedTime, quickReversedTime, insertReversedTime);
	printf("%21s|%17f|%17f|%17f\n", "Min->max sorted array", heapSortedTime, quickSortedTime, insertSortedTime);
}

void printSortAction(char sortType[], char arrayType[]) {
	printf("Sorting %s numbers array with %s...\n", arrayType, sortType);
}
