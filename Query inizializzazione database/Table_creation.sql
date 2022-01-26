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
                                nameAprsStation varchar(10) unique,
                                istatCode char(6) unique not null);
                                
create table aprsdata (name varchar(10),
						 time datetime not null,
                         temperature float default null,
                         pressure float default null,
                         humidity  smallint default null,
                         windDirection float default null,
                         windSpeed float default null,
                         windGust float default null,
                         rainOneHour float default null,
                         rainDay float default null,
                         rainMidNight float default null,
                         luminosity float default null,
                         primary key (name, time));
                         
create table earthquake (eventId varchar(15) primary key,
						time datetime not null,
                        lat double not null,
                        lng double not null,
                        depth float not null,
                        author varchar(50) not null,
                        magType char(2) not null,
                        eventLocationName varchar(60) not null,
                        eventType varchar(20) not null,
                        idArea integer not null,
						foreign key (idArea) references area(IdArea));
                        
create table pcreport (reportId integer primary key auto_increment,
					  time datetime not null,
                      risk varchar(15) not null,
                      info varchar(50) not null,
                      alert varchar(10) not null,
                      cityName varchar(20) not null,
                      provinceName varchar(20) not null,
					  provinceCode char(2) not null,
                      region varchar(20) not null,
                      lat double not null,
                      lng double not null,
                      istatCode char(6) not null,
                      foreign key (istatCode) references area(istatCode),
                      civilProtectionZoneId varchar(20) not null,
                      civilProtectionZoneInfo varchar(20) not null,
                      link varchar(200) not null,
                      datePublication datetime not null);

create table alarm (idAlarm integer primary key auto_increment,
					time timestamp not null default now(),
                    type varchar(15) not null,
                    color varchar(15) not null,
                    idArea integer not null,
                    description varchar(100) default 'no description',
                    foreign key (idArea) references area(idArea));

ALTER TABLE team
ADD CONSTRAINT team_fk_1 FOREIGN KEY (idArea) 
REFERENCES area (idArea) ON DELETE SET NULL ON UPDATE CASCADE;

ALTER TABLE team
ADD CONSTRAINT team_fk_2 FOREIGN KEY (idForeman) 
REFERENCES user (idUser) ON DELETE SET NULL ON UPDATE CASCADE;
                             
ALTER TABLE user
ADD CONSTRAINT user_fk_1 FOREIGN KEY (idTeam) 
REFERENCES team (idTeam) ON DELETE SET NULL ON UPDATE CASCADE;

ALTER TABLE aprsdata
ADD CONSTRAINT area_fk_1 FOREIGN KEY (name) 
REFERENCES area (nameAprsStation) ON DELETE NO ACTION ON UPDATE NO ACTION;
                   
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

/*
DROP TABLE

SET FOREIGN_KEY_CHECKS = 0;
DROP TABLE `test`.`area`, `test`.`team`, `test`.`user`,`test`.`aprsdata`,`test`.`earthquake`, `test`.`pcreport`;
SET FOREIGN_KEY_CHECKS = 1;
*/
