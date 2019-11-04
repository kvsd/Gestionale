#!/bin/bash
touch db.log
echo inizio creazione db 
createdb gestionale
echo schema db
psql -d gestionale -f db_schema.sql 
echo citta
psql -d gestionale -f cittaValues.sql
echo provincia
psql -d gestionale -f provinciaValues.sql
echo stato
psql -d gestionale -f statoValues.sql
echo reg_fiscale
psql -d gestionale -f regFiscaleValues.sql 
echo tipo pagamenti
psql -d gestionale -f tipoPagamentoValues.sql
echo documenti
psql -d gestionale -f documenti.sql
echo permessi
psql -d gestionale -f setPermission.sql
