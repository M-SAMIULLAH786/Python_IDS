# ===========================================
# filter_example.py
# ===========================================
# FILTER FUNCTION (VERY DETAILED)
# filter(function, iterable)
# → list me se sirf wo elements choose karta hai jo condition ko pass karain
#
# Step-by-step:
# 1. Pehle ek function banate hain jo TRUE/FALSE return kare.
# 2. filter() is function ko har item per chalata hai.
# 3. Jis item ke liye TRUE aaye, wo result list me aa jata hai.
# ===========================================

# Step 1: Condition function → number even hai ya nahi?
def is_even(num):
    # Agar number 2 se perfectly divide ho jaye to even hota hai
    return num % 2 == 0

numbers = [1, 2, 3, 4, 5, 6]

# Step 2: filter() ko apna function or list dete hain
# filter(is_even, numbers) → is_even function ko list ke har element par chalata hai
filtered_result = filter(is_even, numbers)

# Step 3: filter() ka result ek "filter object" hota hai
# Isko list me convert karte hain
even_numbers = list(filtered_result)

print("Original list:", numbers)
print("Even numbers after filter():", even_numbers)

################
# ===========================================
# map_example.py
# ===========================================
# MAP FUNCTION (VERY DETAILED)
# map(function, iterable)
# → list ke har element par function apply karta hai
#
# Step-by-step:
# 1. Ek function banate hain (jaise doubling).
# 2. map() is function ko har element par apply karta hai.
# 3. Sab results ek new list ban jate hain.
# ===========================================

# Step 1: Function → number ko 2 se multiply karna
def double(num):
    # Har number ko double kar ke return kar do
    return num * 2

numbers = [1, 2, 3, 4]

# Step 2: map() ko function + list de do
mapped_result = map(double, numbers)

# map() ka result ek map object hota hai → list me convert karo
doubled_numbers = list(mapped_result)

print("Original list:", numbers)
print("Doubled numbers:", doubled_numbers)
#################
# ===========================================
# lambda_example.py
# ===========================================
# LAMBDA FUNCTION (VERY DETAILED)
# → Ek chhota anonymous function (naam ke baghair)
#
# Syntax:
# lambda arguments: expression
#
# Normal function ki jagah use karte hain jab ek line ka function chahiye.
# ===========================================

# Normal function
def add(a, b):
    return a + b

# Same kaam lambda se ek line me:
add_lambda = lambda a, b: a + b

print("Normal function result:", add(3, 5))
print("Lambda function result:", add_lambda(3, 5))
###################
# ===========================================
# map_lambda_example.py
# ===========================================
# map() + lambda combination
# → List ke har element ko square karna
# ===========================================

numbers = [2, 3, 4, 5]

# map(lambda_function, list)
squared = list(map(lambda x: x * x, numbers))

print("Original list:", numbers)
print("Squared numbers:", squared)
##################################
# ===========================================
# filter_lambda_example.py
# ===========================================
# filter() + lambda combination
# → Sirf odd numbers ko filter karna
# ===========================================

numbers = [1, 2, 3, 4, 5, 6]

# filter → lambda x: x % 2 != 0 (odd numbers)
odd_numbers = list(filter(lambda x: x % 2 != 0, numbers))

print("Original list:", numbers)
print("Odd numbers:", odd_numbers)
