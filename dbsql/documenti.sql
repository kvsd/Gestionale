DROP TABLE fattura_iva;
DROP TABLE documenti_det;
DROP TABLE documenti;
DROP SEQUENCE fatt_seq;
DROP SEQUENCE ddt_seq;

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
							numero_linea INTEGER,
							cod_articolo TEXT,
							descr TEXT,
							quantita DECIMAL,
							unita_misura INTEGER REFERENCES unita_misura(id), --references
							prezzo_unitario DECIMAL, 
							prezzo_totale DECIMAL,
							aliquota_iva DECIMAL REFERENCES cod_iva(descr), --forse percentuale
							riferimentoAmministrazione TEXT);

CREATE TABLE fattura_iva (id SERIAL PRIMARY KEY,
						  id_fattura INTEGER REFERENCES documenti(id),
						  aliquota_iva DECIMAL REFERENCES cod_iva(descr),
						  spese_accessorie DECIMAL,
						  arrotondamento DECIMAL,
						  imponibile DECIMAL,
						  imposta DECIMAL);

