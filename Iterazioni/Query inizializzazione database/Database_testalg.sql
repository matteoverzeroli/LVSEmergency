use testalg;

create table if not exists area (idArea integer primary key auto_increment,
								areaName varchar(50) unique not null,
								lat double not null,
                                lng double not null,
                                nameAprsStation varchar(10) unique,
                                istatCode char(6) unique not null);
                                
create table if not exists aprsdata (name varchar(10),
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

create table if not exists alarm (idAlarm integer primary key auto_increment,
					time timestamp not null default now(),
                    type varchar(15) not null,
                    color varchar(15) not null,
                    idArea integer not null,
                    description varchar(100) default 'no description');