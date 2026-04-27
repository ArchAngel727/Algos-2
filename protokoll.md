# Algos Übung 2 Treecheck

```cpp
struct Node {
  int value = 0;
  Node *left_child = nullptr;
  Node *right_child = nullptr;
};
```

Die Basisstruktur, aus der das Programm einen Baum aufbaut. Speichert einen Integer-Wert sowie zwei Zeiger auf die Kindknoten.

```cpp
void add_value(Node *parent, int val)
```

Fügt val als neuen Knoten in den Teilbaum unter parent ein. Kleinere Werte werden links, größere rechts einsortiert. Ist der Zielplatz bereits besetzt, wird der Algorithmus rekursiv auf dem entsprechenden Kindknoten fortgesetzt, bis ein freier Platz gefunden wird.
Average case: O(log n)
Worst case: O(n)

```cpp
int calculate_height(Node *node)
```

Berechnet rekursiv die Höhe eines Teilbaums ab den gegebenen Knoten.
Average case: O(log n)
Worst case: O(n) - Höhe = n => Linked List

```cpp
int calculate_balance_factor(Node *node)
```

Berechnet rekursiv den Balansfaktor von einem Teilbaum ab den gegebenen Knoten.
Average case: O(log n)
Worst case: O(n)

```cpp
void print_tree(Node *node)
```

Gibt den Baum ab node im Terminal aus.
Average case: O(log n)
Worst case: O(n)

```cpp
Node *find_by_value(Node *node, int val, std::vector<Node *> *path)
```

Sucht nach dem Wert val im Baum. Gibt einen Zeiger auf den Knoten mit diesem Wert zurück, falls er gefunden wurde, andernfalls nullptr.
Average case: O(log n)
Worst case: O(n)

```cpp
void find_subtree(Node *ptr, std::vector<int> &values)
```

Gibt auf der Konsole aus, ob ein Teilbaum im Baum vorhanden ist oder nicht.
Average case: O(m * log n) m = path.size()
Worst case: O(m * n)

```cpp
Node *find_biggest_node(Node *node)
```

Gibt einen pointer zum Knoten mit dem größtem Wert zurück.
Average case: O(log n)
Worst case: O(n)

```cpp
Node *find_smallest_node(Node *node)
```

Gibt einen pointer zum Knoten mit dem kleinsten Wert zurück.
Average case: O(log n)
Worst case: O(n)

```cpp
bool is_tree_avl(Node *node)
```

Eine Funktion die überprüft ob ein Baum ein AVL Baum ist.
Average case: O(n)
Worst case: O(n)

```cpp
void calculate_tree_avg(Node *node, int &sum, int &count)
```

Hilfsfunktion zur Durchschnittsberechnung. Traversiert den Teilbaum ab node rekursiv und aktualisiert die übergebenen Referenzen:

- sum: Summe aller Knotenwerte
- count: Anzahl der besuchten Knoten

Der Durchschnitt ergibt sich nach dem Aufruf aus sum / count.
Average case: O(n)
Worst case: O(n)

```cpp
void free_tree(Node *node)
```

Löscht den Baum

```cpp
std::optional<int> safe_stoi(std::string &str)
```

Konvertiert str sicher in einen Integer. Liefert den Wert bei Erfolg, sonst std::nullopt.

```cpp
std::vector<int> load_file(const char *str)
```

Öffnet die Datei unter dem Pfad str, liest die enthaltenen Ganzzahlen ein und gibt sie als std::vector<int> zurück.
