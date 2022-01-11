use test;
create table if not exists user (idUser integer primary key auto_increment, 
								username varchar(50) unique,
								name varchar(50), surname varchar(50),
                                CF char(16) unique, password varchar(20),
                                address varchar(50), cellNumber integer,
                                sex char, email varchar(50), team integer,
                                role varchar(50), state varchar(8));