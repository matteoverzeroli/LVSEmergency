use test;

#INIZIO: NON MODIFICARE: SERVONO PER VALIDARE I TEST
insert into area (idArea, areaName, lat, lng, istatCode)
values(1, "Bergamo", 45.69499969482422, 9.670000076293945, "016024");

insert into area (idArea, areaName, lat, lng, istatCode)
values(2, "Sovere", 45.81666564941406, 10.033333778381348, "016204");

insert into area (idArea, areaName, lat, lng, istatCode)
values(3, "Costa di Mezzate", 45.66666793823242, 9.800000190734863, "016084");

insert into area (idArea, areaName, lat, lng, istatCode)
values(4, "Dalmine", 45.650001525878906, 9.600000381469727, "016091");

insert into area (idArea, areaName, lat, lng, nameAprsStation, istatCode)
values(5, "Ospitaletto", 45.55527877807617, 10.073333740234375, "FW0796", "017127");

insert into area (idArea, areaName, lat, lng, nameAprsStation, istatCode)
values(6, "Taverna", 39.02101516723633, 16.582666397094727, "FW8778", "079146");

insert into area (idArea, areaName, lat, lng, nameAprsStation, istatCode)
values(7, "Bologna", 44.49388885498047, 11.342778205871582, "EW0690", "037006");

insert into area (idArea, areaName, lat, lng, nameAprsStation, istatCode)
values(8, "Perugia", 43.112098693847656, 12.388799667358398, "DW0950", "054039");

insert into team (idTeam, teamName, idForeman, idArea)
values(1, "BGTeam", null, 1);

insert into team (idTeam, teamName, idForeman, idArea)
values(2, "SVTeam", null, 2);

insert into team (idTeam, teamName, idForeman, idArea)
values(3, "CDMTeam", null, 3);

insert into user (idUser, username,name,surname,CF,password,address,cellNumber,sex,email,idTeam,role,state)
values(1,"admin", "Mario", "Rossi","MRARSS80A01C800V","admin","Via Nazionale 7","3485556255",'M',"mario@rossi.it", null, "ADMINISTRATOR", "ACTIVE");

insert into user (idUser, username,name,surname,CF,password,address,cellNumber,sex,email,idTeam,role,state)
values(2,"admin1", "Daniela", "Rossi","DNARSS80A01C800V","admin1","Via Nazionale 8","325186255",'F',"daniela@rossi.it", null, "ADMINISTRATOR", "ACTIVE");

insert into user (idUser, username,name,surname,CF,password,address,cellNumber,sex,email,idTeam,role,state)
values(3,"admin2", "Luca", "Rossi","LCARSS80A01C800V","admin2","Via Nazionale 9","3252186255",'M',"luca@rossi.it", null, "ADMINISTRATOR", "ACTIVE");

insert into user (idUser, username,name,surname,CF,password,address,cellNumber,sex,email,idTeam,role,state)
values(4,"foreman1", "Giancarlo", "Bianchi","BNARSS80A01C800V","foreman1","Via Verdi 1","3215186255",'M',"giancarlo@bianchi.it",1, "FOREMAN", "ACTIVE");

insert into user (idUser, username,name,surname,CF,password,address,cellNumber,sex,email,idTeam,role,state)
values(5,"foreman2", "Loredana", "Bianchi","LDARSS80A01C800V","foreman2","Via Verdi 2","3355844512",'F',"loredana@bianchi.it",2, "FOREMAN", "ACTIVE");

insert into user (idUser, username,name,surname,CF,password,address,cellNumber,sex,email,idTeam,role,state)
values(6,"foreman3", "Lorenzo", "Verdi","LVARSS80A01C800V","foreman3","Via Bianchi 1","3655844512",'M',"lorenzo@verdi.it",3, "FOREMAN", "ACTIVE");

update team
set idForeman = 4
where idTeam = 1;

update team
set idForeman = 5
where idTeam = 2;

#FINE: NON MODIFICARE: SERVONO PER VALIDARE I TEST