-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE street="Chamberlin Street" AND description LIKE "%duck%";
-- Let's find the three interviews that mention the courthouse on the day of the crime
SELECT id, name, transcript FROM interviews WHERE transcript LIKE "%courthouse%" AND month = 7 AND day = 28;
-- Following Ruth's interview, check the courthouse parking security info for license plates from 10:15 to 10:25
SELECT * FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;
-- Draw up initial list of suspects based on license plate information from Ruth's interview
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25);
-- Draw up list of suspects based on ATM information from Eugene's interview
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"));
-- Narrow down the initial list using the second list of suspects
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25) INTERSECT SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"));
-- Find earliest flight out of Fiftyville the next day, based on Raymonds interview
SELECT id FROM (SELECT id, min(hour) FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND month = 7 AND day = 29);
-- Try to narrow down list of suspects again by checking those who took that early flight out of Fiftyville the next day
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25) INTERSECT SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw")) INTERSECT SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM (SELECT id, min(hour) FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND month = 7 AND day = 29)));