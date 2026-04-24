#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* *************** Book ************************
 * Book:
 *  A data structure representing a single book
 *  in the library system.
 *
 * Fields:
 *   title   - The title of the book (up to 74 chars)
 *   author  - The author's name (up to 49 chars)
 *   year    - The year of publication (can be negative for BCE)
 *   isbn    - The ISBN string identifier (up to 14 chars)
 *   copies  - How many copies are currently available
 */
typedef struct {
    char title[75];
    char author[50];
    int year;
    char isbn[15];
    int copies;
} Book;

/* *************** Library ************************
 * Library:
 *  A data structure representing a collection of books.
 *
 * Fields:
 *   titles  - Pointer to an array of Book structs
 *   size    - The number of books in the library
 */
typedef struct {
    Book* titles;
    int size;
} Library;

// Static array of books to initialize our library
Book books[] = {
    {"1984", "George Orwell", 1949, "9780451524935", 3},
    {"Animal Farm", "George Orwell", 1945, "9780451526342", 5},
    {"To Kill a Mockingbird", "Harper Lee", 1960, "9780061120084", 2},
    {"Pride and Prejudice", "Jane Austen", 1813, "9780141439518", 4},
    {"The Great Gatsby", "F. Scott Fitzgerald", 1925, "9780743273565", 3},
    {"Moby Dick", "Herman Melville", 1851, "9781503280786", 2},
    {"War and Peace", "Leo Tolstoy", 1869, "9781420954207", 1},
    {"The Catcher in the Rye", "J.D. Salinger", 1951, "9780316769488", 4},
    {"Brave New World", "Aldous Huxley", 1932, "9780060850524", 2},
    {"The Picture of Dorian Gray", "Oscar Wilde", 1890, "9780141439570", 5},
    {"The Hobbit", "J.R.R. Tolkien", 1937, "9780547928227", 6},
    {"Fahrenheit 451", "Ray Bradbury", 1953, "9781451673319", 3},   // <-- was semicolon, fixed to comma
    {"The Odyssey", "Homer", -800, "9780140268867", 1},
    {"Gone with the Wind", "Margaret Mitchell", 1936, "9781451635621", 3},
    {"The Brothers Karamazov", "Fyodor Dostoevsky", 1880, "9780374528379", 2},
    {"Wuthering Heights", "Emily Brontë", 1847, "9781853260018", 4},
    {"Jane Eyre", "Charlotte Brontë", 1847, "9780374531553", 2},
    {"Crime and Punishment", "Fyodor Dostoevsky", 1866, "9780486457888", 1},
    {"The Grapes of Wrath", "John Steinbeck", 1939, "9780143039433", 3},
    {"The Kite Runner", "Khaled Hosseini", 2003, "9781594631930", 2},
    {"The Fault in Our Stars", "John Green", 2012, "9780525478812", 5}
};

// Function prototypes
void displayBooks(Library lib);
void addCopies(Library* lib, char ISBN[], int copies);  // takes pointer so we can modify it
Library findByAuthor(Library lib, char name[]);

/* *************** main ************************
 * main:
 *  Entry point. Builds a Library from the static
 *  books array and tests all three functions.
 */
int main() {
    int size = 21;

    // Build the library from the static array
    Library lib;
    lib.titles = books;
    lib.size = size;

    // Test 1: Display all books
    printf("===== All Books =====\n");
    displayBooks(lib);

    // Test 2: Add copies to Fahrenheit 451 by ISBN
    printf("\n===== Adding 3 copies to Fahrenheit 451 =====\n");
    addCopies(&lib, "9781451673319", 3);
    displayBooks(lib);

    // Test 3: Find all books by George Orwell
    printf("\n===== Books by George Orwell =====\n");
    Library orwell = findByAuthor(lib, "George Orwell");
    displayBooks(orwell);
    free(orwell.titles);  // free the malloc'd memory from findByAuthor

    // Test 4: Find books by an author not in the library
    printf("\n===== Books by Unknown Author =====\n");
    Library unknown = findByAuthor(lib, "Unknown Author");
    if (unknown.size == 0) {
        printf("No books found for that author.\n");
    }
    free(unknown.titles);

    return 0;
}

/* *************** displayBooks ************************
 * displayBooks:
 *  Iterates over every book in the library and prints
 *  its details in a readable format.
 *
 * We assume:
 *   lib.titles is a valid pointer with lib.size entries.
 * We return:
 *   nothing (void).
 * Caller is responsible for:
 *   passing a properly initialized Library struct.
 */
void displayBooks(Library lib) {
    for (int i = 0; i < lib.size; i++) {
        printf("There are %d copies of \"%s\" by %s, published in %d. ISBN: %s.\n",
            lib.titles[i].copies,
            lib.titles[i].title,
            lib.titles[i].author,
            lib.titles[i].year,
            lib.titles[i].isbn);
    }
}

/* *************** addCopies ************************
 * addCopies:
 *  Searches the library for a book matching the given
 *  ISBN and adds the specified number of copies to it.
 *
 * We assume:
 *   lib is a valid pointer to an initialized Library.
 *   ISBN is a null-terminated string.
 *   new_copies is a positive integer.
 * We return:
 *   nothing (void).
 * We guarantee:
 *   If the ISBN is found, copies is increased by new_copies.
 *   If the ISBN is not found, the library is unchanged.
 * Caller is responsible for:
 *   passing a valid Library pointer and a correct ISBN string.
 */
void addCopies(Library* lib, char ISBN[], int new_copies) {
    for (int i = 0; i < lib->size; i++) {
        if (strcmp(ISBN, lib->titles[i].isbn) == 0) {
            lib->titles[i].copies += new_copies;  // <-- was = instead of +=, now correctly adds
            return;  // ISBN is unique, stop once found
        }
    }
    printf("Warning: ISBN %s not found in library.\n", ISBN);
}

/* *************** findByAuthor ************************
 * findByAuthor:
 *  Searches the library for all books written by the
 *  given author and returns them as a new Library.
 *
 * We assume:
 *   lib.titles is a valid pointer with lib.size entries.
 *   name is a null-terminated string.
 * We return:
 *   A new Library containing only books by that author.
 *   The returned Library's titles array is malloc'd.
 * We guarantee:
 *   On return, results.size reflects the number of matches.
 *   If no matches found, results.size == 0.
 * Caller is responsible for:
 *   calling free() on the returned Library's titles pointer.
 */
Library findByAuthor(Library lib, char name[]) {
    Library results;
    results.titles = malloc(lib.size * sizeof(Book));
    int count = 0;

    for (int i = 0; i < lib.size; i++) {
        if (strcmp(name, lib.titles[i].author) == 0) {
            results.titles[count] = lib.titles[i];
            count++;
        }
    }

    results.size = count;
    return results;
}
