#include <iostream>
using namespace std;
int search(int arr[], int l, int r);
int main()
{
  int exp[] = {2, 4, -2, 5, -5, 7, 6, -2, 3, 5, 2, 6};
  cout << endl;
  cout << search(exp, 0, 11);
  return 0;
}
int search(int arr[], int l, int r)
{
  if (l == r)
  {
    return arr[l];
  }
  int mid = l + (r - l) / 2;
  int resL = search(arr, l, mid);
  int resR = search(arr, mid + 1, r);
  int keyl = 0, keyr = 0;
  int tmpl = 0, tmpr = 0;
  for (int i = mid; i >= l; i--)
  {
    tmpl += arr[i];
    if (tmpl > keyl)
    {
      keyl = tmpl;
    }
  }
  for (int i = mid + 1; i <= r; i++)
  {
    tmpl += arr[i];
    if (tmpl > keyl)
    {
      keyl = tmpl;
    }
  }
  int resmid = keyl + keyr;
  int res = resL > resR ? resL : resR;
  return res > resmid ? res : resmid;
}