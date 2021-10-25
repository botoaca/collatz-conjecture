#include <stdio.h>
#include <stdlib.h>

/* for plotting */
#include "external/include/pbPlots.h"
#include "external/include/supportLib.h"

/*
Collatz Conjecture

Consider the following operation on an arbitrary positive integer:
    If the number is even, divide it by two.
    If the number is odd, triple it and add one.

*/

/*
used realloc() instead

double*
insert(double* arr, int val, int len)
{
    double* new_arr = malloc(sizeof(double) * (len + 1));
    
    for (int i = 0; i < len; i++)
        new_arr[i] = arr[i];

    new_arr[len] = val;
    free(arr);
    return new_arr;
}
*/

int
main()
{
    int n, appeared_1 = false, iterations = 0;
    double* arr = malloc(sizeof(double));

    RGBABitmapImageReference* imgRef    = CreateRGBABitmapImageReference();
    ScatterPlotSeries* series           = GetDefaultScatterPlotSeriesSettings();
    ScatterPlotSettings* settings       = GetDefaultScatterPlotSettings();

    settings->title             = L"Collatz Conjecture";
    settings->titleLength       = wcslen(settings->title);

    settings->xLabel            = L"iterations";
    settings->xLabelLength      = wcslen(settings->xLabel);

    settings->yLabel            = L"number";
    settings->yLabelLength      = wcslen(settings->yLabel);

    settings->width             = 800;
    settings->height            = 600;

    settings->autoBoundaries    = true;
	settings->autoPadding       = true;

    printf("n = ");
    scanf("%d", &n);

    /* main logic */
    while (!appeared_1)
    {
        printf("%d -> ", n);
        arr = realloc(arr, sizeof(double) * (iterations + 1));
        arr[iterations] = (double)n;

        if (n % 2 == 0)
            n /= 2;
        else /* if (n % 2 != 0) */
            n = (n * 3) + 1;

        if (n == 1)
            appeared_1 = true;
    
        iterations++;
    }

    double* xs = malloc(sizeof(double) * iterations);
    for (int i = 0; i < iterations; i++)
        xs[i] = i;
    
    series->xs = xs;
    series->xsLength = iterations;
    series->ys = arr;
    series->ysLength = iterations;
    
    ScatterPlotSeries* s[] = { series };
    settings->scatterPlotSeries = s;
    settings->scatterPlotSeriesLength = 1;

    DrawScatterPlotFromSettings(imgRef, settings);
    
    size_t pngLen;
    double* pngData = ConvertToPNG(&pngLen, imgRef->image);
    WriteToFile(pngData, pngLen, "collatz.png");
    DeleteImage(imgRef->image);

    printf("1 (is looping)");
    printf("\n%d\n", iterations);

    return EXIT_SUCCESS;
}