#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
int data[100000];
int tmp[100000];
int ran[100000];
int rev[100000];
double DATA[7][6] = { 0 };//Bubble,Selection,Insertion,Merge,Quick1,2,3
char data_index[7][100] = { "\t","Random1000","Reverse1000","Random10000","Reverse10000","Random100000","Reverse100000" };
char Category[7][100] = { "Bubble","Selection","Insertion","Merge","Quick1","Quick2","Quick3" };
clock_t end, start;
#define DATALENGTH 100000

void Random_n(int n)
{
	int a, i;
	for (int i = 0; i < n; i++) {
		a = rand() % n + 1;
		ran[i] = a;
	}
}

void Reverse_n(int n)
{
	int a, i;
	a = n;
	for (int i = 0; i < n; i++)
		rev[i] = n--;
}
swap(int data[], int a, int b)
{
	int tmp = data[a];
	data[a] = data[b];
	data[b] = tmp;

}
double bubblesort(int data[], int n)
{
	Random_n(n);
	Reverse_n(n);
	int i, j = 0;
	start = clock();
	for (int i = 0; i < n - 1; i++) {
		for (j = 0; j < n - 1; j++)
		{
			if (data[i] > data[j])
				swap(data, i, j);
		}
	}
	end = clock();
	return (double)(end - start) / (CLOCKS_PER_SEC);
}

double Insertionsort(int data[], int n)
{
	Random_n(n);
	Reverse_n(n);
	int i, j;
	start = clock();
	for (i = 1; i < n; i++)
	{
		int key = data[i];
		for (j = i - 1; j >= 0; j--) {
			if (data[j] > key)
				data[j + 1] = data[j];
			else break;
		}
		data[j + 1] = key;
	}
	end = clock();
	return (double)(end - start) / (CLOCKS_PER_SEC);
}
void merge(int data[], int first, int mid, int last)
{

	int i, j, k, l;
	i = first;
	j = mid + 1;
	k = first;

	while (i <= mid && j <= last) {
		if (data[i] <= data[j])
			tmp[k++] = data[i++];
		else
			tmp[k++] = data[j++];
	}

	if (i > mid) {
		for (l = j; l <= last; l++)
			tmp[k++] = data[l];
	}
	else {
		for (l = i; l <= mid; l++)
			tmp[k++] = data[l];
	}
	for (l = first; l <= last; l++) {
		data[l] = tmp[l];
	}
}

double merge_sort(int data[], int first, int last) {
	Random_n(last);
	Reverse_n(last);
	int mid;
	start = clock();
	if (first < last) {
		mid = (first + last) / 2;
		merge_sort(data, first, mid);
		merge_sort(data, mid + 1, last);
		merge(data, first, mid, last);
	}
	end = clock();
	return (double)(end - start) / (CLOCKS_PER_SEC);
}

double selectionsort(int data[], int n) {
	int k = 0;
	start = clock();
	for (int last = n - 1; last > 0; last--)
	{
		int k = last;
		for (int i = 0; i < last; i++) {
			if (data[i] > data[last]) {
				k = i;
				swap(data, k, last);
			}

		}
	}
	end = clock();
	return (double)(end - start) / (CLOCKS_PER_SEC);
}

double quickSort1(int data[], int n, int m) {
	Random_n(m);
	Reverse_n(m);
	start = clock();
	if (n < m) {
		int q = partition1(data, n, m);
		quickSort1(data, n, q - 1);
		quickSort1(data, q, m);
	}
	end = clock();
	return (double)(end - start) / (CLOCKS_PER_SEC);
}

int  partition1(int data[], int p, int r) {
	int x = data[r];	//pivot
	int i = p - 1;
	if (i <-1)return 0;
	for (int j = p; j < r; j++) {

		if (data[j] <= x) {
			i++;
			swap(data, i, j);
		}
	}
	swap(data, i + 1, r);
	return i + 1;
}

int MedianOfThree(int A[], int p, int r) {
	int a = A[p];
	int b = A[r];
	int c = A[(int)(p + r) / 2];

	int arr[] = { a,b,c };
	bubblesort(arr, 3);

	return arr[1];

}
int  partition2(int A[], int p, int r) {
	int x = MedianOfThree(A, p, r);
	int i = p - 1;
	if (i <-1)return 0;
	for (int j = p; j <r; j++) {

		if (A[j] <= x) {
			i++;
			swap(A, i, j);
		}
	}
	swap(data, i + 1, r);
	return i + 1;
}


double quickSort2(int A[], int p, int r) {
	Random_n(r);
	Reverse_n(r);
	start = clock();
	if (p < r) {
		int q = partition2(A, p, r);
		quickSort2(A, p, q - 1);
		quickSort2(A, q, r);
	}
	end = clock();
	return (double)(end - start) / (CLOCKS_PER_SEC);
}

