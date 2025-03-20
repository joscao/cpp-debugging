#include <chrono>
#include <mpi.h>
#include <stdio.h>
#include <thread>
#include <iostream>

/*
 * WARNING: THIS IS AN INTENTIALLY FAULTY PROGRAM TO DEMONSTRATE DEBUGGING TECHNIQUES
 */

void time_consuming_function(){
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

int main() {
  MPI_Init(NULL,NULL);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Request req;

  int sendbuf = 2;
  int recvbuf = 3;

  if (rank == 0) {
    MPI_Isend(&sendbuf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &req);
    time_consuming_function();
    std::cout << "Rank" << rank << " sendbuf=" << sendbuf << std::endl;
  }
  if (rank == 1) {
    MPI_Irecv(&recvbuf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &req);
    time_consuming_function();

    std::cout << "Rank=" << rank << " recvbuf=" << recvbuf << std::endl;
  }

  MPI_Finalize();
}
