#include <stdio.h>

#ifndef WIERSZE
#define WIERSZE 8
#endif

#ifndef KOLUMNY
#define KOLUMNY 8
#endif

#ifndef DLUGOSC
#define DLUGOSC 5
#endif

// oblicza maksimum z dwóch liczb
int max(int a, int b);

// oblicza minimum z dwóch liczb
int min(int a, int b);

// wyświetla który gracz powinien wykonać ruch jako następny
void player_move_display(int moves_counter);

// ustawia tablicę do rozgrywki w stanie początkowym
void set_board_to_starting_state(char Board[][KOLUMNY]);

// wyświetla tablicę aktualnego stanu gry
void display_board(char Board[][KOLUMNY]);

// wypisuje nazwy kolumn planszy
void display_columns_names();

// wykonuje ruch gracza umieszczając 1 lub 2 w odpowiedniej komórce tablicy
// następnie przy pomocy funkcji pomocniczych modyfikuje i wyświtelta stan
// gry oraz sprawdza czy ruch doprowawdził do wygranej, któregoś z graczy
int player_move_function(char Board[][KOLUMNY], int player_move,
                         int moves_counter);

// wyświetla aktualny stan gry
int display_game_state(char Board[][KOLUMNY], int moves_counter,
                       int player_move);

// sprawdza czy wykonany przez gracza ruch spowodował wygraną,
// któregoś z graczy przy pomocy funkcji pomocniczych
int check_if_won(char Board[][KOLUMNY], int row_number, int column_number);

// sprawdza czy wykonany przez gracza ruch utworzył palindrom odpowiedniej
// długości w poziomie
int check_if_won_horizontal(char Board[][KOLUMNY], int row_number,
                            int column_number);

// sprawdza czy wykonany przez gracza ruch utworzył palindrom odpowiedniej
// długości w pionie
int check_if_won_vertical(char Board[][KOLUMNY], int row_number,
                          int column_number);

// sprawdza czy wykonany przez gracza ruch utworzył palindrom
// odpowiedniej długości po skosie idąc po planszy do góry i w prawo
int check_if_won_diagonal1(char Board[][KOLUMNY], int row_number,
                           int column_number);

// sprawdza czy wykonany przez gracza ruch utworzył palindrom
// odpowiedniej długości po skosie idąc po planszy do w dół i w prawo
int check_if_won_diagonal2(char Board[][KOLUMNY], int row_number,
                           int column_number);

int main() {

  int moves_counter = 0;              // numer wykonywanego w rozgrywce ruchu
  char Board[WIERSZE][KOLUMNY] = {0}; // inicjalizuje tablicę gry
  set_board_to_starting_state(Board); // ustawia grę w stanie początkowym

  int player_move = 0; // zmienna, służąca za ruch gracza

  do {
    // sprawdza czy gra została wygrna przez któregoś z graczy, oraz wyświtela
    // jej stan
    int result = display_game_state(Board, moves_counter, player_move);
    // jeśli gra nie została wygrana, pobierany jest ruch gracza
    if (result == 0) {
      player_move = getchar();
      getchar();
    }
    moves_counter++;
    if (result) { // jeśli gra została wygrana wypisujemy zwycięzcę
      player_move = '.';
      printf("%d!\n", 1 + (moves_counter % 2));
    }

  } while (player_move != '.'); // powtarzamy czynności aż do zakończenia gry
                                // znakiem "." lub zwycięstwa gracza

  return 0;
}

// wyświetla który gracz powinien wykonać ruch jako następny
void player_move_display(int moves_counter) {

  if (moves_counter % 2 == 1) {

    printf("2:\n");

  } else {

    printf("1:\n");
  }
  return;
}

// ustawia tablicę do rozgrywki w stanie początkowym
void set_board_to_starting_state(char Board[][KOLUMNY]) {

  for (int i = 0; i < WIERSZE; i++) {

    for (int j = 0; j < KOLUMNY; j++) {

      Board[i][j] = '-';
    }
  }

  return;
}

// wyświetla tablicę aktualnego stanu gry
void display_board(char Board[][KOLUMNY]) {

  for (int i = 0; i < WIERSZE; i++) {

    for (int j = 0; j < KOLUMNY; j++) {

      printf(" %c", Board[i][j]);
    }
    printf("\n");
  }
}

