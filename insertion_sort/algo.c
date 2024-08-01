#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void generateRandomFiles() {
    int sizes[100];
    int count = 100;
    for (int i = 0; i < 100; i++) {
        sizes[i] = count;
        count += 100;
    }
    // int sizes[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    srand(time(0));

    for (int i = 0; i < numSizes; i++) {
        char filename[50];
        sprintf(filename, "input_%d.txt", sizes[i]);
        FILE *file = fopen(filename, "w");

        if (file == NULL) {
            printf("Error opening file %s\n", filename);
            exit(1);
        }

        for (int j = 0; j < sizes[i]; j++) {
            int num = rand() % 10000; // Generate random numbers between 0 and 9999
            fprintf(file, "%d ", num);
        }

        fclose(file);
    }

    printf("Random files generated successfully!\n");
}

void reverseArray(int arr[], int n) {
    int temp;
    for (int i = 0; i < n / 2; i++) {
        temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }
}

void sortFilesAndMeasureTime() {
    int sizes[100];
    int count = 100;
    for (int i = 0; i < 100; i++) {
        sizes[i] = count;
        count += 100;
    }
    // int sizes[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    char outputFilename_avg[50];
    char outputFilename_best[50];
    char outputFilename_worst[50];
    sprintf(outputFilename_avg, "outputAvg.txt");
    sprintf(outputFilename_best, "outputBest.txt");
    sprintf(outputFilename_worst, "outputWorst.txt");

    // Clear contents of output files before writing new data
    FILE *outputFileAvg = fopen(outputFilename_avg, "w");
    FILE *outputFileBest = fopen(outputFilename_best, "w");
    FILE *outputFileWorst = fopen(outputFilename_worst, "w");
    if (outputFileAvg) fclose(outputFileAvg);
    if (outputFileBest) fclose(outputFileBest);
    if (outputFileWorst) fclose(outputFileWorst);

    for (int i = 0; i < numSizes; i++) {
        char inputFilename[50];
        sprintf(inputFilename, "input_%d.txt", sizes[i]);

        FILE *file = fopen(inputFilename, "r");
        if (file == NULL) {
            printf("Error opening file %s\n", inputFilename);
            exit(1);
        }

        int *arr = (int*)malloc(sizes[i] * sizeof(int));
        for (int j = 0; j < sizes[i]; j++) {
            fscanf(file, "%d", &arr[j]);
        }
        fclose(file);

        // Average case (randomly ordered array)
        clock_t startAvg = clock();
        insertionSort(arr, sizes[i]);
        clock_t endAvg = clock();
        double time_taken_avg = ((double)(endAvg - startAvg)) / CLOCKS_PER_SEC;
        outputFileAvg = fopen(outputFilename_avg, "a");
        fprintf(outputFileAvg, "%d %f\n", sizes[i], time_taken_avg);
        fclose(outputFileAvg);

        // Best case (already sorted array)
        clock_t startBest = clock();
        insertionSort(arr, sizes[i]);
        clock_t endBest = clock();
        double time_taken_best = ((double)(endBest - startBest)) / CLOCKS_PER_SEC;
        outputFileBest = fopen(outputFilename_best, "a");
        fprintf(outputFileBest, "%d %f\n", sizes[i], time_taken_best);
        fclose(outputFileBest);

        // Reverse the sorted array for the worst case scenario
        reverseArray(arr, sizes[i]);
        clock_t startWorst = clock();
        insertionSort(arr, sizes[i]);
        clock_t endWorst = clock();
        double time_taken_worst = ((double)(endWorst - startWorst)) / CLOCKS_PER_SEC;
        outputFileWorst = fopen(outputFilename_worst, "a");
        fprintf(outputFileWorst, "%d %f\n", sizes[i], time_taken_worst);
        fclose(outputFileWorst);

        free(arr);
    }

    printf("Files sorted and results saved successfully!\n");
}

int main() {
    generateRandomFiles();
    sortFilesAndMeasureTime();
    return 0;
}
