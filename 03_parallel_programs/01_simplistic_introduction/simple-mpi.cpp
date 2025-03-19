//adapted example from https://github.com/TomMelt/mdb/blob/main/examples/simple-mpi-cpp.cpp

# include <cstdlib>
# include <ctime>
# include <iostream>
# include <mpi.h>
# include <unistd.h>

void leveltwo(){
  std::cout << "in level 2" << '\n';
}

void levelone(){
  std::cout << "in level 1" << '\n';
  MPI_Barrier(MPI_COMM_WORLD);
  leveltwo();
}

int main(void){
  int process_rank, size_of_cluster;

  float var = 0.;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size_of_cluster);
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

  var = 10.*process_rank;

  if (process_rank == 0){
    std::cout << "process 0 sleeping for 3s..." << '\n';

    for (int i = 0; i < 3; ++i) {
      sleep(1);
      std::cout << i << " s..." << '\n';
    }
  }

  MPI_Barrier(MPI_COMM_WORLD);
  levelone();

  std::cout << "internal process: " << process_rank << " of " << size_of_cluster << '\n';
  std::cout <<  "var = " << var << '\n';

  MPI_Finalize();
}