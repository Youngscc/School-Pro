-- MySQL dump 10.13  Distrib 8.0.28, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: competition_manager
-- ------------------------------------------------------
-- Server version	8.0.28

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `competition`
--

DROP TABLE IF EXISTS `competition`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `competition` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(45) DEFAULT NULL,
  `Start_Time` date DEFAULT NULL,
  `End_Time` date DEFAULT NULL,
  `Level` enum('国际级','国家级','地区级','省级','市级') DEFAULT NULL,
  `Scope` varchar(45) DEFAULT NULL,
  `Host` varchar(45) DEFAULT NULL,
  `Position` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `Name_UNIQUE` (`Name`),
  KEY `Host_School_idx` (`Host`),
  CONSTRAINT `Host_School` FOREIGN KEY (`Host`) REFERENCES `school` (`Name`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `members_of`
--

DROP TABLE IF EXISTS `members_of`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `members_of` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `Player` int DEFAULT NULL,
  `Team` int DEFAULT NULL,
  `Role` enum('教练','队长','队员') DEFAULT NULL,
  PRIMARY KEY (`ID`),
  KEY `members_of_players_ID_fk` (`Player`),
  KEY `members_of_team_ID_fk` (`Team`),
  CONSTRAINT `members_of_players_ID_fk` FOREIGN KEY (`Player`) REFERENCES `players` (`ID`),
  CONSTRAINT `members_of_team_ID_fk` FOREIGN KEY (`Team`) REFERENCES `team` (`ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `participate-in`
--

DROP TABLE IF EXISTS `participate-in`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `participate-in` (
  `Team` varchar(45) DEFAULT NULL,
  `Competititon` varchar(45) DEFAULT NULL,
  `Medal` enum('金奖','银奖','铜奖','优胜奖') DEFAULT NULL,
  `Place` int DEFAULT NULL,
  `Category` enum('正式','非正式') DEFAULT NULL,
  KEY `participate-in_competition_Name_fk` (`Competititon`),
  KEY `participate-in_team_Name_fk` (`Team`),
  CONSTRAINT `participate-in_competition_Name_fk` FOREIGN KEY (`Competititon`) REFERENCES `competition` (`Name`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `participate-in_team_Name_fk` FOREIGN KEY (`Team`) REFERENCES `team` (`Name`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `players`
--

DROP TABLE IF EXISTS `players`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `players` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `First Name` varchar(40) DEFAULT NULL,
  `Last Name` varchar(40) DEFAULT NULL,
  `Sex` enum('男','女') DEFAULT NULL,
  `E-mail` varchar(40) DEFAULT NULL,
  `Grade` enum('大一','大二','大三','大四','大五','研一','研二','研三') DEFAULT NULL,
  `College` varchar(40) DEFAULT NULL,
  `new_column` int DEFAULT NULL,
  `School` varchar(40) DEFAULT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `players_E-mail_uindex` (`E-mail`),
  KEY `players_school_Name_fk` (`School`),
  CONSTRAINT `players_school_Name_fk` FOREIGN KEY (`School`) REFERENCES `school` (`Name`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `school`
--

DROP TABLE IF EXISTS `school`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `school` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(45) DEFAULT NULL,
  `Nation` varchar(45) DEFAULT NULL,
  `Province` varchar(45) DEFAULT NULL,
  `City` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `Name_UNIQUE` (`Name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `team`
--

DROP TABLE IF EXISTS `team`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `team` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(45) DEFAULT NULL,
  `School` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `Name_UNIQUE` (`Name`),
  KEY `From_School_idx` (`School`),
  CONSTRAINT `From_School` FOREIGN KEY (`School`) REFERENCES `school` (`Name`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-04-29 15:42:37
