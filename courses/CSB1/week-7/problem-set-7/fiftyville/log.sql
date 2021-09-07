-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE street="Chamberlin Street" AND description LIKE "%duck%";
-- Let's find the three interviews that mention the courthouse on the day of the crime
SELECT id, name, transcript FROM interviews WHERE transcript LIKE "%courthouse%" AND month = 7 AND day = 28;