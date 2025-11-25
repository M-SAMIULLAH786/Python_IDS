students = ["Ali", "Sara", "Sami"]
marks = [88, 92, 75]

pairs = zip(students, marks)
high = filter(lambda x: x[1] >= 80, pairs)

print(list(high))
