def getNumbers():
    numStr = input("Please input numbers(split by space): ")
    nums = numStr.split(' ')
    nums = list(map(eval, nums))
    return nums


def getAverage(nums):
    return sum(nums) / len(nums)


def getVariance(nums, average):
    dev = 0.0
    for num in nums:
        dev += (num - average) ** 2
    return dev / (len(nums) - 1)


def getMedian(nums):
    nums = sorted(nums)
    size = len(nums)
    if size % 2:
        med = nums[size // 2]
    else:
        med = (nums[size // 2 - 1] + nums[size // 2]) / 2
    return med


numbers = getNumbers()
average = getAverage(numbers)
variance = getVariance(numbers, average)
median = getMedian(numbers)
print("平均数：{:.2f} 方差：{:.2f} 中位数：{}".format(average, variance, median))
input()
