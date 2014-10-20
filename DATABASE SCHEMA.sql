CREATE TABLE user_db (id SERIAL PRIMARY KEY, 
                      name TEXT UNIQUE NOT NULL);
INSERT INTO user_db(name) VALUES('kvsd');
INSERT INTO user_db(name) VALUES('gianpaolo');
--##############################################################################
CREATE TABLE cat_merce (id SERIAL PRIMARY KEY, 
                        descr TEXT UNIQUE NOT NULL);
INSERT INTO cat_merce VALUES(0, '-----');
INSERT INTO cat_merce(descr) VALUES('Ferramenta');
INSERT INTO cat_merce(descr) VALUES('Utensileria');
INSERT INTO cat_merce(descr) VALUES('Elettroutensili');
INSERT INTO cat_merce(descr) VALUES('Serrature');
INSERT INTO cat_merce(descr) VALUES('Casalinghi');
INSERT INTO cat_merce(descr) VALUES('Giardinaggio');
--##############################################################################
CREATE TABLE cod_iva (id SERIAL PRIMARY KEY, 
                      descr NUMERIC UNIQUE NOT NULL CHECK (descr>=0));
INSERT INTO cod_iva(descr) VALUES(4);
INSERT INTO cod_iva(descr) VALUES(10);
INSERT INTO cod_iva(descr) VALUES(20);
INSERT INTO cod_iva(descr) VALUES(21);
INSERT INTO cod_iva(descr) VALUES(22);
--##############################################################################
CREATE TABLE unita_misura(id SERIAL PRIMARY KEY,
                          descr TEXT UNIQUE NOT NULL);
INSERT INTO unita_misura VALUES (0, '-----');
INSERT INTO unita_misura(descr) VALUES('pz');
INSERT INTO unita_misura(descr) VALUES('cf');
INSERT INTO unita_misura(descr) VALUES('kg');
INSERT INTO unita_misura(descr) VALUES('mm');
INSERT INTO unita_misura(descr) VALUES('gr');
--##############################################################################
CREATE TABLE sede_magazzino(id SERIAL PRIMARY KEY, 
                            descr TEXT UNIQUE NOT NULL);
INSERT INTO sede_magazzino VALUES (0, '-----');
INSERT INTO sede_magazzino(descr) VALUES ('Viale Diaz 55');
INSERT INTO sede_magazzino(descr) VALUES ('Via Aidone 23');
INSERT INTO sede_magazzino(descr) VALUES ('Via Aidone 10');
--##############################################################################
CREATE TABLE marca(id SERIAL PRIMARY KEY,
                   descr TEXT UNIQUE NOT NULL);
INSERT INTO marca VALUES (0, '-----');
INSERT INTO marca(descr) VALUES ('Usag');
INSERT INTO marca(descr) VALUES ('Ausonia');
INSERT INTO marca(descr) VALUES ('LTL');
INSERT INTO marca(descr) VALUES ('Krino');
INSERT INTO marca(descr) VALUES ('Dremel');
INSERT INTO marca(descr) VALUES ('Kodak');
--##############################################################################
CREATE TABLE tipo_ditta(id SERIAL PRIMARY KEY,
                        descr TEXT UNIQUE NOT NULL);
INSERT INTO tipo_ditta VALUES (0, '-----');
INSERT INTO tipo_ditta(descr) VALUES('privato');
INSERT INTO tipo_ditta(descr) VALUES('ditta individuale');
INSERT INTO tipo_ditta(descr) VALUES('società');
--##############################################################################
CREATE TABLE citta(id SERIAL PRIMARY KEY,
                   descr TEXT UNIQUE NOT NULL);
INSERT INTO citta VALUES (0, '-----');
INSERT INTO citta(descr) VALUES ('Enna');
INSERT INTO citta(descr) VALUES ('Catania');
INSERT INTO citta(descr) VALUES ('Palermo');
INSERT INTO citta(descr) VALUES ('Ragusa');
INSERT INTO citta(descr) VALUES ('Siracusa');
INSERT INTO citta(descr) VALUES ('Leonforte');
INSERT INTO citta(descr) VALUES ('Agrigento');
INSERT INTO citta(descr) VALUES ('Messina');
--##############################################################################
CREATE TABLE provincia(id SERIAL PRIMARY KEY,
                       descr TEXT UNIQUE NOT NULL);
