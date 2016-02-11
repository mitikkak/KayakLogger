
def get_lines(file_name, filter = None):
    file = get_file_handle(file_name)
    if file is None: return []
    lines = file.read().splitlines()
    if filter:
        lines = get_matching_lines(lines, filter)
    return lines

def get_matching_lines(lines, filter):
    filtered = []
    for line in lines:
        if filter in line: filtered.append(line)
    return filtered
def get_file_handle(file_name):
    try:
        file = open(file_name, "r")
        return file
    except IOError:
        print "file_reader failed. file %s not existing" % (file_name)
        return None
