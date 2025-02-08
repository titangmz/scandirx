from ._scandirx import walk as c_walk

def walk(path, max_depth=2):
    """Python wrapper for the C extension."""
    return c_walk(path, max_depth)