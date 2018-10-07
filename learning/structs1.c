#include <stdio.h>

typedef struct person {
  double age;
} Person;

int main(int argc, char const *argv[])
{
  Person me;
  me.age = 19.9;
  return 0;
}
