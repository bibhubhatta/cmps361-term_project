import os
import re

path = os.path.dirname(os.path.realpath(__file__)) + "\\" + "..\\" + "assembler_lib\\"


def is_cpp_file(file_name):
    return file_name.endswith(".cpp") or file_name.endswith(".h")


for file in os.listdir(path):

    if is_cpp_file(file):
        with open(path + file, "r") as f:
            data = f.read()

        # Replace all variable names starting with "_" with "m_"
        data = re.sub(r'\b_[a-zA-Z0-9_]*\b', lambda x: "m" + x.group(0), data)

        with open(path + file, "w") as f:
            # Write the file
            f.write(data)
