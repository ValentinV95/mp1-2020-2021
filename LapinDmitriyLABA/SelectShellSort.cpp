
int SelCom = 0;
int SelPer = 0;


void SelectSort(double* a, size_t size) {
    for (int i = 0; i < size - 1; i++) {
        int min_id = i;
        for (int j = i + 1; j < size; j++) {
            SelCom++;
            if (a[j] < a[min_id]) {
                min_id = j;
                
            }
        }

        if (min_id > i) {
            SelPer++;

            double temp = a[min_id];
            a[min_id] = a[i];
            a[i] = temp;
        }

    }
}


int getSelectComparsion() {
    int temp = SelCom;
    SelCom = 0;
    return temp;
}
int getSelectPermutation() {
    int temp = SelPer;
    SelPer = 0;
    return temp;
}


int ShellCom = 0;
int ShellPer = 0;


void ShellSort(double* a, size_t size) {


    for (size_t step = size / 2; step > 0; step /= 2) {

        for (size_t i = step; i < size; i++) {
            double temp = a[i];
            int j = i;
            while (j >= step && a[j - step] > temp) {
                ShellCom++;
                ShellPer++;
                a[j] = a[j - step];
                j -= step;

            }
            ShellPer++;
            a[j] = temp;


        }
    }
}






int getShellComparsion() {
    int temp = ShellCom;
    ShellCom = 0;
    return temp;
}
int getShellPermutation() { 
    int temp = ShellPer;
    ShellPer = 0;
    return temp;
}