INSERT INTO provincia VALUES (0, '-----');
INSERT INTO provincia(descr) VALUES ('Agrigento');
INSERT INTO provincia(descr) VALUES ('Caltanissetta');
INSERT INTO provincia(descr) VALUES ('Catania');
INSERT INTO provincia(descr) VALUES ('Enna');
INSERT INTO provincia(descr) VALUES ('Messina');
INSERT INTO provincia(descr) VALUES ('Palermo');
INSERT INTO provincia(descr) VALUES ('Ragusa');
INSERT INTO provincia(descr) VALUES ('Siracusa');
INSERT INTO provincia(descr) VALUES ('Trapani');
--##############################################################################
CREATE TABLE cap(id SERIAL PRIMARY KEY,
                 descr TEXT UNIQUE NOT NULL);
INSERT INTO cap VALUES (0, '-----');
INSERT INTO cap(descr) VALUES ('94100');
INSERT INTO cap(descr) VALUES ('90010');
INSERT INTO cap(descr) VALUES ('95010');
INSERT INTO cap(descr) VALUES ('98020');
INSERT INTO cap(descr) VALUES ('91100');
--##############################################################################
CREATE TABLE stato(id SERIAL PRIMARY KEY,
                   descr TEXT UNIQUE NOT NULL);
INSERT INTO stato VALUES (0, '-----');
INSERT INTO stato(descr) VALUES ('Italia');
INSERT INTO stato(descr) VALUES ('Francia');
INSERT INTO stato(descr) VALUES ('Svizzera');
INSERT INTO stato(descr) VALUES ('Germania');
INSERT INTO stato(descr) VALUES ('Spagna');
--##############################################################################
CREATE TABLE banca (id SERIAL PRIMARY KEY,
		    descr TEXT UNIQUE NOT NULL);
INSERT INTO banca VALUES (0, '-----');
INSERT INTO banca(descr) VALUES('BNL');
INSERT INTO banca(descr) VALUES('Unicredit');
--##############################################################################
CREATE TABLE agenzia (id SERIAL PRIMARY KEY,
                      descr TEXT UNIQUE NOT NULL);
INSERT INTO agenzia VALUES (0, '-----');
--##############################################################################
CREATE TABLE tipo_pagamento (id SERIAL PRIMARY KEY, 
                             descr TEXT UNIQUE NOT NULL);
INSERT INTO tipo_pagamento VALUES (0, '-----');
INSERT INTO tipo_pagamento(descr) VALUES ('Contanti');
INSERT INTO tipo_pagamento(descr) VALUES ('Bancomat');
INSERT INTO tipo_pagamento(descr) VALUES ('Carta di credito');
INSERT INTO tipo_pagamento(descr) VALUES ('Assegno');
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
INSERT INTO aspetto_beni(descr) VALUES ('Sacchetto');
INSERT INTO aspetto_beni(descr) VALUES ('Scatola');
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
                    cel TEXT,
                    email TEXT);
INSERT INTO agenti(id, nome, cognome) VALUES(0, '-----', '-----');
INSERT INTO agenti(nome, cognome) VALUES('Antonello', 'La delfa');
INSERT INTO agenti(nome, cognome) VALUES('Vincenzo', 'Calogero');
INSERT INTO agenti(nome, cognome) VALUES('Dario', 'Catarrese');
INSERT INTO agenti(nome, cognome) VALUES('Alessandro', 'Cusumano');
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
INSERT INTO anagrafica(fornitore, cliente, rag_sociale, cod_fisc, prt_iva) VALUES('t','f','Calogero', '00000000000','00000000000');
INSERT INTO anagrafica(fornitore, cliente, rag_sociale, cod_fisc, prt_iva) VALUES('t','f','Guaiana', '00000000000','00000000000');
INSERT INTO anagrafica(fornitore, cliente, rag_sociale, cod_fisc, prt_iva) VALUES('t','f','Virlinzi', '00000000000','00000000000');
INSERT INTO anagrafica(fornitore, cliente, rag_sociale, cod_fisc, prt_iva) VALUES('t','f','Viglietta', '00000000000','00000000000');
INSERT INTO anagrafica(fornitore, cliente, rag_sociale, cod_fisc, prt_iva) VALUES('t','f','Melchioni', '00000000000','00000000000');
--##############################################################################
CREATE VIEW vw_anagrafica ("Id", "Ragione sociale", "Tipo di ditta",
       "Nome", "Cognome", "Indirizzo", "Citta", "Provincia", "CAP",
       "Stato", "Codice fiscale", "Partita Iva", "Agente", "Telefono",
       "Fax", "Cellulare", "Email", "Sito web", "Banca", "Agenzia",
       "Conto", "Swift", "Iban", "Destinazione merce", "Note") AS
