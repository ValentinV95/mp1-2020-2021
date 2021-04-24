#ifndef SORT_H
#define SORT_H

extern unsigned int permutation;
extern unsigned int comparison;
void BubbleSort(unsigned int, float*);
void ShellSort(unsigned int, float*);
void MergeSort(unsigned int, unsigned int, float*, float*);
void SRadixSort(float*, float*, long*, long);

#endif