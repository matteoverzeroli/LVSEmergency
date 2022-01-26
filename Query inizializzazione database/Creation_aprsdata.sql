CREATE TABLE test.aprsdata (
  `name` varchar(10) NOT NULL,
  `time` datetime NOT NULL,
  `temperature` float DEFAULT NULL COMMENT '- Unit of measure: °C\n- Max value: -20 °C\n- Min value: +50 °C',
  `pressure` float DEFAULT NULL COMMENT '- Unit of measure: hPa \n- Max value: 1100 hPa\n- Min value: 900 hPa',
  `humidity` smallint(6) DEFAULT NULL COMMENT '- Unit of measure: %\n- Max value: 100 %\n- Min value: 1 %',
  `windDirection` int(11) DEFAULT NULL COMMENT '- Unit of measure: °\\n- Max value: 360°\\n- Min value: 0°',
  `windSpeed` float DEFAULT NULL COMMENT '- Unit of measure: m/s \n- Max value: 40 m/s\n- Min value: 0 m/s',
  `windGust` float DEFAULT NULL COMMENT '- Unit of measure: m/s \n- Max value: 40 m/s\n- Min value: 0 m/s',
  `rainOneHour` float DEFAULT NULL COMMENT '- Unit of measure: mm \n- Max value: 5 mm\n- Min value: 0 mm',
  `rainDay` float DEFAULT NULL COMMENT '- Unit of measure: mm \n- Max value: 50 mm\n- Min value: 0 mm',
  `rainMidNight` float DEFAULT NULL COMMENT '- Unit of measure: mm \n- Max value: 50 mm\n- Min value: 0 mm',
  `luminosity` float DEFAULT NULL COMMENT '- Unit of measure: W/m^2',
  PRIMARY KEY (`name`,`time`),
  CONSTRAINT `aprs_code_fk` FOREIGN KEY (`name`) REFERENCES `area` (`nameAprsStation`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1