import csv
import os
import cs50
from sys import argv, exit


# Makes sure that there are 2 command line arguments after "python"
if len(argv) != 2:
    print("Usage: python import.py data.csv")
    exit(1)
    
   
# Remembers the second command line argument which is the csv data file
data_file = argv[1]


# Opens up a new blank database in 'students.db'
open("students.db", "w").close()


# Opens student database in SQLite
db = cs50.SQL("sqlite:///students.db")

# Creates the table in the students databse with columns of 'id', which is the primary key and is autoincremented, first name, middle name, last name, house and birth year
db.execute("CREATE TABLE students (id INTEGER PRIMARY KEY AUTOINCREMENT, first VARCHAR(255), middle VARCHAR(255), last VARCHAR(255), house VARCHAR(10), birth INTEGER)")


# This section of the code reads the csv databse file and stores its contents into memeory
# First checks if the file exists and then opens the file
if os.path.isfile(data_file):
    with open(data_file, "r") as file:
        
        # Puts the csv file in a more user friendly format
        csv_reader = csv.DictReader(file, delimiter=",")
        
        # Reads each row of the csv database file
        for row in csv_reader:
            
            # Stores the name, house and birth data into separate temporary variables
            name = row["name"].split(" ")
            house = row["house"]
            birth = row["birth"]
            
            # If the given name is two words, saves the first word as the first name and the second as the last name
            if len(name) == 2:
                first = name[0]
                last = name[1]
                
                # Then inputs the stored first, last, house and birth year into the 'students.db' table
                db.execute("INSERT INTO students (first, last, house, birth) VALUES (?, ?, ?, ?)",
                           first, last, house, birth)
                    
            # If the given names is three words, saves the first word as the first name, second as the middle name and third as the last name        
            else:
                first = name[0]
                middle = name[1]
                last = name[2]
            
                # Then inputs the stores first, middle, last, house and birth year into the 'students.db' table
                db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                           first, middle, last, house, birth)

# If the data.csv file does not exist, prints error message listed below and exits program
else:
    print("data.csv does not exist")
    exit(2)