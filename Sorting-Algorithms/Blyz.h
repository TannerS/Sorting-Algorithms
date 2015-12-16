
namespace Blyz
{
#pragma region Sorter Class
	template <class T>
	class Sorter
	{
	public:
		static void mergeSort(T*, int, int);
		static void quickSortRanomPivot(T*, int, int);
		static void quickSort(T*, int, int);
		static void quickInsertionSort(T*, int, int);
		static void insertionSort(T*, int, int);
		static void maxHeapSort(T*, int);
		static void minHeapSort(T*, int);

	private:
		static void merge(T*, T*, int, int, int);
		static void mergeSort(T*, T*, int, int);
		static void quickSortPartition(T*, int, int, int&);
		static void quickSort(T*, int, int, int);
		static void quickInsertionSort(T*, int, int, int);
		static void quickSortRanomPivot(T*, int, int, int);
		static void swap(T*, int, int);
		static void maxHeapify(T*, int, int);
		static void minHeapify(T*, int, int);
	};

#pragma endregion

#pragma region Merge Sort

	template <typename T>
	void Sorter<T>::mergeSort(T* arr, int low, int high)
	{
		T* temp = new T[(high - low) + 1];
		mergeSort(arr, temp, low, high);
		delete[] temp;
	}

	template <typename T>
	void Sorter<T>::mergeSort(T* arr, T* temp, int low, int high)
	{
		if (low < high)
		{
			int mid = ((low + high) / 2);
			mergeSort(arr, temp, low, mid);
			mergeSort(arr, temp, mid + 1, high);
			merge(arr, temp, low, mid, high);
		}
	}

	template <typename T>
	void Sorter<T>::merge(T* arr, T* temp, int low, int mid, int high)
	{
		int i = low;
		int k = low;
		int j = mid + 1;

		while (i <= mid && j <= high)
		{
			if (*(arr + i) <= *(arr + j))
				*(temp + k++) = *(arr + i++);
			else
				*(temp + k++) = *(arr + j++);
		}

		if (i > mid)
		{
			while (j <= high)
				*(temp + k++) = *(arr + j++);
		}
		else
		{
			while (i <= mid)
				*(temp + k++) = *(arr + i++);
		}

		for (int p = low; p <= high; p++)
			*(arr + p) = *(temp + p);
	}


#pragma endregion

#pragma region Insertion Sort

	template <typename T>
	void Sorter<T>::insertionSort(T* arr, int low, int high)
	{
		for (int i = low, j = 0; i <= high; i++)
		{
			T element = *(arr + i);
			j = i;

			while (j > 0 && *(arr + (j - 1)) > element)
			{
				*(arr + j) = *(arr + (j - 1));
				j--;
			}
			*(arr + j) = element;
		}
	}

#pragma endregion

#pragma region Quick Sort

	template <typename T>
	void Sorter<T>::quickSort(T* arr, int low, int high, int pivot)
	{
		if (low < high)
		{
			quickSortPartition(arr, low, high, pivot);
			quickSort(arr, low, pivot - 1, pivot);
			quickSort(arr, pivot + 1, high, pivot);
		}
	}

	template <typename T>
	void Sorter<T>::quickSort(T* arr, int low, int high)
	{
		int pivot = 0;
		if (low < high)
		{
			quickSortPartition(arr, low, high, pivot);
			quickSort(arr, low, pivot - 1, pivot);
			quickSort(arr, pivot + 1, high, pivot);
		}
	}


	template <typename T>
	void Sorter<T>::quickSortPartition(T* arr, int low, int high, int& pivot)
	{
		T v = *(arr + low);
		int j = low;

		for (int i = low + 1; i <= high; i++)
		{
			if (*(arr + i) < v)
			{
				j++;
				swap(arr, i, j);
			}
		}
		pivot = j;
		swap(arr, low, pivot);
	}

#pragma endregion 

#pragma region Quick Insertion Sort

	template <typename T>
	void Sorter<T>::quickInsertionSort(T* arr, int low, int high)
	{
		int pivot = 0;
		if (((high - low) + 1) <= 16)
			insertionSort(arr, low, high);
		else
		{
			quickSortPartition(arr, low, high, pivot);
			quickInsertionSort(arr, low, pivot - 1, pivot);
			quickInsertionSort(arr, pivot + 1, high, pivot);
		}
	}

