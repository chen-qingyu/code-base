import time


def LCS(str1: str, str2: str) -> int:
    # 直接递归，时间复杂度 O(2^n)
    if str1 == "" or str2 == "":
        return 0
    elif str1[0] == str2[0]:
        return 1 + LCS(str1[1:], str2[1:])
    else:
        return max(LCS(str1[1:], str2), LCS(str1, str2[1:]))


def LCS_detail(str1: str, str2: str) -> str:
    # 直接递归，时间复杂度 O(2^n)
    if str1 == "" or str2 == "":
        return ""
    elif str1[-1] == str2[-1]:
        return LCS_detail(str1[:-1], str2[:-1]) + str1[-1]
    else:
        x = LCS_detail(str1[:-1], str2)
        y = LCS_detail(str1, str2[:-1])
        return x if len(x) > len(y) else y


def LCS_DP(str1: str, str2: str) -> int:
    # 动态规划，时间复杂度 O(n^2)
    row = len(str1)
    col = len(str2)
    dp = [[0] * (col + 1) for i in range(row + 1)]
    for r in range(row):
        for c in range(col):
            if str1[r] == str2[c]:
                dp[r + 1][c + 1] = dp[r][c] + 1
            else:
                dp[r + 1][c + 1] = max(dp[r][c + 1], dp[r + 1][c])
    return dp[row][col]


def LCS_DP_detail(str1: str, str2: str) -> str:
    # 动态规划，时间复杂度 O(n^2)
    row = len(str1)
    col = len(str2)
    dp = [[""] * (col + 1) for i in range(row + 1)]
    for r in range(row):
        for c in range(col):
            if str1[r] == str2[c]:
                dp[r + 1][c + 1] = dp[r][c] + str1[r]
            else:
                dp[r + 1][c + 1] = (dp[r][c + 1] if len(dp[r][c + 1]) > len(dp[r + 1][c]) else dp[r + 1][c])
    return dp[row][col]


if __name__ == '__main__':
    start = time.time()
    print(LCS("program", "algorithm"))
    print(LCS("educational", "advantage"))
    print(LCS("aaaaaaaaaaa", "aaaaaaaaaaa"))
    print(LCS("aaaaaaaaaaa", "bbbbbbbbbbb"))
    end = time.time()
    print("直接递归耗时：{:.4f} s".format(end - start))
    print("-" * 10)

    print(LCS_detail("program", "algorithm"))
    print(LCS_detail("educational", "advantage"))
    print(LCS_detail("aaaaaaaaaaa", "aaaaaaaaaaa"))
    print(LCS_detail("aaaaaaaaaaa", "bbbbbbbbbbb"))
    print("-" * 10)

    start = time.time()
    print(LCS_DP("program", "algorithm"))
    print(LCS_DP("educational", "advantage"))
    print(LCS_DP("aaaaaaaaaaa", "aaaaaaaaaaa"))
    print(LCS_DP("aaaaaaaaaaa", "bbbbbbbbbbb"))
    end = time.time()
    print("动态规划耗时：{:.4f} s".format(end - start))
    print("-" * 10)

    print(LCS_DP_detail("program", "algorithm"))
    print(LCS_DP_detail("educational", "advantage"))
    print(LCS_DP_detail("aaaaaaaaaaa", "aaaaaaaaaaa"))
    print(LCS_DP_detail("aaaaaaaaaaa", "bbbbbbbbbbb"))
