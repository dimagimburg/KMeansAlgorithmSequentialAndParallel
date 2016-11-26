# KMeans Clusters Finding Algorithm Sequential And Parallel

Parallel and sequential implementation of cluster finding algorithm based on KMeans, parallel is implemented with CUDA and OpenMP, communication is done with MPI (mpich1.4.1p)

## Instalation:
1. (if you use visual studio) link the MPICH library follow those instructions: http://nick-goodman.blogspot.co.il/2012/02/using-mpich-from-ms-visual-studio-2010.html

## The problem world:

*impleneted for points [(x,y) plane], each point is moving in circle around its center*

Given input is:

1. **N** - number of points (a, b, radius)
2. **K** - number of clusters wanted
2. **delta_t** - the time step between calculation of centers of the clusters
3. **T** - time interval
4. **LIMIT** - the max number of iterations fo KMeans alg.

![Point p moves](https://s18.postimg.org/jdsa8btah/2016_10_19_1119.png)

input is delivered from file looks like:

**line 1:** N K delta_t T LIMIT

**line 2 - line N:** point_index x y radius

## Tests:
### Test 1:
first test was made on 14 points as in the image below:

![Point p moves](https://raw.githubusercontent.com/dimagimburg/KMeansAlgorithmSequentialAndParallel/master/input_test_1.png)

points were chosen to get 3 very strong and easy visible clusters.
