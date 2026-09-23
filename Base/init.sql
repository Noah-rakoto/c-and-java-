-- Active: 1790178221188@@127.0.0.1@3306@corba_voiture
-- 1. Création de la base de données
CREATE DATABASE IF NOT EXISTS corba_voiture;

-- 2. Sélection de la base de données pour les commandes suivantes
USE corba_voiture;

-- 3. Création de la table
CREATE TABLE IF NOT EXISTS Voiture (
    id INT AUTO_INCREMENT PRIMARY KEY, -- Optionnel mais recommandé : un identifiant unique
    nom VARCHAR(20),
    marque VARCHAR(20)
);

-- 4. Insertion des données (possibilité d'insérer toutes les lignes en une seule commande)
INSERT INTO Voiture (nom, marque) VALUES 
('Slave', 'Toyota'),
('Slave1', 'Toyota'),
('Slave2', 'Toyota'),
('Slave3', 'Toyota'),
('Slave4', 'Toyota');