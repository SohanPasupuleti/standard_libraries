SELECT country, continent, population
FROM countries c
WHERE (
    SELECT COUNT(*)
    FROM countries
    WHERE continent = c.continent AND population > c.population
) < 3
ORDER BY continent, population DESC;
