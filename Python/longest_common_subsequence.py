import timeit


def lcs(str1: str, str2: str) -> int:
    # 直接递归，时间复杂度 O(2^n)
    if str1 == "" or str2 == "":
        return 0
    elif str1[0] == str2[0]:
        return 1 + lcs(str1[1:], str2[1:])
    else:
        return max(lcs(str1[1:], str2), lcs(str1, str2[1:]))


def lcs_detail(str1: str, str2: str) -> str:
    # 直接递归，时间复杂度 O(2^n)
    if str1 == "" or str2 == "":
        return ""
    elif str1[-1] == str2[-1]:
        return lcs_detail(str1[:-1], str2[:-1]) + str1[-1]
    else:
        x = lcs_detail(str1[:-1], str2)
        y = lcs_detail(str1, str2[:-1])
        return x if len(x) > len(y) else y


def lcs_dp(str1: str, str2: str) -> int:
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


def lcs_dp_detail(str1: str, str2: str) -> str:
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
    assert lcs("program", "algorithm") == 3
    assert lcs("educational", "advantage") == 4
    assert lcs("aaaaaaaaaaa", "aaaaaaaaaaa") == 11
    assert lcs("aaaaaaaaaaa", "bbbbbbbbbbb") == 0

    assert lcs_detail("program", "algorithm") == "grm"
    assert lcs_detail("educational", "advantage") == "dana"
    assert lcs_detail("aaaaaaaaaaa", "aaaaaaaaaaa") == "aaaaaaaaaaa"
    assert lcs_detail("aaaaaaaaaaa", "bbbbbbbbbbb") == ""

    assert lcs_dp("program", "algorithm") == 3
    assert lcs_dp("educational", "advantage") == 4
    assert lcs_dp("aaaaaaaaaaa", "aaaaaaaaaaa") == 11
    assert lcs_dp("aaaaaaaaaaa", "bbbbbbbbbbb") == 0

    assert lcs_dp_detail("program", "algorithm") == "grm"
    assert lcs_dp_detail("educational", "advantage") == "dana"
    assert lcs_dp_detail("aaaaaaaaaaa", "aaaaaaaaaaa") == "aaaaaaaaaaa"
    assert lcs_dp_detail("aaaaaaaaaaa", "bbbbbbbbbbb") == ""

    print("lcs: {:.4f}s".format(timeit.timeit('lcs("program", "algorithm")', 'from __main__ import lcs', number=10)))
    print("lcs_dp: {:.4f}s".format(timeit.timeit('lcs_dp("program", "algorithm")', 'from __main__ import lcs_dp', number=10)))
