"""
 ID: tfan0328
 PROG: shuttle
 LANG: PYTHON3
 """
import math

fin = open('shuttle.in', 'r')
N = int(fin.readline().strip())

diff = [-1, 2, 1, -2, -2, -1, 2, 2, 2, 1, -2, -2 ,-2, -2, -1, 2, 2, 2, 2, 2, 1, -2, -2 ,-2, -2, -2, -2, -1, 2, 2, 2, 2, 2, 2, 2, 1, -2, -2 ,-2, -2, -2, -2, -2, -2, -1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, -2, -2 ,-2, -2, -2, -2, -2, -2, -2, -2, -1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, -2, -2 ,-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1]

len = N*N+2*N
arr = []
arr.append(N+1)
mid = math.floor(len/2)

for i in range(1, mid+1):
  arr.append(arr[i-1]+diff[i-1])

for i in range(mid+1, len+1):
  if len % 2 != 0:
    arr.append(arr[i-1]+diff[2*mid-i+1])
  else:
    arr.append(arr[i-1]+diff[2*mid-i])

with open('shuttle.out', 'w') as fout:
  counter = 0
  for i in range(1, len+1):
    if i == len or counter == 19:
      fout.write(str(arr[i])+'\n')
      counter = 0
    else:
      fout.write(str(arr[i])+' ')
      counter += 1

