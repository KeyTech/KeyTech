-- Insert script to fill the lock service database.
use lockservice;
DELETE FROM testFrameLog;
DELETE FROM userLog;
DELETE FROM roomUnlimitedAccess;
DELETE FROM accessGroupUnlimitedAccess;
DELETE FROM userAccessGroup;
DELETE FROM reservation;
DELETE FROM reservationTime;
DELETE FROM unlimitedAccess;
DELETE FROM room;
DELETE FROM accessGroup;
DELETE FROM user;

-- Default tables
INSERT INTO user (userIdentifier, pincode, firstname, lastname)
VALUES (123456, 1234, 'Janitor', 'Janitor'),
(473712, 0000, 'Nathanael', 'Zitter'),
(474296, 1111, 'Hanna', 'Hermsen'),
(099999, 9999, 'Teacher', 'Teacher'),
(111222, 3333, 'Daniel', 'Rosenkranz'),
(444555, 6666, 'Matt', 'Damon'),
(777888, 9999, 'Boy', 'Wonder'), -- No assigned group yet.
(654321, 4321, 'Lazy', 'Guy I');

INSERT INTO accessGroup (groupname)
VALUES ('KeyTech'),
('Teachers'),
('Janitors'),
('TeamDropbox'),
('TeamGamers');

INSERT INTO room (lockIdentifier, roomName)
VALUES (1, 'C311'),
(2, 'C312'),
(3, 'C3YY'),
(4, 'C1YY'),
(5, 'A109');

INSERT INTO unlimitedAccess (name)
VALUES ('Janitors');

INSERT INTO reservationTime (name, startTime, endTime)
VALUES ('morning', '08:45:00', '11:59:59'),
('midday', '12:00:00', '14:14:59'),
('afternoon', '14:15:00', '17:29:59'),
('whole_day', '08:45:00', '17:30:00');

INSERT INTO reservation (groupname, lockIdentifier, creationDate, repeatInterval, startDate, endDate, reservationTimeName)
VALUES ('KeyTech', 1, SYSDATE(), 'DAY', DATE(SYSDATE()), DATE_ADD(DATE(SYSDATE()), INTERVAL 1 DAY), 'whole_day'), -- enddate is current date + 30 days.
('Teachers', 2, SYSDATE(), 'MONTH', DATE(SYSDATE()), DATE_ADD(DATE(SYSDATE()), INTERVAL 4 WEEK), 'morning'),
('KeyTech', 3, SYSDATE(), 'MONTH', DATE(SYSDATE()), DATE_ADD(DATE(SYSDATE()), INTERVAL 4 WEEK), 'afternoon'),
('TeamDropbox', 3, SYSDATE(), 'WEEK', DATE(SYSDATE()), DATE_ADD(DATE(SYSDATE()), INTERVAL 1 WEEK), 'morning'),
('TeamDropbox', 2, SYSDATE(), 'DAY', DATE(SYSDATE()), DATE_ADD(DATE(SYSDATE()), INTERVAL 1 DAY), 'afternoon'),
('Teachers', 4, SYSDATE(), 'DAY', DATE(SYSDATE()), DATE_ADD(DATE(SYSDATE()), INTERVAL 1 DAY), 'midday'),
('TeamGamers', 5, SYSDATE(), 'WEEK', DATE(SYSDATE()), DATE_ADD(DATE(SYSDATE()), INTERVAL 2 WEEK), 'midday');

-- Link tables
INSERT INTO userAccessGroup (userIdentifier, groupName)
VALUES (473712, 'KeyTech'),
(474296, 'KeyTech'),
(099999, 'Teachers'),
(111222, 'TeamDropbox'),
(444555, 'TeamDropbox'),
(654321, 'TeamGamers');

INSERT INTO accessGroupUnlimitedAccess (groupName, unlimitedAccessName)
VALUES ('Janitors', 'Janitors');

INSERT INTO roomUnlimitedAccess (lockIdentifier, unlimitedAccessName)
VALUES (1, 'Janitors'),
(2, 'Janitors'),
(3, 'Janitors'),
(4, 'Janitors'),
(5, 'Janitors');

-- Log tables
INSERT INTO userLog (userIdentifier, lockIdentifier, logDate)
VALUES (473712, 3, NOW());

INSERT INTO testFrameLog (lockIdentifier, receivedDate)
VALUES (2, NOW());
