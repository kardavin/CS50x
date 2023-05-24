-- Uses IMDb database
-- SQL query to list all directors who directed a movie with at least a 9.0 rating


-- Selects all people's names from the 'people' table...
SELECT name FROM people 

-- who have their id's appear in...
WHERE id IN 

-- rows from the 'directors' table...
(SELECT person_id FROM directors 

-- who's movie id appears in...
WHERE movie_id IN 

-- the 'ratings' tables...
(SELECT movie_id FROM ratings 

-- for movies that have at least a 9.0 rating
WHERE rating >= 9.0))