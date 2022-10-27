/* 
Divide and Conquer
  IF -> dp(i, j) = min(0<=k<=j) dp(i - 1, k - 1) + C(k + j)
  AND HOLDS -> opt(i, j) <= opt(i, j + 1)
  Complexity from O(nm^2) to O(nmlgm)
  NOTES -> Process row to row, checking mid and dividing optk
 */ 

/*
Knuths Opt
  IF -> dp(i, j) = min(i<=k<j) dp(i, k) + dp(k + 1, j) + C(i, j)
  AND HOLDS -> opt(i, j - 1) <= opt(i, j) <= opt(i + 1, j)
  Complexity from O(n^3) to O(n^2)
  NOTES -> Process row to row, checking mid and dividing optk
*/
