CREATE TABLE user_db (id SERIAL PRIMARY KEY, 
                      name TEXT UNIQUE NOT NULL);
INSERT INTO user_db(name) VALUES('postgres');
--##############################################################################
CREATE TABLE cat_merce (id SERIAL PRIMARY KEY, 
                        descr TEXT UNIQUE NOT NULL);
INSERT INTO cat_merce VALUES(0, '-----');
--##############################################################################
CREATE TABLE cod_iva (id SERIAL PRIMARY KEY, 
                      descr NUMERIC UNIQUE NOT NULL CHECK (descr>=0));
--##############################################################################
CREATE TABLE unita_misura(id SERIAL PRIMARY KEY,
                          descr TEXT UNIQUE NOT NULL);
INSERT INTO unita_misura VALUES (0, '-----');
--##############################################################################
CREATE TABLE sede_magazzino(id SERIAL PRIMARY KEY, 
                            descr TEXT UNIQUE NOT NULL);
INSERT INTO sede_magazzino VALUES (0, '-----');
--##############################################################################
CREATE TABLE marca(id SERIAL PRIMARY KEY,
                   descr TEXT UNIQUE NOT NULL);
INSERT INTO marca VALUES (0, '-----');
--##############################################################################
CREATE TABLE tipo_ditta(id SERIAL PRIMARY KEY,
                        descr TEXT UNIQUE NOT NULL);
INSERT INTO tipo_ditta VALUES (0, '-----');
--##############################################################################
CREATE TABLE citta(id SERIAL PRIMARY KEY,
                   descr TEXT UNIQUE NOT NULL);
INSERT INTO citta VALUES (0, '-----');
--##############################################################################
CREATE TABLE provincia(id SERIAL PRIMARY KEY,
                       descr TEXT UNIQUE NOT NULL, 
					   sigla TEXT UNIQUE NOT NULL);
INSERT INTO provincia VALUES (0, '-----', '-----');
--##############################################################################
CREATE TABLE cap(id SERIAL PRIMARY KEY,
                 descr TEXT UNIQUE NOT NULL);
INSERT INTO cap VALUES (0, '-----');
--##############################################################################
CREATE TABLE stato (id SERIAL PRIMARY KEY, 
	                descr TEXT UNIQUE NOT NULL, 
					sigla TEXT UNIQUE NOT NULL);
INSERT INTO stato VALUES (0, '-----');
--##############################################################################
CREATE TABLE banca (id SERIAL PRIMARY KEY,
		    descr TEXT UNIQUE NOT NULL);
INSERT INTO banca VALUES (0, '-----');
--##############################################################################
CREATE TABLE agenzia (id SERIAL PRIMARY KEY,
                      descr TEXT UNIQUE NOT NULL);
INSERT INTO agenzia VALUES (0, '-----');
--##############################################################################
CREATE TABLE tipo_pagamento (id SERIAL PRIMARY KEY, 
                             descr TEXT UNIQUE NOT NULL);
INSERT INTO tipo_pagamento VALUES (0, '-----');
--##############################################################################
CREATE TABLE casuale_trasporto (id SERIAL PRIMARY KEY,
                                descr TEXT UNIQUE NOT NULL);
INSERT INTO casuale_trasporto VALUES (0, '-----');
--##############################################################################
CREATE TABLE vettore (id SERIAL PRIMARY KEY,
                      descr TEXT UNIQUE NOT NULL);
INSERT INTO vettore VALUES (0, '-----');
--##############################################################################
CREATE TABLE aspetto_beni (id SERIAL PRIMARY KEY,
                           descr TEXT UNIQUE NOT NULL);
INSERT INTO aspetto_beni VALUES (0, '-----');
--##############################################################################
CREATE TABLE azienda (id INTEGER PRIMARY KEY, 
                      rag_sociale TEXT UNIQUE NOT NULL,
                      nome TEXT,
					  cognome TEXT,
                      indirizzo TEXT NOT NULL,
                      id_citta INTEGER REFERENCES citta(id) DEFAULT 0,
                      id_provincia INTEGER REFERENCES provincia(id) DEFAULT 0,
		      		  id_cap INTEGER REFERENCES cap(id) DEFAULT 0,
                      id_stato INTEGER REFERENCES stato(id) DEFAULT 0,
                      tel TEXT,
                      fax TEXT,
                      email TEXT,
                      prt_iva TEXT UNIQUE NOT NULL,
                      cod_fisc TEXT UNIQUE NOT NULL,
                      iscr_trib TEXT NOT NULL, --iscrizione tribunale
                      cciaa TEXT NOT NULL, --Camera di commercio, industria artigianato e agricoltura
		      		  reg_imprese TEXT NOT NULL,
		      		  logo BYTEA);
INSERT INTO azienda(id, rag_sociale, indirizzo, prt_iva, cod_fisc, iscr_trib, cciaa, reg_imprese)
			VALUES('0', 'ragione sociale', 'indirizzo', '00000000000', 'XXXYYY00X00X000Y', '000000', '00000', '00000');
