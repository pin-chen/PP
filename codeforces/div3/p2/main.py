#import json
num = dict()
for i in range(495):
  for j in range(i):
    num[2020*j+2021*(i-j)] = 1
t = input()
for x in range(int(t)):
  n = int(input())
  if n in num:
    print('YES')
  else:
    print('NO')