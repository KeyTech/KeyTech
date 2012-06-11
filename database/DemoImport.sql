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
(121212, 1212, 'Leraar1', 'Leraar1'),
(343434, 3434, 'Leraar2', 'Leraar2'),
(565656, 5656, 'Leraar3', 'Leraar3'), -- Has office rights to C202
(787878, 7878, 'Student1', 'Student1'),
(909090, 9090, 'Student2', 'Student2');

INSERT INTO accessGroup (groupname)
VALUES ('Students'),
('Teachers'),
('Office');

INSERT INTO room (lockIdentifier, roomName)
VALUES (1, 'C311'),
(2, 'C312'),
(3, 'C3YY'),
(4, 'C202'); -- Office

INSERT INTO unlimitedAccess (name)
VALUES ('Janitors');

INSERT INTO reservationTime (name, startTime, endTime)
VALUES ('morning', '08:45:00', '11:59:59'),
('midday', '12:00:00', '14:14:59'),
('afternoon', '14:15:00', '17:29:59'),
('whole_day', '08:45:00', '17:30:00');

INSERT INTO reservation (groupname, lockIdentifier, creationDate, repeatInterval, startDate, endDate, reservationTimeName)
VALUES ('Teachers', 1, SYSDATE(), 'DAY', DATE(SYSDATE()), DATE_ADD(DATE(SYSDATE()), INTERVAL 1 DAY), 'whole_day'), -- enddate is current date + 30 days.
('Teachers', 2, SYSDATE(), 'MONTH', DATE(SYSDATE()), DATE_ADD(DATE(SYSDATE()), INTERVAL 4 WEEK), 'midday'),
('Students', 3, SYSDATE(), 'MONTH', DATE(SYSDATE()), DATE_ADD(DATE(SYSDATE()), INTERVAL 4 WEEK), 'afternoon'),
('Office', 4, SYSDATE(), 'DAY', DATE(SYSDATE()), DATE_ADD(DATE(SYSDATE()), INTERVAL 1 DAY), 'whole_day');

-- Link tables
INSERT INTO userAccessGroup (userIdentifier, groupName)
VALUES (121212, 'Teachers'),
(343434, 'Teachers'),
(565656, 'Teachers'),
(787878, 'Students'),
(909090, 'Students'),
(565656, 'Office'), -- Teacher 3
(123456, 'Janitors');

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
