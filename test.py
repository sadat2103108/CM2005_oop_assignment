

n = 29
v = []
for _ in range(n):
    s = input().split()
    x = float(s[1])
    v.append(x)


# for x in v:
#     print(x)


print(sum(v)/len(v))

