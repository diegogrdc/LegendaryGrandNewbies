/* 
Divide and Conquer
  IF -> dp(i, j) = min(0<=k<=j) dp(i - 1, k - 1) + C(k + j)
  THEN -> opt(i, j) <= opt(i, j + 1)
  Complexity from O(nm^2) to O(nmlgm)
  NOTES -> Process row to row, checking mid and dividing optk
 */ 
