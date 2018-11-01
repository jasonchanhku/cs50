from cs50 import get_float

n = get_float("Change owed: ") * 100

coins = [25, 10, 5, 1]

counter = 0

for coin in coins:
    #print("coin is: ", coin)
    while( (n >= coin) & (n!= 0)):
        #print("n is", n)
        counter += 1
        n = n - coin
        #print("n after is: ", n)


print(counter)