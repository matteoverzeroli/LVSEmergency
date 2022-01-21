use test;

insert into area (areaName, lat, lng, istatCode)
values("bergamo", 1.0, 1.0, "016024");

insert into area (areaName, lat, lng, istatCode)
values("sovere", 1.0, 1.0, "123154");

insert into team (teamName, idForeman, idArea)
values("Val Cavallina", null, 1);

insert into user (username,name,surname,CF,password,address,cellNumber,sex,email,idTeam,role,state)
values("pluto", "ciccio", "ciccio","awbgdwsf","ciccio","aea","3485556255","M","aa@aa.it",1,"VOLUNTEER","ACTIVE");

insert into user (username,name,surname,CF,password,address,cellNumber,sex,email,idTeam,role,state)
values("pippo", "pippo", "ciccio","awbgwsf","pippo","aea","3485556255","M","aa@aa.it",1,"FOREMAN","ACTIVE");

insert into user (username,name,surname,CF,password,address,cellNumber,sex,email,idTeam,role,state)
values("admin", "pippo", "ciccio","awgwsf","admin","aea","3485556255","M","aa@aa.it",1,"ADMINISTRATOR","ACTIVE");

update team
set idForeman = 2
where idTeam = 1;