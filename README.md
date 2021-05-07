# minishell-shared guida 2021 - versione italiana

## commands 
- `echo`,  echo emette gli argomenti separati da uno spazio. Restituisce sempre il valore zero.

###### ___flags____`-n`. Sopprime il carattere di newline `\n` finale, in modo che il testo emesso successivamente prosegua di seguito.
- `cd`, cambia la directory corrente. Se non viene specificata la destinazione, si intende la directory contenuta nella variabile HOME.
- `pwd`, emette il percorso della directory attuale.
- `export`, esporta le variabili in modo che siano passate all'ambiente dei processi figli (e questi ultimi possano utilizzarle).
- `unset`, elimina le variabili.
- `env`, mostra le variabili di ambiente con i loro valori.
- `exit`, esce dal minishell.
