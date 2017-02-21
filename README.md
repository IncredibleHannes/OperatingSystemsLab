# BetriebsystemePraktikumAufgabe1
### Team
Johannes Hartmann, Jonas Einig
## Wie verhält sich das Programm bei gleicher Eingabe und Ausgabe Datei?
Es bricht mit Fehler ab!

## Weshalb ist es wichtig die Ausgangsdatei ausschließlich zum lesen und die Zieldatei ausschließlich zum schreiben zu öffnen?
Dies ist wichtig um geordnet linear durch die Dateien zu iterieren. So wird vermieden, dass das Programm aus den Dateien sowohl liest als auch in sie hineinschreibt. Dadurch könnten sich die read/write pointer in den files ungewollt verschieben.
## Warum soll die Zeitmessung im tmp Verzeichnis durchgeführt werden?
Das tmp Verzeichnis wird bei Neustart gelöscht und somit der auch die Testdateien.

## Zeitmessungen:
getestet auf I7 neuerer Generation



| buffersize       | zeit in s     |  
|------------------|---------------|  
| 1                | 42s           |  
| 2                | 21s           |  
| 4                | 11s           |  
| 8                | 6s            |  
| 16               | 3s            |  
| 32               | 1s            |  
| 64               | 0s            |  
| ...              | 0s            |  
| 65536            | 0s            |  
