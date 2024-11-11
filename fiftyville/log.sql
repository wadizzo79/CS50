-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE street='Humphrey Street';
SELECT * FROM crime_scene_reports WHERE day='28' AND month='7';
SELECT * FROM interviews WHERE day='28' AND month='7';
SELECT * FROM bakery_security_logs WHERE day='28' AND month='7';
SELECT * FROM atm_transactions WHERE day='28' AND month='7' AND atm_location='Leggett Street';
SELECT * FROM bank_accounts;
SELECT * FROM flights WHERE day='29' AND month='7';
SELECT * FROM airports;
SELECT * FROM phone_calls WHERE day='28' AND month='7' AND duration<60;
SELECT * FROM passengers JOIN flights ON passengers.flight_id=flights.id WHERE day='29' AND month='7' AND hour='8' AND minute='20';
SELECT passengers.flight_id,passengers.passport_number,people.name,people.phone_number,people.license_plate FROM passengers
JOIN people ON passengers.passport_number=people.passport_number JOIN flights ON passengers.flight_id=flights.id
WHERE day='29' AND month='7' AND hour='8' AND minute='20';
SELECT * FROM bakery_security_logs WHERE day='28' AND month='7' AND hour='10' AND activity='exit';
SELECT * FROM bakery_security_logs JOIN people ON bakery_security_logs.license_plate=people.license_plate WHERE day='28' AND month='7' AND hour='10' AND minute<25 AND activity='exit';
SELECT * FROM people JOIN phone_calls ON people.phone_number=phone_calls.caller WHERE day='28' AND month='7' AND duration < 60;
SELECT passengers.flight_id,passengers.passport_number,people.name,people.phone_number,people.license_plate,phone_calls.caller,phone_calls.receiver FROM passengers
JOIN people ON passengers.passport_number=people.passport_number JOIN flights ON passengers.flight_id=flights.id JOIN phone_calls ON people.phone_number=phone_calls.receiver
WHERE flights.day='29' AND flights.month='7' AND hour='8' AND minute='20' AND duration<60;
SELECT passengers.passport_number,people.id,people.name,people.phone_number,people.license_plate FROM passengers JOIN flights ON passengers.flight_id=
flights.id JOIN people ON passengers.passport_number=people.passport_number JOIN bakery_security_logs ON people.license_plate=bakery_security_logs.license_plate
WHERE flights.day='29' AND flights.month='7' AND flights.hour='8' AND flights.minute='20' AND activity='exit';
SELECT atm_transactions.account_number,year,month,day,person_id,name FROM atm_transactions JOIN bank_accounts ON atm_transactions.account_number=bank_accounts.account_number
JOIN people ON bank_accounts.person_id=people.id WHERE day='28' AND month='7' AND atm_location='Leggett Street' AND transaction_type='withdraw';
SELECT * FROM people JOIN phone_calls ON people.phone_number=phone_calls.receiver WHERE day='28' AND month='7' AND duration < 60;
SELECT * FROM bakery_security_logs WHERE day='28' AND month='7' AND hour='10' AND minute < 25 AND activity='exit';
SELECT * FROM bakery_security_logs JOIN people ON bakery_security_logs.license_plate=people.license_plate JOIN bank_accounts ON people.id=bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number=atm_transactions.account_number WHERE atm_transactions.day='28' AND atm_transactions.month='7' AND bakery_security_logs.hour='10'
AND bakery_security_logs.minute<25 AND atm_location='Leggett Street';
SELECT * FROM bakery_security_logs JOIN people ON bakery_security_logs.license_plate=people.license_plate JOIN bank_accounts ON people.id=bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number=atm_transactions.account_number WHERE atm_transactions.day='28' AND atm_transactions.month='7' AND atm_location='Leggett Street'
AND transaction_type='withdraw' AND bakery_security_logs.hour='10'AND bakery_security_logs.minute<25;
