#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>
using namespace std;

int fibonacci_sum_naive(long long n) {
  if (n <= 1)
    return n;

  long long previous = 0;
  long long current  = 1;
  long long sum      = 1;

  for (long long i = 0; i < n - 1; ++i) {
    long long tmp_previous = previous;
    previous = current;
    current = tmp_previous + current;
    sum += current;
  }

  return sum % 10;
}

long long pisano_period(long long m, vector<long long> &memo)
{
  memo.clear();
  memo.push_back(0);
  memo.push_back(1);
  long long prev = 1;
  long long i = 2;
  while(true) {
    long long cur = (memo[i-1]+memo[i-2])%m;
    if ( cur == 1 && prev == 0 ) {
      memo.pop_back();
      break;
    }
    memo.push_back(cur);
    prev = cur;
    ++i;
  }

  return memo.size();
}

int fibonacci_sum(long long n) {
  if (n <= 1)
    return n;

  vector<long long> memo;
  long long pp = pisano_period(10, memo);
  long long sum = (std::accumulate(memo.begin(), memo.end(), 0)%10) * ((n+1) / pp);
  long long sum_partial = std::accumulate(memo.begin(), memo.begin()+((n+1)%pp), 0)%10;

  //cout << "sum: " << sum << " sum_partial: " << sum_partial << endl;

  return (sum+sum_partial)%10;
}

void stress_test()
{
  for(int i = 0; i < 20; ++i)
    {
      cout << "Cur i: " << i << " ... ";
      int f_s_naive = fibonacci_sum_naive(i);
      int f_s = fibonacci_sum(i);
      cout << " Naive: " << f_s_naive << " Fast: " << f_s << endl;
      if( f_s_naive != f_s ){
	cout << "FAILED\n";
	exit(-1);
      }
    }
}

int main() {
  long long n = 0;
  std::cin >> n;
  //std::cout << fibonacci_sum_naive(n);
  std::cout << fibonacci_sum(n);
  //stress_test();
}

