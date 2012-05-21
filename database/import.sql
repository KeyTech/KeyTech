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
(099999, 9999, 'Teacher', 'Teacher');

INSERT INTO accessGroup (groupname)
VALUES ('KeyTech'),
('Teachers'),
('Janitors');

INSERT INTO room (lockIdentifier, roomName)
VALUES (1, 'C311'),
(2, 'C312'),
(3, 'C3YY');

INSERT INTO unlimitedAccess (name)
VALUES ('Janitors');

INSERT INTO reservationTime (name, startTime, endTime)
VALUES ('morning', '08:45:00', '11:59:59'),
('midday', '12:00:00', '14:14:59'),
('afternoon', '14:15:00', '17:29:59'),
('whole_day', '08:45:00', '17:30:00');

INSERT INTO reservation (groupname, lockIdentifier, creationDate, repeatInterval, startDate, endDate, reservationTimeName)
VALUES ('KeyTech', 1, SYSDATE(), 'DAY', DATE(SYSDATE()), DATE(SYSDATE()+2592000), 'whole_day'), -- enddate is current date + 30 days.
('Teachers', 2, SYSDATE(), 'MONTH', DATE(SYSDATE()), DATE(SYSDATE()+2592000), 'morning'),
('KeyTech', 3, SYSDATE(), 'WEEK', DATE(SYSDATE()), DATE(SYSDATE()+2592000), 'afternoon');

-- Link tables
INSERT INTO userAccessGroup (userIdentifier, groupName)
VALUES (473712, 'KeyTech'),
(474296, 'KeyTech'),
(099999, 'Teachers');

INSERT INTO accessGroupUnlimitedAccess (groupName, unlimitedAccessName)
VALUES ('Janitors', 'Janitors');

INSERT INTO roomUnlimitedAccess (lockIdentifier, unlimitedAccessName)
VALUES (1, 'Janitors'),
(2, 'Janitors'),
(3, 'Janitors');

-- Log tables
INSERT INTO userLog (userIdentifier, lockIdentifier, logDate)
VALUES (473712, 3, SYSDATE()-(24*60*60));

INSERT INTO testFrameLog (lockIdentifier, receivedDate)
VALUES (2, SYSDATE()-24);