void bubblesort(double* mas, int size)
{
	int count_comp = 0, count_perm = 0;
	int flag;
	for (int i = 0; i < size; ++i)
	{
		flag = 0;
		for (int j = 0; j < size - i - 1; ++j)
		{
			count_comp++;
			if (mas[j] > mas[j + 1])
			{
				count_perm++;
				double swap = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = swap;
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}
	std::cout << "number of comparisons " << count_comp << std::endl;
	std::cout << "number of permutations " << count_perm << std::endl;
}
