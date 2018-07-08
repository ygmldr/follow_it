import random
import time

f = open('setlen.ini','r')
t = int(f.readline())
r = int(f.readline())
f.close()
r -= 1
print(t,r)
for i in range(0,t):
    print(random.randint(0,r))
