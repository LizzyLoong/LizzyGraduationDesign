


def format_string_from_csv():
    print(1)


def is_number(char):
    print(1)


def recognize_string(formatted_string):
    string_length=len(formatted_string)
    num_array=[]
    print(string_length)
    for i in range(string_length):
        if formatted_string[i].isdigit():
            num_array.append(formatted_string[i])
    print(num_array)


string="{{1,2,3,4,5},{6,7,8}},"


# format_string_from_csv()
recognize_string("lizzy12,34332")