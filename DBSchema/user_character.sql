USE zozo_lobby;
CREATE TABLE `user_character` (
  `id` bigint NOT NULL,
  `user_id` bigint DEFAULT NULL,
  `name` varchar(45) DEFAULT NULL,
  `level` int DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;