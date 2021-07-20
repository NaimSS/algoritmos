// gcd(a,m) == 1, otherwise there is no inverse!!!
// if gcd(a,m)!=1, is a good idea to factor and then join by CRT
template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a; swap(a, m);
    u -= t * v; swap(u, v);
  }
  assert(m == 1);
  return u;
}
