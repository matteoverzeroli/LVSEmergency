use test;
create table if not exists user (idUser integer primary key auto_increment, 
								username varchar(50) unique not null,
								name varchar(50) not null, 
                                surname varchar(50) not null,
                                CF char(16) unique, 
                                password varchar(20) not null,
                                address varchar(50) not null, 
                                cellnumber varchar(10) not null,
                                sex char not null, 
                                email varchar(50) not null, 
                                team integer default null,
                                role varchar(50) not null, 
                                state varchar(8) default "INACTIVE");
                                
create table if not exists team (idTeam integer primary key auto_increment,
								teamName varchar(20) unique,
                                idForeman integer,
                                FOREIGN KEY (idForeman) REFERENCES user(idUser) ON DELETE SET NULL ON UPDATE CASCADE);
                                
ALTER TABLE `user`
								ADD CONSTRAINT `user_ibfk_1` FOREIGN KEY (`team`) 
								REFERENCES `team` (`idTeam`) ON DELETE SET NULL ON UPDATE CASCADE;