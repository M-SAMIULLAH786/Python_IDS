class Student:
    def __init__(self, name, marks):
        self.name = name
        self.marks = marks

    def percentage(self):
        return sum(self.marks) / len(self.marks)

    def grade(self):
        p = self.percentage()
        if p >= 85:
            return "A"
        elif p >= 70:
            return "B"
        elif p >= 60:
            return "C"
        else:
            return "D"

    def gpa(self):
        g = self.grade()
        if g == "A":
            return 4.0
        if g == "B":
            return 3.0
        if g == "C":
            return 2.0
        return 1.0


student = Student("Samiullah", [88, 92, 79, 85])

print("Name:", student.name)
print("Percentage:", student.percentage())
print("Grade:", student.grade())
print("GPA:", student.gpa())
