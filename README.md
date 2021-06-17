# minishell-shared guida 2021 - versione italiana

### PUSH TOOLS
directory: `program_utils`

To use: mv `program_name` ../

`./42search` `Name`. Example `./42search .DS_Store`
- `Cerca` in tutte le sotto-directory il file indicato

Result: 
```
I finded this files: 
1
./.DS_Store
```

`./42delete` `Name`. Example `./42delete .DS_Store`

Result: 
```
I finded this files: 
1
./.DS_Store

Press Y/y to delete all files: 
```

- `Elimina` in tutte le sotto-directory il file indicato (Chiede conferma) `Y/y or aborting....`

## commands 
- `echo`,  echo emette gli argomenti separati da uno spazio. Restituisce sempre il valore zero.

###### ___flags____`-n`. Sopprime il carattere di newline `\n` finale, in modo che il testo emesso successivamente prosegua di seguito.
- `cd`, cambia la directory corrente. Se non viene specificata la destinazione, si intende la directory contenuta nella variabile HOME.
- `pwd`, emette il percorso della directory attuale.
- `export`, esporta le variabili in modo che siano passate all'ambiente dei processi figli (e questi ultimi possano utilizzarle).
- `unset`, elimina le variabili.
- `env`, mostra le variabili di ambiente con i loro valori.
- `exit`, esce dal minishell.

### Appunti

functions:
```
get_next_line = solita get_next_line applicata come push_swap checker

graphic_hub = funzione che gestisce la grafica del output, completamente personalizzabile -- return int (1)
	- print_logo = stampa il logo di minishell -- return = void
	- print_idle = stampa l'interfaccia della shell -- return void
main.c
	- main = programma principale = chiama delle semplici funzioni -- return int (0) 
	- find_command = legge il comando dato nella shell e lo stampa con \n alla fine 
			se non lo trova richiama error404 -- return int (1)

ft_execute_commands
	- Esegue i comandi trovati e passati :D

find_path: 
	- Trova il path attuale, attraverso la funzione getcwd() PATH_MAX(4096) + 1(.) -- return (char *) 
	  ritorna il path (per semplificare il comando pwd)

change_path:
	- Cambia directory attraverso il comando chdir() in caso di errore stampa "cd: no such file or directory: Users/directory_name\n" 
	  in questo modo la directory di find_path() viene cambiata in automatico :D -- return int (1) (Successo) int(0) (Fallito)

```
variables:
```	
main.c
		- 
```
commands:
```
		- i comandi hanno un id deinito nei define
		- exit esegue l'exit con eventuali free del programma
		- error404 stampa il comando non trovato
```

roba speciale: 
```
	- printf("\e[1;1H\e[2J"); pulisce lo schermo;
	- printf(")
```