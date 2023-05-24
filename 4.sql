-- Uses IMDb database
-- SQL query to list the number of movies that have a IMDb rating of 10.0


-- Selects the number of movies from the 'movies' table...
SELECT count(title) FROM movies 

-- for movies that have its movie id appear in...
WHERE id IN 

-- rows from the 'ratings' table...
(SELECT movie_id FROM ratings 

-- that have a rating of 10.0
WHERE rating == 10.0)