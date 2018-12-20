#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define VALUE_RANGE    10000

static int *_alloc_array(size_t size)
{
  int   *array;

  array = malloc(sizeof(*array) * size);
  if (!array)
  {
    fprintf(stderr, "Could not allocate memory... Exiting.\n");
    exit(EXIT_FAILURE);
  }
  srand(time(NULL));
  for (size_t i = 0; i < size; i++)
    array[i] = rand() % VALUE_RANGE;
  return array;
}

static void _swap(int *array, unsigned int p1, unsigned int p2)
{
  int   mem;

  mem = array[p1];
  array[p1] = array[p2];
  array[p2] = mem;
}

static void _heapify(int *array, size_t size, unsigned int node)
{
  unsigned int  left;
  unsigned int  right;
  unsigned int  largest;

  left = node * 2 + 1;
  right = node * 2 + 2;
  largest = node;
  if (left < size && array[largest] < array[left])
    largest = left;
  if (right < size && array[largest] < array[right])
    largest = right;
  if (largest != node)
  {
    _swap(array, node, largest);
    _heapify(array, size, largest);
  }
}

void heapsort(int *array, size_t size)
{
  for (int i = size / 2 - 1; i >= 0; i--)
    _heapify(array, size, i);
  for (int i = size - 1; i >= 0; i--)
  {
    _swap(array, 0, i);
    _heapify(array, i, 0);
  }
}

int main(int ac, char **av)
{
  int           *array;
  size_t        size;

  if (ac != 2)
  {
    fprintf(stderr, "Usage: %s size\n", av[0]);
    return EXIT_FAILURE;
  }
  size = atoi(av[1]);
  array = _alloc_array(size);
  heapsort(array, size);
  return EXIT_SUCCESS;
}
