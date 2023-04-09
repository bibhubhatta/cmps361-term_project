import os
import re

path = os.path.dirname(os.path.realpath(__file__)) + "\\" + "..\\" + "assembler_lib\\"


def is_cpp_file(file_name):
    return file_name.endswith(".cpp") or file_name.endswith(".h")


def prefix_class_members(data):
    # Replace all variable names starting with "_" with "m_"
    data = re.sub(r'\b_[a-zA-Z0-9_]*\b', lambda x: "m" + x.group(0), data)
    return data


def main():
    cpp_files = [file for file in os.listdir(path) if is_cpp_file(file)]
    for file in cpp_files:
        with open(path + file, "r") as f:
            data = f.read()

        data = prefix_class_members(data)

        with open(path + file, "w") as f:
            # Write the file
            f.write(data)


if __name__ == "__main__":
    main()
