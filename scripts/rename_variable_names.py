import os
import re

paths = [os.path.dirname(os.path.realpath(__file__)) + "\\" + "..\\" + "assembler_lib\\",
         os.path.dirname(os.path.realpath(__file__)) + "\\" + "..\\"]


def is_cpp_file(file_name):
    return file_name.endswith(".cpp") or file_name.endswith(".h")


def prefix_class_members(data):
    # Replace all variable names starting with "_" with "m_"
    data = re.sub(r'\b_[a-zA-Z0-9_]*\b', lambda x: "m" + x.group(0), data)
    return data


def convert_to_camel_case(data):
    # Replace all variable names that are not camel case with camel case

    # Iterate over each word in the file
    for word in re.findall(r'\b[a-zA-Z0-9_]*\b', data):
        if "_" in word:
            parts = word.split("_")

            first_part = parts.pop(0)
            if first_part == "m":  # If the variable is class member
                camel_cased_word = "m_"
            elif first_part == "a":  # If the variable is a function argument
                camel_cased_word = "a_"
            else:
                camel_cased_word = first_part

            for part in parts:
                # Capitalize the first letter
                camel_cased_word += part.capitalize()

            # Replace the word with the camel cased word
            data = data.replace(word, camel_cased_word)

    return data


def main():
    cpp_files = []
    for path in paths:
        for file in os.listdir(path):
            if is_cpp_file(file):
                cpp_files.append(path + file)

    for file in cpp_files:
        with open(file, "r") as f:
            data = f.read()

        data = prefix_class_members(data)
        data = convert_to_camel_case(data)

        with open(file, "w") as f:
            # Write the file
            f.write(data)


if __name__ == "__main__":
    main()
