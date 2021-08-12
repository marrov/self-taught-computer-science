def main():
    num = input("Number: ")

    if len(num) == 15 and (num[0:2] == "34" or num[0:2] == "37"):
        if luhn(num):
            print("AMEX")
    elif len(num) == 16 and (int(num[0:2]) >= 51 and int(num[0:2]) <= 55):
        if luhn(num):
            print("MASTERCARD")
    elif (len(num) == 13 or len(num) == 16) and num[0] == "4":
        if luhn(num):
            print("VISA")
    else:
        print("INVALID")

    return

def luhn(num):
    return true

if __name__ == "__main__":
    main()