#pragma once

/*
 * WARNING: THIS IS AN INTENTIALLY FAULTY PROGRAM TO DEMONSTRATE DEBUGGING TECHNIQUES
 */

#include <vector>
#include <cstddef>

struct sparse_matrix {
    std::vector<double> values;
    std::vector<size_t> col_index;
    std::vector<size_t> row_index;
};

struct solution {
    std::vector<double> solution;
    size_t iterations;
    double final_residuum;
};

solution conjugate_gradient(const sparse_matrix &matrix, const std::vector<double> &rhs,
                            size_t max_iterations, double reduction_factor);
