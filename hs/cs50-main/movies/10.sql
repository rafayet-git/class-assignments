SELECT DISTINCT name FROM directors
JOIN people ON directors.person_id = people.id
WHERE movie_id IN (
    SELECT movie_id FROM ratings
    WHERE rating >= "9.0"
);
