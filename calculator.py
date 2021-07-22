print("This is a calculator program demo, have fun!")
print("Available operations: + - * / % **")
print("Use exit() to exit\n")
while True:
    try:
        print("Answer: " + str(eval(input("Please input a formula: "))) + "\n")
    except Exception:
        print("Input error.\n")
