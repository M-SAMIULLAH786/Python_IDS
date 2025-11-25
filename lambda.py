products = [
    ("Laptop", 120000),
    ("Mouse", 1500),
    ("Keyboard", 4000)
]

sorted_products = sorted(products, key=lambda x: x[1])
print(sorted_products)
