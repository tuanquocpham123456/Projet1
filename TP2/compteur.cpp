/*
 * Travail : TP2
 * Auteurs : Thierry Beaulieu (2014211) et Tuan Quoc Pham (2012681)
 * Section # : 02
 * Équipe # : 21
 * Description: Ce programme fait en sorte qu'une DEL s'allume en rouge pendant 1 seconde après
 * qu'on ait appuyer et relâcher 5 fois un bouton-poussoir.
 * 
 * Tableau d'états :
 * 
 * 
  +==============+================+==============+=================+
  | État présent | Entrée: Bouton | État suivant | Sortie: Lumière |
  +==============+================+==============+=================+
  | INIT         | 0              | INIT         | Éteint          |
  +--------------+----------------+--------------+-----------------+
  | INIT         | 1              | Appuye1      | Éteint          |
  +--------------+----------------+--------------+-----------------+
  | Appuye1      | 0              | Appuye1      | Éteint          |
  +--------------+----------------+--------------+-----------------+
  | Appuye1      | 1              | Appuye2      | Éteint          |
  +--------------+----------------+--------------+-----------------+
  | Appuye2      | 0              | Appuye2      | Éteint          |
  +--------------+----------------+--------------+-----------------+
  | Appuye2      | 1              | Appuye3      | Éteint          |
  +--------------+----------------+--------------+-----------------+
  | Appuye3      | 0              | Appuye3      | Éteint          |
  +--------------+----------------+--------------+-----------------+
  | Appuye3      | 1              | Appuye4      | Éteint          |
  +--------------+----------------+--------------+-----------------+
  | Appuye4      | 0              | Appuye4      | Éteint          |
  +--------------+----------------+--------------+-----------------+
  | Appuye4      | 1              | Appuye5      | Éteint          |
  +--------------+----------------+--------------+-----------------+
  | Appuye5      | X              | INIT         | Rouge           |
  +--------------+----------------+--------------+-----------------+
 */
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

const uint8_t TOUTE_SORTIE = 0xff;
const uint8_t TOUTE_ENTREE = 0x00;

const uint8_t ROUGE = 0b10;
const uint8_t ETEINT = 0b0;
const uint8_t D2 = 0b100;

enum Etat
{
  INIT,
  APPUYE1,
  APPUYE2,
  APPUYE3,
  APPUYE4,
  APPUYE5
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

// main
int main()
{
  DDRA = TOUTE_SORTIE;
  DDRD = TOUTE_ENTREE;

  Etat etat = INIT;
  while (true)
  {
    bool estAppuyee = debounce();
    if (estAppuyee)
    {
      switch (etat)
      {
      case INIT:
        etat = APPUYE1;
        break;
      case APPUYE1:
        etat = APPUYE2;
        break;
      case APPUYE2:
        etat = APPUYE3;
        break;
      case APPUYE3:
        etat = APPUYE4;
        break;
      case APPUYE4:
        etat = APPUYE5;
      case APPUYE5:
        PINA = ROUGE;
        _delay_ms(1000);
        PINA = ETEINT;
        etat = INIT;
        break;
      }
    }
  }
}