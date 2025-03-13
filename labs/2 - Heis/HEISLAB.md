# TTK4235 – Tilpassede datasystemer  
_Vår 2024_

**Norges teknisk-naturvitenskapelige universitet**  
**Lab 2 – Institutt for teknisk kybernetikk**  
**Heisprosjektet**

---

## Revisjonshistorie

| År          | Forfatter(er)                                              |
|-------------|------------------------------------------------------------|
| 2014        | Øyvind Stavdahl, Anders Rønning Petersen                     |
| 2016        | Øyvind Stavdahl, Konstanze Kölle                             |
| 2017        | Ragnar Ranøyen Homb, Bjørn-Olav Holtung Eriksen              |
| 2020        | Kolbjørn Austreng                                            |
| 2021–2023   | Kiet Tuan Hoang                                             |
| 2024        | Terje Haugland Jacobsson, Tord Natlandsmyr                   |

---

## I. Introduksjon – Praktisk rundt laben

I heisprosjektet skal dere bruke det dere har lært i de tidligere fem øvingene til å samarbeide om et større prosjekt, nemlig utviklingen av programvare for logikkstyring av et fysisk system – i dette tilfellet en heismodell.

Som dere vet, er programmeringsspråket **C** et kraftig verktøy som ofte benyttes i industrielle sanntidsapplikasjoner og maskinnær programvare. I denne laben skal dere bruke C til å implementere et styresystem for en fysisk heismodell i Sanntidssalen (se Introduksjon III) som styres via en Arduino. Før implementasjonen må systemet beskrives og dokumenteres med UML.

For å strukturere arbeidet og sikre verifikasjon av akseptkriterier, skal den pragmatiske V-modellen benyttes (se Appendiks A). Rapporten skal gjenspeile denne modellen. Det anbefales å bruke git (sammen med en kodevertsplattform, f.eks. GitHub) slik at git-historikken speiler den pragmatiske V-modellen.

---

## Godkjenning

Heislaben vil ikke telle på sluttkarakteren i år, men den må godkjennes for at dere skal kunne gå opp til eksamen. Prosjektet er konseptuelt delt inn i tre deler (oppgaver), som i utgangspunktet må godkjennes:

- **UML-del:**  
  Inneholder klasse-, sekvens- og tilstandsdiagrammer. Her skal dere strukturere heisprosjektet før implementasjonen.
  
- **Implementasjons-del med FAT:**  
  Inneholder en FAT (Factory Acceptance Test) (se Appendiks B). Denne testen viser at implementasjonen faktisk oppfører seg som en heis.
  
- **Refleksjonsdel:**  
  Inneholder refleksjoner rundt egen implementasjon, bruk av UML og V-modellen, samt dokumentasjon av eventuell bruk av generative KI-verktøy (se Appendiks D).

Bruk av git og dokumentering med doxygen er ikke obligatorisk, men anbefales for å lette arbeidet og vil kunne trekke opp prosjektet dersom andre mangler oppdages.

Rapporten (maks ti sider, inkludert figurer) leveres på Blackboard sammen med all kildekode, slik at FAT-resultatene kan replikeres.

---

## Viktige datoer

Heisprosjektets FAT utføres i uke 11 på Sanntidssalen, med tidspunkt avhengig av når dere har saltid. Arbeidsplassene vil bli besøkt av studass eller vitass som utfører FAT med deres styresystem.

Etter FAT leveres rapport og kode (som en zip-fil) inn på Blackboard uken etter.

| Viktige dato | Beskrivelse                      |
|--------------|----------------------------------|
| Labtid, uke 11 | FAT                           |
| Fredag 22. mars | Rapport + kode som zip-fil    |

---

## II. Introduksjon – Praktisk rundt de utleverte filene

I denne laben får dere utlevert en rekke `.c`- og `.h`-filer under mappen `skeleton_project`. Tabellen nedenfor oppsummerer filene og angir hvilke som skal endres:

| Fil                                   | Skal filen(e) endres? |
|---------------------------------------|-----------------------|
| `skeleton_project/Makefile`           | Ja                    |
| `skeleton_project/SimElevatorServer`  | Nei                   |
| `skeleton_project/SimElevatorServer.exe` | Nei                |
| `skeleton_project/simulator.con`      | Nei                   |
| `skeleton_project/source/main.c`      | Ja                    |
| `skeleton_project/source/driver/elevio.c` | Helst ikke         |
| `skeleton_project/source/driver/elevio.h` | Helst ikke         |
| `skeleton_project/source/driver/elevio.con` | Nei               |
| `skeleton_project/source/driver/con_load.h` | Nei              |
| `skeleton_project/source/driver/elev_test.c` | Nei              |
| `Main/*`                             | Nei                   |
| `.github/*`                          | Nei                   |

