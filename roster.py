import csv
import os
import cs50
from sys import argv, exit


# Makes sure that there are 2 command line arguments after "python"
if len(argv) != 2:
    print("Usage: python roster.py house")
    exit(1)


# Remembers the second command line argument which is the csv data file
house = argv[1]


# Opens student database in SQLite
db = cs50.SQL("sqlite:///students.db")


# Runs an SQL query to list all of the first, middle and last names along with the birth year for all students in the given house from the command line argument
# Stores this list in 'list' variable
list = db.execute("SELECT first, middle, last, birth FROM students WHERE house == ? ORDER BY last",
                  house)
   

# Iterates through each element in the list    
for i in list:
    
    # If there is no middle name, then prints "<first name> <last name>, born <birth year>"
    if i['middle'] is None:
        print(f"{i['first']} {i['last']}, born {i['birth']}")
    
    # If there is a middle name, then prints "<first name> <middle name> <last name>, born <birth year>"    
    else:
        print(f"{i['first']} {i['middle']} {i['last']}, born {i['birth']}")
    
