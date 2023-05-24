-- Uses IMDb database
-- SQL query to list all movie titles released in 2008


-- Selects the movie titles from the 'movies' table...
SELECT title FROM movies 

-- for movies that were released in 2008 (pulled from the 'year' column)
WHERE year = "2008"