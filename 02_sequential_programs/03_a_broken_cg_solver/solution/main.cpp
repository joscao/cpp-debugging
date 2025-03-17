// Compile the code with g++ -Wall -std=c++11 main.cpp conjugate_gradient.cpp -o cg_solver
// and then run the executable cg_solver.

#include "conjugate_gradient.h"
#include <cmath>
#include <iostream>
#include <cstddef>
#include <cassert>

std::vector<double> create_rhs_small(){
    return {14,2};
};

sparse_matrix create_matrix_small(){
    return {{2,-1,-1,1},{0,1,0,1},{0,2,4}};
};


std::vector<double> create_rhs_larger(){
    return {6,3,10,9,12};
};

sparse_matrix create_matrix_larger(){
    return {
        { 
          2,-1,
         -1,2,-1,
         -1,2,-1,
         -1,2,-1,
         -1,2
        },
        {
            0,1,
            0,1,2,
            1,2,3,
            2,3,4,
            3,4
        },
        {0,2,5,8,11,13}
    };
};


int main() {
    //smaller matrix
    {
        sparse_matrix A = create_matrix_small();
        std::vector<double> b = create_rhs_small();
    
        const int N = b.size();
    
        assert(N == A.row_index.size() - 1);
    
        for (int p = 4; p <= 16; p += 2) {
            double reduction_factor = std::pow(10, -p);
            auto x = conjugate_gradient(A, b, N*N, reduction_factor);
            std::cout << "CG: " << x.iterations << " iterations, reduction factor " << reduction_factor << ", residuum " << x.final_residuum << " with solution vector x = {";
            std::cout << x.solution[0] << " " << x.solution[1] << "}\n";
        }
    }
    
    //larger matrix
    {
        sparse_matrix A = create_matrix_larger();
        std::vector<double> b = create_rhs_larger();
    
        const int N = b.size();
    
        assert(N == A.row_index.size() - 1);
    
        for (int p = 4; p <= 16; p += 2) {
            double reduction_factor = std::pow(10, -p);
            auto x = conjugate_gradient(A, b, N*N, reduction_factor);
            std::cout << "CG: " << x.iterations << " iterations, reduction factor " << reduction_factor << ", residuum " << x.final_residuum << " with solution vector x = {";
            std::cout << x.solution[0] << " " << x.solution[1] << " " << x.solution[2] << " " << x.solution[3] << " " << x.solution[4] << "}\n";
        }
    }
    return 0;
}
