import csv

books = []

# Adds books to shelf by reading from books.csv
with oprn("books.csv") as file:
    text = file.read()
# Print books
