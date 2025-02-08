import scandirx

def test_walk():
    """Ensure scandirx returns a list of paths."""
    result = scandirx.walk(".")
    assert isinstance(result, list)
    assert len(result) > 0  # Ensure we find something
