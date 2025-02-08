import scandirx

def list_files(directory, max_depth=1):
    """
    Lists all files and directories within the specified directory up to the given depth.
    
    Args:
        directory (str): The path to the directory to list.
        max_depth (int): The maximum depth to traverse.

    Returns:
        list: A list of file and directory paths.
    """
    paths = scandirx.walk(directory, max_depth)
    for path in paths:
        print(path)

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python list_files.py <directory> [max_depth]")
    else:
        directory = sys.argv[1]
        max_depth = int(sys.argv[2]) if len(sys.argv) > 2 else 1
        list_files(directory, max_depth)
