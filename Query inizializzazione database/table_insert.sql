use test;
insert into user (username,name,surname,CF,password,address,cellnumber,sex,email,team,role,state)
values("pluto", "ciccio", "ciccio","awbgdwsf","ciccio","aea","3485556255","M","aa@aa.it",null,"VOLUNTEER","ACTIVE");

insert into user (username,name,surname,CF,password,address,cellnumber,sex,email,team,role,state)
values("pippo", "pippo", "ciccio","awbgwsf","pippo","aea","3485556255","M","aa@aa.it",null,"FOREMAN","ACTIVE");

insert into user (username,name,surname,CF,password,address,cellnumber,sex,email,team,role,state)
values("admin", "pippo", "ciccio","awgwsf","admin","aea","3485556255","M","aa@aa.it",null,"ADMINISTRATOR","ACTIVE");

insert into user (username,name,surname,CF,password,address,cellnumber,sex,email,team,role,state)
values("matteo", "pippo", "ciccio","awgsf","matteo","aea","3485556255","M","aa@aa.it",1,"VOLUNTEER","ACTIVE");

SELECT * FROM USER;

insert into team (teamName, idForeman)
values("Val Cavallina", 3);

SELECT * FROM TEAM;