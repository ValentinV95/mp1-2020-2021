#pragma once
typedef struct inf
{
    int count_if, count_swap;
} inf;

void merge_sort(float* array, int n);
void shell_sort(float* arr, int n);
void insert_sort(float* arr, int n);
void hoar_sort(float* arr, int first, int n);
inf radix_sort(float* arr, int size);
void print_if_and_swap();
void obnull_if_swap();
