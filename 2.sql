-- Uses IMDb database
-- SQL query to list the birth year of Emma Stone


-- Selects the birth year from the 'people' table...
SELECT birth FROM people 

-- from rows that have "Emma Stone" in the 'name' column
WHERE name == "Emma Stone"