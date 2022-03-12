# *LVSEmergency* - Progetto per il corso Progettazione Algoritmi e Computabilità
Università degli Studi di Bergamo - Scuola di Ingegneria - Corso di Laurea Magistrale in Ingegneria Informatica - A.A. 2021/2022

<p align="center">
  <img 
    width="200"
    height="200"
    src="https://user-images.githubusercontent.com/49780669/156330790-336ee29d-ac22-4cdb-af0a-6ba840d2b0c6.png"
  >
</p>

## Descrizione del progetto
Il progetto si presenta come un prototipo di una applicazione creata a supporto delle attività della Protezione Civile. Infatti, partendo da esigenze reali, si è progettata un'applicazione che permette di fornire servizi utili nella gestione delle squadre della Protezione Civile (es. anagrafica, gestione interventi ...). Inoltre, l'implementazione si è concentrata sullo sviluppo dei componenti che permettono la raccolta e l'analisi dei dati (meteorologici, terremoti, bollettini ufficiali della protezione civile), recuperati da API disponibili sul web, con la finalità di generare allarmi. 
Si è scelto di sviluppare l'applicazione secondo l'approccio esagonale a microservizi, utilizzando API HTTP/REST. Il progetto si compone di tre parti fondamentali:
1. **Web Server**: realizzato in Java grazie al Framework *Spring*;
2. **Client App**: applicativo lato client per l'interazione dell'utente con il sistema, sviluppato utilizzando *Qt* e C++;
3. **Data Analyzer e Data Collector**: applicazioni scritte in Python per la raccolta e analisi dei dati.

Il web server e il database sono stati distribuiti su *Azure*, mentre il *Data Analyzer e Data Collector* su un Raspberry PI 4. L'app client può essere distribuita sia su pc sia su mobile.

## Struttura repository
Nella repository sono stati inseriti tutti i documenti prodotti nelle iterazioni. Il file **Documentazione.pdf** contiene la documentazione completa dell'applicazione ed è disponibile nella root della repository. Le cartelle sono state organizzate nel modo seguente:
* *Client App*: contiene i progetti dell'applicazione client utilizzata dagli utenti, suddivisi per iterazioni eseguite;
* *Data Collector and Data Analyzer*: contiene gli script Python e i dati di test per i componenti *Data Analyzer* e *Data Collector*;
* *Documentazione*: file .tex/immagini/diagrammi utilizzati per la documentazione; 
* *Query inizializzazione database*: script sql per l'inizializzazione del database sviluppato;
* *Web Server*: contiene i progetti Spring del server realizzati, suddivisi per iterazioni;
* *LVSEmergency.apk*: eseguibile per android.

## Autori
Davide Salvetti - Matricola 1057596

Lorenzo Leoni - Matricola 1053379

Matteo Verzeroli - Matricola 1057926
