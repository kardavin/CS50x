-- Uses IMDb database
-- SQL query to list the average rating for all movies released in 2012


-- Averages all of ratings from the 'ratings' table...
SELECT avg(rating) FROM ratings 

-- for all movies...
WHERE movie_id IN 

-- listed in the 'movies' table...
(SELECT id FROM movies 

-- that were released in 2012
WHERE year == 2012)