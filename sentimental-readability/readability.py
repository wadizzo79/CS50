from cs50 import get_string

text = get_string("Text: ")


def count_letters(text):
    letters = 0
    length = len(text)
    for i in range(length):
        if text[i].isalpha():
            letters += 1
    return letters


def count_words(text):
    words = 1
    length = len(text)
    for i in range(length):
        if text[i] == ' ':
            words += 1
    return words


def count_sentences(text):
    sentences = 0
    length = len(text)
    for i in range(length):
        if text[i] == '.' or text[i] == '?' or text[i] == '!':
            sentences += 1
    return sentences


letters = count_letters(text)
words = count_words(text)
sentences = count_sentences(text)

L = float(letters / words * 100)
S = float(sentences / words * 100)
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")

elif index > 16:
    print("Grade 16+")

else:
    print(f"Grade {index}")
