    // https://codeforces.com/contest/1105/submission/48631669
#include <random>
#include <chrono>

    auto timer_start = chrono::steady_clock::now().time_since_epoch().count(); // at beggining of main()
    
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    
    auto timer_now = chrono::steady_clock::now().time_since_epoch().count(); // right before your loops starts
    
    while((timer_now - timer_start) / 1e9 < TL) {
        shuffle(v.begin(), v.end(), rng);
        
        timer_now = chrono::steady_clock::now().time_since_epoch().count();
    }
