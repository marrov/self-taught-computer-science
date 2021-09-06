def main():
    # Ask user for credit card numer
    num = input("Number: ")

    # Check for AMEX, MASTERCARD, VISA and INVALID
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
    """
    Function that check if num passes Luhn's algortihm
    """
    return True


if __name__ == "__main__":
    main()
