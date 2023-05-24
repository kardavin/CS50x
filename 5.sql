-- Uses IMDb database
-- SQL query to list all of the movie titles (alphabetically) and release dates for all Harry Potter movies (that being all titles including the words "Harry Potter")


-- Selects movie titles and release dates (from column 'year') from 'movies' table...
SELECT title, year FROM movies

-- from all movies including the words "Harry Potter"
WHERE title LIKE "Harry Potter%" 

-- Sorts the selected titles alphabetically
ORDER BY year