// wypisuje nazwy kolumn planszy
void display_columns_names() {

  for (int j = 'a'; j < KOLUMNY + 'a'; j++) {

    printf(" %c", (char)j);
  }
  printf("\n");
}

// wykonuje ruch gracza umieszczając 1 lub 2 w odpowiedniej komórce tablicy
// następnie przy pomocy funkcji pomocniczych modyfikuje i wyświetla stan
// gry oraz sprawdza czy ruch doprowawdził do wygranej, któregoś z graczy
int player_move_function(char Board[][KOLUMNY], int player_move,
                         int moves_counter) {

  int row_number = WIERSZE - 1;
  int column_number = player_move - 'a';

  // szuka pierwszego wolnego pola na ruch gracza w danej kolumnie
  while (row_number > 0 && Board[row_number][column_number] != '-') {

    row_number--;
  }

  char current_player_char = (char)((moves_counter + 1) % 2) + '1';

  // wpisuje bezpiecznie w odpowiendnie miejsce ruch gracza
  if (row_number >= 0 && Board[row_number][column_number] == '-') {
    Board[row_number][column_number] = current_player_char;
  }
  // wyświetla stan gry po modyfikacji
  display_board(Board);
  display_columns_names();

  int won = 0; // zmienna przechowująca informację o wygranej

  // sprawdza czy gra została wygrana
  won = check_if_won(Board, row_number, column_number);
  if (!won)
    player_move_display(moves_counter);

  // zwraca informację o tym czy gra została wygrana
  return won;
}

// wyświetla aktualny stan gry
int display_game_state(char Board[][KOLUMNY], int moves_counter,
                       int player_move) {

  if (moves_counter > 0) {

    return player_move_function(Board, player_move, moves_counter);

  } else {

    display_board(Board);
    display_columns_names();
    player_move_display(moves_counter);
  }

  return 0;
}

// sprawdza czy wykonany przez gracza ruch spowodował wygraną,
// któregoś z graczy przy pomocy funkcji pomocniczych
int check_if_won(char Board[][KOLUMNY], int i, int j) {

  return (check_if_won_diagonal2(Board, i, j) ||
          check_if_won_diagonal1(Board, i, j) ||
          check_if_won_horizontal(Board, i, j) ||
          check_if_won_vertical(Board, i, j));
}

// sprawdza czy wykonany przez gracza ruch utworzył palindrom odpowiedniej
// długości w poziomie
int check_if_won_horizontal(char Board[][KOLUMNY], int row_number,
                            int column_number) {

  int first_column_index = max(0, column_number - DLUGOSC + 1);

  int pallindromic_char_counter = 0; // licznik znaków, które są parami takie
                                     // same, patrząc od końca i początku

  // wyznaczamy bezpiecznie wszystkie możliwe początki palindromu
  for (int start_column_index = first_column_index;
       pallindromic_char_counter < DLUGOSC &&
       start_column_index <= column_number &&
       start_column_index + DLUGOSC - 1 < KOLUMNY;
       start_column_index++) {

    // liczba znaków z których musi składać się palindorm
    int number_of_palindromic_chars = (DLUGOSC + 1) / 2;
    // liczba znaków, które zachowują palindromiczną własność słowa
    pallindromic_char_counter = 0;

    // dla każdego możliwego początku palindromu będziemy sprawdzać ciąg znaków
    // długości DLUGOSC, realizujemy to porównując kolejne znaki od końca i
    // początku możliwego palindromu
    for (int head_column_index = start_column_index,
             tail_column_index = start_column_index + DLUGOSC - 1;
         (number_of_palindromic_chars > 0) && head_column_index < KOLUMNY &&
         tail_column_index < KOLUMNY && pallindromic_char_counter < DLUGOSC;
         head_column_index++, tail_column_index--) {

      if (Board[row_number][head_column_index] !=
              Board[row_number][tail_column_index] ||
          '-' == Board[row_number][head_column_index] ||
          '-' == Board[row_number][tail_column_index]) {

      } else {
        // za każdym razem kiedy znajdujemy takie same znaki zwiększamy ich
        // numer o 2
        pallindromic_char_counter += 2;
      }
      number_of_palindromic_chars--;
    }
  }
  // zwracamy infomację, czy udało się znaleźć odpowiednio długi palindrom
  return (pallindromic_char_counter >= DLUGOSC);
}

