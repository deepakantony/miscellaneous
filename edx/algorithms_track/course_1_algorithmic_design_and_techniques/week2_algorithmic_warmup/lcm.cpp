#include <iostream>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

long gcd(int a, int b)
{
  if(a==0) return b;
  if(b==0) return a;
  return gcd(b, a%b);
}

long long lcm_fast(int a, int b) {
  return ((long long)a*b)/(long long)(gcd(a,b));
}

void stress_test()
{
  srand(2);
  for(int i = 0; i < 100000; ++i) {
    int a = rand()%10000;
    int b = rand()%10000;
    std::cout << "Testing - a: " << a << " b: " << b << std::endl;
    long long lcm_f = lcm_fast(a,b);
    long long lcm_n = lcm_naive(a,b);
    if(lcm_f != lcm_n) {
      std::cout << "lcm_fast: " << lcm_f << " lcm_naive: " << lcm_n << "\n";
      exit(-1);
    }
  }
}

int main() {
  int a, b;
  std::cin >> a >> b;
  //std::cout << lcm_naive(a, b) << std::endl;
  std::cout << lcm_fast(a, b) << std::endl;
  //stress_test();
  return 0;
}
