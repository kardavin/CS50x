-- Uses IMDb database
-- SQL query to list all movies and their ratings that were released in 2010
-- The list is organized first by ratings in descending order and if movies have the same ratings, then the list is organized by title alphabetically


-- Selects all movie titles and ratings...
SELECT movies.title, ratings.rating 

-- from the joined 'movies' and 'ratings' table linked by the 'id' column in the 'movies' table set equal to the 'movie_id' column in the 'ratings' table...
FROM movies JOIN ratings ON id = movie_id 

-- for all movies released in 2010
WHERE movies.year == 2010 

-- Sorts the list by rating in descending order, and if movies have the same ratings, then the list is organized by title alphabetically
ORDER BY rating DESC, title ASC