-- Uses IMDb database
-- SQL query to list the top 5 movies (based on the ratings given) Chadwick Boseman has starred in, sorted in descending order


-- Select movie titles...
SELECT title 

-- from the joined 'movies' and 'ratings' tables linked by the movies' id's listed in both tables...
FROM movies JOIN ratings ON id = movie_id 

-- whose movie id appears in...
WHERE id IN 

-- rows from the 'stars' table...
(SELECT movie_id FROM stars 

-- which has a person id that appears in...
WHERE person_id IN 

-- the 'people' table...
(SELECT id FROM people 

-- that has the name "Chadwick Boseman"
WHERE name == "Chadwick Boseman")) 

-- Sorts the list by rating in descending order
ORDER BY rating DESC 

-- Limits the list to 5 items
LIMIT 5