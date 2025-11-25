items = ["Milk", "Bread", "Eggs", "Butter", "Rice", "Juice"]
prices = [180, 120, 250, 450, 300, 200]
quantities = [2, 1, 0, 1, 3, 0]

data = list(zip(items, prices, quantities))

available_items = list(filter(lambda x: x[2] > 0, data))

bills = list(map(lambda x: (x[0], x[2], x[1] * x[2]), available_items))

sorted_bill = sorted(bills, key=lambda x: x[2], reverse=True)

total = sum(map(lambda x: x[2], sorted_bill))

print("Item  Qty  Total")
for item, qty, total_price in sorted_bill:
    print(item, qty, total_price)

print("Grand Total:", total)