--##############################################################################
CREATE TABLE agenti(id SERIAL PRIMARY KEY,
                    nome TEXT,
                    cognome TEXT NOT NULL,
                    tel TEXT,
	    		    fax TEXT,
                    cel TEXT,
                    email TEXT);
INSERT INTO agenti(id, nome, cognome) VALUES(0, '-----', '-----');
--##############################################################################
CREATE TABLE anagrafica(id SERIAL PRIMARY KEY,
                       fornitore BOOL NOT NULL,
                       cliente BOOL NOT NULL,
                       rag_sociale TEXT UNIQUE NOT NULL,
                       id_tipo_ditta INTEGER references tipo_ditta(id) DEFAULT 0,
                       nome TEXT,
                       cognome TEXT,
                       indirizzo TEXT,
                       id_citta INTEGER references citta(id) DEFAULT 0,
                       id_provincia INTEGER references provincia(id) DEFAULT 0,
                       id_cap INTEGER references cap(id) DEFAULT 0,
                       id_stato INTEGER references stato(id) DEFAULT 0,
                       cod_fisc TEXT NOT NULL,
                       prt_iva TEXT NOT NULL,
                       id_agente INTEGER references agenti(id) DEFAULT 0,
                       tel TEXT,
                       fax TEXT,
                       cel TEXT,
                       email TEXT,
                       sito_web TEXT,
                       banca TEXT,
                       agenzia TEXT,
                       conto TEXT,
                       swift TEXT,
                       iban TEXT,
                       dest_merce TEXT,
                       note TEXT);
INSERT INTO anagrafica(id, fornitore, cliente, rag_sociale, cod_fisc, prt_iva) VALUES(0, 't','t','-----', '','');
--######################################################################################
CREATE TABLE magazzino (id SERIAL PRIMARY KEY,
                        descr TEXT,
                        id_fornitore INTEGER NOT NULL references anagrafica(id),
                        id_marca INTEGER references marca(id) DEFAULT 0,
                        modello TEXT,
                        cod_articolo TEXT,
                        cod_fornitore TEXT,
                        cod_barre TEXT,
                        id_merce INTEGER references cat_merce(id) DEFAULT 0,
                        cod_iva NUMERIC references cod_iva(descr),
                        id_unita_misura INTEGER references unita_misura(id) DEFAULT 0,
                        scorta_minima DECIMAL,
                        quantita DECIMAL NOT NULL,
                        prezzo_fattura DECIMAL NOT NULL,
                        sconto_fornitore TEXT,
                        prezzo_acquisto DECIMAL,
						ricarico TEXT,
                        iva DECIMAL,
                        prezzo_finito DECIMAL,
                        prezzo_vendita DECIMAL,
						prezzo_vendita_b DECIMAL,
                        fattura TEXT,
                        data_arrivo DATE DEFAULT current_date,
                        id_sede_magazzino INTEGER references sede_magazzino(id) DEFAULT 0,
                        note TEXT);
--######################################################################################
CREATE TABLE listino_storico (id_articolo INTEGER  NOT NULL references magazzino(id) ON DELETE CASCADE,
                              data_arrivo DATE DEFAULT current_date,
                              quantita DECIMAL NOT NULL,
                              prezzo_fattura DECIMAL NOT NULL,
                              sconto_fornitore TEXT,
                              prezzo_acquisto DECIMAL,
			      			  ricarico TEXT,
                              iva DECIMAL,
                              prezzo_finito DECIMAL,
                              prezzo_vendita DECIMAL,
							  prezzo_vendita_b DECIMAL,
                              fattura TEXT,
			      UNIQUE(id_articolo, data_arrivo));
--########################################################################################
CREATE VIEW vw_inventario AS
SELECT quantita AS "Quantità",
       descr AS "Descrizione",
       prezzo_acquisto::money AS "Prezzo Acquisto",
       (quantita*prezzo_acquisto)::money As "SubTotale"
FROM magazzino WHERE quantita!=0 ORDER BY "Descrizione";
--###########################################################################################
CREATE TABLE prima_nota (id SERIAL,
			 data DATE DEFAULT current_date,
			 descr TEXT,
			 entrata_cassa DECIMAL DEFAULT 0,
			 uscita_cassa DECIMAL DEFAULT 0,
			 entrata_banca DECIMAL DEFAULT 0,
			 uscita_banca DECIMAL DEFAULT 0);
--###########################################################################################
CREATE VIEW vw_prima_nota AS
SELECT id AS "Id",
       data AS "Data",
       descr AS "Descrizione",
       entrata_cassa::money AS "Entrata Cassa",
       uscita_cassa::money AS "Uscita Cassa",
       entrata_banca::money AS "Entrata Banca",
       uscita_banca::money AS "Uscita Banca"
FROM prima_nota
ORDER BY data;

--PERMISSION#################################################################################
CREATE ROLE gestionale_user;
GRANT ALL ON ALL TABLES IN SCHEMA public TO gestionale_user;
GRANT ALL ON ALL SEQUENCES IN SCHEMA public TO gestionale_user;
