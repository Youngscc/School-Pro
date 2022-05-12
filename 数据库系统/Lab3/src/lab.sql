CREATE DATABASE  IF NOT EXISTS `competition_manager`;
USE `competition_manager`;

CREATE TABLE `competition` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(45) DEFAULT NULL,
  `Time` date DEFAULT NULL,
  `Level` enum('国际级','国家级','地区级','省级','市级') DEFAULT NULL,
  `Host` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `Name_UNIQUE` (`Name`),
  KEY `Host_School_idx` (`Host`),
  CONSTRAINT `Host_School` FOREIGN KEY (`Host`) REFERENCES `school` (`Name`) ON DELETE CASCADE ON UPDATE CASCADE
) ;

CREATE TABLE `members_of` (
  `Player` int NOT NULL,
  `Team` varchar(45) NOT NULL,
  `Role` enum('教练','队长','队员') DEFAULT NULL,
  PRIMARY KEY (`Player`,`Team`),
  KEY `members_of_team_ID_fk_idx` (`Team`),
  CONSTRAINT `members_of_players_ID_fk` FOREIGN KEY (`Player`) REFERENCES `players` (`ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `members_of_team_ID_fk` FOREIGN KEY (`Team`) REFERENCES `team` (`Name`) ON DELETE CASCADE ON UPDATE CASCADE
) ;

CREATE TABLE `participate_in` (
  `Team` varchar(45) NOT NULL,
  `Competition` varchar(45) NOT NULL,
  `Medal` enum('金奖','银奖','铜奖','优胜奖') DEFAULT NULL,
  `Place` int DEFAULT NULL,
  `Category` enum('正式','非正式') DEFAULT NULL,
  PRIMARY KEY (`Team`,`Competition`),
  KEY `participate-in_competition_Name_fk` (`Competition`),
  CONSTRAINT `participate-in_competition_Name_fk` FOREIGN KEY (`Competition`) REFERENCES `competition` (`Name`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `participate-in_team_Name_fk` FOREIGN KEY (`Team`) REFERENCES `team` (`Name`) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE `players` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(40) DEFAULT NULL,
  `Sex` enum('男','女') DEFAULT NULL,
  `E_mail` varchar(40) DEFAULT NULL,
  `School` varchar(40) DEFAULT NULL,
  `College` varchar(40) DEFAULT NULL,
  `Grade` enum('大一','大二','大三','大四','大五','研一','研二','研三','教师') DEFAULT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `players_E-mail_uindex` (`E_mail`),
  KEY `players_school_Name_fk` (`School`),
  CONSTRAINT `players_school_Name_fk` FOREIGN KEY (`School`) REFERENCES `school` (`Name`) ON DELETE CASCADE ON UPDATE CASCADE
) ;

CREATE TABLE `school` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(45) DEFAULT NULL,
  `Nation` varchar(45) DEFAULT NULL,
  `Province` varchar(45) DEFAULT NULL,
  `City` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `Name_UNIQUE` (`Name`)
) ;

CREATE TABLE `team` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(45) DEFAULT NULL,
  `School` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `Name_UNIQUE` (`Name`),
  KEY `From_School_idx` (`School`),
  CONSTRAINT `From_School` FOREIGN KEY (`School`) REFERENCES `school` (`Name`) ON DELETE CASCADE ON UPDATE CASCADE
) ;
