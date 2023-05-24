-- Uses IMDb database
-- SQL query to list all people who have starred in movies who also starred Kevin Bacon (the one born in 1958) (List does not include Kevin Bacon)


-- Selects the names of the people from the 'people' table...
SELECT name FROM people

-- who's name isn't Kevin Bacon and who's id appears in...
WHERE name != "Kevin Bacon" AND id IN 

-- rows from the 'stars' table...
(SELECT person_id FROM stars 

-- who has a movie id that appears in...
WHERE movie_id IN 

-- rows from the 'stars' table...
(SELECT movie_id FROM stars 

-- who has a person id that appears in...
WHERE person_id IN

-- the 'people' table...
(SELECT id FROM people 

-- whose name is Kevin Bacon and birth year is 1958
WHERE name = "Kevin Bacon" AND birth = 1958)))