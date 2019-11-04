DROP TABLE IF EXISTS documenti_iva;
DROP TABLE IF EXISTS documenti_det;
DROP TABLE IF EXISTS documenti;

DROP SEQUENCE IF EXISTS fatt_seq;
DROP SEQUENCE IF EXISTS ddt_seq;

CREATE SEQUENCE fatt_seq;
CREATE SEQUENCE ddt_seq;

CREATE TABLE documenti (id SERIAL PRIMARY KEY, 
						id_cliente INTEGER REFERENCES anagrafica(id),
					    id_tipo_documento INTEGER REFERENCES tipo_documento(id), 
					    id_moneta INTEGER REFERENCES moneta(id),
						data DATE DEFAULT current_date,
						years INTEGER DEFAULT date_part('YEARS', current_date),
					    nr_documento TEXT, --sequenza fatt_se o dtt_Seq
					    importo_tot DECIMAL, --comprensivo d'iva
						arrotondamento DECIMAL,
						casuale TEXT);

CREATE TABLE documenti_det (id SERIAL PRIMARY KEY,
							id_documento INTEGER REFERENCES documenti(id) ON DELETE CASCADE,
							linea INTEGER,
							cod_articolo TEXT,
							descr TEXT,
							quantita DECIMAL,
							um TEXT REFERENCES unita_misura(descr),
							prezzo_unitario DECIMAL, 
							prezzo_totale DECIMAL,
							aliquota_iva DECIMAL REFERENCES cod_iva(descr), --percentuale
							rif TEXT); --riferimento amministrazione

CREATE TABLE documenti_iva (id SERIAL PRIMARY KEY, 
							id_documento INTEGER REFERENCES documenti(id) ON DELETE CASCADE, 
							aliquota_iva DECIMAL,
							imponibile DECIMAL,
							imposta DECIMAL);