SELECT anagrafica.id, anagrafica.rag_sociale, tipo_ditta.descr,
       anagrafica.nome, anagrafica.cognome, anagrafica.indirizzo,
       citta.descr, provincia.descr, cap.descr, stato.descr,
       anagrafica.cod_fisc, anagrafica.prt_iva, agenti.cognome,
       anagrafica.tel, anagrafica.fax, anagrafica.cel,
       anagrafica.email, anagrafica.sito_web, anagrafica.banca,
       anagrafica.agenzia, anagrafica.conto, anagrafica.swift,
       anagrafica.iban, anagrafica.dest_merce, anagrafica.note 
FROM anagrafica, tipo_ditta, citta, provincia, cap, stato, agenti
WHERE id_tipo_ditta=tipo_ditta.id AND
      id_citta=citta.id AND
      id_provincia=provincia.id AND
      id_cap=cap.id AND
      id_stato=stato.id AND
      id_agente=agenti.id
ORDER BY anagrafica.rag_sociale;
--##############################################################################
CREATE VIEW vw_anagrafica_clienti ("Id", "Ragione sociale", "Tipo di ditta",
       "Nome", "Cognome", "Indirizzo", "Citta", "Provincia", "CAP", "Stato", 
       "Codice fiscale", "Partita Iva", "Agente","Telefono", "Fax", "Cellulare",
       "Email", "Sito web", "Banca", "Agenzia", "Conto", "Swift", "Iban",
       "Destinazione merce", "Note") AS
SELECT anagrafica.id, anagrafica.rag_sociale, tipo_ditta.descr,
       anagrafica.nome, anagrafica.cognome, anagrafica.indirizzo,
       citta.descr, provincia.descr, cap.descr, stato.descr,
       anagrafica.cod_fisc, anagrafica.prt_iva, agenti.cognome,
       anagrafica.tel, anagrafica.fax, anagrafica.cel,
       anagrafica.email, anagrafica.sito_web, anagrafica.banca,
       anagrafica.agenzia, anagrafica.conto, anagrafica.swift,
       anagrafica.iban, anagrafica.dest_merce, anagrafica.note 
FROM anagrafica, tipo_ditta, citta, provincia, cap, stato, agenti
WHERE anagrafica.cliente=true AND
      id_tipo_ditta=tipo_ditta.id AND
      id_citta=citta.id AND
      id_provincia=provincia.id AND
      id_cap=cap.id AND
      id_stato=stato.id AND
	  id_agente=agenti.id
ORDER BY anagrafica.rag_sociale;
--##############################################################################
CREATE VIEW vw_anagrafica_fornitori ("Id", "Ragione sociale", "Tipo di ditta",
       "Nome", "Cognome", "Indirizzo", "Citta", "Provincia", "CAP", "Stato", 
       "Codice fiscale", "Partita Iva", "Agente", "Telefono", "Fax", "Cellulare",
       "Email", "Sito web", "Banca", "Agenzia", "Conto", "Swift", "Iban",
       "Destinazione merce", "Note") AS
