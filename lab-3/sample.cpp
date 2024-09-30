#include<bits/stdc++.h>
using namespace std;
#define modm 1000000007


long long mod_pow(long long x, long long i, long long m) {
    long long result = 1;
    x %= m; // Take x modulo m initially to avoid overflow

    while (i > 0) {
        // If i is odd, multiply x with result
        if (i % 2 == 1) {
            result = (result * x) % m;
        }

        // Square x and reduce it modulo m
        x = (x * x) % m;

        // Divide i by 2
        i /= 2;
    }

    return result;
}


int modCal(int num, int pow){
    int ans = 1;
    for(int i  = 1;i <= pow;i++){
        ans = ((ans % modm) * (num % modm)) % modm;
    }
    return ans;
}
int main(){
  cout << modCal(263,4) << endl;
  cout << mod_pow(263,4,modm);
}
