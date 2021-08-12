def main():
    num = input("Number: ")

    if len(num) == 15 and (num[0:2] == "34" or num[0:2] == "37"):
        print("AMEX")
    elif len(num) == 16 and (int(num[0:2]) >= 51 and int(num[0:2]) <= 55):
        print("MASTERCARD")
    elif (len(num) == 13 or len(num) == 16) and num[0] == "4":
        print("VISA")
    else:
        print("INVALID")

    # TODO: if not invalid, use Lunh's algorithm to check if valid

    return

def luhn(num):
    return true

if __name__ == "__main__":
    main()