---

## III. Introduksjon – Heisen på sanntidslaben

Dere skal bruke en fysisk modell av en heis, som styres med et Arduino-basert styresystem. Modellen består av tre hovedelementer:
- Selve heismodellen
- Betjeningspanel
- Motorstyringsboks

Det finnes en heismodell på nesten alle arbeidsplassene i Sanntidssalen.

### III.1 Heis-modell

Heismodellen (se **Figure 1**) består av en heisstol som beveger seg opp og ned langs en stolpe – tilsvarende heisrommet og sjakten i en ekte heis.

**Figure 1: Heismodellen på sanntidslaben**  
_![Figure 1: Heis-modellen på sanntidslaben](#)_

Langs heisbanen er det montert fire hall-effektsensorer som fungerer som etasjeindikatorer. Over øverste etasje og under nederste etasje finnes endestoppbrytere som kutter motorpådraget dersom heisen beveger seg utenfor sitt lovlige område. Dersom heisen treffer en endestopp, må heisstolen manuelt flyttes bort før motoren kan aktiveres på nytt.

### III.2 Betjeningsboks

Betjeningsboksen er delt inn i to:
- **Etasjepanel:**  
  Har bestillingsknapper for opp- og nedretning for hver etasje. Hver knapp har et lys for å indikere om en bestilling er mottatt. I tillegg er det lys som viser hvilken etasje heisen befinner seg i.
- **Heispanel:**  
  Inneholder bestillingsknapper for hver etasje og en stoppknapp for nødstans. Alle knappene har lys, og panelet inkluderer også et etasjeindikatorlys og et lys som markerer “DØR ÅPEN”. Det er også en obstruksjonsbryter for å simulere at en person blokkerer døren.

**Figure 2: Etasje- og Heispanel i sanntidslaben**  
_![Figure 2: Etasje- og Heispanel i sanntidslaben](#)_

### III.3 Motorstyringsboks

Motorstyringsboksen forsyner heismodellen med effekt og forsterker signalet fra datamaskinen. Motoren kan få 0–5 V, og retningen settes via et retningsbit. I tillegg kan man hente ut et analogt tacho-signal og en digital encoderverdi for å lese av motorens hastighet og posisjon. Disse signalene er nevnt for fullstendighetens skyld, men dere behøver ikke ta stilling til dem i prosjektet.

### III.4 Virkemåte og oppkobling

For at heisen skal fungere som ønsket, er det noen viktige punkter:

- **Lys:**  
  Alle lys må settes eksplisitt – det finnes ingen automatikk mellom hall-sensor og etasjeindikator.

- **Endestopp:**  
  Om endestoppbryterne aktiveres, kuttes pådraget. Heisstolen må manuelt flyttes bort fra bryterne før nytt pådrag.

- **Motorpinner:**  
  Rød og blå ledning forsyner motoren med effekt og kobles til M+ og M– på motorstyringsboksen.

- **Oppstart:**  
  Programmet kompileres med `make` og kjøres med `./elevator`. Før heisen startes må elevatorserver (eller simulatorserver) startes i et eget terminalvindu.

- **Hjemmearbeid:**  
  Dersom man jobber hjemmefra, startes simulatoren med `./SimElevatorServer` i et separat terminalvindu før kompilering og kjøring av `./elevator`.

**Figure 3: Skjermbilde av terminalene og kommandoene for å kjøre heisen**  
_![Figure 3: Terminalkommandoer](#)_

---

## Appendiks A – V-modellen

V-modellen illustreres i **Figure 4** og understreker viktigheten av å ikke hoppe direkte inn i implementasjonen uten en grundig analyse, design og testing.

### A.1 Arkitekturdesign

- Forstå kravene i spesifikasjonen før implementasjon.
- Bestem en overordnet arkitektur – for eksempel at heisen skal ha et køsystem for bestillinger, uten å spesifisere implementasjonsdetaljer.
- Bruk klasse- og sekvensdiagrammer for å visualisere modulene og deres funksjonalitet.

### A.2 Moduldesign

- Bestem hvilke moduler som trengs, og vurder om de må lagre tilstander.
- Skill ut funksjonalitet som krever tilstandshåndtering.
- Bruk klasse- og tilstandsdiagrammer for å beskrive modulene.

### A.3 Implementasjon

- Oversett diagrammene til kode.
- Vær forberedt på å revidere arkitektur og moduldesign underveis.
- Reflekter over forskjellen mellom å programmere inn i et språk og i et språk.

### A.4 Enhetstesting

- Test hver modul grundig med veldefinerte tester.
- Test både normale tilfeller og grensetilfeller (border cases) for å fange opp feil.

### A.5 Integrasjonstesting

- Test hvordan modulene fungerer sammen.
- Bruk sekvensdiagrammer for å sikre at modulene kommuniserer korrekt.
- Eksempel: Mars Climate Orbiter-feilen illustrerer viktigheten av integrasjonstesting.

**Figure 4: Illustrasjon av V-modellen**  
_![Figure 4: V-modellen](#)_

---

## Appendiks B – FAT (Factory Acceptance Test)

FAT-en sikrer at heissystemet oppfører seg som forventet i henhold til kravspesifikasjonen. Dette er en avgjørende del av prosjektet.

### B.1 FAT – Heisspesifikasjoner

#### **Krav: Oppstart**

| Punkt | Beskrivelse |
|-------|-------------|
| O1    | Ved oppstart skal heisen alltid komme til en definert tilstand. (Styresystemet vet hvilken etasje heisen står i.) |
| O2    | Om heisen starter i en udefinert tilstand, skal systemet ignorere alle bestillinger før heisen har kommet i en definert tilstand. |
| O3    | Systemet skal ikke akseptere urealistiske startbetingelser (f.eks. at heisen er over 4. etasje eller under 1. etasje). |

#### **Krav: Håndtering av bestillinger**

| Punkt | Beskrivelse |
|-------|-------------|
| H1    | Det skal ikke være mulig at en bestilling overses. Alle bestillinger skal betjenes, selv om nye bestillinger oppstår. |
| H2    | Heisen skal ikke betjene bestillinger fra utenfor heisrommet hvis den er i bevegelse i motsatt retning av bestillingen. |
| H3    | Når heisen stopper i en etasje, antas det at alle ventende tar plass, og de som skal av går ut. Bestillinger i denne etasjen regnes som ekspedert. |
| H4    | Heisen skal stå stille dersom den ikke har noen ubetjente bestillinger. |

#### **Krav: Bestillingslys- og etasjelys**

| Punkt | Beskrivelse |
|-------|-------------|
| L1    | Når en bestilling gjøres, skal lyset i bestillingsknappen lyse helt til bestillingen er utført (både for bestillinger inne i heisen og utenfor). |
| L2    | Hvis en bestillingsknapp ikke har en tilhørende bestilling, skal lyset være slukket. |
| L3    | Ved ankomst til en etasje skal korrekt etasjelys være tent. |
| L4    | Dersom heisen er i bevegelse mellom etasjer, skal etasjelyset for den sist besøkte etasjen være tent. |
| L5    | Kun ett etasjelys skal være tent av gangen. |
| L6    | Stoppknappen skal lyse så lenge den er trykket inn; den slukkes straks knappen slippes. |

#### **Krav: Heis-dør**

| Punkt | Beskrivelse |
|-------|-------------|
| D1    | Når heisen ankommer en etasje med en aktiv bestilling, skal døren åpnes i 3 sekunder før den lukkes. |
| D2    | Heisen skal være lukket dersom den ikke har ubetjente bestillinger. |
| D3    | Hvis stoppknappen trykkes mens heisen er i en etasje, skal døren åpnes og forbli åpen så lenge stoppknappen er aktiv, pluss ytterligere 3 sekunder etter at knappen slippes. |
| D4    | Om obstruksjonsbryteren aktiveres mens døren er åpen, skal døren forbli åpen inntil signalet går lavt, hvoretter døren lukkes etter 3 sekunder. |

#### **Krav: Sikkerhet**

| Punkt | Beskrivelse |
|-------|-------------|
| S1    | Heisen skal alltid stå stille når døren er åpen. |
| S2    | Heisdøren skal aldri åpnes utenfor en etasje. |
| S3    | Heisen skal aldri bevege seg utenfor det definerte området (1 til 4 etasje). |
| S4    | Ved trykking av stoppknappen skal heisen stoppe umiddelbart. |
| S5    | Ved trykking av stoppknappen skal alle ubetjente bestillinger slettes. |
| S6    | Så lenge stoppknappen holdes inne, skal heisen ignorere alle nye bestillinger. |
| S7    | Etter at stoppknappen slippes, skal heisen stå stille til den mottar nye bestillinger. |

#### **Krav: Robusthet**

| Punkt | Beskrivelse |
|-------|-------------|
| R1    | Obstruksjonsbryteren skal ikke påvirke systemet når døren er lukket. |
| R2    | Programmet skal ikke måtte startes på nytt pga. udefinert oppførsel (f.eks. krasj eller minnelekkasje). |
| R3    | Etter at heisen har kommet til en definert tilstand ved oppstart, skal ikke nye kalibreringsrunder være nødvendig. |

#### **Krav: Tillegg**

| Punkt | Beskrivelse |
|-------|-------------|
| Y1    | Avvik fra vanlig heisoppførsel kan gi trekk på FAT-testen. Bruk sunn fornuft, og spør ved usikkerhet. |

---

### B.2 FAT – Testspesifikasjoner

**FAT-test: Oppstart**

- **O1:** Sørger systemet for at heisen kommer i en definert tilstand?
- **O2:** Ignoreres bestillinger før heisen har kommet i en definert tilstand?
- **O3:** Ignoreres stoppknappen under initialisering?

**FAT-test: Håndtering av bestillinger**

- **H1:** Går heisen til riktig etasje når en bestilling mottas fra etasjepanelet?
- **H2:** Går heisen til riktig etasje når en bestilling mottas fra heispanelet?
- **H3:** Hvis heisen er på vei fra 4. til 1. etasje og en bestilling opp i 2. etasje kommer, kjører heisen først til 1. etasje før den går til 2.?
- **H4:** Håndteres alle bestillingene dersom flere knapper trykkes samtidig?
- **H5:** Blir alle bestillinger ekspedert, selv med vedvarende trykking av andre knapper (unntatt stopp)? (Altså, blir ikke heisen "fastlåst" mellom etasjene?)

**FAT-test: Bestillingslys og etasjelys**

- **L1:** Blir riktig etasjelys tent når heisen ankommer en etasje?
- **L2:** Dersom heisen befinner seg mellom 2. og 3. etasje og er på vei oppover, lyser etasjelyset i 2. etasje?
- **L3:** Blir lyset tent i bestillingsknappene når de trykkes?
- **L4:** Slukker lyset i bestillingsknappene når bestillingen er ekspedert (dvs. når heisen ankommer etasjen)?

**FAT-test: Heis-dør**

- **D1:** Åpnes døren (lyser dørlyset) når heisen stopper i en etasje?
- **D2:** Er døren åpen i 3 sekunder?
- **D3:** Står heisen stille i de 3 sekundene døren er åpen?
- **D4:** Lukkes døren før heisen kjøres videre?
- **D5:** Lukkes døren og står heisen stille når det ikke er noen nye bestillinger?

**FAT-test: Sikkerhet**

- **S1:** Stopper heisen umiddelbart ved trykking av stoppknappen?
- **S2:** Blir alle bestillinger slettet (og lyset i bestillingsknappene slukkes) ved trykking av stoppknappen?
- **S3:** Er stoppknappens lys tent mens knappen trykkes?
- **S4:** Ignoreres trykk på alle bestillingsknapper mens stoppknappen er aktiv?
- **S5:** Blir heisen stående i ro etter at stoppknappen slippes?
- **S6:** Husker heisen sin posisjon ved nødstopp mellom etasjer (altså, kreves det ikke ny initialisering)?
- **S7:** Åpnes døren dersom stoppknappen aktiveres i en etasje?

**FAT-test: Robusthet**

- **R1:** Hvor stabilt er programmet? Må programmet startes på nytt under presentasjonen?

> **Merk:** FAT-delen er svært viktig for å verifisere at implementasjonen oppfyller alle kravene i spesifikasjonen.

---

## Appendiks C – Bruk av KI

Dere må oppgi all bruk av KI-baserte verktøy i arbeidet med heisprosjektet. Viktige punkter:
- Ikke bruk KI i "åpen-sløyfe".
- Vær kritisk til informasjon generert av KI, da slike verktøy (som ChatGPT og Llama) kan "hallusinere" og gi falsk informasjon.
- KI skal kun brukes som et verktøy for problemløsning – ikke som erstatning for egen forståelse.
- Husk å dokumentere all bruk av generativ KI i prosjektet (se Appendiks D for detaljer).

---

## Appendiks D – Kommentar til refleksjonsdelen

I refleksjonsdelen skal dere reflektere over arbeidet med prosjektet. Dette inkluderer:
- **UML og V-modellen:**  
  - Hvordan har bruken av disse metodene påvirket implementasjonen gjennom prosjektet?
  - Hvilke designvalg ble endret underveis, og hvorfor?
  - Kunne prosjektet vært enklere med en annen metode?

- **KI:**  
  - Hva har KI blitt brukt til i prosjektet?
  - Hvilke effekter har bruken av KI hatt på arbeidet?

- **Robusthet, skalerbarhet og vedlikehold:**  
  - Har UML og V-modellen bidratt til bedre robusthet, skalerbarhet og vedlikehold? Eller har de hatt motsatt effekt?

---

## Appendiks E – Heissimulator

Heissimulatoren kan benyttes for testing hjemme. Den simulerer den fysiske heisen med samme funksjonalitet, og man kan velge antall etasjer.

### E.1 Initialisering av heissimulator

1. Åpne terminalen i mappen `skeleton_project`.
2. Kjør kommandoen:  
   ```bash
   chmod +x SimElevatorServer
