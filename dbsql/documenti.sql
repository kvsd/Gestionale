CREATE SEQUENCE fatt_seq;
CREATE SEQUENCE dtt_seq;

CREATE TABLE documenti (id SERIAL PRIMARY KEY, 
						id_cliente INTEGER REFERENCES anagrafica(id),
					    id_tipo_documento INTEGER REFERENCES tipo_documento(id), 
					    id_divisa INTEGER REFERENCES moneta(id),
						data DATE DEFAULT current_date,
					    nr_documento TEXT, --sequenza fatt_se o dtt_Seq
					    importo_tot DECIMAL,
						arrotondamento DECIMAL,
						casuale TEXT);

CREATE TABLE documenti_det (id SERIAL PRIMARY KEY,
							descr TEXT,
							quantita DECIMAL,
							unita_misura INTEGER, --references
							prezzo_unitario DECIMAL, 
							prezzo_totale DECIMAL,
							aliquota_iva DECIMAL, --forse percentuale
							riferimentoAmministrazione TEXT);
