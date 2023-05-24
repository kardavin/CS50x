-- Uses IMDb database
-- SQL query to list all people who starred in movies released in 2004, sorted by birth year in ascending order


-- Selects the names of all people from the 'people' table...
SELECT name FROM people 

-- whose id appears in...
WHERE id IN 

-- rows from the 'stars' table...
(SELECT person_id FROM stars 

-- which has their movie_id appear in...
WHERE movie_id IN 

-- rows from the 'movies' table...
(SELECT id FROM movies 

-- that has the release year of 2004
WHERE year == 2004)) 

-- Sorts the list by birth year in ascending order
ORDER BY birth