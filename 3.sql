-- Uses IMDb database
-- SQL query to list all movie titles alphabetically released on or after 2018 (including those scheduled ot be released in the future)


-- Selects the movie titles from the 'movies' table...
SELECT title FROM movies 

-- for movies that were released on or after 2018 (pulled from the 'year' column)
WHERE year >= 2018 

-- Sorts the selected titles alphabetically
ORDER BY title