# Practice tasks — strings

> **Compilation:** `gcc -Wall -Wextra -Wpedantic -std=c2x -o prog prog.c`
> **Memory check:** `valgrind --leak-check=full ./prog`

## Extended practice tasks

### String encryption pipeline

**Constraints:** you may not use the indexing operator `[]` or modifiable file-scope (global) variables.

1. Write a `read_line` function that reads a whole line from the user up to the first newline `'\n'` and returns a pointer to it. The backing array must be dynamically allocated and grown as needed; read one character at a time so you can detect the newline.

2. Write a `trim` function that takes a pointer to a dynamically allocated string and reallocates it so that any trailing storage past the `'\0'` is released. It returns a pointer to the trimmed string.

3. Write a `safe_free` function that safely frees a dynamically allocated array: no dangling pointers (the pointer is set to null afterwards) and no attempt to free an empty pointer. It takes a double pointer so it can modify the caller's pointer.

4. Write a `generate_key` function that builds and returns a 26-character encryption key from an input string. The key is formed as follows: take the letters of the input in order, upper-case them, and place them into the key, **skipping any letter already present**; then fill the remaining positions with the remaining letters of the alphabet, in order.

   Example — input `"PointerStoPointerS"`:
   ```
   Alphabet:      A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
   Generated key: P O I N T E R S A B C D F G H J K L M Q U V W X Y Z
   ```

5. Write an `encrypt` function that encrypts a string using the key from task 4. A letter at alphabet index `i` is replaced by the letter at position `i` in the key. Letter case is preserved; non-letter characters are unchanged.

   Example with key `LONGSETCRAKYBDFHIJMPQUVWXZ`:
   ```
   Input:      "Returns the length"
   Encrypted:  "Jspqjdm pcs ysdtpc"
   ```

6. Write a `decrypt` function — the inverse of `encrypt`. Given the encrypted text and the key, each letter is mapped back to the corresponding alphabet letter.

7. Combine everything into one program: read a pass-phrase (`read_line`) and build a key from it; read the text to encrypt (`read_line`); trim both buffers (`trim`); encrypt and print; decrypt and print; free all memory (`safe_free`).

### Sentence splitting and joining

1. Write a `divide` function that splits a string into an array of sentences. Sentences in the input may be separated by `'-'`, `'.'`, or `';'`. It returns a dynamically allocated array of pointers to the individual sentences and reports the number of sentences through an extra pointer parameter. In `main`, pass the input string as a command-line argument (`argv[1]`), build the array, and print all sentences.

2. Write a `cut` function that converts a string to the `camelCase` convention — each word starts with a capital letter and spaces are removed. It modifies the string in place and trims its length with `realloc`.
   ```
   Input:  "was too wet"
   Output: "WasTooWet"
   ```
   In `main`, convert each sentence produced in task 1 and print the result.

3. Write a `join` function that concatenates all sentences from the array of pointers into one new, dynamically allocated string. It takes the array and its length and returns a pointer to the new string. In `main`, build the joined string from the camelCase sentences and print it.

4. Write a program that takes two command-line strings and prints:
   - how many times the second string occurs in the first **as a separate word** (word separators: space, `,`, `.`, `;`, `:`),
   - how many times it occurs **as a substring** (non-overlapping occurrences).

   Use `<string.h>` functions such as `strstr`, `strtok`, `strlen`, and `strcmp`.
   ```
   ./prog "The sun did not shine. It was too wet to play. So we sat in the house, All that cold, cold, wet day." we
   word 'we' occurs: 1
   substring 'we' occurs: 3
   ```

---
---

## New tasks — easy

### P1 — Length without `strlen`
Write a function that returns the length of a string without using any library function. Test on several strings, including the empty string `""`.

### P2 — Swap letter case
Write a function that swaps every lower-case letter to upper case and vice versa, **without using `toupper`/`tolower` or any `<ctype.h>` function**. Non-letter characters are unchanged.
```
Input:  "Hello, World! 123"
Output: "hELLO, wORLD! 123"
```

