import os
import re

this_file_path = os.path.realpath(__file__)
project_path = f"{os.path.dirname(this_file_path)}\\..\\"

paths = [project_path,
         project_path + "assembler_lib\\"]


def is_cpp_file(file_name):
    return file_name.endswith(".cpp") or file_name.endswith(".h")


def prefix_class_members(data):
    # Replace all variable names starting with "_" with "m_"
    data = re.sub(r'\b_[a-zA-Z0-9_]*\b', lambda x: "m" + x.group(0), data)
    return data


def convert_to_camel_case(data):
    ignored = ["find_if", "c_str", "out_of_range", "push_back", "pop_back", "is_open", "static_cast"]

    # Iterate over each word in the file
    for word in re.findall(r'\b[a-zA-Z0-9_]*\b', data):
        if "_" in word and word not in ignored and not word[0].isupper():
            camel_cased_word = get_camel_case(word)
            data = re.sub(r'\b' + word + r'\b', camel_cased_word, data)

    return data


def get_camel_case(word):
    parts = word.split("_")

    if len(parts) == 0:
        return word

    first_part = parts.pop(0)
    if first_part == "m":  # If the variable is class member
        camel_cased_word = "m_" + parts.pop(0).capitalize()
    elif first_part == "a":  # If the variable is a function argument
        camel_cased_word = "a_" + parts.pop(0).capitalize()
    else:
        camel_cased_word = first_part.capitalize()

    for part in parts:
        # Capitalize the first letter
        camel_cased_word += part.capitalize()

    return camel_cased_word


def substitute_br_with_bell(data):
    br = r"________________________________________________________\\n\\n"
    bell = "🔔"
    data = re.sub(br, bell, data)
    return data


def substitute_bell_with_br(data):
    bell = "🔔"
    br = r"________________________________________________________\\n\\n"
    data = re.sub(bell, br, data)
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

        data = substitute_br_with_bell(data)
        data = prefix_class_members(data)
        data = convert_to_camel_case(data)
        data = substitute_bell_with_br(data)

        with open(file, "w") as f:
            # Write the file
            f.write(data)


if __name__ == "__main__":
    # Restore files to original state before running the script
    command = f"cd {project_path}; git stage {this_file_path} ; git restore ."
    os.system("powershell.exe " + command)
    main()
