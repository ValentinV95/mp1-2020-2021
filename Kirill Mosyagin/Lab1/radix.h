int count_comp = 0, count_perm = 0;

void create_counters(double* mas, long* counters, long size)
{
    memset(counters, 0, 256 * sizeof(double) * sizeof(long));

    unsigned char* flag = (unsigned char*)mas;
    unsigned char* end_of_mas = (unsigned char*)(mas + size);

    while (flag != end_of_mas)
    {
        for (int i = 0; i < sizeof(double); i++)
            counters[256 * i + *flag++]++;
    }
}


void radix_pass(short Offset, long size, double* mas, double* dest, long* count)
{
    long temp_sum = 0, * count_flag = count, buf;

    for (int i = 256; i > 0; --i, ++count_flag)
    {
        buf = *count_flag;
        *count_flag = temp_sum;
        temp_sum += buf;
    }

    unsigned char* flag = (unsigned char*)mas + Offset;
    double* mas_flag = mas;

    for (long i = size; i > 0; --i, flag += sizeof(double), ++mas_flag)
    {
        count_perm++;
        count_flag = count + *flag;
        dest[*count_flag] = *mas_flag;
        ++(*count_flag);
    }
}

void radix_last_pass(short Offset, long size, double* mas, double* dest, long* count)
{
    long buf, * count_flag = count;

    long num_neg = 0;


    for (int i = 128; i < 256; i++)
        num_neg += count[i];

    long temp_sum = num_neg;

    for (int i = 0; i < 128; ++i, ++count_flag)
    {
        buf = *count_flag;
        *count_flag = temp_sum;
        temp_sum += buf;
    }

    temp_sum = count[255] = 0;
    count_flag = count + 254;

    for (int i = 254; i >= 128; --i, --count_flag)
    {
        *count_flag += temp_sum;
        temp_sum = *count_flag;
    }

    unsigned char* flag = (unsigned char*)mas + Offset;;
    double* mas_flag = mas;

    for (long i = size; i > 0; --i, flag += sizeof(double), ++mas_flag)
    {
        count_perm++;
        count_flag = count + *flag;
        if (*flag < 128) dest[(*count_flag)++] = *mas_flag;
        else dest[--(*count_flag)] = *mas_flag;
    }
}

void radix_sort(double*& source_mas, long size)
{
    double* out_mas = (double*)malloc(size * sizeof(double));
    unsigned short i;
    long* count, * counters = (long*)malloc(256 * sizeof(double) * sizeof(double));

    create_counters(source_mas, counters, size);

    for (i = 0; i < sizeof(double) - 1; i++)
    {
        count = counters + 256 * i;
        radix_pass(i, size, source_mas, out_mas, count);
        double* ttemp;
        ttemp = source_mas;
        source_mas = out_mas;
        out_mas = ttemp;
    }

    count = counters + 256 * i;

    radix_last_pass(i, size, source_mas, out_mas, count);

    delete source_mas;
    source_mas = out_mas;
    free(counters);
    std::cout << "number of comparisons " << count_comp << std::endl;
    std::cout << "number of permutations " << count_perm << std::endl;
}