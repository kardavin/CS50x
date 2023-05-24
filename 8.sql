-- Uses IMDb database
-- SQL query to list all people  who starred in the movie Toy Story


-- Select all names of people from the 'people' table...
SELECT name FROM people 

-- that have their id's appear in...
WHERE id IN 

-- rows in the 'stars' table...
(SELECT person_id FROM stars 

-- that has the 'movie_id' appear in... 
WHERE movie_id IN 

-- rows from the 'movies' table...
(SELECT id FROM movies 

-- whose title is Toy Story
WHERE title = "Toy Story"))