int  partition3(int A[], int p, int r) {
	int pivotindex = p + 1 + (rand() % (r - p + 1));	//pivotindex;
	int x = A[pivotindex];		//pivot
	int i = p - 1;
	if (i < -1)return 0;
	for (int j = p; j < r; j++) {
		if (A[j] <= x) {
			i++;
			swap(data, i, j);
		}
	}
	swap(A, i + 1, r);
	return i + 1;
}

double quickSort3(int A[], int p, int r) {
	Random_n(r);
	Reverse_n(r);
	start = clock();
	if (p < r) {
		int q = partition3(A, p, r);
		quickSort3(A, p, q - 1);
		quickSort3(A, q, r);
	}
	end = clock();
	return (double)(end - start) / (CLOCKS_PER_SEC);
}
void max_heapify(int data[], int i, int n)
{
	if (i * 2 > n) return;
	int k = 2 * i;
	if (k + 1 <= n && data[k] < data[k + 1]) k++;
	if (data[i] >= data[k]) return;
	swap(data,i,k);
	max_heapify(data, k, n);

}

void build_max_heap(int data[], int n)
{
	for (int i = n / 2; i >= 1; i--) {
		max_heapify(data, i, n);
	}
}

double heapsort(int data[], int n) {
	build_max_heap(data, n);
	start = clock();

	for (int i = n; i > 1; i--) {
		swap(data,1,i);
		n--;
		max_heapify(data, 1, n);

	}
	end = clock();
	return (double)(end - start) / (CLOCKS_PER_SEC);
}
void print() {
	Random_n(100000);
	Reverse_n(100000);
	printf("\t\tRandom1000\tReverse1000\tRandom10000\tReverse10000\tRandom100000\tReverse100000\n\n\n");
	printf("Bubble    \t ");
	printf("%lf \t%lf\t%lf\t%lf\t%lf\t%lf ", bubblesort(ran, 1000), bubblesort(rev, 1000), bubblesort(ran, 10000), bubblesort(rev, 10000), bubblesort(ran, 100000), bubblesort(rev, 100000));
	printf("\nSelection    \t");
	printf("%lf \t%lf \t%lf \t%lf \t%lf \t%lf\n", selectionsort(ran, 1000), selectionsort(rev, 1000), selectionsort(ran, 10000), selectionsort(rev, 10000), selectionsort(ran, 100000), selectionsort(rev, 100000));
	printf("Insertion    \t ");
	printf("%lf \t%lf \t%lf \t%lf \t%lf \t%lf\n", Insertionsort(ran, 1000), Insertionsort(rev, 1000), Insertionsort(ran, 10000), Insertionsort(rev, 10000), Insertionsort(ran, 100000), Insertionsort(rev, 100000));
	printf("Merge    \t ");
	printf("%lf \t%lf \t%lf \t%lf \t%lf \t%lf\n", merge_sort(ran, 0, 1000), merge_sort(rev, 0, 1000), merge_sort(ran, 0, 10000), merge_sort(rev, 0, 10000), merge_sort(ran, 0, 100000), merge_sort(rev, 0, 100000));
	printf("Quick1    \t ");
	printf("%lf \t%lf \t%lf \t%lf \t%lf \t%lf\n", quickSort1(ran, 0, 1000), quickSort1(rev, 0, 1000), quickSort1(ran, 0, 10000), quickSort1(rev, 0, 10000), quickSort1(ran, 0, 100000), quickSort1(rev, 0, 100000));
	printf("Quick2    \t ");
	printf("%lf \t%lf \t%lf \t%lf \t%lf \t%lf\n", quickSort2(ran, 0, 1000), quickSort2(rev, 0, 1000), quickSort2(ran, 0, 10000), quickSort2(rev, 0, 10000), quickSort2(ran, 0, 100000), quickSort2(rev, 0, 100000));
	printf("Quick3    \t ");
	printf("%lf \t%lf \t%lf \t%lf \t%lf \t%lf\n", quickSort3(ran, 0, 1000), quickSort3(rev, 0, 1000), quickSort3(ran, 0, 10000), quickSort3(rev, 0, 10000), quickSort3(ran, 0, 100000), quickSort3(rev, 0, 100000));
	printf("heap sort\t ");
	printf("%lf \t%lf \t%lf \t%lf \t%lf \t%lf\n", heapsort(ran, 1000), heapsort(rev, 1000), heapsort(ran, 10000), heapsort(rev, 10000), heapsort(ran, 100000), heapsort(rev, 100000));
}
int main(void)
{
	print();
	getchar();
}