### P3 — Count vowels with a bit mask
Write a function that counts the vowels (`a, e, i, o, u`, upper and lower case) in a string, using a **bit mask** rather than a chain of `if`/`else` comparisons.
```
"Programming in C" → 5
```

### P4 — Reverse a string in place
Write a function that reverses a string **without allocating any extra memory**.
```
Input:  "abcdef"
Output: "fedcba"
```

### P5 — Copy a string without `strcpy`
Write a function that copies a source string into a destination (including the terminating `'\0'`), without using `strcpy` or any `<string.h>` function. Assume the destination has enough room.

---

## New tasks — medium

### S1 — Remove duplicate letters
Write a function that modifies a string so that each letter (case-insensitively) appears only once — the first occurrence is kept. Non-letter characters stay in place.
```
Input:  "Programming"
Output: "Progamin"
```

### S2 — Count occurrences: word vs substring
Write two functions. The first counts how many times a given string appears in a text **as a separate word** (separators: space, comma, period, semicolon, colon). The second counts how many times it appears **as a substring** (non-overlapping occurrences).
```
text = "we were here, we saw we"
word = "we"

as a word      → 3
as a substring → 4   (3 separate + 1 inside "were")
```

### S3 — ROT-N cipher
Write an encrypting and a decrypting function. Encryption shifts each letter by `n` positions in the alphabet (wrapping around from `'z'` to `'a'`); case is preserved and non-letters are unchanged. Decryption shifts by `-n`.
```
n = 3
Encrypt: "Hello, World!" → "Khoor, Zruog!"
Decrypt: "Khoor, Zruog!" → "Hello, World!"
```

### S4 — Split a string into sentences
Write a function that splits a string into sentences separated by `'.'`, `';'`, or `'-'`. It returns a dynamically allocated array of pointers to the sentences and reports their count through a pointer parameter. The program takes the input from `argv[1]`, prints the numbered sentences, and frees the memory.
```
./prog "Ala ma kota. Kot ma Ale - naprawde; serio"
Sentence 1: Ala ma kota
Sentence 2:  Kot ma Ale
Sentence 3:  naprawde
Sentence 4:  serio
```

---

## New tasks — hard

### T1 — Substitution cipher with a key
Write three functions: key generation, encryption, and decryption.

Key generation builds a 26-character key that is a permutation of the alphabet: first the non-repeating letters of a pass-phrase (upper-cased), then the rest of the alphabet in order.
```
Pass-phrase: "Metody Numeryczne"
Key:          M E T O D Y N U A B C F G H I J K L P Q R S V W X Z
```
Encryption and decryption are substitution-based, preserving letter case; non-letters are unchanged.

**Program:**
- Read the pass-phrase dynamically (character by character, growing the buffer with `realloc`).
- Read the text to encrypt the same way.
- Trim both buffers (`realloc` down to the exact length).
- Generate the key, encrypt and print, decrypt and print.
- Free all memory.

**You may not use the `[]` operator — pointer arithmetic only.**

### T2 — Dynamic sentence array with camelCase
The program takes a string as `argv[1]`. Write three functions:
- one that splits the string into sentences (separators `'.'`, `';'`, `'-'`) and returns a dynamic array of pointers plus the count through a parameter;
- one that converts a sentence to camelCase — each word capitalised, spaces removed, length trimmed with `realloc`;
- one that concatenates the array of sentences into a single new, dynamically allocated string.
```
./prog "metody numeryczne sa fajne. naprawde; nie zartuje"

Sentences:
  metody numeryczne sa fajne
  naprawde
  nie zartuje

camelCase:
  MetodyNumeryczneSaFajne
  Naprawde
  NieZartuje

Joined: MetodyNumeryczneSaFajneNaprawdeNieZartuje
```

### T3 — Safe memory handling
Write four functions forming a small library for working safely with dynamic strings:
- **read line:** allocate a small initial buffer and double it with `realloc` when full; read characters up to `'\n'`.
- **trim:** `realloc` down to the exact length.
- **concatenate:** grow the first string with `realloc` by the length of the second and append it.
- **safe free:** free the memory and set the pointer to null (double-pointer parameter); do nothing for a null pointer.

Test: read two strings, concatenate them with a space in between, print the result and its length, then free the memory.
