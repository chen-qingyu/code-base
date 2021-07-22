days = 365
dayup = pow(1 + 0.01, days)
daydown = pow(1 - 0.01, days)
print("每天进步百分之一，一年后进步{:.3f}。".format(dayup))
print("每天退步百分之一，一年后剩下{:.3f}。".format(daydown))
print("两者相差{:.2f}倍。".format(dayup / daydown))
