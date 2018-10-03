# parallel_matrix_multiply
Develop a parallel implementation of matrix multiplication as a group

This project will cover three different implementations of matrix multiplication:
* A sequential solution
* A pthread solution
* An OpenMP solution

It will also include an implementation of the Neighbor problem which is defined as follows:
Add up values for all neighbors (and self)

Adjust self based on these rules( top to bottom priority ):
% 10 == 0                        0
Under 50                         Add 3
Over 50 under 150         Subtract 3 Can't go negative(0)
over 150                          1
