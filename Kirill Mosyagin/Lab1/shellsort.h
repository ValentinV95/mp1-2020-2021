void shellsort(double* mas, int size) 
{
	int count_comp = 0, count_perm = 0;
	double swap;
	int i, j, k, step;
	for (step = size / 2; step > 0; step /= 2)
	{
		for (i = 0; i < step; ++i)
		{
			for (j = i + step; j < size; j += step)
			{
				swap = mas[j];
				k = j - step;
				count_comp++;
				while (k >= 0 && mas[k] >= mas[k + step])
				{
					count_comp++;
					count_perm++;
					mas[k + step] = mas[k];
					mas[k] = swap;
					k = k - step;
				}
			}
		}
	}
	std::cout << "number of comparisons " << count_comp << std::endl;
	std::cout << "number of permutations " << count_perm << std::endl;
}