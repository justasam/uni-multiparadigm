#include <iostream>
#include <sstream>
#include <ctime>
#include <random>
#include "HashTable.h"

long randRange(long from, long to) {
  static std::default_random_engine generator(time(0));
  static std::uniform_int_distribution<long> d(from, to);
  return d(generator);
}

long randRange(long to) {
  return randRange(0, to);
}

/*
  https://cp-algorithms.com/algebra/binary-exp.html
*/
long binpow(long a, long b, long m) {
  a %= m;
  long res = 1;
  while (b > 0) {
    if (b & 1)
      res = res * a % m;
    a = a * a % m;
    b >>= 1;
  }
  return res;
}

/*
  https://stackoverflow.com/questions/1623375/writing-your-own-square-root-function
*/
long sqrt(long number) {
  if (number < 0) return 0;
  long a = 1, b = number;
  while(abs(a - b)> 1) {
    a = (a+b) / 2;
    b = number / a;
  }
  return a;
}

long findOrder(long n, long g) {
  HashTable Ord;
  long r, y;
  long tempVal;
  
  for (long i = 0; i < sqrt(n); i++) {
    r = randRange(n-1);
    y = binpow(g, r, n);
    tempVal = Ord.getValue(y);
    if (tempVal != KEY_NOT_FOUND) {
      if (r == tempVal) continue;
      if (r > tempVal) return r - tempVal;
      return tempVal - r;
    }
    Ord.insert(y, r);
  }

  return n - 1;
}

long findLogo(long n, long g, long a, bool &found) {
  long r, y;
  long tempVal;

  found = true;
  HashTable A, B;

  for (long i = 0; i < sqrt(n); i++) {
    r = randRange(n-1);
    y = a * binpow(g, r, n) % n;
    tempVal = B.getValue(y);
    if (tempVal != KEY_NOT_FOUND) return tempVal - r;
    A.insert(y, r);
    r = randRange(n-1);
    y = binpow(g, r, n);
    tempVal = A.getValue(y);
    if (tempVal != KEY_NOT_FOUND) return r - tempVal;
    B.insert(y, r);
  }

  found = false;
  return 0;
}

int main(int argc, char** argv) {
  if (argc != 4) {
    cout << "You must provide 3 arguments: g a n" << endl;
    return 1;
  }
  long g, a, n, o, l;
  bool found;

  g = atoi(argv[1]);
  a = atoi(argv[2]);
  n = atoi(argv[3]);
  o = findOrder(n, g);
  l = findLogo(n, g, a, found);

  if (!found) return 1;

  long answer = l % o;
  if (answer < 0) answer += o;

  cout << answer << endl;
  return 0;
}