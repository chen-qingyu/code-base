import numpy as np
import time


def LCS(str1, str2):
    # 直接递归，时间复杂度 O(2^n)
    if str1 == "" or str2 == "":
        return 0
    elif str1[0] == str2[0]:
        return 1 + LCS(str1[1:], str2[1:])
    else:
        return max(LCS(str1[1:], str2), LCS(str1, str2[1:]))


def LCS_DP(str1, str2):
    # 动态规划，时间复杂度 O(n^2)
    row = len(str1)+1
    col = len(str2)+1
    dp = np.zeros((row, col), dtype=int)
    for r in range(1, row):
        for c in range(1, col):
            if str1[r-1] == str2[c-1]:
                dp[r][c] = 1+dp[r-1][c-1]
            else:
                dp[r][c] = max(dp[r-1][c], dp[r][c-1])
    return dp[row-1][col-1]


start = time.time()
print(LCS_DP("program", "algorithm"))
print(LCS_DP("educational", "advantage"))
print(LCS_DP("aaaaaaaaaaa", "aaaaaaaaaaa"))
print(LCS_DP("aaaaaaaaaaa", "bbbbbbbbbbb"))
end = time.time()
print("动态规划：{:.4f} s".format(end-start))

start = time.time()
print(LCS("program", "algorithm"))
print(LCS("educational", "advantage"))
print(LCS("aaaaaaaaaaa", "aaaaaaaaaaa"))
print(LCS("aaaaaaaaaaa", "bbbbbbbbbbb"))
end = time.time()
print("直接递归：{:.4f} s".format(end-start))
