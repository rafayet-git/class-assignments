-- find the crime scene log and id of the crime, we see the cs50 duck id is 295
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
SELECT id, description FROM crime_scene_reports
WHERE year = 2021
AND month = 7
AND day = 28
AND street = "Humphrey Street";

-- look at the interviews that happened
SELECT id, name, transcript FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28;

--| 162 | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
SELECT id, account_number, amount FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND atm_location = "Leggett Street"
AND transaction_type = "withdraw";
-- too many ppl, find bank acc and ppl from acc number, list of possible suspects
SELECT name, phone_number, passport_number, license_plate FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = "Leggett Street"
        AND transaction_type = "withdraw"
    )
);

--| 161 | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
SELECT id, minute, license_plate FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND activity = "exit"
AND license_plate IN(
    SELECT license_plate FROM people
    WHERE id IN (
        SELECT person_id FROM bank_accounts
        WHERE account_number IN (
            SELECT account_number FROM atm_transactions
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND atm_location = "Leggett Street"
            AND transaction_type = "withdraw"
        )
    )
);

--update list of suspects
SELECT name, phone_number, passport_number, license_plate FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND activity = "exit"
    AND license_plate IN(
        SELECT license_plate FROM people
        WHERE id IN (
            SELECT person_id FROM bank_accounts
            WHERE account_number IN (
                SELECT account_number FROM atm_transactions
                WHERE year = 2021
                AND month = 7
                AND day = 28
                AND atm_location = "Leggett Street"
                AND transaction_type = "withdraw"
            )
        )
    )
);
--| 163 | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
SELECT id, caller, receiver, duration FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration <= 60
AND caller IN (
    SELECT phone_number FROM people
    WHERE license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND activity = "exit"
        AND license_plate IN(
            SELECT license_plate FROM people
            WHERE id IN (
                SELECT person_id FROM bank_accounts
                WHERE account_number IN (
                    SELECT account_number FROM atm_transactions
                    WHERE year = 2021
                    AND month = 7
                    AND day = 28
                    AND atm_location = "Leggett Street"
                    AND transaction_type = "withdraw"
                )
            )
        )
    )
);

-- update suspects
SELECT name, phone_number, passport_number, license_plate FROM people
WHERE phone_number IN (
    SELECT caller FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration <= 60
    AND caller IN (
        SELECT phone_number FROM people
        WHERE license_plate IN (
            SELECT license_plate FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND activity = "exit"
            AND license_plate IN(
                SELECT license_plate FROM people
                WHERE id IN (
                    SELECT person_id FROM bank_accounts
                    WHERE account_number IN (
                        SELECT account_number FROM atm_transactions
                        WHERE year = 2021
                        AND month = 7
                        AND day = 28
                        AND atm_location = "Leggett Street"
                        AND transaction_type = "withdraw"
                    )
                )
            )
        )
    )
);
--check for fligts, day is 29
SELECT id, origin_airport_id, destination_airport_id, hour, minute FROM flights
WHERE year = 2021
AND month = 7
AND day = 29;

--scan airports
SELECT abbreviation, full_name, city FROM airports
WHERE id IN(
    SELECT destination_airport_id FROM flights
    WHERE year = 2021
    AND month = 7
    AND day = 29
);

-- scan suspect
SELECT passport_number, seat FROM passengers
WHERE passport_number IN (
    SELECT passport_number FROM people
    WHERE phone_number IN (
        SELECT caller FROM phone_calls
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND duration <= 60
        AND caller IN (
            SELECT phone_number FROM people
            WHERE license_plate IN (
                SELECT license_plate FROM bakery_security_logs
                WHERE year = 2021
                AND month = 7
                AND day = 28
                AND hour = 10
                AND activity = "exit"
                AND license_plate IN(
                    SELECT license_plate FROM people
                    WHERE id IN (
                        SELECT person_id FROM bank_accounts
                        WHERE account_number IN (
                            SELECT account_number FROM atm_transactions
                            WHERE year = 2021
                            AND month = 7
                            AND day = 28
                            AND atm_location = "Leggett Street"
                            AND transaction_type = "withdraw"
                        )
                    )
                )
            )
        )
    )
);



-- 3592750733 appears three times in passenger list so probably not her
-- FINAL SUSPECTS
-- Taylor | (286) 555-6063 | 1988161715      | 1106N58 reciever: (676) 555-6554
-- Bruce  | (367) 555-5533 | 5773159633      | 94KL13X reciever: (375) 555-8161
-- lets scan log times more precisely "you might want to look for cars that left the parking lot in that time frame."

SELECT id, hour, minute, activity, license_plate FROM bakery_security_logs
WHERE license_plate = "1106N58" OR license_plate = "94KL13X";

-- bruce is the most likely suspect as it's closest to robbery time
-- find accompliace

SELECT name, phone_number, passport_number, license_plate FROM people
WHERE phone_number = "(375) 555-8161";
-- robin likely accompliace

-- where they go??
SELECT flight_id, seat FROM passengers
WHERE passport_number = 5773159633;
--flight id 36
SELECT destination_airport_id FROM flights
WHERE id = 36;
-- airport 4
SELECT city FROM airports
WHERE id = 4;
-- they are at nyc