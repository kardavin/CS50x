-- Uses IMDb database
-- SQL query to list all movies in which Johnny Depp and Helen Bonham Carter have both starred in


-- Selects movie titles...
SELECT title 

-- from the joined 'movies', 'stars', and 'people' tables...
-- (the 'stars' table is linked to the 'movies' table by the movie id's in both tables)
-- (the 'people' table is linked to the joint table by the people's id's in both tables)
FROM movies JOIN stars ON movie_id = movies.id JOIN people ON person_id = people.id

-- which has the names Johnny Depp or Helena Bonham Carter
WHERE name = "Johnny Depp" OR name = "Helena Bonham Carter"

-- The list is then grouped by movie id and only the ones listed more than once are kept in the list
GROUP BY movie_id HAVING count(movie_id) > 1