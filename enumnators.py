# ===========================================
# enumerate_example.py
# ===========================================
# enumerate()
# → List ke har element ke saath uska INDEX bhi deta hai.
#
# Example:
# 0 Ali
# 1 Sami
# 2 Ahmed
# ===========================================

names = ["Ali", "Sami", "Ahmed"]

for index, value in enumerate(names):
    print(index, value)
