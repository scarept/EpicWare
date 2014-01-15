USE [master]
GO

/****** Object:  Database [epicwar2e]    Script Date: 01/13/2014 18:31:38 ******/
CREATE DATABASE [epicwar2e] ON  PRIMARY 
( NAME = N'epicwar2e', FILENAME = N'c:\Program Files\Microsoft SQL Server\MSSQL10.SQLEXPRESS\MSSQL\DATA\epicwar2e.mdf' , SIZE = 3328KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'epicwar2e_log', FILENAME = N'c:\Program Files\Microsoft SQL Server\MSSQL10.SQLEXPRESS\MSSQL\DATA\epicwar2e_log.LDF' , SIZE = 832KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO

ALTER DATABASE [epicwar2e] SET COMPATIBILITY_LEVEL = 100
GO

IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [epicwar2e].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO

ALTER DATABASE [epicwar2e] SET ANSI_NULL_DEFAULT OFF 
GO

ALTER DATABASE [epicwar2e] SET ANSI_NULLS OFF 
GO

ALTER DATABASE [epicwar2e] SET ANSI_PADDING OFF 
GO

ALTER DATABASE [epicwar2e] SET ANSI_WARNINGS OFF 
GO

ALTER DATABASE [epicwar2e] SET ARITHABORT OFF 
GO

ALTER DATABASE [epicwar2e] SET AUTO_CLOSE ON 
GO

ALTER DATABASE [epicwar2e] SET AUTO_CREATE_STATISTICS ON 
GO

ALTER DATABASE [epicwar2e] SET AUTO_SHRINK OFF 
GO

ALTER DATABASE [epicwar2e] SET AUTO_UPDATE_STATISTICS ON 
GO

ALTER DATABASE [epicwar2e] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO

ALTER DATABASE [epicwar2e] SET CURSOR_DEFAULT  GLOBAL 
GO

ALTER DATABASE [epicwar2e] SET CONCAT_NULL_YIELDS_NULL OFF 
GO

ALTER DATABASE [epicwar2e] SET NUMERIC_ROUNDABORT OFF 
GO

ALTER DATABASE [epicwar2e] SET QUOTED_IDENTIFIER OFF 
GO

ALTER DATABASE [epicwar2e] SET RECURSIVE_TRIGGERS OFF 
GO

ALTER DATABASE [epicwar2e] SET  ENABLE_BROKER 
GO

ALTER DATABASE [epicwar2e] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO

ALTER DATABASE [epicwar2e] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO

ALTER DATABASE [epicwar2e] SET TRUSTWORTHY OFF 
GO

ALTER DATABASE [epicwar2e] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO

ALTER DATABASE [epicwar2e] SET PARAMETERIZATION SIMPLE 
GO

ALTER DATABASE [epicwar2e] SET READ_COMMITTED_SNAPSHOT OFF 
GO

ALTER DATABASE [epicwar2e] SET HONOR_BROKER_PRIORITY OFF 
GO

ALTER DATABASE [epicwar2e] SET  READ_WRITE 
GO

ALTER DATABASE [epicwar2e] SET RECOVERY SIMPLE 
GO

ALTER DATABASE [epicwar2e] SET  MULTI_USER 
GO

ALTER DATABASE [epicwar2e] SET PAGE_VERIFY CHECKSUM  
GO

ALTER DATABASE [epicwar2e] SET DB_CHAINING OFF 
GO




insert into countries (name) values ('Portugal')
insert into countries (name) values ('Spain')
insert into countries (name) values ('Italy')
insert into countries (name) values ('France')
insert into games(name) values('Hangman')
insert into games(name) values('TicTacToe')
insert into games(name) values('Labyrinth')
insert into languages(name,reference) values ('Português','pt-PT')
insert into languages(name,reference) values ('English','en')
insert into languages(name,reference) values ('Français','fr')
insert into hangmantopic(nome,languageID) values ('Musica',(select id from languages where name = 'Portugues'))
insert into hangmantopic(nome,languageID) values ('Cinema',(select id from languages where name = 'Portugues'))
insert into hangmantopic(nome,languageID) values ('Music',(select id from languages where name = 'English'))
insert into hangmantopic(nome,languageID) values ('Cinema',(select id from languages where name = 'English'))
insert into hangmantopic(nome,languageID) values ('Musique',(select id from languages where name = 'Français'))
insert into hangmantopic(nome,languageID) values ('Cinema',(select id from languages where name = 'Français'))
insert into hangmanword(nome,topicid) values ('guitarra', (select topicid from hangmantopic where nome='Musica'))
insert into hangmanword(nome,topicid) values ('vocalista', (select topicid from hangmantopic where nome='Musica'))
insert into hangmanword(nome,topicid) values ('piano', (select topicid from hangmantopic where nome='Musica'))
insert into hangmanword(nome,topicid) values ('saxofone', (select topicid from hangmantopic where nome='Musica'))
insert into hangmanword(nome,topicid) values ('camara', (select topicid from hangmantopic where nome='Cinema'))
insert into hangmanword(nome,topicid) values ('realizador', (select topicid from hangmantopic where nome='Cinema'))
insert into hangmanword(nome,topicid) values ('cenario', (select topicid from hangmantopic where nome='Cinema'))
insert into hangmanword(nome,topicid) values ('figurante', (select topicid from hangmantopic where nome='Cinema'))
insert into moods(name) values ('Triste')
insert into moods(name) values ('Normal')
insert into moods(name) values ('Feliz')
insert into tagconnections(tag) values ('Amigo')
insert into tagconnections(tag) values ('Namorado')
insert into tagconnections(tag) values ('Casado')
insert into tagconnections(tag) values ('Trabalho')
insert into tagconnections(tag) values ('Escola')
insert into tagconnections(tag) values ('Familia')
insert into webpages_roles(rolename) values ('Administrator')
insert into webpages_roles(rolename) values ('User')