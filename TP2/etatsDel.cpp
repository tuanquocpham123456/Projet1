/*
 * Travail : TP2
 * Auteurs : Thierry Beaulieu (2014211) et Tuan Quoc Pham (2012681)
 * Section # : 02
 * Équipe # : 21
 * Description: À l'aide d'une machine à état, ce programme permet de faire varier les couleurs
 * d'une DEL à l'aide de combinaisons spécifiques au moyen d'un bouton-poussoir.
 * 
 * Tableau d'états :
 * 
 *   
  +==============+================+============+=================+
  | État initial | Entrée: Bouton | État final | Sortie: Lumière |
  +==============+================+============+=================+
  | INIT         |              0 | INIT       | Rouge           |
  +--------------+----------------+------------+-----------------+
  | INIT         |              1 | Appuye1    | Ambre           |
  +--------------+----------------+------------+-----------------+
  | Appuye1      |              0 | Relache1   | Vert            |
  +--------------+----------------+------------+-----------------+
  | Appuye1      |              1 | Appuye1    | Ambre           |
  +--------------+----------------+------------+-----------------+
  | Relache1     |              0 | Relache1   | Vert            |
  +--------------+----------------+------------+-----------------+
  | Relache1     |              1 | Appuye2    | Rouge           |
  +--------------+----------------+------------+-----------------+
  | Appuye2      |              0 | Relache2   | Éteint          |
  +--------------+----------------+------------+-----------------+
  | Appuye2      |              1 | Appuye2    | Rouge           |
  +--------------+----------------+------------+-----------------+
  | Relache2     |              0 | Relache2   | Éteint          |
  +--------------+----------------+------------+-----------------+
  | Relache2     |              1 | Appuye3    | Vert            |
  +--------------+----------------+------------+-----------------+
  | Appuye3      |              0 | INIT       | Rouge           |
  +--------------+----------------+------------+-----------------+
  | Appuye3      |              1 | Appuye3    | Vert            |
  +--------------+----------------+------------+-----------------+
 */
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

const uint8_t TOUTE_SORTIE = 0xff;
const uint8_t TOUTE_ENTREE = 0x00;

const uint8_t VERT = 0b01;
const uint8_t ROUGE = 0b10;
const uint8_t ETEINT = 0b0;
const uint8_t D2 = 0b100;

enum Etat
{
  INIT,
  APPUYE1,
  APPUYE2,
  APPUYE3,
  RELACHE1,
  RELACHE2
};

bool debounce()
{
  if (PIND & D2)
  {
    _delay_ms(10);
    return PIND & D2;
  }
  return false;
}

void afficherCouleurAmbre()
{
  PORTA = GREEN;
  _delay_ms(5);
  PORTA = RED;
  _delay_ms(5);
}

// main
int main()
{
  DDRA = TOUTE_SORTIE;
  DDRD = TOUTE_ENTREE;

  Etat etat = INIT;
  PORTA = ROUGE;
  while (true)
  {
    bool estAppuyee = debounce();
    if (estAppuyee)
    {
      switch (etat)
      {
      case INIT:
        etat = APPUYE1;
      case APPUYE1:
        afficherCouleurAmbre();
        break;
      case RELACHE1:
        etat = APPUYE2;
      case APPUYE2:
        PORTA = ROUGE;
        break;
      case RELACHE2:
        etat = APPUYE3;
      case APPUYE3:
        PINA = VERT;
        break;
      }
    }
    else
    {
      switch (etat)
      {
      case INIT:
        PORTA = ROUGE;
        break;
      case APPUYE1:
        etat = RELACHE1;
      case RELACHE1:
        PORTA = VERT;
        break;
      case APPUYE2:
        etat = RELACHE2;
      case RELACHE2:
        PORTA = ETEINT;
        break;
      case APPUYE3:
        etat = INIT;
        PINA = ROUGE;
        break;
      }
    }
  }
}