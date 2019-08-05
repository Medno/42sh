# 42sh

Creation of a UNIX shell under POSIX

Final project of the UNIX branch at Ecole 42

Bash referenced. Recode of the built-ins like:

- cd
- echo
- exit
- env
- setenv
- unsetenv

Executions of binaries with their parameters and gestion of the PATH variable, handling redirections, handling logical operators like &&, || and ;

Features:

	-	Advanced line edition

	-	Inhibitors (simple quote, double quote, backslash)

	-	Advanced redirections

	-	Dynamic completion

	-	Local variables with built-ins unset and export

	-	Expansions ($, ~)

	-	Gestion of CDPATH variable
	
## Turn-in: 
```
make
./42sh
```
Enjoy !

----------------------------------------------------------------------------------

Création d'un shell UNIX sous la norme POSIX.

Shell de référence : Bash.

Projet final de la branche UNIX à l'Ecole 42.

Recodage des builtins de shell : cd, echo, exit, env, setenv, unsetenv.

Execution de binaire avec leurs paramètres et gestion du PATH.

Gestion des redirections complètes.

Gestion des operateurs logiques (&& et ||) et séparateurs (;)

Features:

	-	Edition de ligne avancée
	
	-	Inhibiteurs (simple quote, double quote, backslash)
	
	-	Redirections avancées : l'aggrégation des sorties de fichier et le heredoc
	
	-	Completion dynamique
	
	-	Variables locales avec les builtins unset et export
	
	-	Expansions (dollar et tilde)
	
	-	Gestion du CDPATH
	
	
## Installation:
```
make
./42sh
```

# Auteurs
Projet réalisé par : [Hugo Lely](https://github.com/hlely), [Hugo Fouques](https://github.com/fookh), [Kiyan Yazdani](https://github.com/kyazdani42) et [Philippe Chadenier](https://github.com/Medno)
