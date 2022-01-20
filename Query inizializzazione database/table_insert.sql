use test;

insert into user (username,name,surname,CF,password,address,cellNumber,sex,email,idTeam,role,state)
values("pluto", "ciccio", "ciccio","awbgdwsf","ciccio","aea","3485556255","M","aa@aa.it",null,"VOLUNTEER","ACTIVE");

insert into user (username,name,surname,CF,password,address,cellNumber,sex,email,idTeam,role,state)
values("pippo", "pippo", "ciccio","awbgwsf","pippo","aea","3485556255","M","aa@aa.it",null,"FOREMAN","ACTIVE");

insert into user (username,name,surname,CF,password,address,cellNumber,sex,email,idTeam,role,state)
values("admin", "pippo", "ciccio","awgwsf","admin","aea","3485556255","M","aa@aa.it",null,"ADMINISTRATOR","ACTIVE");

insert into area (areaName, lat, lng, istatCode)
values("bergamo", 1.0, 1.0, 016024);

insert into team (teamName, idForeman, idArea)
values("Val Cavallina", 1, 1);

update user
set idTeam = 1
where idUser = 1 or idUser = 2 or idUser = 3 ;