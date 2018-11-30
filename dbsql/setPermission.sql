--Crea il gruppo gestionale user e assegna la possibilita' di 
--modificare le tabelle e le sequenze agli utenti appartenenti
--al gruppo.
CREATE ROLE gestionale_user;
GRANT ALL ON ALL TABLES IN SCHEMA public TO gestionale_user;
GRANT ALL ON ALL SEQUENCES IN SCHEMA public TO gestionale_user;

