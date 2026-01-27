CREATE TABLE `character` (
    `id` BIGINT,
    `user_id` BIGINT,
    `name` VARCHAR(1024),
    `level` INT,
    PRIMARY KEY(`id`),
    KEY `idx_user_id` (`user_id`)
)