SELECT anagrafica.id, anagrafica.rag_sociale, tipo_ditta.descr,
       anagrafica.nome, anagrafica.cognome, anagrafica.indirizzo,
       citta.descr, provincia.descr, cap.descr, stato.descr,
       anagrafica.cod_fisc, anagrafica.prt_iva, agenti.cognome,
       anagrafica.tel, anagrafica.fax, anagrafica.cel,
       anagrafica.email, anagrafica.sito_web, anagrafica.banca,
       anagrafica.agenzia, anagrafica.conto, anagrafica.swift,
       anagrafica.iban, anagrafica.dest_merce, anagrafica.note 
FROM anagrafica, tipo_ditta, citta, provincia, cap, stato, agenti
WHERE anagrafica.fornitore=true AND
      id_tipo_ditta=tipo_ditta.id AND
      id_citta=citta.id AND
      id_provincia=provincia.id AND
      id_cap=cap.id AND
      id_stato=stato.id AND
      id_agente=agenti.id
ORDER BY anagrafica.rag_sociale;
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
                        id_cod_iva INTEGER references cod_iva(id) DEFAULT 0,
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
                        fattura TEXT,
                        data_arrivo DATE DEFAULT current_date,
                        id_sede_magazzino INTEGER references sede_magazzino(id) DEFAULT 0,
                        note TEXT);
INSERT INTO magazzino VALUES(DEFAULT, 'batteria alcalina AA', 1, 1, 'extra', '0000','0000', '00000000', 1, 1, 1, 10, 10, '10.00', 50, '7.50', 50, '2.15',
                             '9.15', '9.20', '241', DEFAULT, 1, 'note');
INSERT INTO magazzino VALUES(DEFAULT, 'batteria alcalina AAA', 1, 1, 'extra', '0000','0000', '00000000', 1, 1, 1, 10, 10, '10.00', 50, '7.50', 50, '2.15',
                             '9.15', '9.20', '241', DEFAULT, 1, 'note');
--######################################################################################
CREATE VIEW vw_magazzino ("Id", "Descrizione", "Fornitore", "Marca", "Modello", "Cod.Articolo", "Cod.Fornitore",
                          "Cod.EAN", "Cat.Merce", "Cod.IVA", "UM", "Scorta Minima", "Quantità", "Prezzo Fattura", "Sconto", 
                          "Prezzo Acquisto", "Ricarico", "Iva", "Prezzo Finito", "Prezzo Vendità", "Nr.Fattura", "Data Arrivo", "Sede Magazzino",
                          "Note") AS
SELECT mgz.id, mgz.descr, anag.rag_sociale, marca.descr, mgz.modello, mgz.cod_articolo, mgz.cod_fornitore, mgz.cod_barre,
       cat_merce.descr, cod_iva.descr, um.descr, mgz.scorta_minima, mgz.quantita, mgz.prezzo_fattura::money, mgz.sconto_fornitore,
       mgz.prezzo_acquisto::money, mgz.ricarico, mgz.iva::money, mgz.prezzo_finito::money, mgz.prezzo_vendita::money, mgz.fattura, mgz.data_arrivo, sm.descr,
       mgz.note FROM magazzino AS mgz, anagrafica AS anag, marca, cat_merce, cod_iva, unita_misura AS um, sede_magazzino AS sm
WHERE anag.id = mgz.id_fornitore AND
      marca.id = mgz.id_marca AND
      cat_merce.id = mgz.id_merce AND
      cod_iva.id = mgz.id_cod_iva AND
      um.id = mgz.id_unita_misura AND
      sm.id = id_sede_magazzino
ORDER BY mgz.id;
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
                              fattura TEXT);
--########################################################################################
CREATE VIEW vw_listino_storico ("Id Articolo", "Data", "Quantità", "Prezzo Fattura", "Sconto", "Prezzo Acquisto", "Ricarico", "IVA", "Prezzo finito", "Prezzo Vendità", "Nr. Fattura") AS
SELECT ls.id_articolo, ls.data_arrivo, ls.quantita, ls.prezzo_fattura::money, ls.sconto_fornitore, ls.prezzo_acquisto::money, ls.ricarico, ls.iva::money, ls.prezzo_finito::money, ls.prezzo_vendita::money, ls.fattura FROM listino_storico AS ls ORDER BY ls.id_articolo, ls.data_arrivo;
