# ===========================================
# zip_example.py
# ===========================================
# ZIP FUNCTION
# zip(list1, list2, ...)
# → 2 ya zyada lists ko pair bana kar combine karta hai.
#
# Notes:
# - Pairing index-to-index basis per hoti hai.
# - Agar lists unequal hon → shortest list ke hisaab se pairing hoti hai.
# ===========================================

names = ["Ali", "Sami", "Ahmed"]
ages = [20, 22, 25]

# zip(names, ages) → ('Ali', 20), ('Sami', 22) ...
paired_data = list(zip(names, ages))

print("Paired data:", paired_data)
