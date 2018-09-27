#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

int64_t MaxPairwiseProductBruteForce(const vector<int>& numbers) {
  int64_t result = 0;
  int n = numbers.size();
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (((int64_t)numbers[i]) * numbers[j] > result) {
        result = (int64_t)(numbers[i]) * (numbers[j]);
      }
    }
  }
  return result;
}

int64_t MaxPairwiseProduct_BigO_2N(const vector<int>& numbers) {
  int64_t L1, L2;
  int n = numbers.size();

  L1 = L2 = 0;

  for(int i = 0; i < n; ++i)
    if(numbers[i] > L1) { L2 = L1; L1 = numbers[i]; }
    else if(numbers[i] > L2) {L2 = numbers[i]; }

  int64_t result = L1 * L2;
  return result;
}

//#define STRESS_TEST
#ifndef STRESS_TEST
int main() {
  int n;
  cin >> n;
  vector<int> numbers(n);
  for (int i = 0; i < n; ++i) {
    cin >> numbers[i];
  }

  int64_t result = MaxPairwiseProduct_BigO_2N(numbers);
  cout << result << "\n";
  return 0;
}
#else
void StressTest(int N, int M)
{
  while(true) {
  int numbers_size = rand()%N + 2;
  
  vector<int> numbers(numbers_size, 0);
  for(int i = 0; i < numbers_size; ++i)
    numbers[i] = rand()%M;

  int64_t brute_force_res = MaxPairwiseProductBruteForce(numbers);
  int64_t bigo_2n_res = MaxPairwiseProduct_BigO_2N(numbers);

  for(int i = 0; i < numbers_size; ++i)
    cout << numbers[i] << " ";
  cout << "\n";
  if (brute_force_res == bigo_2n_res)
    cout << "OK\n";
  else {
    cout << "NOT OK - brute_force_res: " << brute_force_res << " bigo_2n_res: " << bigo_2n_res << "\n";
    return;
  }
  }
}

int main() {

  srand(0); // same seed all the time
  StressTest(100000,100000);

  return 0;
}
#endif
