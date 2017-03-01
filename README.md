# BetriebssystemePraktikumAufgabe7
### Team
Johannes Hartmann & Jonas Einig


## 7.3

| Iterations   | sequentiel | criticcal | atomic   | reduction|
|--------------|------------|-----------|----------|----------|
| 150 000 000  | 2.562s     | 48.183s   | 28.724s  | 0.785s   |
|--------------|------------|-----------|----------|----------|
|1 500 000 000 | 31.153s    | 7m52.279s | 4m46.460 | 8.593s   |
|--------------|------------|-----------|----------|----------|




### critical
Da die Threads warten müssen, bis der Zugriff auf die Variable erlaubt wird, finden die Berechnungen nicht paralell statt. Dadurch gibt es keinen Vorteil gegenüber der sequentiellen Berechnung. Mit den critical-Anweisungen wird sogar mehr Zeit benötigt, da ein großer Overhead wegen des Schedulen der Threads existiert.

### atomic
Hier tritt das selbe Problem auf wie bei critical. Jedoch bekommt der Compiler bei atomic-Anweisungen mehr Freiheiten und Möglichkeiten zur Optimierung. So werden hier bessere Laufzeiten erreicht.

### reduction
Durch die Reduktion können die Berechnungen echt paralell ausgeführt werden.
Für jedes i wird die Berechnung ausgeführt und das Ergebnis in eine Liste geschrieben. Nach der Berechnung werden einfach die Listenelemente addiert.

## 7.4
Die Programierung einer parallelen Berechnung ist deutlich einfacher als mittels POSIX-Threads.
OpenMP bietet bei komplexen Parallelisierungsproblemem einfache Lösungen. (u.a. Reduction)
