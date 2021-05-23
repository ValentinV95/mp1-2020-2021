void mergeSort(double* mas, int left_half, int right_half) 
{
	//int count_comp = 0, count_perm = 0;
	if (left_half == right_half) return; 
	int mid = (left_half + right_half) / 2; 
	mergeSort(mas, left_half, mid);
	mergeSort(mas, mid + 1, right_half);
	int i = left_half; 
	int j = mid + 1; 
	double* tmp = (double*)malloc((right_half - left_half + 1) * sizeof(double)); 

	for (int step = 0; step < right_half - left_half + 1; step++) 
	{
		
		if ((j > right_half) || ((i <= mid) && (mas[i] < mas[j])(count_comp++)) )
		{
			tmp[step] = mas[i];
			i++;
		}
		else
		{
			tmp[step] = mas[j];
			j++;
		}
	}

	for (int step = 0; step < right_half - left_half + 1; step++)
	{
		count_perm++;
		mas[left_half + step] = tmp[step];
	}
	free(tmp);	
}
