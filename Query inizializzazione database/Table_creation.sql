use test;
create table if not exists user (idUser integer primary key auto_increment, 
								username varchar(50) unique not null,
								name varchar(50) not null, 
                                surname varchar(50) not null,
                                CF char(16) unique, 
                                password varchar(20) not null,
                                address varchar(50) not null, 
                                cellNumber varchar(10) not null,
                                sex char not null, 
                                email varchar(50) not null, 
                                idTeam integer,
                                role varchar(50) not null, 
                                state varchar(8) default "INACTIVE");
                                
create table if not exists team (idTeam integer primary key auto_increment,
								teamName varchar(20) unique,
                                idForeman integer default null,
                                idArea integer default null,
                                foreign key (idForeman) references user(idUser) on delete set null on update cascade);

create table if not exists area (idArea integer primary key auto_increment,
								areaName varchar(50) unique not null,
								lat double not null,
                                lng double not null,
                                istatCode char(6) not null);

ALTER TABLE team
ADD CONSTRAINT team_fk_1 FOREIGN KEY (idArea) 
REFERENCES area (idArea) ON DELETE SET NULL ON UPDATE CASCADE;

ALTER TABLE team
ADD CONSTRAINT team_fk_2 FOREIGN KEY (idForeman) 
REFERENCES user (idUser) ON DELETE SET NULL ON UPDATE CASCADE;
                             
ALTER TABLE user
ADD CONSTRAINT user_fk_1 FOREIGN KEY (idTeam) 
REFERENCES team (idTeam) ON DELETE SET NULL ON UPDATE CASCADE;
                   
                   

/*
delete constraint 

ALTER TABLE team
DROP FOREIGN KEY team_fk_1;

ALTER TABLE user
DROP FOREIGN KEY user_fk_1;
*/

/*
disable or activate foreign key check
SET FOREIGN_KEY_CHECKS = 0;
SET FOREIGN_KEY_CHECKS = 1;
*/