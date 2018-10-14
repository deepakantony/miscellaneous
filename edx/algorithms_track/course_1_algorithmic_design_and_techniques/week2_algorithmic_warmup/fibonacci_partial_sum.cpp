#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>
using namespace std;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
  long long sum = 0;

  long long current = 0;
  long long next  = 1;

  for (long long i = 0; i <= to; ++i) {
    if (i >= from) {
      sum += current;
    }

    long long new_current = next;
    next = next + current;
    current = new_current;
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

int fibonacci_partial_sum(long long m, long long n) {
  if( m == 0 ) return fibonacci_sum(n);

  int sum_m_1 = fibonacci_sum(m-1);
  int sum_n = fibonacci_sum(n);
  //cout << " \n sum_m_1: " << sum_m_1 << " sum_n: " << sum_n << endl;
  return (((sum_n - sum_m_1) % 10) + 10) % 10;
}

void stress_test()
{
  for(int i = 0; i < 40; ++i)
    for(int j = 0; j <= i; ++j)
    {
      cout << "Cur i: " << i << " Cur j: " << j << " ... ";
      int p_s_naive = get_fibonacci_partial_sum_naive(j,i);
      int p_s = fibonacci_partial_sum (j,i);
      cout << " Naive: " << p_s_naive << " Fast: " << p_s << endl;
      if( p_s_naive != p_s ){
	cout << "FAILED\n";
	exit(-1);
      }
    }
}


int main() {
  long long from, to;
  std::cin >> from >> to;
  //std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
  std::cout << fibonacci_partial_sum(from, to) << '\n';
  //stress_test();
}

