emails = ["user@gmail.com", "abc@", "info@yahoo.com", "test.com"]

valid = list(filter(lambda e: "@" in e and "." in e, emails))
print(valid)
