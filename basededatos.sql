-- Crear la base de datos
CREATE DATABASE JuegoDB;
GO

-- Usar la base de datos
USE JuegoDB;
GO

-- Crear la tabla Jugador
CREATE TABLE Jugador (
    ID INT IDENTITY(1,1) PRIMARY KEY,
    Nombre NVARCHAR(50) UNIQUE NOT NULL,
    NumeroPartidas INT DEFAULT 0
);
GO

-- Crear la tabla CategoriaPersonajes
CREATE TABLE CategoriaPersonajes (
    IDCategoria INT IDENTITY(1,1) PRIMARY KEY,
    NombreCategoria NVARCHAR(50) NOT NULL,
    IDJugador INT NOT NULL,
    FOREIGN KEY (IDJugador) REFERENCES Jugador(ID) ON DELETE CASCADE
);
GO

-- Insertar datos en la tabla Jugador
INSERT INTO Jugador (Nombre, NumeroPartidas) VALUES
(N'Carlos', 10),
(N'Ana', 15),
(N'Luis', 8);
GO

-- Insertar datos en la tabla CategoriaPersonajes
INSERT INTO CategoriaPersonajes (NombreCategoria, IDJugador) VALUES
(N'Actor', 1),
(N'Pintor', 2),
(N'Músico', 3);
GO
