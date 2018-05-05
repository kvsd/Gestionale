CREATE TABLE reg_fiscale (id SERIAL PRIMARY KEY,
						  descr TEXT UNIQUE NOT NULL,
						  sigla TEXT UNIQUE NOT NULL);
INSERT INTO reg_fiscale VALUES (0, '-----', '-----');

INSERT INTO reg_fiscale VALUES(DEFAULT, 'Ordinario', 'RF01');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'Contribuenti minimi', 'RF02');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'Agricoltura e attività connesse e pesca', 'RF04');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'Vendita sali e tabacchi', 'RF05');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'Commercio fiammiferi', 'RF06');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'Editoria', 'RF07');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'Gestione servizi telefonia pubblica', 'RF08');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'Rivendita documenti di trasporto pubblico e di sosta', 'RF09');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'Intrattenimenti, giochi e altre attività di cui alla tariffa allegata al DPR 640/72', 'RF10');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'Agenzie viaggi e turismo', 'RF11');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'Agriturismo', 'RF12');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'Vendite a domicilio', 'RF13');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'Rivendita beni usati, oggetti d’arte, d’antiquariato o da collezione', 'RF14');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'Agenzie di vendite all’asta di oggetti d’arte, antiquariato o da collezione', 'RF15');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'IVA per cassa P.A.', 'RF16');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'IVA per cassa', 'RF17');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'Altro', 'RF18');
INSERT INTO reg_fiscale VALUES(DEFAULT, 'Regime forfettario', 'RF19');
