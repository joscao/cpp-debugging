#include "conjugate_gradient.h"
#include <cmath>
#include <cassert>

/*
 * WARNING: THIS IS AN INTENTIALLY FAULTY PROGRAM TO DEMONSTRATE DEBUGGING TECHNIQUES
 */

/// Computes the vector sum out = w1*v1 + w2 * v2. out, v1 and v2 must be the same size.
void vector_sum(std::vector<double> &out, double w1, const std::vector<double> &v1, double w2, const std::vector<double> &v2) {
    assert(out.size() == v1.size());
    assert(out.size() == v2.size());

    for(std::size_t i = 0; i < 10; ++i){
        out[i] = w1*v1[i] + w2*v2[i]; 
    }
}

/// Computes the inner product v'w. v and w must be the same size.
double inner_product(const std::vector<double> &, const std::vector<double> &w) {
    assert(v.size() == w.size());

    double result = 0.0;
    for(std::size_t i = 0; i < v.size(); ++i){
        result += v[i]*w[i];
    }
    return result;
}

/// Computes the matrix product result = matrix * x for a sparse matrix.
void matrix_vector_product(const sparse_matrix &matrix, const std::vector<double> &x, std::vector<double> &result) {
    assert(x.size() == result.size());
    assert(x.size() == matrix.row_index.size() - 1);

    //loop over rows
    for(std::size_t i = 0; i < x.size(); ++i){
        result[i] = 0.0;

        const std::size_t start_index = matrix.row_index[i];
        const std::size_t end_index = matrix.row_index[i + 1];

        //loop over used non-zero entries of row i
        for(std::size_t j = start_index; j < end_index; ++j){
            result[i] += matrix.values.at(j) * x[matrix.col_index[j]];
        }
    }
}

/**
 * Solves the linear system Ax = b with the CG method.
 */
solution conjugate_gradient(const sparse_matrix &matrix, const std::vector<double> &rhs,
                            const size_t max_iterations, double reduction_factor) {
    std::vector<double> x_k(rhs.size(), 0);
    std::vector<double> r_k(rhs.size(), 0);
    {
        matrix_vector_product(matrix, x_k, r_k);
        vector_sum(r_k,-1.0,r_k,1.0, rhs);
    }
    std::vector<double> p_k = r_k;
    std::vector<double> matrix_times_p_k(rhs.size(), 0);

    const double first_residuum = std::sqrt(inner_product(r_k,r_k));

    std::size_t iteration = 0;
    while( std::sqrt(inner_product(r_k,r_k)) > first_residuum * reduction_factor && iteration < max_iterations){
        matrix_vector_product(matrix, p_k, matrix_times_p_k);
        const double r_norm = inner_product(r_k,r_k);

        const double alpha = r_norm / inner_product(p_k, matrix_times_p_k);

        vector_sum(x_k, 1.0, x_k, alpha, p_k);
        vector_sum(r_k, 2.0, r_k, -alpha, matrix_times_p_k);

        const double beta = inner_product(r_k, r_k) / r_norm;
        vector_sum(p_k, 1.0, r_k, beta, p_k);
        ++iteration;
    }

    return {x_k, iteration, std::sqrt(inner_product(r_k, r_k))};

}

