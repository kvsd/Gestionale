CREATE TABLE user_db (id SERIAL PRIMARY KEY, 
                      name TEXT UNIQUE NOT NULL);
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
                       descr TEXT UNIQUE NOT NULL);
INSERT INTO provincia VALUES (0, '-----');
--##############################################################################
CREATE TABLE cap(id SERIAL PRIMARY KEY,
                 descr TEXT UNIQUE NOT NULL);
INSERT INTO cap VALUES (0, '-----');
--##############################################################################
CREATE TABLE stato(id SERIAL PRIMARY KEY,
                   descr TEXT UNIQUE NOT NULL);
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
--##############################################################################
CREATE VIEW vw_anagrafica ("Id", "Ragione sociale", "Tipo di ditta",
       "Nome", "Cognome", "Indirizzo", "Citta", "Codice fiscale", 
       "Partita Iva", "Agente", "Telefono", "Fax", "Cellulare", "Email", 
       "Sito web", "Banca", "Agenzia", "Conto", "Swift", "Iban", 
       "Destinazione merce", "Note") AS
SELECT anagrafica.id, anagrafica.rag_sociale, tipo_ditta.descr,
       anagrafica.nome, anagrafica.cognome, anagrafica.indirizzo,
       citta.descr, 
       anagrafica.cod_fisc, anagrafica.prt_iva, agenti.cognome,
       anagrafica.tel, anagrafica.fax, anagrafica.cel,
       anagrafica.email, anagrafica.sito_web, anagrafica.banca,
       anagrafica.agenzia, anagrafica.conto, anagrafica.swift,
       anagrafica.iban, anagrafica.dest_merce, anagrafica.note 
FROM anagrafica, tipo_ditta, citta, agenti
WHERE id_tipo_ditta=tipo_ditta.id AND
      id_citta=citta.id AND
      id_agente=agenti.id
ORDER BY anagrafica.rag_sociale;
--##############################################################################
CREATE VIEW vw_anagrafica_clienti ("Id", "Ragione sociale", "Tipo di ditta",
       "Nome", "Cognome", "Indirizzo", "Citta", 
       "Codice fiscale", "Partita Iva", "Agente","Telefono", "Fax", "Cellulare",
       "Email", "Sito web", "Banca", "Agenzia", "Conto", "Swift", "Iban",
       "Destinazione merce", "Note") AS
SELECT anagrafica.id, anagrafica.rag_sociale, tipo_ditta.descr,
       anagrafica.nome, anagrafica.cognome, anagrafica.indirizzo,
       citta.descr,
       anagrafica.cod_fisc, anagrafica.prt_iva, agenti.cognome,
       anagrafica.tel, anagrafica.fax, anagrafica.cel,
       anagrafica.email, anagrafica.sito_web, anagrafica.banca,
       anagrafica.agenzia, anagrafica.conto, anagrafica.swift,
       anagrafica.iban, anagrafica.dest_merce, anagrafica.note 
FROM anagrafica, tipo_ditta, citta, agenti 
WHERE anagrafica.cliente=true AND
      id_tipo_ditta=tipo_ditta.id AND
      id_citta=citta.id AND
      id_agente=agenti.id
ORDER BY anagrafica.rag_sociale;
--##############################################################################
CREATE VIEW vw_anagrafica_fornitori ("Id", "Ragione sociale", "Tipo di ditta",
       "Nome", "Cognome", "Indirizzo", "Citta",  
       "Codice fiscale", "Partita Iva", "Agente", "Telefono", "Fax", "Cellulare",
       "Email", "Sito web", "Banca", "Agenzia", "Conto", "Swift", "Iban",
       "Destinazione merce", "Note") AS
SELECT anagrafica.id, anagrafica.rag_sociale, tipo_ditta.descr,
       anagrafica.nome, anagrafica.cognome, anagrafica.indirizzo,
       citta.descr, 
       anagrafica.cod_fisc, anagrafica.prt_iva, agenti.cognome,
       anagrafica.tel, anagrafica.fax, anagrafica.cel,
       anagrafica.email, anagrafica.sito_web, anagrafica.banca,
       anagrafica.agenzia, anagrafica.conto, anagrafica.swift,
       anagrafica.iban, anagrafica.dest_merce, anagrafica.note 
FROM anagrafica, tipo_ditta, citta, agenti
WHERE anagrafica.fornitore=true AND
      id_tipo_ditta=tipo_ditta.id AND
      id_citta=citta.id AND
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
                        fattura TEXT,
                        data_arrivo DATE DEFAULT current_date,
                        id_sede_magazzino INTEGER references sede_magazzino(id) DEFAULT 0,
                        note TEXT);
--######################################################################################
CREATE VIEW vw_magazzino ("Id", "Descrizione", "Fornitore", "Marca", "Modello", "Cod.Articolo", "Cod.Fornitore",
                          "Cod.EAN", "Cat.Merce", "Cod.IVA", "UM", "Scorta Minima", "Quantità", "Prezzo Fattura", "Sconto", 
                          "Prezzo Acquisto", "Ricarico", "Iva", "Prezzo Finito", "Prezzo Vendità", "Nr.Fattura", "Data Arrivo", "Sede Magazzino",
                          "Note") AS
SELECT mgz.id, mgz.descr, anag.rag_sociale, marca.descr, mgz.modello, mgz.cod_articolo, mgz.cod_fornitore, mgz.cod_barre,
       cat_merce.descr, format('%s%%', mgz.cod_iva), um.descr, mgz.scorta_minima, mgz.quantita, mgz.prezzo_fattura::money, mgz.sconto_fornitore,
       mgz.prezzo_acquisto::money, mgz.ricarico, mgz.iva::money, mgz.prezzo_finito::money, mgz.prezzo_vendita::money, mgz.fattura, mgz.data_arrivo, sm.descr,
       mgz.note FROM magazzino AS mgz, anagrafica AS anag, marca, cat_merce, unita_misura AS um, sede_magazzino AS sm
WHERE anag.id = mgz.id_fornitore AND
      marca.id = mgz.id_marca AND
      cat_merce.id = mgz.id_merce AND
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
CREATE VIEW vw_listino_storico ("Id Articolo", "Data", "Quantità", "Prezzo Fattura", 
				"Sconto", "Prezzo Acquisto", "Ricarico", "IVA", 
				"Prezzo finito", "Prezzo Vendità", "Nr. Fattura") AS 
SELECT ls.id_articolo, ls.data_arrivo, ls.quantita, ls.prezzo_fattura::money, 
	ls.sconto_fornitore, ls.prezzo_acquisto::money, ls.ricarico, ls.iva::money, 
	ls.prezzo_finito::money, ls.prezzo_vendita::money, ls.fattura 
FROM listino_storico AS ls 
ORDER BY ls.id_articolo, ls.data_arrivo;
--##########################################################################################
CREATE VIEW vw_inventario AS
SELECT quantita AS "Quantità",
       descr AS "Descrizione",
       prezzo_acquisto::money AS "Prezzo Acquisto",
       (quantita*prezzo_acquisto)::money As "SubTotale"
FROM magazzino WHERE quantita!=0 ORDER BY "Descrizione";
--###########################################################################################


--PERMISSION#################################################################################
GRANT ALL ON ALL TABLES IN SCHEMA public TO gestionale_user;
GRANT ALL ON ALL SEQUENCES IN SCHEMA public TO gestionale_user;

