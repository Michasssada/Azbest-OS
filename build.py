import os

def get_all_files(directory):
    files_list = []
    for root, _, files in os.walk(directory):
        for file in files:
            # Construct the relative file path (foldername/filename)
            relative_path = os.path.join(root, file).replace(directory + os.sep, "")
            files_list.append(relative_path)
    return files_list

files_to_build = get_all_files()