def test(word):
    print(word)
    pass

context = []
always_available = {"Test": test}
default = {}
actor = {}
specific_actor = {}

always_available["Test"]("yo")