#include <mpi.h>
#include <cstdio>

#define PART_A_MAT_TAG 0
#define B_MAT_TAG 1
#define BASE_C_MAT_TAG 2

//#define A(i, j, m) a_mat[(i) * m + (j)]
//#define B(i, j) b_mat[(i) * l + (j)] 

int world_rank, world_size;

// Read size of matrix_a and matrix_b (n, m, l) and whole data of matrixes from stdin
//
// n_ptr:     pointer to n
// m_ptr:     pointer to m
// l_ptr:     pointer to l
// a_mat_ptr: pointer to matrix a (a should be a continuous memory space for placing n * m elements of int)
// b_mat_ptr: pointer to matrix b (b should be a continuous memory space for placing m * l elements of int)
void construct_matrices(int *n_ptr, int *m_ptr, int *l_ptr, int **a_mat_ptr, int **b_mat_ptr)
{
    // Init MPI
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    if (world_rank == 0) {
        // Read n, m, l
        if (scanf("%d %d %d", n_ptr, m_ptr, l_ptr) != 3) {
            fprintf(stderr, "ERROR: Invalid input arguments\n");
            MPI_Abort(MPI_COMM_WORLD, -1);
        }
        // Allocate memory for a and b
        *a_mat_ptr = new int[(*n_ptr) * (*m_ptr)];
        *b_mat_ptr = new int[(*m_ptr) * (*l_ptr)];
        // Read matrix a
        for (int i = 0; i < (*n_ptr); ++i) {
            for (int j = 0; j < (*m_ptr); ++j) {
                if (scanf("%d", (*a_mat_ptr) + i * (*m_ptr) + j) != 1) {
                    fprintf(stderr, "ERROR: Invalid input arguments\n");
                    MPI_Abort(MPI_COMM_WORLD, -1);
                }
            }
        }
        // Read matrix b
        for (int i = 0; i < (*m_ptr); ++i) {
            for (int j = 0; j < (*l_ptr); ++j) {
                if (scanf("%d", (*b_mat_ptr) + j * (*m_ptr) + i) != 1) { // Transpose
                    fprintf(stderr, "ERROR: Invalid input arguments\n");
                    MPI_Abort(MPI_COMM_WORLD, -1);
                }
            }
        }
    }
    // Broadcast n, m, l
    MPI_Bcast(n_ptr, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(m_ptr, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(l_ptr, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

// Just matrix multiplication (your should output the result in this function)
// 
// n:     row number of matrix a
// m:     col number of matrix a / row number of matrix b
// l:     col number of matrix b
// a_mat: a continuous memory placing n * m elements of int
// b_mat: a continuous memory placing m * l elements of int
void matrix_multiply(const int n, const int m, const int l, const int *a_mat, const int *b_mat)
{
    if (world_rank == 0) {
        // Request and Status for MPI_Irecv
        MPI_Request a_mat_part_requests[world_size];
        MPI_Request b_mat_part_requests[world_size];
        MPI_Status a_mat_part_status[world_size];
        MPI_Status b_mat_part_status[world_size];
        // Split matrix a into n / world_size parts
        int a_mat_part_index[world_size + 1];
        for (int i = 0; i < world_size; ++i) {
            a_mat_part_index[i] = i * (n / world_size);
        }
        a_mat_part_index[world_size] = n;
        // Send matrix b to other processes
        for (int i = 1; i < world_size; ++i) {
            MPI_Isend(b_mat, m * l, MPI_INT, i, B_MAT_TAG, MPI_COMM_WORLD, b_mat_part_requests + i);
        }
        // Send parts of matrix a to other processes
        for (int i = 1; i < world_size; ++i) {
            MPI_Isend(a_mat + a_mat_part_index[i] * m, (a_mat_part_index[i + 1] - a_mat_part_index[i]) * m, MPI_INT, i, PART_A_MAT_TAG, MPI_COMM_WORLD, a_mat_part_requests + i);
        }
        // Allocate memory for c (result)
        int *c_mat = new int[n * l];
        // memset c_mat to 0
        memset(c_mat, 0, sizeof(int) * n * l);
        // Calculate the part of matrix c with rank 0
        for (int i = a_mat_part_index[0]; i < a_mat_part_index[1]; ++i) {
            for (int j = 0; j < l; ++j) {
                for (int k = 0; k < m; ++k) {
                    c_mat[i * l + j] += a_mat[i * m + k] * b_mat[j * m + k];
                }
            }
        }
        // Wait for other processes to receive parts of matrix a and matrix b
        MPI_Waitall(world_size - 1, a_mat_part_requests + 1, a_mat_part_status + 1);
        MPI_Waitall(world_size - 1, b_mat_part_requests + 1, b_mat_part_status + 1);
        // Request and Status for MPI_Irecv
        MPI_Request c_mat_part_requests[n - a_mat_part_index[1]];
        MPI_Status c_mat_part_status[n - a_mat_part_index[1]];
        // Receive parts of matrix c from other processes
        for (int i = 1; i < world_size; ++i) {
            for (int j = a_mat_part_index[i]; j < a_mat_part_index[i + 1]; ++j) {
                MPI_Irecv(c_mat + j * l, l, MPI_INT, i, BASE_C_MAT_TAG + (j - a_mat_part_index[i]), MPI_COMM_WORLD, c_mat_part_requests + (j - a_mat_part_index[1]));
            }  
        }
        // Wait for other processes to receive parts of matrix c
        MPI_Waitall(n - a_mat_part_index[1], c_mat_part_requests, c_mat_part_status);
        // Print matrix c
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < l; ++j) {
                printf("%d ", c_mat[i * l + j]);
            }
            printf("\n");
        }
        // Release memory
        delete[] c_mat;
    } else {
        // Allocate memory for part of matrix a and matrix b
        int part_index = world_rank * (n / world_size);
        int part_size = (world_rank == world_size - 1) ? (n - part_index) : (n / world_size);
        int *a_mat_part = new int[part_size * m];
        int *b_mat_part = new int[l * m];
        // Request for MPI_Irecv
        MPI_Request a_mat_part_request;
        MPI_Request b_mat_part_request;
        // Receive part of matrix a
        // Receive part of matrix b
        MPI_Irecv(b_mat_part, l * m, MPI_INT, 0, B_MAT_TAG, MPI_COMM_WORLD, &b_mat_part_request);
        MPI_Irecv(a_mat_part, part_size * m, MPI_INT, 0, PART_A_MAT_TAG, MPI_COMM_WORLD, &a_mat_part_request);
        // Allocate memory for part of matrix c
        int *c_mat_part = new int[part_size * l];
        // memset c_mat_part to 0
        memset(c_mat_part, 0, sizeof(int) * part_size * l);
        // Request and Status for MPI_Isend
        MPI_Request c_mat_part_requests[part_size];
        MPI_Status c_mat_part_status[part_size];
        // Wait for receiving part of matrix a and matrix b
        MPI_Wait(&a_mat_part_request, MPI_STATUS_IGNORE);
        // Calculate part of matrix c and send it to rank 0
        for (int i = 0; i < part_size; ++i) {
            for (int j = 0; j < l; ++j) {
                for (int k = 0; k < m; ++k) {
                    c_mat_part[i * l + j] += a_mat_part[i * m + k] * b_mat_part[j * m + k];
                }
            }
            MPI_Isend(c_mat_part + i * l, l, MPI_INT, 0, BASE_C_MAT_TAG + i, MPI_COMM_WORLD, c_mat_part_requests + i);
        }
        // Wait for sending part of matrix c
        MPI_Waitall(part_size, c_mat_part_requests, c_mat_part_status);
        // Release memory
        delete[] a_mat_part;
        delete[] b_mat_part;
        delete[] c_mat_part;
    }
}

// Remember to release your allocated memory
void destruct_matrices(int *a_mat, int *b_mat)
{
    // Release memory
    if (world_rank == 0) {
        delete[] a_mat;
        delete[] b_mat;
    }
}