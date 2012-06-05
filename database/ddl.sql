--
-- DDL-script for network lock service database.
-- 
-- For the PDM diagram, see: http://jira.icaprojecten.nl/browse/KTC-54
--

DROP DATABASE lockservice;
CREATE DATABASE lockservice;

USE lockservice;

CREATE TABLE user (
	userIdentifier INT UNSIGNED NOT NULL,
	pincode SMALLINT UNSIGNED NOT NULL,
	firstname VARCHAR(40) NOT NULL,
	lastname VARCHAR(40) NOT NULL,
	blocked BOOLEAN NOT NULL DEFAULT FALSE,
	CONSTRAINT pk_user PRIMARY KEY (userIdentifier)
);

CREATE TABLE accessGroup (
	groupName VARCHAR(30) NOT NULL,
	CONSTRAINT pk_accessGroup PRIMARY KEY (groupName)
);

CREATE TABLE room(
	lockIdentifier SMALLINT UNSIGNED NOT NULL,
	roomName VARCHAR(30) NOT NULL,
	CONSTRAINT pk_room PRIMARY KEY(lockIdentifier),
	CONSTRAINT ak_room UNIQUE(roomName)
);

CREATE TABLE unlimitedAccess(
	name VARCHAR(30) NOT NULL,
	CONSTRAINT pk_unlimitedAccess PRIMARY KEY(name)
);

CREATE TABLE reservationTime(
	name VARCHAR(30) NOT NULL,
	startTime TIME NOT NULL,
	endTime TIME NOT NULL,
	CONSTRAINT pk_reservationTime PRIMARY KEY(name),
	CONSTRAINT ak_reservationTime UNIQUE(startTime, endTime)
);

CREATE TABLE reservation(
	reservationIdentifier INT NOT NULL AUTO_INCREMENT,
	groupName VARCHAR(30) NOT NULL,
	lockIdentifier SMALLINT UNSIGNED NOT NULL,
	creationDate DATETIME NOT NULL,
	repeatInterval ENUM('DAY', 'WEEK', 'MONTH') NOT NULL,
	startDate DATE NOT NULL,
	endDate DATE NULL,
	reservationTimeName VARCHAR(30) NOT NULL,
	CONSTRAINT pk_reservation PRIMARY KEY(reservationIdentifier),
	CONSTRAINT ak_reservation UNIQUE(groupName, lockIdentifier, startDate),
	CONSTRAINT fk_reservation_accessGroup 
		FOREIGN KEY (groupName)
		REFERENCES accessGroup(groupName),
	CONSTRAINT fk_reservation_room 
		FOREIGN KEY (lockIdentifier)
		REFERENCES room(lockIdentifier),
	CONSTRAINT fk_reservation_reservationTime
		FOREIGN KEY (reservationTimeName)
		REFERENCES reservationTime(name)
);

-- Log tables

CREATE TABLE userLog(
	userIdentifier INT UNSIGNED NOT NULL,
	lockIdentifier SMALLINT UNSIGNED NOT NULL,
	logDate DATETIME NOT NULL,
	result ENUM('PERMISSION_GRANTED' ,'INCORRECT_ID', 'NO_ACCESS', 'USER_BLOCKED') NOT NULL,
	CONSTRAINT fk_userLog_user 
		FOREIGN KEY (userIdentifier)
		REFERENCES user(userIdentifier),
	CONSTRAINT fk_userLog_room 
		FOREIGN KEY (lockIdentifier)
		REFERENCES room(lockIdentifier)
);

CREATE TABLE testFrameLog(
	lockIdentifier SMALLINT UNSIGNED NOT NULL,
	receivedDate DATETIME NOT NULL
);

-- Link tables

CREATE TABLE userAccessGroup(
	userIdentifier INT UNSIGNED NOT NULL,
	groupName VARCHAR(30) NOT NULL,
	CONSTRAINT pk_userAccessGroup PRIMARY KEY(userIdentifier, groupName),
	CONSTRAINT fk_userAccessGroup_user 
		FOREIGN KEY (userIdentifier) 
		REFERENCES user(userIdentifier),
	CONSTRAINT fk_userAccessGroup_accessGroup 
		FOREIGN KEY (groupName) 
		REFERENCES accessGroup(groupName)
);

CREATE TABLE accessGroupUnlimitedAccess(
	groupName VARCHAR(30) NOT NULL,
	unlimitedAccessName VARCHAR(30) NOT NULL,
	CONSTRAINT pk_accessGroupUnlimitedAccess PRIMARY KEY(groupName, unlimitedAccessName),
	CONSTRAINT fk_accessGroupUnlimitedAccess_accessGroup 
		FOREIGN KEY (groupName) 
		REFERENCES accessGroup(groupName),
	CONSTRAINT fk_accessGroupUnlimitedAccess_unlimitedAccess 
		FOREIGN KEY (unlimitedAccessName) 
		REFERENCES unlimitedAccess(name)
);

CREATE TABLE roomUnlimitedAccess(
	lockIdentifier SMALLINT UNSIGNED NOT NULL,
	unlimitedAccessName VARCHAR(30) NOT NULL,
	CONSTRAINT pk_roomUnlimitedAccess PRIMARY KEY(lockIdentifier, unlimitedAccessName),
	CONSTRAINT fk_roomUnlimitedAccess_room 
		FOREIGN KEY (lockIdentifier) 
		REFERENCES room(lockIdentifier),
	CONSTRAINT fk_roomUnlimitedAccess_unlimitedAccess 
		FOREIGN KEY (unlimitedAccessName) 
		REFERENCES unlimitedAccess(name)
);
