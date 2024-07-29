void insertionSort(Element E[], long long int first, long long int last) {
	if ((last - first) < 1) { return; }
	for (long long int i = (first + 1); i <= last; i++) {
		for (long long int j = i; j > first; j--) {
			if (E[j] < E[j - 1]) { swap(&E[j], &E[j - 1]); }
			else { break; }
		}
	}
}

void mergeSort(Element E[], long long int first, long long int last) {
	if ((last - first) < 1) { return; }
	long long int mid = (first + last) / 2;
	mergeSort(E, first, mid);
	mergeSort(E, (mid + 1), last);
	merge(E, first, mid, last);
}