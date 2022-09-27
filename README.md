# FDF [[Sujet](https://github.com/tvarnier/rubik/blob/master/rubik.pdf)]

<br>

Tout le monde connaît le Rubik’s Cube, et il y a de fortes chances pour que vous vous
soyez déjà un peu esquinté ce qui vous sert de cerveau dessus à un moment dans votre
vie.

Il s’agit en effet d’un simple projet d’algorithmie, faisant un
peu appel à de la représentation dans l’espace, à quelques vagues notions de théorie des
groupes, un peu aussi à votre cerveau, bref, des bricoles.

<br>

<div>
  <img src="https://github.com/tvarnier/rubik/blob/master/img/visualizer.gif" align="middle">
</div>

<br>

## LANCER LE PROJET

<br>

Lancer la commande `make` pour compiler le projet.

Il suffit ensuite de lancer la commande `./rubik [-v] [-s <nbrIterations> ou <rotations>]`
 * `-v` pour lancer le visualisateur
 * De base le programe fait un melange du Rubik de 30 iterations sinon :
   * `-s <nbrIterations>` pour choisir le nombre d'iterations
   * `<rotations>` indiquer une serie de rotations precise, exemple `"R U2 L' B' D2 F"`

<br>

L'algorithme utilisé est grandement inspiré par celui de [Kociemba](http://kociemba.org/cube.htm)

Il permet de resoudre rapidement un cube en 30 rotations ou moins maximum