// sprawdza czy wykonany przez gracza ruch utworzył palindrom odpowiedniej
// długości w pionie
int check_if_won_vertical(char Board[][KOLUMNY], int row_number,
                          int column_number) {

  int first_row_index = max(0, row_number - DLUGOSC + 1);

  // licznik znaków, które są parami takie same, patrząc od końca i początku
  int pallindromic_char_counter = 0;

  // wyznaczamy bezpiecznie wszystkie możliwe początki palindromu
  for (int start_row_index = first_row_index;
       pallindromic_char_counter < DLUGOSC && start_row_index <= row_number &&
       start_row_index + DLUGOSC - 1 < WIERSZE;
       start_row_index++) {

    // liczba znaków z których musi składać się palindorm
    int number_of_palindromic_chars = (DLUGOSC + 1) / 2;
    // liczba znaków, które zachowują palindromiczną własność słowa
    pallindromic_char_counter = 0;

    // dla każdego możliwego początku palindromu będziemy sprawdzać ciąg znaków
    // długości DLUGOSC, realizujemy to porównując kolejne znaki od końca i
    // początku możliwego palindromu
    for (int head_row_index = start_row_index,
             tail_row_index = start_row_index + DLUGOSC - 1;
         (number_of_palindromic_chars > 0) && head_row_index < WIERSZE &&
         tail_row_index < WIERSZE && pallindromic_char_counter < DLUGOSC;
         head_row_index++, tail_row_index--) {

      if (Board[head_row_index][column_number] !=
              Board[tail_row_index][column_number] ||
          '-' == Board[head_row_index][column_number] ||
          '-' == Board[tail_row_index][column_number]) {

      } else {

        // za każdym razem kiedy znajdujemy takie same znaki zwiększamy ich
        // numer o 2
        pallindromic_char_counter += 2;
      }
      number_of_palindromic_chars--;
    }

  } // zwracamy infomację, czy udało się znaleźć odpowiednio długi palindrom
  return (pallindromic_char_counter >= DLUGOSC);
}

// sprawdza czy wykonany przez gracza ruch utworzył palindrom
// odpowiedniej długości po skosie idąc po planszy do góry i w prawo
int check_if_won_diagonal1(char Board[][KOLUMNY], int row_number,
                           int column_number) {

  // współrzędne początku i końca pierwszego palindormu
  int first_row_index = row_number;
  int first_column_index = column_number;
  int end_index_row = row_number;
  int end_index_column = column_number;

  int dlugosc = 1; // długość aktualnie znaleznionego palindromu

  // znajduje bezpiecznie współrzędne komórki początku pierwszego palindromu
  while ((first_row_index > 0) && (first_column_index > 0) &&
         (dlugosc < DLUGOSC)) {

    first_row_index--;
    first_column_index--;
    dlugosc++;
  }
  dlugosc = 1;
  // znajduje bezpiecznie współrzędne komórki końca pierwszego palindromu
  while ((end_index_row < WIERSZE - 1) && (end_index_column < KOLUMNY - 1) &&
         (dlugosc < DLUGOSC)) {

    end_index_row++;
    end_index_column++;
    dlugosc++;
  }
  // liczba znaków, które zachowują palindromiczną własność słowa
  int pallindromic_char_counter = 0;

  // wyznacza w bezpiczny sposób wszystkie możliwe początki palindromu
  for (int start_row_index = first_row_index,
           start_column_index = first_column_index;
       pallindromic_char_counter < DLUGOSC &&
       start_row_index <= first_row_index &&
       start_column_index <= first_column_index;
       start_row_index++, start_column_index++) {

    // liczba znaków z których musi składać się palindorm
    int number_of_palindromic_chars = (DLUGOSC + 1) / 2;
    pallindromic_char_counter = 0;

    // dla każdego możliwego początku palindromu będziemy sprawdzać ciąg znaków
    // długości DLUGOSC, realizujemy to porównując kolejne znaki od końca i
    // początku możliwego palindromu
    for (int head_row_index = start_row_index,
             head_column_index = start_column_index,
             tail_row_index = start_row_index + DLUGOSC - 1,
             tail_colum_index = start_column_index + DLUGOSC - 1;
         (number_of_palindromic_chars > 0) && head_row_index < WIERSZE &&
         tail_row_index < WIERSZE && tail_colum_index < KOLUMNY &&
         head_column_index < KOLUMNY;
         head_row_index++, head_column_index++, tail_row_index--,
             tail_colum_index--) {

      if (Board[head_row_index][head_column_index] !=
              Board[tail_row_index][tail_colum_index] ||
          (Board[head_row_index][head_column_index] == '-' ||
           '-' == Board[tail_row_index][tail_colum_index])) {

      } else {

        // za każdym razem kiedy znajdujemy takie same znaki zwiększamy ich
        // numer o 2
        pallindromic_char_counter += 2;
      }
      number_of_palindromic_chars--;
    }
  }
  // zwracamy infomację, czy udało się znaleźć odpowiednio długi palindrom
  return (pallindromic_char_counter >= DLUGOSC);
}