	template <typename T>
	void Sorter<T>::quickInsertionSort(T* arr, int low, int high, int pivot)
	{
		if (((high - low) + 1) <= 16)
			insertionSort(arr, low, high);
		else
		{
			quickSortPartition(arr, low, high, pivot);
			quickInsertionSort(arr, low, pivot - 1, pivot);
			quickInsertionSort(arr, pivot + 1, high, pivot);
		}
	}

#pragma endregion 

#pragma region Random Quick Sort

	template <typename T>
	void Sorter<T>::quickSortRanomPivot(T* arr, int low, int high)
	{
		srand(time(NULL));
		int pivot = 0;
		if (low < high)
		{
			int range = (high - low) + 1;
			if (range >= 16)
				swap(arr, low, low + rand() % (range));
			quickSortPartition(arr, low, high, pivot);
			quickSortRanomPivot(arr, low, pivot - 1, pivot);
			quickSortRanomPivot(arr, pivot + 1, high, pivot);
		}
	}

	template <typename T>
	void Sorter<T>::quickSortRanomPivot(T* arr, int low, int high, int pivot)
	{
		srand(time(NULL));

		if (low < high)
		{
			int range = (high - low) + 1;
			if (range >= 16)
				swap(arr, low, low + rand() % (range));
			quickSortPartition(arr, low, high, pivot);
			quickSortRanomPivot(arr, low, pivot - 1, pivot);
			quickSortRanomPivot(arr, pivot + 1, high, pivot);
		}
	}

#pragma endregion

#pragma region Swap

	template <typename T>
	void Sorter<T>::swap(T* arr, int i, int j)
	{
		if (!(*(arr + i) == *(arr + j)))
		{
			*(arr + i) = *(arr + i) ^ *(arr + j);
			*(arr + j) = *(arr + i) ^ *(arr + j);
			*(arr + i) = *(arr + i) ^ *(arr + j);
		}
	}

#pragma endregion 

#pragma region HeapSort

	template <typename T>
	void Sorter<T>::maxHeapSort(T* arr, int size)
	{
		for (int cursor = ((int)floor((size / 2) - 1)); cursor >= 0; cursor--)
			maxHeapify(arr, cursor, size - 1);

		for (int cursor = size - 1; cursor >= 1; cursor--)
		{
			swap(arr, cursor, 0);
			maxHeapify(arr, 0, cursor - 1);
		}
	}

	template <typename T>
	void Sorter<T>::maxHeapify(T* arr, int parent, int size)
	{
		int lchild = (parent * 2) + 1;
		int rchild = (parent * 2) + 2;
		int largest = 0;

		if (lchild <= size && arr[lchild] > arr[parent])
			largest = lchild;
		else
			largest = parent;

		if (rchild <= size && arr[rchild] > arr[largest])
			largest = rchild;

		if (largest != parent)
		{
			swap(arr, largest, parent);
			maxHeapify(arr, largest, size);
		}
	}

	template <typename T>
	void Sorter<T>::minHeapSort(T* arr, int size)
	{
		for (int cursor = ((int)floor((size / 2) - 1)); cursor >= 0; cursor--)
			minHeapify(arr, cursor, size - 1);

		for (int cursor = size - 1; cursor >= 1; cursor--)
		{
			swap(arr, cursor, 0);
			minHeapify(arr, 0, cursor - 1);
		}
	}

	template <typename T>
	void Sorter<T>::minHeapify(T* arr, int parent, int size)
	{
		int lchild = (parent * 2) + 1;
		int rchild = (parent * 2) + 2;
		int smallest = 0;

		if (lchild <= size && arr[lchild] < arr[parent])
			smallest = lchild;
		else
			smallest = parent;

		if (rchild <= size && arr[rchild] < arr[smallest])
			smallest = rchild;

		if (smallest != parent)
		{
			swap(arr, smallest, parent);
			minHeapify(arr, smallest, size);
		}
	}

#pragma endregion 
}
