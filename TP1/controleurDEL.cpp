#include <avr/io.h> // Il s'agit de la bibliotheque qui permet de faire la lecture et l'ecriture avec le microcontroleur.
#include <util/delay.h> // Cette bilbiotheque nous permet de produire un delais d'une taille definie en ms.

#define VERT 0x01 // PINA = VERT;
#define JAUNE 0x02 // PINA = JAUNE;
#define F_CPU 8000000


// Methode qui permet de changer la couleur de la lumiere
void changementCouleur(uint8_t& couleurCourante){
  if (couleurCourante == VERT){
    couleurCourante = JAUNE;
  } else {
    couleurCourante = VERT;
  }
}

// Methode qui verifie s'il y a eu un changement d'etat
bool verifieSiRelachementInterupteur(bool etatInitial, bool etatFinal){
  if (etatInitial == true && etatFinal == false){
    return true;
  }
  return false;
}

// Methode qui verifie l'etat courant est a On et qu'il ne s'agit pas d'un changement soudain.
bool verifieSiInterupteurUtilise(){
  uint8_t lecteur = 0x00;

  // On fait la première lecture du port D2.
  lecteur = PIND & (1 << PORTD2);

  if (lecteur == (1 << PORTD2)){

    // On fait une deuxie lecture du port D2 apres un delai.
    _delay_ms(10);
    lecteur = PIND & (1 << PORTD2);

    if (lecteur == (1 << PORTD2)){
      return true;
    }
  }
  return false;
}

// main
int main()
{
  DDRA = 0xff; 
  DDRD = 0x00; 

  bool etatInitial = false;
  bool etatFinal = false;
  uint8_t couleurCourante = 0x00;

  for(;;){

    // 1. On verifie que l'interupteur est en cours d'utilisation.
    if (verifieSiInterupteurUtilise()){
      etatFinal = true;
      PINA = couleurCourante;
      
    } else {
      etatFinal = false;
      PINA = 0x00;
    }
    // 2. Lorsque l'interupteur est relache, on change la couleur.
    if(verifieSiRelachementInterupteur(etatInitial, etatFinal)){
      changementCouleur(couleurCourante);
    }

    // 3. Pour la prochaine iteration, l'etat initial devriendra l'etat final.
    etatInitial = etatFinal;
  }

  return 0; 
}