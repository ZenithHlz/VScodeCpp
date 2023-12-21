#include <iostream>
#include <vector>

std::vector<int> multiplyByTwo(const std::vector<int>& num) {
   std::vector<int> result;
   int carry = 0;

   for (int i = num.size() - 1; i >= 0; i--) {
       int product = num[i] * 2 + carry;
       result.insert(result.begin(), product % 10);
       carry = product / 10;
   }

   if (carry > 0) {
       result.insert(result.begin(), carry);
   }

   return result;
}

std::vector<int> calculatePowerOfTwo(int exponent) {
   std::vector<int> result = { 1 }; // Start with 2^0 = 1

   for (int i = 0; i < exponent; i++) {
       result = multiplyByTwo(result);
   }

   return result;
}

int main() {
   std::vector<int> num = calculatePowerOfTwo(15000);
   for (int digit : num) {
       std::cout << digit;
   }
   std::cout << std::endl;

   return 0;
}