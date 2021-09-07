-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE street="Chamberlin Street" AND description LIKE "%duck%";
-- Let's find the three interviews that mention the courthouse on the day of the crime
SELECT id, name, transcript FROM interviews WHERE transcript LIKE "%courthouse%" AND month = 7 AND day = 28;
-- Following Ruth's interview, check the courthouse parking security info for license plates from 10:15 to 10:25
SELECT * FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;