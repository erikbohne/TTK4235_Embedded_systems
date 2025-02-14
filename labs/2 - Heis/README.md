# Case-beskrivelser

## Bestille heis
- **Precondition**: Heisen har strøm og er i drift. Obstruksjon er av.
- **Trigger**: Trykker på "opp" eller "ned" i en etasje.
- **Suksess-scenarioer**: Heisen kommer og åpner døren.

## Velge etasje
- **Precondition**: Heisen har strøm og ingen obstrusjon. Stopp knapp urørt.
- **Trigger**: Trykker på etasjeskapp.
- **Suksess-scenarioer**: Heisen kjører til ønsket etasje.

## Stoppe heisen
- **Precondition**: Heisen er i drift.
- **Trigger**: Trykker på stoppknapp.
- **Suksess-scenarioer**: Heissystemet avsluttes.

# Tilstand

## Variabler
* Sate: Tilstandsmaskines staus
* Floor: har kontroll på etasjen
* Stop_next: om man stopper på neste stopp
* Open_door: om døren er åpen

## Heisen står i ro på etasje

## Heisen betjener etasje

## Heisen kjører opp

## Heisen kjører ned

# Sekvens

## 

# Klasse

## Queue
```
typedef enum { 
    UP = 1
    DOWN = -1
} Direction;

floor: int
direction: Direction
```

