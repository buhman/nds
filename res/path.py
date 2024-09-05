from os import path

def texture_path(s):
    return path.join('..', 'texture', s)

def model_path(s):
    return path.join('..', 'model', s)
