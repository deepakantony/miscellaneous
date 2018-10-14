#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

long long get_fibonacci_huge_naive(long long n, long long m) {
  if (n <= 1)
    return n;

  long long previous = 0;
  long long current  = 1;

  for (long long i = 0; i < n - 1; ++i) {
    long long tmp_previous = previous;
    previous = current;
    current = tmp_previous + current;
  }

  return current % m;
}

long long get_pisano_period(long long m, vector<long long> &memo)
{
  assert(m>1);

  memo.clear();
  memo.push_back(0);
  memo.push_back(1);
  long long prev = 1;
  long long i = 2;

  while(true) {
    long long cur = (memo[i-2]+memo[i-1])%m;

    if(cur == 1 && prev == 0) {
      memo.pop_back();
      break;
    }

    memo.push_back(cur);
    ++i;
    prev = cur;
  }
  
  return memo.size();
}

long long get_fibonacci_huge(long long n, long long m) {
  if (n==0) return 0;
  if (m==1) return 0;
  
  vector<long long> memo;
  long long pp = get_pisano_period(m,memo);
  //cout << "Pisano period: " << pp << "\n";
  return memo[n%pp];
}

void stress_test()
{
  for(int i = 0; i < 100000; ++i) {
    long long m = rand() % 10000 + 1;

    long long naive = get_fibonacci_huge_naive(i, m);
    long long fast = get_fibonacci_huge(i, m);
    cout << "N: " << i << " M: " << m << " naive: " << naive << " fast: " << fast << endl;
    if ( naive != fast ) {
      cout << "FAILED\n";
      break;
    }
  }
}

int main() {
  long long n, m;
  std::cin >> n >> m;
  //std::cout << get_fibonacci_huge_naive(n, m) << '\n';
  std::cout << get_fibonacci_huge(n, m) << '\n';
  //stress_test();
}

