class BankAccount:
    def __init__(self, owner, balance=0):
        self.owner = owner
        self.balance = balance

    def deposit(self, amount):
        self.balance += amount
        return self.balance

    def withdraw(self, amount):
        if amount > self.balance:
            return None
        self.balance -= amount
        return self.balance

    def get_balance(self):
        return self.balance


account = BankAccount("Samiullah", 5000)

account.deposit(2000)
account.withdraw(1500)

print("Owner:", account.owner)
print("Final Balance:", account.get_balance())
