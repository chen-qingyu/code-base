def get_average(nums):
    return sum(nums) / len(nums)


def get_variance(nums):
    average = get_average(nums)
    dev = 0.0
    for num in nums:
        dev += (num - average) ** 2
    return dev / (len(nums) - 1)


def get_median(nums):
    nums = sorted(nums)
    size = len(nums)
    if size % 2 == 1:
        med = nums[size // 2]
    else:
        med = (nums[size // 2 - 1] + nums[size // 2]) / 2
    return med


numbers = list(map(eval, input("Please input numbers(split by space): ").split(' ')))
average = get_average(numbers)
variance = get_variance(numbers)
median = get_median(numbers)
print(f"平均数：{average} 方差：{variance} 中位数：{median}")
