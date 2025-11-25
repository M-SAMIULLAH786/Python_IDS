usd_prices = [5, 10, 20, 50]
rate = 278

pkr_prices = list(map(lambda p: p * rate, usd_prices))
print(pkr_prices)
