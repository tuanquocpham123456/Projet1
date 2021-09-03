#include <avr/io.h> // Il s'agit de la bibliotheque qui permet de faire la lecture et l'ecriture avec le microcontroleur.
#define F_CPU 8000000
#include <avr/delay.h> // Cette bilbiotheque nous permet de produire un delais d'une taille definie en ms.

#define VERT 0x01
#define JAUNE 0x02
int main()
{

  DDRA = 0xff; //One PORT A est en mode sortie. En theorie, il ne serait necessaire que d'avoir le port A0 et le port A1 comme etant des ports de sortie.
  // par contre, dans notre situation, on est paresseux donc on fera l'utilisation de 0xff ce qui veut dire que tout les ports A seront des ports de sortie.
  // par contre, si l'on voulait etre riguoureux, il serait possible d'ecrire que l'on voudrait avoir DDRA = 0b00000011.

  DDRD = 0x00; // PORT D est en mode entree. Il s'agit de la meme explication, mais pour l'entree. On a ete paresseux.

  uint8_t valeur = 0x00; 
  uint8_t lecteur = 0x00;

  bool alternator = false;
  bool stateOldMachine = false;
  bool stateMachine = false;

  // (1 << PORTD2) = 00000100

  for(;;) // Deuxième partie où on fait l'utilisation des entrées.
  {
    lecteur = PIND & (1 << PORTD2);

// On vérifie que l'utilisateur est bel et bien en train de faire l'ouverture du bouton.
    if (lecteur == (1 << PORTD2)) {
      _delay_ms(10);
      if (lecteur == (1 << PORTD2)){
        stateMachine = true;
        // Il n'y a eu aucun changement.
        if (stateOldMachine == true){
          if (alternator){
           PINA = VERT;
          } else {
            PINA = JAUNE;
          }
        }
        // Il y a eu un changement.
        else {
          alternator = !alternator;
          if (alternator){
            PINA = VERT;
          } else {
            PINA = JAUNE;
          }
        }
        stateOldMachine = stateMachine;

      } else {
        stateOldMachine = false;
      }
    } else {
      stateOldMachine = false;
    }

  }
  // On vérifie que l'utilisateur a relâché le bouton




  return 0; 
}

