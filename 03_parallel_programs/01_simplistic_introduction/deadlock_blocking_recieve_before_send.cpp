#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * WARNING: THIS IS AN INTENTIALLY FAULTY PROGRAM TO DEMONSTRATE DEBUGGING TECHNIQUES
 */

int main(int argc, char* argv[]) {

  long number_of_elements;
  int myrank, total_ranks, right_neighbor, left_neighbor;
  int *sendbuf, *recvbuf;

  if (argc != 2) {
    printf("Usage: %s number_of_elements\n", argv[0]);
    return 1;
  }
  number_of_elements = strtol(argv[1], NULL, 10);

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &total_ranks);

  sendbuf = (int*)calloc(number_of_elements, sizeof(*sendbuf));
  recvbuf = (int*)calloc(number_of_elements, sizeof(*recvbuf));

  right_neighbor = (myrank+1) % total_ranks;
  left_neighbor = (myrank+total_ranks-1) % total_ranks;

  printf("%d: Receiving %ld elements of type int from my left neighbor %d.\n", myrank, number_of_elements, left_neighbor);
  MPI_Recv(recvbuf, number_of_elements, MPI_INT, left_neighbor, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  printf("%d: Sending %ld elements of type int to my right neighbor %d.\n", myrank, number_of_elements, right_neighbor);
  MPI_Send(sendbuf, number_of_elements, MPI_INT, right_neighbor, 0, MPI_COMM_WORLD);

  printf("%d: Done.\n", myrank);

  free(recvbuf);
  free(sendbuf);

  MPI_Finalize();

  return 0;
}