// sprawdza czy wykonany przez gracza ruch utworzył palindrom
// odpowiedniej długości po skosie idąc po planszy w dół i w prawo
int check_if_won_diagonal2(char Board[][KOLUMNY], int row_number,
                           int column_number) {

  // współrzędne początku i końca pierwszego palindormu
  int first_row_index = row_number;
  int first_column_index = column_number;
  int end_index_row = row_number;
  int end_index_column = column_number;
  int dlugosc = 1; // długość aktualnie znaleznionego palindromu

  // znajduje bezpiecznie współrzędne komórki początku pierwszego palindromu
  while ((first_row_index < WIERSZE - 1) && (first_column_index > 0) &&
         (dlugosc < DLUGOSC)) {

    first_row_index++;
    first_column_index--;
    dlugosc++;
  }
  dlugosc = 1;
  // znajduje bezpiecznie współrzędne komórki końca pierwszego palindromu
  while ((end_index_row > 0) && (end_index_column < KOLUMNY - 1) &&
         (dlugosc < DLUGOSC)) {

    end_index_row--;
    end_index_column++;
    dlugosc++;
  }
  // liczba znaków, które zachowują palindromiczną własność słowa
  int pallindromic_char_counter = 0;

  // wyznacza w bezpiczny sposób wszystkie możliwe początki palindromu
  for (int start_row_index = first_row_index,
           start_column_index = first_column_index;
       pallindromic_char_counter < DLUGOSC && start_row_index < WIERSZE &&
       start_column_index >= 0 && start_row_index - DLUGOSC + 1 >= 0 &&
       start_column_index + DLUGOSC - 1 < WIERSZE;
       start_row_index++, start_column_index--) {

    // liczba znaków z których musi składać się palindorm
    int number_of_palindromic_chars = (DLUGOSC + 1) / 2;
    pallindromic_char_counter = 0;

    // dla każdego możliwego początku palindromu będziemy sprawdzać ciąg znaków
    // długości DLUGOSC, realizujemy to porównując kolejne znaki od końca i
    // początku możliwego palindromu
    for (int head_row_index = start_row_index,
             head_column_index = start_column_index,
             tail_row_index = start_row_index - DLUGOSC + 1,
             tail_column_index = start_column_index + DLUGOSC - 1;
         (number_of_palindromic_chars > 0) && head_row_index >= 0 &&
         tail_row_index < WIERSZE && tail_column_index >= 0 &&
         tail_column_index < KOLUMNY && head_column_index < KOLUMNY &&
         pallindromic_char_counter < DLUGOSC;
         head_row_index--, head_column_index++, tail_row_index++,
             tail_column_index--) {

      if (Board[head_row_index][head_column_index] !=
              Board[tail_row_index][tail_column_index] ||
          (Board[head_row_index][head_column_index] == '-' ||
           '-' == Board[tail_row_index][tail_column_index])) {

      } else {

        // za każdym razem kiedy znajdujemy takie same znaki zwiększamy ich
        // numer o 2
        pallindromic_char_counter += 2;
      }
      number_of_palindromic_chars--;
    }
  }
  // zwracamy infomację, czy udało się znaleźć odpowiednio długi palindrom
  return (pallindromic_char_counter >= DLUGOSC);
}
// oblicza większą z liczba a, b
int max(int a, int b) {

  if (a > b) {

    return a;

  } else {

    return b;
  }
}

// oblicza mniejszą z liczba a, b
int min(int a, int b) {

  if (a < b) {

    return a;

  } else {

    return b;
  }
}
